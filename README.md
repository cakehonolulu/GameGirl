# GameGirl
<p align="center">
  <img src="resources/banner.png"/>
</p>

[![CodeQL](https://github.com/cakehonolulu/GameGirl/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/cakehonolulu/GameGirl/actions/workflows/codeql-analysis.yml)

`GameGirl` is a GameBoy (DMG-01) emulator written in C.

It's prupose is to serve as a low-level learning experience for me.

## Features
* DMG-01 CPU Implementation (4.194304 MHz, 8-bit Sharp LR35902) &nbsp;&nbsp;->&nbsp;&nbsp; 10%
* DMG-01 PPU Implementation 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;10%
* BootROM emulation&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; -> &nbsp;&nbsp;100%

Cart-less boot | Inserted cart boot
:-------------------------:|:-------------------------:
<img src="resources/bromnocart.gif" width="400"> | <img src="resources/bromcart.gif" width="400">

### Interesting development facts
51 Instructions needed to be implemented to execute DMG-01's BootROM until the end (Infinite Loop)

### Credits
Logo Font: Yoster Island Font made by codeman38

Emulator and Logo Palette: WildLeoKnight Gameboy Palettes Set
