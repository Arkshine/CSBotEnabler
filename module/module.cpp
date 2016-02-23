//
// Metamod CS Bot Enabler
// Copyright (C) Vincent Herbet (Arkshine)
//
// This software is licensed under the GNU General Public License, version 2.
// For full license details, see LICENSE file.
//

#include "module.h"
#include "memory.h"
#include "gamedata.h"
#include <amtl/am-utility.h>

cvar_t CvarInitPrecacheRadioSounds = { "csbot_precache_radio_sounds", "0", FCVAR_SERVER };
cvar_t *CvarPrecacheRadioSounds;

bool ModuleLoaded;

static bool EnableBotPhraseManagerInitializeFailMessage()
{
	return CvarPrecacheRadioSounds->value != 0;
}

static bool EnableBotProfileManagerInitialize()
{
	return true;
}

static bool EnableBotConsoleVariableRegister()
{
	return true;
}

static bool EnableBotConsoleCommandRegister()
{
	return true;
}

static bool EnableBotConsoleExecuteComamnds()
{
	return true;
}

static bool EnableValidateMapData()
{
	return true;
}

static bool EnableProcessAddBot()
{
	return true;
}

typedef void(*pfnClientPrint) (entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4);
static pfnClientPrint ClientPrintOriginalAddress(nullptr);
static void ClientPrintCustom(entvars_t *client, int msg_dest, const char *msg_name, const char *param1, const char *param2, const char *param3, const char *param4)
{
	if (param1[STATIC_LENGTH("#Game_radio")] == '_')
	{
		param1 = "#Game_radio";
		param3 = param4;
		param4 = nullptr;
	}

	(*ClientPrintOriginalAddress)(client, msg_dest, msg_name, param1, param2, param3, param4);
}

bool EnableCsBot()
{
	auto addressContainedInMod = reinterpret_cast<void*>(MDLL_Spawn);

	ke::AutoPtr<Memory> memUtils(new Memory(addressContainedInMod));

	struct sigData
	{
		const byte*   pattern;
		const size_t  pattern_length;
		const char*   pattern_info;
		void*         address;
		void*         address_original;
	};

	#define SIGNATURE(name, address)  SIGNATURE_##name, ARRAY_LENGTH(SIGNATURE_##name), #name, reinterpret_cast<void*>(address)

	sigData signatures[] =
	{
		{ SIGNATURE(PHRASE_MANAGER    , EnableBotPhraseManagerInitializeFailMessage) },
		{ SIGNATURE(PROFILE_MANAGER   , EnableBotProfileManagerInitialize) },
		{ SIGNATURE(REGISTER_CVARS    , EnableBotConsoleVariableRegister) },
		{ SIGNATURE(REGISTER_COMMANDS , EnableBotConsoleCommandRegister) },
		{ SIGNATURE(EXECUTE_COMMANDS  , EnableBotConsoleExecuteComamnds) },
		{ SIGNATURE(VALIDATE_MAP_DATA , EnableValidateMapData) },
		{ SIGNATURE(PROCESS_ADD_BOT   , EnableProcessAddBot) },
		{ SIGNATURE(CLIENT_PRINT      , ClientPrintCustom) },
	};

	for (size_t i = 0; i < ARRAY_LENGTH(signatures); ++i)
	{
		auto signature = signatures[i];
		auto address = memUtils->FindPattern(signature.pattern, signature.pattern_length);

		if (!address || !memUtils->RedirectFunctionCall(static_cast<byte*>(address) + 1, reinterpret_cast<void*>(signature.address), &signature.address_original))
		{
			LOG_CONSOLE(PLID, "   Error: Could not patch \"%s\"", MODULE_NAME, signature.pattern_info);
		}

		if (!strcmp(signature.pattern_info, "CLIENT_PRINT"))
		{
			ClientPrintOriginalAddress = reinterpret_cast<pfnClientPrint>(signature.address_original);
		}
	}

	return true;
}

void OnMetaAttach()
{
	LOG_CONSOLE(PLID, "   %s v%s", MODULE_NAME, MODULE_VERSION);

	if (strcmp(GET_GAME_INFO(PLID, GINFO_NAME), "cstrike"))
	{
		LOG_CONSOLE(PLID, "   Status: Failed. This module is only for Counter-Strike 1.6");
		return;
	}

	CVAR_REGISTER(&CvarInitPrecacheRadioSounds);
	CvarPrecacheRadioSounds = CVAR_GET_POINTER(CvarInitPrecacheRadioSounds.name);

	ModuleLoaded = EnableCsBot();

	LOG_CONSOLE(PLID, "   Status: %s.\n", ModuleLoaded ? "Loaded" : "Failed");

}

void OnServerActivate(edict_t *pEdictList, int edictCount, int clientMax)
{
	if (ModuleLoaded)
	{
		SERVER_COMMAND("exec cstrike/addons/csbot_enabler/config.cfg\n");
		SERVER_EXECUTE();

		if (CvarPrecacheRadioSounds->value != 0.0f)
		{
			PrecacheRadioSounds();
		}
	}
}