/*
  AccessPanel.h - Library for managing access using 4x4 matrix keypad.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#ifndef AccessPanel_h
#define AccessPanel_h

#include "Arduino.h"
#include "Keypad.h"
#include "EEPROM.h"

class AccessPanel {
    public:
        byte cols = 4;
        byte rows = 4;

        AccessPanel( byte rowsPins[4], byte columnsPins[4] ) {
            for( int i = 0; i < 4; i++ ) {
                this->_accessCode[i] = EEPROM.read(i);
                this->_rowPins[i] = rowsPins[i];
                this->_colPins[i] = columnsPins[i];
            }
        };

        Keypad keypad = Keypad(makeKeymap(this->_fourFourKeys), this->_rowPins, this->_colPins, this->rows, this->cols);
        
        void setAccessCode( char newAccessCode[4] ) {
          for( int i = 0; i < 4; i++ ) {
            this->_accessCode[i] == newAccessCode[i];
            EEPROM.write(i, newAccessCode[i]);
          }
        };

        void scanForInput() {
          char key = this->keypad.getKey();
          if( key ) this->processKeyPress( key );
         };

         bool requestAccess() {
          return this->_accessGranted;
         };

         void resetAccess() {
          this->_accessGranted = false;
          this->_resetCurrentCode();
         };
         
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
        
        void processKeyPress( char key ) {
           if( key == '#' )  this->_accessGranted = this->_checkCode();
           else {
            if ( this->_currentCodePosition == 4 ) {
              this->_resetCurrentCode();
              this->_currentCode[0] = key;
              this->_currentCodePosition++;
              return;
            }
            this->_currentCode[ this->_currentCodePosition ] = key;
            this->_currentCodePosition++;
           }
         };

         bool _checkCode() {
            for( int i = 0; i < 4; i++ ) {
              if( !( this->_accessCode[i] == this->_currentCode[i] ) ) {
                this->_resetCurrentCode();
                return false;
              }
            }
            this->_resetCurrentCode();
            return true;
         };
         
         void _resetCurrentCode() {
          for( int i = 0; i < 4; i++ ) this->_currentCode[i] = 'x'; 
          this->_currentCodePosition = 0;
         };

};

#endif