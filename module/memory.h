//
// Metamod CS Bot Enabler
// Copyright (C) Vincent Herbet (Arkshine)
//
// This software is licensed under the GNU General Public License, version 2.
// For full license details, see LICENSE file.
//

#ifndef _CSBOT_ENABLER_MEMORY_H_
#define _CSBOT_ENABLER_MEMORY_H_

#include "amxxmodule.h"
#include <amtl/am-platform.h>

#if defined(KE_POSIX)
#  include <stdint.h>
#  include <amtl/am-vector.h>
#  include <sm_symtable.h>
#  include <sys/mman.h>
#  include <unistd.h>
#  include <stdlib.h>
#  include <fcntl.h>
#  include <link.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  define PAGE_SIZE	4096
#  define PAGE_ALIGN_UP(x)	((x + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#  define ALIGN(ar) ((long)ar & ~(PAGE_SIZE-1))
#  define PAGE_EXECUTE_READWRITE	PROT_READ|PROT_WRITE|PROT_EXEC
#  if defined(KE_LINUX)
#    include <malloc.h>
#  endif
#endif

#if defined(KE_MACOSX)
#  include <CoreServices/CoreServices.h>
#endif

#if defined(KE_WINDOWS)
#  include <windows.h>
#endif

#define STATIC_LENGTH(string) (sizeof(string) - sizeof('\0'))

class Memory
{
public:

	explicit Memory(void *containedAddress);
	virtual ~Memory();

public:

	struct DynLibInfo
	{
		void *baseAddress;
		size_t memorySize;
	};

#if defined(KE_POSIX)
	struct LibSymbolTable
	{
		SymbolTable table;
		uintptr_t lib_base;
		uint32_t last_pos;
	};
#endif

	template <typename T>
	bool CompareMemoryWithoutWildCard(const T *startPointer, const T *pattern, const size_t length)
	{
		for (byte index = 0; startPointer[index] == pattern[index]; )
		{
			if (++index == length)
			{
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool CompareMemory(const T *startPointer, const T *pattern, const size_t length, const byte wildCard = '*')
	{
		for (byte index = 0; pattern[index] == wildCard || startPointer[index] == pattern[index]; )
		{
			if (++index == length)
			{
				return true;
			}
		}

		return false;
	}

	bool RedirectFunctionCall(void *callAddress, void *newFunctionAddress, void **originalFunctionAddress = nullptr);
	bool ProtectMemory(void *address, size_t length, int protection);

	void *FindPatternWithoutWildCard(const byte *pattern, const size_t length, const size_t stepSize = sizeof(byte));
	void *FindPattern(const byte *pattern, const size_t length, const size_t stepSize = sizeof(byte), const byte wildCard = '*');

	bool GetLibraryInfo(const void *libPtr, DynLibInfo &lib);

private:

	DynLibInfo m_LibraryInfos;
};

#endif // _CSBOT_ENABLER_MEMORY_H_
