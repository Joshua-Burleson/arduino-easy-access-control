/*
  doorAccess.ino - Sketch demonstrating simple usage of custom libraries for access-control.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#include <LockServo.h>
#include <AccessPanel.h>
#include <SonarProximity.h>

byte keypadRowPinSet[4] = {2, 3, 4, 5};
byte keypadColPinSet[4] = {6, 7, 8, 9};
char newCode[4] = {'1', '2', '3', '4'};

LockServo lockServo = LockServo( true );
AccessPanel accessPanel = AccessPanel(keypadRowPinSet, keypadColPinSet);
SonarProximity proximitySensor = SonarProximity(12, 11);

void setup() {
  lockServo.attach(10);
  lockServo.lock();
  accessPanel.setAccessCode( newCode );
}

void loop() {
  accessPanel.scanForInput();
  if( accessPanel.requestAccess() || proximitySensor.proximityTrigger() ) {
    lockServo.unlock();
    delay( 3000 );
    lockServo.lock();
    accessPanel.resetAccess();
  }
}