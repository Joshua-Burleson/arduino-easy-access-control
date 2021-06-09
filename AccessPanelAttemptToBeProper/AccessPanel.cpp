/*
  AccessPanel.h - Library for managing access using 4x4 matrix keypad.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#include <Arduino.h>
#include <AccessPanel.h>
#include <Keypad.h>
#include <EEPROM.h>

AccessPanel::AccessPanel( byte rowsPins[4], byte columnsPins[4] ) {
    for( int i = 0; i < 4; i++ ) {
        this->_accessCode[i] = EEPROM.read(i);
        this->_rowPins[i] = rowsPins[i];
        this->_colPins[i] = columnsPins[i];
    }
};

Keypad AccessPanel::keypad = Keypad(makeKeymap(this->_fourFourKeys), this->_rowPins, this->_colPins, this->rows, this->cols);
        
void AccessPanel::setAccessCode( char newAccessCode[4] ) {
    for( int i = 0; i < 4; i++ ) {
    this->_accessCode[i] == newAccessCode[i];
    EEPROM.write(i, newAccessCode[i]);
    }
};

void AccessPanel::scanForInput() {
    char key = this->keypad.getKey();
    if( key ) this->_processKeyPress( key );
};

bool AccessPanel::requestAccess() {
    return this->_accessGranted;
};

void AccessPanel::resetAccess() {
    this->_accessGranted = false;
    this->_resetCurrentCode();
};

void AccessPanel::_processKeyPress( char key ) {
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

bool AccessPanel::_checkCode() {
    for( int i = 0; i < 4; i++ ) {
        if( !( this->_accessCode[i] == this->_currentCode[i] ) ) {
            this->_resetCurrentCode();
            return false;
        }
    }
    this->_resetCurrentCode();
    return true;
};

void AccessPanel::_resetCurrentCode() {
    for( int i = 0; i < 4; i++ ) this->_currentCode[i] = 'x'; 
    this->_currentCodePosition = 0;
};