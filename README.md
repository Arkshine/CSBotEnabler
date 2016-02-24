
![image](http://i.imgur.com/xpKqV6U.jpg)
# CS Bot Enabler [![Build Status](https://travis-ci.org/Arkshine/CSBotEnabler.svg?branch=master)](https://travis-ci.org/Arkshine/CSBotEnabler) [![Build status](https://ci.appveyor.com/api/projects/status/nu0u6ofigy48epiq/branch/master?svg=true)](https://ci.appveyor.com/project/Arkshine/csbotenabler/branch/master)

A Metamod module to enable CS Bot in Counter-Strike 1.6.

## Introduction

Originally written by `Whistler` using metamod hooks, modified by `Immortal_BLG` and `Safety1st` to patch memory directly instead.

__What are the difference?__

This version is based on memory patching as well for efficiency and targeting only bot stuff, in addition to:
- Linux support
- Works only on HLDS build >= 5971
- An option to precache radio sounds
- Non-bot stuffs removed
- Some general code cleanup

## Configuration

The only configuration of this module is a cvar which allows to precache radio sounds used by the bots. Located in :page_facing_up:`csbot_enabler/config.ini`:

```
// Precache all bot radio sounds.
// Please note:
//   BotChatter.db must be present.
//   Keep in mind that's about 487 files for ~10 Mo total to download.
//   Files are precached via the generic files buffer.
// -
// Default: "0"
csbot_precache_radio_sounds "0"
```

if you want to know what are the cvars and commands available for CS Bots, type in the server console:

```
cvarlist bot
cmdlist bot
```

## Installation

1. Stop your server & donwload latest version
2. Unzip content to your server in :open_file_folder:`cstrike`
3. Open & add an entry in :page_facing_up:`metamod/plugins.ini`:
    - Windows: `win32 addons/csbot_enabler/csbot_enabler_mm.dll`
    - Linux: `linux addons/csbot_enabler/csbot_enabler_mm_i386.so`
4. Open & configure the cvar in :page_facing_up:`csbot_enabler/config.ini`
5. Start your server and enjoy.
