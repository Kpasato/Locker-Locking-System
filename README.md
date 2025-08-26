Automated Locker System

**Overview**

The Automated Locker System is an Arduino-based accessibility project designed to provide students with physical challenges a reliable and user-friendly locker experience. The system combines electronic and mechanical components with software to ensure secure access while maintaining a physical failsafe.

***Features:***

Keypad-controlled locking mechanism with password entry stored in EEPROM for non-volatile storage

Failsafe manual unlock feature to guarantee accessibility during power or system failures

Two-relay power control system to manage the linear actuator (lock/unlock function)

OLED display interface for clear user feedback (e.g., access granted/denied)

3D-printed component housings for durability and ease of installation

Password reset capability for user flexibility

Hardware Components

Arduino Uno R4 Minima

4x4 Matrix Keypad

Frienda I2C OLED Display

Mini Linear Actuator (replacing standard solenoid lock)

2-Channel Relay Module

DC-DC Buck Step-Down Module (powered by DeWalt 12V battery with RONFACE adapter)

Manual key-based lock for failsafe access

Software

Language: C (Arduino IDE)

Libraries Used:

Adafruit_Keypad (for keypad input)

EEPROM.h (for password storage)

Adafruit_GFX and Adafruit_SSD1306 (for OLED display)

The system is programmed with modular code structure, separating password management, actuator control, and display functions for readability and maintainability.

How It Works

User enters a passcode on the keypad.

The Arduino checks the passcode against the one stored in EEPROM.

If correct, the relay powers the actuator to unlock the locker.

The OLED display provides feedback (“Access Granted” / “Access Denied”).

A manual key mechanism provides backup access if electronics fail.

Project Goals

Improve accessibility for students with physical challenges.

Provide a reliable locker solution with both digital convenience and manual reliability.

Demonstrate integration of hardware design, embedded programming, and 3D printing in a real-world system.
