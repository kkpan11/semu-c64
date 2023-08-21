# Running Linux on a Commodore C-64

"But does it run Linux?" can now be finally and affirmatively answered for the Commodore C64!

![Booted](booted.jpeg)

There is a catch (rather: a couple) of course: It runs *extremely* slowly and it needs a RAM Expansion Unit (REU), as there is no chance to fit it all into just 64KiB.

It even emulates virtual memory with an MMU.

I have **not** tested it on **real hardware yet**, that's the next challenge .. for you. So please send me a link to a timelapse video of an original unit with REU booting Linux :D

# Building it

Just use `make`. You need [`mos-c64-clang`](https://github.com/llvm-mos/).

Change the single `C64` variable at the top of the Makefile and you should be able to switch between a `x86_64` and an `llvm-mos-6502` build of the code.

The notes from the [original README](README.original.md) apply for the most part. The kernel configuration is different, though, as the kernel from the original `semu` is too bloated with huge section alignments. A more fitting kernel configuration can be found in the `config` subfolder. Finally, to assemble it all into the REU image needed for the VICE emulator, use the `mk_linux_reu.py` script. It still uses the original `initrd` image, as that works just well.

# Running it

To run it, simply create a `.d64` file containing the compiled `semu` executable (or simply select the correct path for a virtual disk drive in the emulator). Then (in VICE EMU), go to Preferences | Settings | Cartridges | RAM Expansion Module, enable it and select the file `reufile.linux`, and make sure to select the correct size (16MiB) as well. If you started `x64` from the console, a message that it loaded successfully should appear.

Then, do `LOAD "SEMU",8,1` and `run` and ... *wait* ... (hours!). With "warp mode" enabled in the emulator, the first boot messages should appear within a few minutes, though.

You can also use the PC `semu` binary with the `-k` option to load the reufile.linux into the PC emulator and you should get a 100% identical boot sequence, as everything should be deterministic until the first keypress.

I plan to add an archive with all the neccessary premade binaries as soon as I figured out how to do that on github. Look for something on the "Releases" tab.

# Further notes

- The screenshots took VICE *a couple hours* in "warp mode" (activate it with Alt-W) to generate. So, as is, a real C64 should be able to boot Linux within a week or so.

- The compiled 6502 code is not really optimized yet, and it might be realistic to squeeze a factor 10x of performance out of this. Maybe even a simple form of JIT compilation? It should also be possible to implement starting a checkpointed VM (quickly precomputed on `x86-64`) to avoid the lengthy boot process. Maybe `X` on an emulated framebuffer device in 320x200 graphics mode? VIC-II DRI? :D

- I also tested a minimal micropython port (I can clean it up and post it on github if there is interest), that one does not use the MMU and is almost barely remotely usable with lots of optimism at 100% speed...

- The generated `semu` executable is a generic RISCV32 emulator and it simply assumes that the REU maps to the address range 0x00000000 .. 0x01000000. You should be able to compile any (embedded, bare-bones) RISCV32 executable that uses just the emulated UART, fill it up to a size of 16MiB, load it as a REU-image into VICE and run it using the same `semu` 6510 binary.

- Likewise, I made a simple [kernalemu](https://github.com/mist64/kernalemu) fork with "REU support" which seems to run a lot faster than Vice.

- The emulated UART does upper-/lowercase PETSCII<->ASCII translation. That could use a lot of improvement, though ...

# Thanks

This is in essence a fork of the very nicely minimalist RISC-V32 emulator named [semu](https://github.com/sysprog21/semu), compiled and ported using the new [llvm-mos](https://github.com/llvm-mos/) and would not have been so possible without all that previous work.

# (Boot animation)
![(Boot animation)](boot_anim.gif)

Time not to scale.
