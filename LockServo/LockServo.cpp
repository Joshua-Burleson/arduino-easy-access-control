/*
  LockServo.cpp - Library for using standard servo for locking and unlocking.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#include <Arduino.h>
#include <LockServo.h>

LockServo::LockServo( bool startLocked = true ) {
  this->setLockedState( startLocked );
};

LockServo::LockServo( int pinNumber ) {
  this->_pin = pinNumber;
  this->setLockedState( true );
};

LockServo::LockServo( int pinNumber, bool startLocked = true ) {
  this->_pin = pinNumber;
  this->setLockedState( startLocked );
};

void LockServo::start() {
  this->setPin( this->_pin );
  this->setLockedState( this->_lockedState );
}

void LockServo::calibrationCycle( int first = 0, int second = 45, int third = 90, int fourth = 135, int fifth = 180, bool finalPositionLocked = true ) {
  delay(4500);
  this->write(first);
  delay(4500);
  this->write(second);
  delay(4500);
  this->write(third);
  delay(4500);
  this->write(fourth);
  delay(4500);
  this->write(fifth);
  delay(7500);
  this->setLockedState( finalPositionLocked );
};

void LockServo::unlock() {
  this->write( this->_unlocked );
  this->_lockedState = false;
};
void LockServo::lock() {
  this->write( this->_locked );
  this->_lockedState = true;
};
void LockServo::setPin( int pinNumber ) {
  this->_pin = pinNumber;
  this->attach( pinNumber );
};
void LockServo::setLockedPosition( int lockedAngle ){
    this->_locked = lockedAngle;
};
void LockServo::setUnlockedPosition( int unlockedAngle ){
    this->_unlocked = unlockedAngle;
};
void LockServo::setLockedState( bool newLockedState ) {
  newLockedState ? this->lock() : this->unlock();
};
void LockServo::stopMotor() {
  delay(10);
  this->detach();
};
void LockServo::startMotor() {
  this->attach( this->_pin );
};
bool LockServo::isLocked() {
  return this->_lockedState;
};