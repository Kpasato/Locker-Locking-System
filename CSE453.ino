// Use this example with the Adafruit Keypad products.
// You'll need to know the Product ID for your keypad.
// Here's a summary:
//   * PID3844 4x4 Matrix Keypad
//   * PID3845 3x4 Matrix Keypad
//   * PID1824 3x4 Phone-style Matrix Keypad
//   * PID1332 Membrane 1x4 Keypad
//   * PID419  Membrane 3x4 Matrix Keypad

#include "Adafruit_Keypad.h"
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   30
#define LOGO_WIDTH    128
// define your pins here
// define your specific keypad here via PID
#define KEYPAD_PID3845

#define R1    2
#define R2    3
#define R3    4
#define R4    5
#define C1    8
#define C2    9
#define C3    10
//#define C4    11

//PINS FOR LINEAR ACTUATOR AND POWER
#define ACTUATOR_PIN 6
#define PWR_PIN       12
#include "keypad_config.h"

// UB LOGO
const unsigned char epd_bitmap_Screenshot_2025_03_11_213839[] PROGMEM = {
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xe0, 0x30, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x79, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x71, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf0, 0x71, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xdf, 0xdf, 0xff, 0xff,
 0xff, 0xff, 0x33, 0xfd, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xdf, 0x07, 0xfd, 0xbf, 0xdf, 0xff, 0xff,
 0xff, 0xff, 0x3b, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xdf, 0xb7, 0xf9, 0xbf, 0xdf, 0xff, 0xff,
 0xff, 0xff, 0x3a, 0x0c, 0xb2, 0x31, 0x8d, 0x9b, 0x38, 0xcf, 0xb4, 0xd8, 0x10, 0xd8, 0xff, 0xff,
 0xff, 0xff, 0x3b, 0x6d, 0xb6, 0xdb, 0xbd, 0xbb, 0x7e, 0xdf, 0x86, 0xd9, 0xbe, 0xd3, 0x7f, 0xff,
 0xff, 0xff, 0x3b, 0x6d, 0xd4, 0xfb, 0xcd, 0xbd, 0x7a, 0xdf, 0xb6, 0xd9, 0xb0, 0xd7, 0x7f, 0xff,
 0xff, 0xff, 0xb3, 0x6c, 0xce, 0xf3, 0xed, 0xbc, 0xf2, 0xdf, 0xb6, 0xd9, 0xb6, 0xd2, 0x7f, 0xff,
 0xff, 0xff, 0xc6, 0x6c, 0xee, 0x33, 0x8c, 0xdc, 0xf8, 0x67, 0x0e, 0x49, 0x10, 0x98, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// class keypad custom config
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String star = "*";
String pound = "#";
int address = 0;
int pixloc = 0;
String attempt = "";
String combination = "1234";
String resetcode = "56";
String masterCode = "6554888"; // Teacher override passcode

// states for passcode during process of changing it or not
enum PasscodeState { NORMAL_STATE, VERIFY_OLD_STATE, NEW_ENTRY_STATE, CONFIRM_NEW_STATE };
PasscodeState currentState = NORMAL_STATE;
bool teacherOverride = false;  // Tracks if teacher override is in progress

unsigned long lasttouchedtime;
unsigned long overalltime;
unsigned long timesincetouched;
bool idleMode = false;//flag for idle to turn on ub logo
void resetAllStates();
void drawbitmap();
void displaysmallword(String output);
void displaycode(String output);
void getkeycodeonstart();
void checktime();

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {}}
  
  pinMode(ACTUATOR_PIN, OUTPUT);
  digitalWrite(ACTUATOR_PIN, LOW);
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(PWR_PIN, HIGH); //keeps system on
  
  getkeycodeonstart(); //Retrieve stored combination or set default
  customKeypad.begin();
  drawbitmap(); //display UB logo on boot for 1.5 seconds
  delay(1500);}

