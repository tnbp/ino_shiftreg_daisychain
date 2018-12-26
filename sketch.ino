const short PIN_LATCH = 11;
const short PIN_CLOCK = 12;
const short PIN_DATA = 10;

const short PIN_BTN_INC = 2;
const short PIN_BTN_DEC = 3;

const short SHIFTREGS = 2;

unsigned int counter = 0;
unsigned int counterOld = 0;
bool incWasDown = false;
bool decWasDown = false;

// binary counter
// increments when a button is pressed; current limit: 2^16-1 (but increases by 2^8 with additional shift registers)

void setup() {
	pinMode(PIN_LATCH, OUTPUT);
	pinMode(PIN_CLOCK, OUTPUT);
	pinMode(PIN_DATA, OUTPUT);

	pinMode(PIN_BTN_INC, INPUT);
	digitalWrite(PIN_BTN_INC, HIGH);
	pinMode(PIN_BTN_DEC, INPUT);
	digitalWrite(PIN_BTN_DEC, HIGH);

	digitalWrite(PIN_LATCH, LOW);
	for (int i = 0; i < 2; i++) shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 255);
	digitalWrite(PIN_LATCH, HIGH);

	delay(3000);
	for (int i = 0; i < 6; i++) {
		digitalWrite(PIN_LATCH, LOW);
		shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0xAA);
		shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0xAA);
		digitalWrite(PIN_LATCH, HIGH);
		delay(300);
		digitalWrite(PIN_LATCH, LOW);
		shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0x55);
		shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0x55);
		digitalWrite(PIN_LATCH, HIGH);
		delay(300);
	}
	digitalWrite(PIN_LATCH, LOW);
	shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0x00);
	shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, 0x00);
	digitalWrite(PIN_LATCH, HIGH);
}

void loop() {
	if (digitalRead(PIN_BTN_INC) == LOW) {
		incWasDown = true;
	}
	else if (digitalRead(PIN_BTN_INC) == HIGH && incWasDown) {
		counter++;
		incWasDown = false;
	}
	if (digitalRead(PIN_BTN_DEC) == LOW) {
		decWasDown = true;
	}
	else if (digitalRead(PIN_BTN_DEC) == HIGH && decWasDown) {
		counter--;
		decWasDown = false;
	}
	if (counter != counterOld) {
		digitalWrite(PIN_LATCH, LOW);
		for (int i=SHIFTREGS-1; i>=0; i--) {
			shiftOut(PIN_DATA, PIN_CLOCK, LSBFIRST, counter >> (8*i));
		}
		digitalWrite(PIN_LATCH, HIGH);
		counterOld = counter;
	}
	delay(10);
}
