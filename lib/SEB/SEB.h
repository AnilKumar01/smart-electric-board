#ifndef SEB_CORE_H_
#define SEB_CORE_H_

// digital pins
typedef enum {
  PIN_00 = 0,
  PIN_01,
  PIN_02,
  PIN_03,
  PIN_04,
  PIN_05,
  PIN_06,
  PIN_07,
  PIN_08,
  PIN_09,
  PIN_10,
  PIN_11,
  PIN_12,
  PIN_13
} DigitalPin;

// serial pins
typedef enum {
  PIN_RX = 0,
  PIN_TX
} SerialPin;

// status flag values
typedef enum {
  STA_OFF = 0,
  STA_ON
} StatusFlag;

// Appliance structure
typedef struct {
  int id;
	//DigitalPin iPin;
	DigitalPin oPin;

	StatusFlag applianceStatusFlag;
} Appliance;

// list of globals
extern const long DEBOUNCE;
extern const int MAX_IN_PIN;
extern const int MAX_OUT_PIN;
extern const int MAX_APPLIANCES;
extern long BOARD_TIMER;

// list of core functions
void setOutputPinValueHigh(DigitalPin*);
void setOutputPinValueLow(DigitalPin*);

void setStatusFlagOn(StatusFlag*);
void setStatusFlagOff(StatusFlag*);
void toggleStatusFlag(StatusFlag*);

bool isInputPinValueHigh(DigitalPin*);
bool isInputPinValueLow(DigitalPin*);
bool isStatusFlagOn(StatusFlag*);
bool isStatusFlagOff(StatusFlag*);

// timer related functions
bool isRightTimeToChangeState(void);

// list of appliance handler functions
void configureApplienceById(int);
void configureAllAppliences(void);
void setApplianceToDefaultState(Appliance*);
void setAllAppliancesToDefaultState(void);
void setApplianceStateOn(Appliance*);
void setApplianceStateOff(Appliance*);
void toggleApplianceState(Appliance*);
void printApplianceStats(Appliance*);

// list of seb functions
void initSebState(void);
void readSebState(void);
void writeSebState(void);
void updateSebState(void);
void refresh(void);

// keyboard specific functions
//void initializeKeyboard(void);
int getApplianceId(const char);

#endif // SEB_CORE_H_
