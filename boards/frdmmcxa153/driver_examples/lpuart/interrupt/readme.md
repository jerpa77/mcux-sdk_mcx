Overview
========
The lpuart_functioncal_interrupt example shows how to use lpuart driver functional
API to receive data with interrupt method:

In this example, one lpuart instance connect to PC, the board will
send back all characters that PC send to the board.

SDK version
===========
- Version: 2.14.2

Toolchain supported
===================
- IAR embedded Workbench  9.40.2
- Keil MDK  5.38.1
- GCC ARM Embedded  12.2
- MCUXpresso  11.9.0

Hardware requirements
=====================
- Type-C USB cable
- FRDM-MCXA153 board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a Type-C USB cable between the host PC and the MCU-Link port(J15) on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the MCU-Link terminal like:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Lpuart functional interrupt example
Board receives characters then sends them out
Now please input:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~