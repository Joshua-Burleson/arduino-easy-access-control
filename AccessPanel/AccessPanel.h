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
                this->accessCode[i] = EEPROM.read(i);
                this->rowPins[i] = rowsPins[i];
                this->colPins[i] = columnsPins[i];
            }
        };

        Keypad keypad = Keypad(makeKeymap(this->fourFourKeys), this->rowPins, this->colPins, this->rows, this->cols);
        
        void setAccessCode( char newAccessCode[4] ) {
          for( int i = 0; i < 4; i++ ) {
            this->accessCode[i] == newAccessCode[i];
            EEPROM.write(i, newAccessCode[i]);
          }
        }

        void scanForInput() {
          char key = this->keypad.getKey();
          if( key ) this->processKeyPress( key );
         }

         bool requestAccess() {
          return this->accessGranted;
         }

         void resetAccess() {
          this->accessGranted = false;
          this->resetCurrentCode();
         }
         
    private:
        bool accessGranted = false;
        int currentCodePosition = 0;
        char accessCode[4] = {'0', '0', '0', '0'};
        char currentCode[4] = {'x', 'x', 'x', 'x'};
        char fourFourKeys[4][4] = {
          {'1', '2', '3', 'A'},
          {'4', '5', '6', 'B'},
          {'7', '8', '9', 'C'},
          {'*', '0', '#', 'D'}
        };
        byte colPins[4] = {6, 7, 8, 9};
        byte rowPins[4] = {2, 3, 4, 5};
        
        void processKeyPress( char key ) {
           if( key == '#' )  this->accessGranted = this->checkCode();
           else {
            if ( this->currentCodePosition == 4 ) {
              this->resetCurrentCode();
              this->currentCode[0] = key;
              this->currentCodePosition++;
              return;
            }
            this->currentCode[ this->currentCodePosition ] = key;
            this->currentCodePosition++;
           }
         }

         bool checkCode() {
            for( int i = 0; i < 4; i++ ) {
              if( !( this->accessCode[i] == this->currentCode[i] ) ) {
                this->resetCurrentCode();
                return false;
              }
            }
            this->resetCurrentCode();
            return true;
         }
         
         void resetCurrentCode() {
          for( int i = 0; i < 4; i++ ) currentCode[i] = 'x'; 
          this->currentCodePosition = 0;
         }

};

#endif