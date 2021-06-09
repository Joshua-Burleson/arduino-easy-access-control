#include <Arduino.h>
#include <LockServo.h>

LockServo::LockServo( bool startLocked = true ) {
  this->setLockedState( startLocked );
};

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
void LockServo::setLockedPosition( int lockedAngle ){
    this->_locked = lockedAngle;
};
void LockServo::setUnlockedPosition( int unlockedAngle ){
    this->_unlocked = unlockedAngle;
};
void LockServo::setLockedState( bool newLockedState ) {
  newLockedState ? this->lock() : this->unlock();
};
bool LockServo::isLocked() {
  return this->_lockedState;
};