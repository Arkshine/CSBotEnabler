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

	#define SIGNATURE_BASE   0xE8,'*','*','*','*'
	#define SIGNATURE_BASE2  SIGNATURE_BASE,0x83,0xC4,0x04,0x84,0xC0,0x0F,0x84,'*','*','*','*'

	const byte SIGNATURE_PHRASE_MANAGER   [] = { SIGNATURE_BASE2,0x56,0x68,'*','*','*','*',0xE8,'*','*','*','*',0x83,'*','*',0x32 };
	const byte SIGNATURE_PROFILE_MANAGER  [] = { SIGNATURE_BASE2,0x56,0x68,'*','*','*','*',0xE8,'*','*','*','*',0x83,'*','*',0x5F };
	const byte SIGNATURE_REGISTER_CVARS   [] = { SIGNATURE_BASE2,0x68,'*','*','*','*',0xFF };
	const byte SIGNATURE_REGISTER_COMMANDS[] = { SIGNATURE_BASE2,0x8B,'*',0x68 };
	const byte SIGNATURE_EXECUTE_COMMANDS [] = { SIGNATURE_BASE2,0x8B,'*','*','*','*','*','*',0xBF,'*','*','*','*',0x8B };
	const byte SIGNATURE_VALIDATE_MAP_DATA[] = { SIGNATURE_BASE2,0xC6,'*','*','*','*','*','*',0xE8,'*','*','*','*',0x85 };
	const byte SIGNATURE_PROCESS_ADD_BOT  [] = { SIGNATURE_BASE2,0x8B,'*','*','*',0x8B };
	const byte SIGNATURE_CLIENT_PRINT     [] = { SIGNATURE_BASE ,0x83,'*','*',0x8A,'*','*','*',0x84,'*',0x74,'*',0x8B,'*','*',0x8B };

#elif defined(KE_POSIX)

	#define SIGNATURE_BASE  0xE8,'*','*','*','*'
	#define SIGNATURE_BASE2 SIGNATURE_BASE,0x84,'*',0x0F,0x84,'*','*','*','*'

	const byte SIGNATURE_PHRASE_MANAGER   [] = { SIGNATURE_BASE ,0x88,'*',0x31,'*',0x84,'*',0x0F };
	const byte SIGNATURE_PROFILE_MANAGER  [] = { SIGNATURE_BASE2,0x8B,'*','*','*','*','*','*',0xC7 };
	const byte SIGNATURE_REGISTER_CVARS   [] = { SIGNATURE_BASE2,0xC7,'*','*','*','*','*','*',0xFF };
	const byte SIGNATURE_REGISTER_COMMANDS[] = { SIGNATURE_BASE ,0x84,'*',0x74,'*',0x8B,'*',0xBA };
	const byte SIGNATURE_EXECUTE_COMMANDS [] = { SIGNATURE_BASE ,0x84,'*',0x74,'*',0xBF,'*','*','*','*',0xB9 };
	const byte SIGNATURE_VALIDATE_MAP_DATA[] = { SIGNATURE_BASE ,0x84,'*',0x74,'*',0xC6 };
	const byte SIGNATURE_PROCESS_ADD_BOT  [] = { SIGNATURE_BASE2,0x83,'*','*',0x8B,'*','*','*','*','*',0x0F };
	const byte SIGNATURE_CLIENT_PRINT     [] = { SIGNATURE_BASE ,0x84,'*',0x0F,'*','*','*','*','*',0x8B,'*','*',0x8B,'*','*','*','*','*',0xC7 };

#endif

extern void PrecacheRadioSounds();

#endif // _CSBOT_ENABLER_GAMEDATA_H_
