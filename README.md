
![image](http://i.imgur.com/xpKqV6U.jpg)
# CS Bot Enabler [![GitHub version](https://badge.fury.io/gh/Arkshine%2FCSBotEnabler.svg)](https://badge.fury.io/gh/Arkshine%2FCSBotEnabler) [![Build Status](https://travis-ci.org/Arkshine/CSBotEnabler.svg?branch=master)](https://travis-ci.org/Arkshine/CSBotEnabler) [![Build status](https://ci.appveyor.com/api/projects/status/nu0u6ofigy48epiq/branch/master?svg=true)](https://ci.appveyor.com/project/Arkshine/csbotenabler/branch/master)

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
:bulb: _All the resources are included in the release package._

if you want to know what are the cvars and commands available for CS Bots, type in the server console:

```
cvarlist bot
cmdlist bot
```

## Installation

You can download package containing everything in the [Releases section](https://github.com/Arkshine/CSBotEnabler/releases/latest).

### Package structure

```

├─ addons
│   └─ csbot_enabler
│       ├─ config.cfg
│       ├─ csbot_enabler_mm.dll
│       └─ csbot_enabler_mm_i386.so
├─ sound
│   └─ radio
│       └─ bot
│           ├─ a.wav
│           ├─ a_bunch_of_them.wav
│           └─ ...
├─ BotChatter.db
└─ BotProfile.db
```

### Steps

1. Stop your server <sup id="a1">[1](#f1)</sup> and donwload latest version
2. Unzip content to your server in :open_file_folder:`cstrike`
3. Open & add an entry in :page_facing_up:`metamod/plugins.ini`:
    <table>
        <tr>
            <td>Windows</td>
            <td>`win32 addons/csbot_enabler/csbot_enabler_mm.dll`</td>
        </tr>
        <tr>
            <td>Linux</td>
            <td>`linux addons/csbot_enabler/csbot_enabler_mm_i386.so`</td>
        </tr>
    </table>
4. Open & configure the cvar in :page_facing_up:`csbot_enabler/config.ini`
5. Start your server and enjoy.

__

<sup id="f1">__1__</sup> _Whatever it's your first install or just updating_ [↩](#a1)
[1]: http://google.com/        "Google"

### Troubleshooting

To check if plugin is properly loaded, type in the server console: `meta list`.
You see something like:
```
meta list
Currently loaded plugins:
      description      stat pend  file              vers      src  load unlod
 [ 1] CS Bot Enabler   RUN   -    csbot_enabler_mm  v1.0.0    ini  ANY   ANY
```
Check the server log as well:
```
CS Bot Enabler v1.0.0
Status: Loaded.
```
- If you see nothing, this means `plugins.ini` of metamod has not been modified. See step 3 above.
- If you see `badf load`, make sure you did not do  a typo in `plugins.ini` of metamod. If not, then report the issue.
- If you see `RUN` but bots are not available, check the server log. It should give some message errors. This means likely memory path has failed. Keep in mind that it works only on HLDS build >= 5971. Report the issue if you have the right version.
