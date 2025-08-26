#ifndef __KEYPAD_CONFIG_H__
#define __KEYPAD_CONFIG_H__

#if defined(KEYPAD_PID1824) || defined(KEYPAD_PID3845) || defined(KEYPAD_PID419)
const byte ROWS = 4; // rows
const byte COLS = 3; // columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
#endif

#if defined(KEYPAD_PID1332)
const byte ROWS = 1;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', '4'}};
byte rowPins[ROWS] = {R1};
byte colPins[COLS] = {C1, C2, C3, C4};
#endif

#endif
