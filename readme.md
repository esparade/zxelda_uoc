# ZXelda UOC #
<p align="center">
  <img src="https://github.com/esparade/zxelda_uoc/blob/master/art/concepts/readme.png?raw=true" alt="CHALKBOARD SCRAPING SOUNDS"/>
</p>

The original _[The Legend of Zelda](https://en.wikipedia.org/wiki/The_Legend_of_Zelda_(video_game))_ game for the [Famicom Disk System](https://en.wikipedia.org/wiki/Famicom_Disk_System) ported over the [ZX Spectrum (48k)](https://en.wikipedia.org/wiki/ZX_Spectrum), with roguelike elements, as a [UOC](https://en.wikipedia.org/wiki/Open_University_of_Catalonia) CS undergraduate thesis project. First semester of 2026. Made by [esparade](https://github.com/esparade).

## The History so far ##
**IN AN INCREDIBLE FAR OUT GALAXY LOST IN THE MINDBOGGLING SIZE OF THE UNIVERSE, AN ENTITY OF INFINITE EVIL HAVE MANAGED TO SEIZE THE DOMAINS OF A DUNGEON.  
GRAB YOUR SWORD AND SEND IT BACK ONCE AND FOR ALL TO THE HELLISH PLACE WHERE HE NEVER SHOULD HAVE ESCAPED THROUGH A DISGUSTING FORBBIDDEN RITUAL.**

### Instructions ###
In this game, your quest is to find a randomly-generated dungeon entrance in the overworld, while you negotiate with evil monsters lurking around. Inside the dungeon, find you way to the evil boss RADEON, avoiding traps and obstacles. Pick keys to open doors. Pick the power left by RADEON after defeat to re-run the game with harder enemies.

## Play ##
[Grab the **latest version** ROM file.](https://github.com/esparade/zxelda_uoc/releases) Use your emulator / original hardware / modern hardware of choice to play it.  
You can play it online at my [homepage](https://rnd-usr.com/zxelda_uoc).

### Controls ###
**Default keys**  
_up_ - **Q**  
_down_ - **A**  
_left_ - **O**  
_right_ - **P**  
_fire_ - **SPACE**

### Cheat ###
Press `6` while ingame to teleport to the start of the dungeon.

## Stats ##
_LOCs_ - **3831**  
_Converted Sprites_ - **87**  
_Unused Sprites_ - **6**  
_Sound effects_ - **7**  
_Maps_ - **28**

### Memory Map ###

| Segment                    | Start | End  | Size   | Contents                      |
|----------------------------|-------|------|--------|-------------------------------|
| CRT0 startup (z88dk)       |`5E88` |`5EFF`| 120 B  | init, stack, heap, entrypoint |
| Float / stack vars         |`5F00` |`5F5B`| 92 B   | DSTORE, DPUSH, FP_SEED...     |
| I/O & sprite renderers     |`5F5C` |`616D`| 274 B  | CLS, PORT, 6xPUT_SPRITE...    |
| Sound fx                   |`616E` |`69DA`| 2157 B | 7xBEEPER SOUNDS               |
| Overworld maps (15)        |`69DB` |`724A`| 2160 B | 15x144 B                      |
| Dungeon maps (13)          |`724B` |`799A`| 1872 B | 13x144 B                      |
| Logic init / rnd / load    |`799B` |`8D98`| 5118 B | START_KEYS, RAND, LOAD_DATA...|
| Sprites & tiles            |`8D99` |`97D9`| 2625 B | SPRITES & TILES               |
| Render engine              |`97DA` |`A5BA`| 3553 B | RENDER_MAP, HUD, REDEFINE...  |
| HUD / gameover             |`A5BB` |`ACFE`| 1860 B | PTS, LIFE, KEY, GAME OVER     |
| transitions / collisions   |`ACFF` |`B17B`| 1149 B | CHANGE_SCREEN, IS_SOLID, PUSH |
| hero animation / combat    |`B17C` |`B9A1`| 2086 B | ANIMATION HERO, SWORD, DROP   |
| item checks / hitboxes     |`B9A2` |`BE27`| 1158 B | HITBOXES, KEY, DOOR           |
| enemy IA                   |`BE28` |`E035`| 8718 B | SPIKE, HEAVY, OCTO, BOSS, SHOT|
| controls / menu system     |`E036` |`E7B3`| 1918 B | REDEFINE KEYS, SCREEN_CHANGE  |
| _MAIN + rainbow effect     |`E7B4` |`E92D`| 378 B  | MAIN LOOP, COLOR SEQUENCE     |
| state vars (BSS)           |`E92E` |`EA47`| 282 B  | X/Y, LIFES, PTS, ENMY_VARS... |
| Libs z88dk (math & i/o)    |`EA48` |`EBE5`| 413 B  | CLOSEALL, L_MULT, L_EQ...     |
| Total                      |       |      |36183 B |                               |

43Kbs .tap binary, from **0x5E88** to **0xEBE5** when loaded.  
Notice final .tap ROM file is 6912 B bigger, which corresponds with the loading screen graphic.

## Development ##
### Compiling ###
`make.bat` is used to generate the ROM file from source. It expects a [z88dk10](https://github.com/z88dk/z88dk) folder (1.10.1 version) on your `C:/` root directory. Adjust accordingly.

### Tests ###
_Game fully tested on:_  
**[ZXSpectrum +](https://en.wikipedia.org/wiki/ZX_Spectrum#ZX_Spectrum+)** /
**[ZXSpectrum 128k +2](https://en.wikipedia.org/wiki/ZX_Spectrum#ZX_Spectrum_+2)** /
**[ZXSpectrum 128k +2A](https://en.wikipedia.org/wiki/ZX_Spectrum#ZX_Spectrum_+2A,_+2B_and_+3B)** /
**[ESPectrum (ESP32 SoC emulator)](https://github.com/EremusOne/ESPectrum)** /
**[Speccy Emulator](https://fms.komkon.org/Speccy/)** /
**[Fuse Emulator](https://fuse-emulator.sourceforge.net/)** /
**[JSspeccy3](https://github.com/gasman/jsspeccy3)**

### Tools ###
_Tools and pipeline used to create the game with:_  
**[bas2tap](https://github.com/speccyorg/bas2tap)** /
**[beepFX](https://zxaaa.net/view_demo.php?id=11376)** /
**[beepola](https://github.com/atsidaev/beepola)** /
**[SevenuP](https://metalbrain.speccy.org/)** /
**[z88dk](https://github.com/z88dk/z88dk)** /
**[ZX Paintbrush](https://sourcesolutions.itch.io/zx-paintbrush)**

## Disclaimer ##
This port and all his assets made by **JGH** (esparade) as a CS undergraduate thesis project at the [UOC](https://en.wikipedia.org/wiki/Open_University_of_Catalonia) university, videogame department, first semester of 2026, guidance by David Masnou Mayoral.  
Original game idea concept by [Shigeru Miyamoto](https://en.wikipedia.org/wiki/Shigeru_Miyamoto).  
All original property are a registered trademark. **©[Nintendo](https://en.wikipedia.org/wiki/Nintendo)**.  
**Not for sale.**

## Changelog ##
- **v13** - 17 Jun (jury presentation)
  - Implemented pushable block functionality.
  - The pushable block now forces the player to traverse the dungeons around dng_e2 // ID64 in a specific order.
  - Implemented the "spike" enemy: spikes located in the corners of the maps that move towards the player in a straight line if they get close.
- **v12** - 31 May (final thesis deadline)
  - Added the rest of the game maps, 26 in total.
  - Upon killing the boss and collecting the item, the player returns to the start, with stronger enemies.
  - The hero now starts the game facing down, centered on the screen.
  - Changed the layout of map dngn_e2 // ID64 and the layout of the surrounding dungeons to implement the pushable block mechanic in the next version.
  - Added all comments to the code.
  - Tons of fixes.
- **v11** - 26 May
  - The menu now features colored text.
  - Enemies now award points.
  - After dying, the game now automatically returns to the menu after 3 seconds.
  - Every HUD element now has its own graphic.
  - Several fixes.
- **v10** - 22 May
  - Fully implemented the "octo" enemy, including its projectile attack.
  - There are now two enemies on every screen except for the starting one.
  - Fixed the position of the dungeon entrance; it is now always in the center of the map.
  - Enemies now respect collisions with walls and other elements.
  - The boss now shoots just like the octos.
  - Several fixes.
- **v9** - 10 May
  - Implemented key remapping functionality.
  - Redrew the initial screen.
  - Implemented the final boss with its 4 surrounding fires, alternating between X and cross positions.
  - Several fixes.
- **v8** - 28 Apr
  - Implemented the title screen.
  - Implemented the shop screen.
  - Implemented the game over screen.
  - Implemented the locked door and key mechanic in the dungeon.
  - Implemented the next dungeon room to demonstrate the key/door element functionality.
  - The HUD now displays all possible adventure items.
  - Dungeons are now decorated with fires.
  - The player now has 3 "hits" (health points).
  - Several fixes.
- **v7** - 20 Apr
  - Implemented the loading screen.
  - The dungeon's "heavy" enemy now drops keys.
  - Several fixes.
- **v6** - 13 Apr
  - Created the complete font family for use in the game.
  - Implemented the "heavy" enemy, which chases the player.
  - The counter now also displays the player's number of keys.
  - Enemies can now drop health.
  - Fixed the random dungeon entrance; the shop is now static and the dungeon is random.
  - Blocks in the dungeon are now impassable.
  - The octo no longer chases the player; it now has a different behavior.
- **v5** - 7 Apr
  - Implemented random dungeon entrance functionality, though it currently affects the shop.
  - Added a sword attack sound effect.
  - The hero is now drawn using an XOR mask to remove the background color around the sprite, making it green and transparent.
  - Incorporated status information into the HUD.
- **v4** - 3 Apr
  - Implemented random dungeon entrance functionality, though it currently affects the shop.
- **v3** - 30 Mar
  - Created the dungeon entrance graphic.
  - Fixed the entry and exit points for each dungeon.
  - Fixed the hero's sprites, which previously moved without pressing any keys.
  - Implemented an enemy that chases the player and kills them upon contact.
  - Implemented the sword attack.
- **v2** - 21 Mar
  - Recreated more sprites from the original game.
  - Created a dungeon map.
- **v1** - 17 Mar
  - Implemented basic screen-switching mechanics.
  - Implemented the state system between menu >> game >> menu (0 and 1 keys).
  - Created the first sprites, including the hero.
- **v0** - 28 Feb
  - Tutorial example, unchanged.
