#include <Arduino.h>
#include <Keypad.h>
#include "SEB.h"

/*
 * List of globals
 */
const long DEBOUNCE = 300;
const int MAX_IN_PIN = 5;
const int MAX_OUT_PIN = 5;
const int MAX_APPLIANCES = 5;
long BOARD_TIMER = 0;

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 3;


char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte KEYPAD_ROW_PINS[KEYPAD_ROWS] = {PIN_08, PIN_07, PIN_06, PIN_05}; 
byte KEYPAD_COL_PINS[KEYPAD_COLS] = {PIN_04, PIN_03, PIN_02};

DigitalPin OUTPUT_PINS[MAX_IN_PIN] = {PIN_09, PIN_10, PIN_11, PIN_12, PIN_13};
//DigitalPin INPUT_PINS[MAX_OUT_PIN] = {PIN_08, PIN_09, PIN_10, PIN_11, PIN_12};
Appliance APPLIANCES[MAX_APPLIANCES];

/*
 * Input/Output pin handler functions
 */
// isOutputPinValueHigh definition
bool isInputPinValueHigh(DigitalPin* iPin) {
	return (digitalRead(*iPin) == HIGH);
}

// isOutputPinValueLow definition
bool isInputPinValueLow(DigitalPin* iPin) {
	return (digitalRead(*iPin) == LOW);
}

// setOutputPinValueHigh definition
void setOutputPinValueHigh(DigitalPin* oPin) {
	digitalWrite(*oPin, HIGH);
}

// setOutputPinValueLow definition
void setOutputPinValueLow(DigitalPin* oPin) {
	digitalWrite(*oPin, LOW);
}


/*
 * Timer handler functions
 */
// isRightTimeToChangeState definition
bool  isRightTimeToChangeState(void) {
	if ((millis() - BOARD_TIMER) > DEBOUNCE) {
		BOARD_TIMER = millis();
		return true;
	}

	return false;
}


/*
 * StatusFlag handler functions
 */
// isStatusFlagOn definition
bool isStatusFlagOn(StatusFlag* pin_sta_f) {
	return (*pin_sta_f == STA_ON);
}

// isStatusFlagOff definition
bool isStatusFlagOff(StatusFlag* pin_sta_f) {
	return (*pin_sta_f == STA_OFF);
}

// setStatusFlagOn definition
void setStatusFlagOn(StatusFlag* pin_sta_f) {
	*pin_sta_f = STA_ON;
}

// setStatusFlagOff definition
void setStatusFlagOff(StatusFlag* pin_sta_f) {
	*pin_sta_f = STA_OFF;
}

// toggleStatusFlag definition
void toggleStatusFlag(StatusFlag* pin_sta_f) {
	if (isStatusFlagOff(pin_sta_f)) {
		setStatusFlagOn(pin_sta_f);
	} else {
		setStatusFlagOff(pin_sta_f);
	}
}


/*
 * Keyboard handler
 */
//
Keypad sebKeypad = Keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

/*
 * Appliance handler functions
 */
// configureApplienceById definition
void configureApplienceById(int id) {
	APPLIANCES[id].id = id;
	APPLIANCES[id].oPin = OUTPUT_PINS[id];
	pinMode(APPLIANCES[id].oPin, OUTPUT);
}

// configureAllAppliences definition
void configureAllAppliences(void) {
	for (int i = 0; i < MAX_APPLIANCES; i++) {
		configureApplienceById(i);
	}
}

// setApplianceToDefaultState definition
void setApplianceToDefaultState(Appliance* appliance) {
	setOutputPinValueLow(&appliance -> oPin);
	setStatusFlagOff(&appliance -> applianceStatusFlag);
}

// setAllAppliancesToDefaultState definition
void setAllAppliancesToDefaultState(void) {
	for (int i = 0; i < MAX_APPLIANCES; i++) {
		setApplianceToDefaultState(&APPLIANCES[i]);
	}
}

// setApplianceStateOn definition
void setApplianceStateOn(Appliance* appliance) {
	setOutputPinValueHigh(&appliance -> oPin);
	setStatusFlagOn(&appliance -> applianceStatusFlag);
}

// setApplianceStateOff definition
void setApplianceStateOff(Appliance* appliance) {
	setOutputPinValueLow(&appliance -> oPin);
	setStatusFlagOff(&appliance -> applianceStatusFlag);
}

// toggleApplianceState definition
void toggleApplianceState(Appliance* appliance) {
	if (isStatusFlagOn(&appliance -> applianceStatusFlag)) {
		setApplianceStateOff(appliance);
	} else {
		setApplianceStateOn(appliance);
	}
}

int getApplianceId(const char code) {
	return ((int)code - 49);
}

// refresh definition
void refresh(void) {
	char keyCode = sebKeypad.getKey();
	if(keyCode && isRightTimeToChangeState()) {
		int applienceId = getApplianceId(keyCode);
		toggleApplianceState(&APPLIANCES[applienceId]);
	}
}
