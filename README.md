# ino_shiftreg_daisychain
Two daisy-chained 74HC595 8-bit shift registers count up to 65535. Happy holidays!

# Note: WIRING
See https://www.arduino.cc/en/Tutorial/ShiftOut for pinout of 74HC595.

* Vcc and GND need to be wired to 5V and GND, respectively.
* Q0 through Q7 are wired to differently-colored LEDs.
* DS on the first shift register is wired to PIN_DATA;
* DS on the second shift register is wired to Q7' on the first shift register.
* OE (negative logic) on both shift registers are wired to GND.
* Both ST_CP are wired to PIN_LATCH.
* Both SH_CP are wired to PIN_CLOCK.
* Both MR (negative logic) are wired to 5V.
* Q7' on the first shift register is wired to DS on the second shift register.

Two more pins, PIN_BTN_INC and PIN_BTN_DEC are each wired to a push button which, when pressed, grounds that pin, causing it to go LOW.
