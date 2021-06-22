/*
  LockServo.h - Library for using standard servo for locking and unlocking.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#ifndef LockServo_h
#define LockServo_h

#include "Arduino.h"
#include "Servo.h"

class LockServo: public Servo {
  public:
    LockServo(bool startLocked);
    LockServo(int pinNumber);
    LockServo(int pinNumber, bool startLocked);
    void calibrationCycle( int first, int second, int third, int fourth, int fifth, bool finalPositionLocked );
    void unlock();
    void lock();
    void setPin( int pinNumber );
    void setLockedPosition( int lockedAngle );
    void setUnlockedPosition( int unlockedAngle );
    void setLockedState( bool newLockedState );
    void start();
    void startMotor();
    void stopMotor();
    bool isLocked();
  private:
    int _angle = 86;
    int _unlocked = 170;
    int _locked = 86;
    int _pin = 10;
    bool _lockedState = true;
};

#endif