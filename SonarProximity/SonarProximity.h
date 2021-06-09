/*
  SonarProximity.h - Library for detecting a proximity trip with a HC-SR04 ultrasonic sensor.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#ifndef SonarProximity_h
#define SonarProximity_h

#include "Arduino.h"

class SonarProximity {
  public:
    SonarProximity(int pingingPin, int echoingPin);
    bool proximityTrigger();
    void setProximityTriggerDistance( long centimeters );
    void setProximityTriggerDistanceImperial( long inches );
    void setProximityTriggerDistanceRaw( long time );
    long getDistance();
    long getInches();
    long getSonarResponseTime();
  private:
    long _sonarCycle();
    long _triggerDistance = 3000;
    long _pingPin;
    long _echoPin;
};

#endif