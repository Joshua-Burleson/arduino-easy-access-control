/* LockServo
 modified 4 Jun 2021
 by Joshua Burleson
*/

#include <Arduino.h>
#include <Servo.h>

class LockServo: public Servo {
  public:
    LockServo() {
      this->setLockedState( false );
    }
    void lock() {
      while( this->angle < this->locked ) {
        ++this->angle;
        this->write( this->angle );
      }
      this->lockedState = true;
    };
    void unlock() {
      while( this->angle > this->unlocked ) {
        --this->angle;
        this->write( this->angle );
      }
      this->lockedState = false;
    };
    void setLockedPosition( int lockedAngle ){
        this->locked = lockedAngle;
    };
    void setUnlockedPosition( int unlockedAngle ){
        this->unlocked = unlockedAngle;
    };
    void setLockedState( bool newLockedState ) {
      newLockedState ? this->lock() : this->unlock();
    };
    bool isLocked() {
      return this->lockedState;
    };
  private:
    int angle = 90;
    int unlocked = 90;
    int locked = 180;
    bool lockedState = true;
};