BeepFX by Shiru


BeepFX is a Windows tool that could be used to create beeper sound 
effects for ZX Spectrum 48K games. 

The effects are defined by a small set of parameters, and stored in a 
compact way, with the player code size just a bit larger than 200 bytes. 
Sound effects could be then compiled into a binary, or saved as an 
assembly source, to be used in a BASIC or machine code program. 

Besides the generated sound effects, there is 1-bit sample support with 
a built-in WAV files converter. This could be used to add short voice 
clips or more realistic sounds. 

There is a demo project demo.spj provided along with the program, 
containing many sound effects. If you can't design your own effects, you 
can just use some of these. 


This software and demo project are provided under the terms of the WTFPL 
v2 license. You are free to use it without any limitations, without any 
warranty. 


You can create a bank that contains up to 128 sound effects. Every 
effect can contain up to 128 blocks of a few types. 

There are four types of the blocks: 

- Tone. It has parameters of the duration, pitch, duty cycle, pitch, and 
duty cycle slide. The duration is measured in frames and frame length. 
Slide values are only applied once per frame. 

- Noise. It has parameters of duration, pitch, and pitch slide. Noise 
pitch has much lower resolution than the tone pitch. 

- Sample. You can import up to 128 samples, if they'll fit into the RAM, 
and use them in any number of sound effects as a block, with the 
parameters being start offset and pitch. This approach allows to reuse 
the same sample in a few different effects with different settings 
without duplicating the sample data in the memory. 

- Pause. It just creates a silence of a specified duratio,n in case when 
you need it to separate the blocks of other types. 


The sound effect player uses contents of the BASIC ROM to generate the 
noise. The editor uses random numbers instead of the actual ROM content, 
which sounds well enough, but if you want to have better accuracy, you 
can place 48.rom file into the the editor folder. 


To use the effects in BASIC, compile them at some high address, like 
60000. Load the code block, POKE the address+1 with effect number 0...N, 
but not higher than the actual number of effects, then call an effect 
with RANDOMIZE USR. For example: 


POKE 60001,0:RANDOMIZE USR 60000



This program uses WTFpl'ed Z80 CPU emulation engine by Ketmar.



Versions:

v1.2  15.11.21 - Sound loops aligned to 8t for better sound quality,
                 drag and drop in the effects and block lists, multi
				 selection to delete many effects at once, copy/paste
				 for effects and blocks through Windows clipboard.
v1.11 20.09.12 - Assembly output is more compatible with assemblers other
                 than SjAsmPlus.
v1.1  31.07.12 - Sample support, Z80 emulation core is replaced.
v1.02 05.12.11 - PlaySound replaced with WaveOut player to fix audio
                 problems in Windows 7.
v1.01 04.12.11 - Minor fixes, Merge project function.
v1.0  03.12.11 - First release.


mailto:shiru@mail.ru
http://shiru.untergrund.net
https://www.patreon.com/shiru8bit