void loop() {
  customKeypad.tick();
  // Process available key events
  while (customKeypad.available()){
    keypadEvent e =customKeypad.read();
    char ch = (char)e.bit.KEY;
    String keypress = String(ch);
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      lasttouchedtime = millis(); // Reset idle timer
      idleMode = false;            // Exit idle mode when any key is pressed
      
      // ====== State Machine for Passcode Flow ======
      switch (currentState) {
        case NORMAL_STATE:
          // Build up the attempt string for digits
          if (keypress != star && keypress != pound) {
            attempt += ch;
            displaycode(attempt);
          }
          // When star is pressed, check for commands
          if (keypress == star) {
            // Teacher override
            if (attempt == masterCode && combination != masterCode) {
              teacherOverride = true;
              currentState = NEW_ENTRY_STATE;
              attempt = "";
              displaysmallword("Override\nEnter new code:\n4-7 digits");
              delay(2000);
            }
            // Reset command (needs to verify old passcode)
            else if (attempt == resetcode) {
              currentState = VERIFY_OLD_STATE;
              attempt = "";
              displaysmallword("RESETTING CODE.\nPLEASE INPUT OLD\nPASSCODE\nTo cancel press #");
              delay(2000);
            }
            // Unlock: entered combination matches current code
            else if (attempt == combination) {
              Serial.println("Correct, Opening Locker");
              displaycode("Correct");
            digitalWrite(ACTUATOR_PIN, HIGH);
            delay(6000);   // keep actuator powered for 6 seconds
            digitalWrite(ACTUATOR_PIN, LOW);}
            // Incorrect input
            else {
              displaysmallword("Incorrect");
              delay(2000);
            }
            attempt = "";
          }
          break;
          
        case VERIFY_OLD_STATE:
          // In this state, user must re-enter the current passcode.
          if (keypress != star && keypress != pound) {
            attempt += ch;
            displaycode(attempt);
          }
          if (keypress == star) {
            if (attempt == combination) {
              currentState = NEW_ENTRY_STATE;
              attempt = "";
              displaysmallword("Enter new passcode:\n4-7 digits\nOr press # to cancel");
              delay(2000);
            } else {
              displaysmallword("Incorrect old passcode.\nTry again\nOr press # to cancel");
              delay(2000);
              attempt = "";
            }
          }
          else if (keypress == pound) {
            resetAllStates();
            displaysmallword("Reset Canceled");
            delay(2000);
          }
          break;
          
        case NEW_ENTRY_STATE:
          // Collect digits for the new passcode.
          if (keypress != star && keypress != pound) {
            attempt += ch;
            displaycode(attempt);
          }
          if (keypress == star) {
            if (attempt.length() >= 4 && attempt.length() <= 7) {
              currentState = CONFIRM_NEW_STATE;
              displaysmallword("Press * to confirm\nor # to re-enter");
              delay(2000);
            } else {
              displaysmallword("Invalid size.\nTry again\nOr press # to cancel");
              delay(2000);
              attempt = "";
            }
          }
          else if (keypress == pound) {
            resetAllStates();
            displaysmallword("Reset Canceled");
            delay(2000);
          }
          break;
          
        case CONFIRM_NEW_STATE:
          // In the confirmation stage, wait only for star (confirm) or pound (re-enter).
          if (keypress == star) {
            // Save new passcode to EEPROM and update variable
            combination = attempt;
            for (int i = 0; i < combination.length(); i++) {
              EEPROM.write(address + i, combination[i]);
            }
            EEPROM.write(address + combination.length(), 0);
            displaysmallword("New Passcode Saved");
            delay(2000);
            resetAllStates();
          }
          else if (keypress == pound) {
            currentState = NEW_ENTRY_STATE;
            attempt = "";
            displaysmallword("Enter new passcode:\n4-7 digits\nOr press # to cancel");
            delay(2000);
          }
          break;
      } // end switch
    } // end if KEY_JUST_PRESSED
  } // end while
  
  delay(50);
  checktime();
  
  // Only update the display if not in idle mode
  if (currentState == NORMAL_STATE && !idleMode) {
    displaycode(attempt);
  }
}
// Helper Functions

void resetAllStates() {// Resets states and clears the attempt variable.
  currentState = NORMAL_STATE;
  teacherOverride = false;
  attempt = "";}
void drawbitmap(void) {//just shows ub logo
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    epd_bitmap_Screenshot_2025_03_11_213839, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();}

void displaysmallword(String output) {//whichever string is inputted is displayed on call.(small size)
  display.clearDisplay();
  display.setCursor(0, 0);  // Set cursor to new position
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  display.print(output);
  display.display();}

void displaycode(String output) {// displays larger text
  display.clearDisplay();
  display.setCursor(0, 0); // Set cursor to new position
  display.setTextSize(2.5);
  display.setTextColor(SSD1306_WHITE);
  display.print(output);
  display.display();}

// Called during setup to pull stored combo if it exists. otherwise it stores the default combo.
void getkeycodeonstart(){
  int j = 0;
  char current;
  bool notStored = (EEPROM.read(address) == 255);
  if (!notStored) {
    combination = "";
    while ((current = EEPROM.read(address + j)) != 0) {
      combination += current;
      j++;}
    Serial.println("Startup Combination from EEPROM: " + combination);
  } else {
    for (int i = 0; i < combination.length(); i++) {
      EEPROM.write(address + i, combination[i]);
    }
    EEPROM.write(address + combination.length(), 0);
    Serial.println("No stored passcode found. Using default: " + combination);
  }}

void checktime() {
  overalltime = millis();
  timesincetouched = overalltime - lasttouchedtime;
  
  // when idle for more than 15 seconds but less than 30 seconds,
  // enter idle mode and display the UB logo only once.
  if (timesincetouched > 15000 && timesincetouched < 30000) {
    if (!idleMode) {
      drawbitmap();
      idleMode = true;
    }
  } else {// If activity resumes (or if not in the idle window), clears idle flag.
    idleMode = false;}
  // After 30 seconds of inactivity, power off.
  if (timesincetouched > 30000) {
    digitalWrite(PWR_PIN, LOW);}}
