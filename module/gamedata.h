//
// Metamod CS Bot Enabler
// Copyright (C) Vincent Herbet (Arkshine)
//
// This software is licensed under the GNU General Public License,version 2.
// For full license details,see LICENSE file.
//

#ifndef _CSBOT_ENABLER_GAMEDATA_H_
#define _CSBOT_ENABLER_GAMEDATA_H_

#include <const.h>

#if defined(KE_WINDOWS)

	#define SIGNATURE_BASE   0xE8, '*', '*', '*', '*'
	#define SIGNATURE_BASE2  SIGNATURE_BASE, 0x83, 0xC4, 0x04, 0x84, 0xC0, '*', '*', '*', '*', '*', '*'

	const byte SIGNATURE_PHRASE_MANAGER   [] = { SIGNATURE_BASE2, '*', '*', 0xE8, '*', '*', '*', '*', 0x83 };
	const byte SIGNATURE_PROFILE_MANAGER  [] = { SIGNATURE_BASE2, 0x57, 0x68, '*', '*', '*', '*', 0xE8, '*', '*', '*', '*', 0xE9 };
	const byte SIGNATURE_REGISTER_CVARS   [] = { SIGNATURE_BASE2, 0x68, '*', '*', '*', '*', 0xFF, '*', '*', '*', '*', '*', 0x68, '*', '*', '*', '*', 0xFF };
	const byte SIGNATURE_REGISTER_COMMANDS[] = { SIGNATURE_BASE2, 0x8B, '*', 0x8B, '*', 0x68, '*', '*', '*', '*', 0xFF, '*', '*', 0x8B, '*', 0x8B, '*', 0x68 };
	const byte SIGNATURE_EXECUTE_COMMANDS [] = { SIGNATURE_BASE2, 0x56, 0x8B, '*', '*', 0xB9, '*', '*', '*', '*', 0x8B, '*', 0x0F };
	const byte SIGNATURE_VALIDATE_MAP_DATA[] = { SIGNATURE_BASE2, 0xC6, '*', '*', '*', '*', '*', '*', 0xE8, '*', '*', '*', '*', 0x85, '*', 0x74, '*', 0x68 };
	const byte SIGNATURE_PROCESS_ADD_BOT  [] = { SIGNATURE_BASE2, '*', '*', 0x83, '*', '*', 0x75, '*', 0x8B, '*', '*', '*', '*', '*', 0x68, '*', '*', '*', '*', 0xFF };
	const byte SIGNATURE_CLIENT_PRINT     [] = { SIGNATURE_BASE, 0x83, '*', '*', 0x80, '*', '*', '*', 0x74, '*', 0x8B, '*', '*', 0xFF, '*', '*', '*', '*', '*', 0x6A, '*', 0x6A, '*', 0x6A, '*', 0xFF, '*', '*', '*', '*', '*', 0x6A, '*', 0xFF };

	const char SIGNATURE_HOSTAGE_IDLETHINK[] = "?IdleThink@CHostage@@QAEXXZ";
	int SIGNATURE_HOSTAGE_IDLETHINK_OFFSET   = 55;
	const byte HOSTAGE_IDLETHINK_REPLACE  [] = { 0x90, 0x90 };

#elif defined(KE_POSIX)

	#define SIGNATURE_BASE  0xE8, '*', '*', '*', '*'
	#define SIGNATURE_BASE2 SIGNATURE_BASE, 0x83, 0xC4, 0x10, 0x84, 0xC0, '*', '*', '*', '*', '*', '*'

	const byte SIGNATURE_PHRASE_MANAGER   [] = { SIGNATURE_BASE2, 0x83, '*', '*', 0xFF, '*', '*', '*', '*', '*', 0x68, '*', '*', '*', '*', 0xE8, '*', '*', '*', '*', 0x83, '*', '*', 0x31, '*', 0xE9 };
	const byte SIGNATURE_PROFILE_MANAGER  [] = { SIGNATURE_BASE, 0x84, '*', 0x0F, '*', '*', '*', '*', '*', 0x8B, '*', '*', '*', 0xC7, '*', '*', '*', '*', '*', '*', 0x89, '*', '*', '*', 0xE8, '*', '*', '*', '*', 0xE9 };
	const byte SIGNATURE_REGISTER_CVARS   [] = { SIGNATURE_BASE2, 0x83, '*', '*', 0x68, '*', '*', '*', '*', 0xFF, '*', '*', '*', '*', '*', 0xC7, '*', '*', '*', '*', '*', '*', 0xFF };
	const byte SIGNATURE_REGISTER_COMMANDS[] = { SIGNATURE_BASE2, '*', 0x68, '*', '*', '*', '*', 0x53, 0xFF, '*', '*', 0x58, 0x8B, '*', 0x5A, 0x68, '*', '*', '*', '*', 0x53, 0xFF, '*', '*', 0x59, 0x58, 0x8B };
	const byte SIGNATURE_EXECUTE_COMMANDS [] = { SIGNATURE_BASE2, '*', '*', 0xBF, '*', '*', '*', '*', 0xB9, '*', '*', '*', '*', 0xF3, '*', 0x0F, '*', '*', '*', '*', '*', 0x8B, '*', '*', '*', '*', '*', 0xBF };
	const byte SIGNATURE_VALIDATE_MAP_DATA[] = { SIGNATURE_BASE2, '*', '*', '*', 0xE8, '*', '*', '*', '*', 0x85, '*', 0x0F, '*', '*', '*', '*', '*', 0x83, '*', '*', 0x68, '*', '*', '*', '*', 0xE8, '*', '*', '*', '*', 0xA1 };
	const byte SIGNATURE_PROCESS_ADD_BOT  [] = { SIGNATURE_BASE2, 0x83, '*', '*', 0x89, '*', 0x8B, '*', '*', '*', '*', '*', 0x0F, '*', '*', '*', '*', '*', 0x85, '*', 0x0F, '*', '*', '*', '*', '*', 0x83, '*', '*', 0x0F };
	const byte SIGNATURE_CLIENT_PRINT     [] = { SIGNATURE_BASE, 0x80, '*', '*', '*', '*', 0x0F, '*', '*', '*', '*', '*', 0x8B, '*', '*', 0x31, '*', 0xBB, '*', '*', '*', '*', 0x8B, '*', '*', '*', '*', '*', 0x89, '*', '*', '*', 0x89 };
	
	const char SIGNATURE_HOSTAGE_IDLETHINK[] = "_ZN8CHostage9IdleThinkEv";
	int SIGNATURE_HOSTAGE_IDLETHINK_OFFSET   = 20;
	const byte HOSTAGE_IDLETHINK_REPLACE  [] = { 0x90, 0xE9 };

#endif

extern void PrecacheRadioSounds();

#endif // _CSBOT_ENABLER_GAMEDATA_H_
