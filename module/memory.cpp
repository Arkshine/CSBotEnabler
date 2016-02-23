//
// Metamod CS Bot Enabler
// Copyright (C) Vincent Herbet (Arkshine)
//
// This software is licensed under the GNU General Public License, version 2.
// For full license details, see LICENSE file.
//

#include "memory.h"

Memory::Memory(void *containedAddress)
{
	GetLibraryInfo(containedAddress, m_LibraryInfos);
}

Memory::~Memory()
{
}

bool Memory::RedirectFunctionCall(void *callAddress, void *newFunctionAddress, void **originalFunctionAddress)
{
	if (!ProtectMemory(callAddress, sizeof(void*), PAGE_EXECUTE_READWRITE))
	{
		return false;
	}

	if (originalFunctionAddress)
	{
		*originalFunctionAddress = reinterpret_cast<void*>(static_cast<uint32*>(callAddress)[0] + reinterpret_cast<uint32>(callAddress) + sizeof(void*));
	}

	reinterpret_cast<uint32*>(callAddress)[0] = reinterpret_cast<uint32>(newFunctionAddress) - reinterpret_cast<uint32>(callAddress) - sizeof(void*);

	return true;
}


bool Memory::ProtectMemory(void *address, size_t length, int protection)
{
#if defined(KE_POSIX)

	return mprotect(reinterpret_cast<void*>(ALIGN(address)), sysconf(_SC_PAGESIZE), protection) != -1;

#elif defined(KE_WINDOWS)

	DWORD old_prot;
	return VirtualProtect(address, length, protection, &old_prot) != FALSE;

#endif
}

void* Memory::FindPatternWithoutWildCard(const byte *pattern, const size_t length, const size_t stepSize)
{
	auto startPointer = m_LibraryInfos.baseAddress;
	auto endPointer = static_cast<byte*> (startPointer) + m_LibraryInfos.memorySize;

	do
	{
		if (CompareMemoryWithoutWildCard(static_cast<byte *>(startPointer), pattern, length))
		{
			return startPointer;
		}
	}
	while ((reinterpret_cast<byte*&>(startPointer) += stepSize) + length <= endPointer);

	return nullptr;
}

void* Memory::FindPattern(const byte *pattern, const size_t length, const size_t stepSize, const byte wildCard)
{
	auto startPointer = m_LibraryInfos.baseAddress;
	auto endPointer = static_cast<byte*> (startPointer) + m_LibraryInfos.memorySize;

	do
	{
		if (CompareMemory(static_cast <byte *>(startPointer), pattern, length, wildCard))
		{
			return startPointer;
		}
	}
	while ((reinterpret_cast<byte*&>(startPointer) += stepSize) + length <= endPointer);

	return nullptr;
}

bool Memory::GetLibraryInfo(const void *libPtr, DynLibInfo &lib)
{
	uintptr_t baseAddr;

	if (!libPtr)
	{
		return false;
	}

#if defined(KE_WINDOWS)

	MEMORY_BASIC_INFORMATION info;

	if (!VirtualQuery(libPtr, &info, sizeof(MEMORY_BASIC_INFORMATION)))
	{
		return false;
	}

	baseAddr = reinterpret_cast<uintptr_t>(info.AllocationBase);

	auto dos = reinterpret_cast<IMAGE_DOS_HEADER *>(baseAddr);
	auto pe  = reinterpret_cast<IMAGE_NT_HEADERS *>(baseAddr + dos->e_lfanew);

	lib.memorySize = pe->OptionalHeader.SizeOfImage;

#elif defined(KE_LINUX)

	Dl_info info;

	if (!dladdr(libPtr, &info) || !info.dli_fbase || !info.dli_fname)
	{
		return false;
	}

	baseAddr = reinterpret_cast<uintptr_t>(info.dli_fbase);
	auto file = reinterpret_cast<Elf32_Ehdr *>(baseAddr);

	if (memcmp(ELFMAG, file->e_ident, SELFMAG) != 0 || file->e_ident[EI_VERSION] != EV_CURRENT)
	{
		return false;
	}
	if (file->e_ident[EI_CLASS] != ELFCLASS32 || file->e_machine != EM_386 || file->e_ident[EI_DATA] != ELFDATA2LSB || file->e_type != ET_DYN)
	{
		return false;
	}

	uint16_t phdrCount = file->e_phnum;
	auto phdr = reinterpret_cast<Elf32_Phdr *>(baseAddr + file->e_phoff);

	for (uint16_t i = 0; i < phdrCount; i++)
	{
		Elf32_Phdr &hdr = phdr[i];

		if (hdr.p_type == PT_LOAD && hdr.p_flags == (PF_X | PF_R))
		{
			lib.memorySize = PAGE_ALIGN_UP(hdr.p_filesz);
			break;
		}
	}

#elif defined(KE_MACOSX)

	Dl_info info;

	if (!dladdr(libPtr, &info) || !info.dli_fbase || !info.dli_fname)
	{
		return false;
	}

	baseAddr = (uintptr_t)info.dli_fbase;
	auto file = reinterpret_cast<struct mach_header *>(baseAddr);

	if (file->magic != MH_MAGIC || file->cputype != CPU_TYPE_I386 || file->cpusubtype != CPU_SUBTYPE_I386_ALL || file->filetype != MH_DYLIB)
	{
		return false;
	}

	uint32_t cmd_count = file->ncmds;
	auto seg = reinterpret_cast<struct segment_command *>(baseAddr + sizeof(struct mach_header));

	for (uint32_t i = 0; i < cmd_count; i++)
	{
		if (seg->cmd == LC_SEGMENT)
		{
			lib.memorySize += seg->vmsize;
		}

		seg = (struct segment_command *)((uintptr_t)seg + seg->cmdsize);
	}

#endif

	lib.baseAddress = reinterpret_cast<void *>(baseAddr);

	return true;
}
