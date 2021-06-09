/*
  AccessPanel.h - Library for managing access using 4x4 matrix keypad.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#ifndef AccessPanel_h
#define AccessPanel_h

#include "Arduino.h"
#include "Keypad.h"

class AccessPanel {
    public:
        byte cols = 4;
        byte rows = 4;
        AccessPanel( byte rowsPins[4], byte columnsPins[4] );

        Keypad keypad;
        
        void setAccessCode( char newAccessCode[4] );

        void scanForInput();

        bool requestAccess();

        void resetAccess();
         
    private:
        bool _accessGranted = false;
        int _currentCodePosition = 0;
        char _accessCode[4] = {'0', '0', '0', '0'};
        char _currentCode[4] = {'x', 'x', 'x', 'x'};
        char _fourFourKeys[4][4] = {
          {'1', '2', '3', 'A'},
          {'4', '5', '6', 'B'},
          {'7', '8', '9', 'C'},
          {'*', '0', '#', 'D'}
        };
        byte _colPins[4] = {6, 7, 8, 9};
        byte _rowPins[4] = {2, 3, 4, 5};
        
        void _processKeyPress( char key );

        bool _checkCode();
        
        void _resetCurrentCode();
};
#endif