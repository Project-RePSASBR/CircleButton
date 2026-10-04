# CircleButton

```
Sly, to hook onto this function, all you've gotta do is jump and hit the circle button.
```

CircleButton is a custom SPRX module for use with the retail PlayStation 3 version of PlayStation All-Stars Battle Royale. CircleButton
implements a function hooking framework that allows for dynamically injecting custom payloads into the game's EBOOT at runtime. These custom 
payloads can be used to read arbitrary memory, perform memory modifications, and implement other mods not typically possible by just patching
the game's filesystem.

## Current Features
1. Hooks for enabling LAN mode, allowing for online play on RPCS3 / Jailbroken PS3 with All-Stars Matchmaker

# Build Prerequisites
- Visual Studio 2013+
- Sony PS3 4.75+ SDK w/ Visual Studio Integration
- [Fixed std::string library](https://github.com/skiff/libpsutil/releases "Fixed std::string library")

# Installation
The easiest and most recommended way of installing or configuring CircleButton is via [AxeHax](https://github.com/Project-RePSASBR/AxeHax). 
The following instructions are intended for advanced users only.

Note that AxeHax can still be used to install CircleButton with your own build. Just put your `CircleButton.sprx` file next to the
AxeHax executable and AxeHax should say 'Found custom CircleButton.sprx next to exe, uploading that instead' when (re)patching.

The game's EBOOT needs to be patched to allow it to load the SPRX.
[SPRXPatcher](https://github.com/NotNite/SPRXPatcher) is a tool that enables this quite well.

Once you've patched your EBOOT, all you need to do is put the SPRX file in the same place you specified when running SPRXPatcher.
Generally, this location should be `/dev_hdd0/plugins/CircleButton.sprx` but you can put it elsewhere if desired.
