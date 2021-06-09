/*
  SonarProximity.cpp - Library for detecting a proximity trip with a HC-SR04 ultrasonic sensor.
  Created by Joshua C. Burleson, June 9, 2021.
  Released into the public domain.
*/
#include <Arduino.h>
#include <SonarProximity.h>

SonarProximity::SonarProximity(int pingingPin, int echoingPin) {
    pinMode( pingingPin, OUTPUT );
    pinMode( echoingPin, INPUT );
    this->_pingPin = pingingPin;
    this->_echoPin = echoingPin;
};

bool SonarProximity::proximityTrigger(){
    return this->_sonarCycle() <= this->_triggerDistance;
};

void SonarProximity::setProximityTriggerDistance( long centimeters ) {
    this->_triggerDistance = centimeters * 29 * 2;
};

void SonarProximity::setProximityTriggerDistanceImperial( long inches ) {
    this->_triggerDistance = inches * 74 * 2;
};

void SonarProximity::setProximityTriggerDistanceRaw( long time ) {
    this->_triggerDistance = time;
};

long SonarProximity::getDistance() {
    return this->_sonarCycle() / 29 / 2;
};

long SonarProximity::getInches() {
    return this->_sonarCycle() / 74 / 2;
};

long SonarProximity::getSonarResponseTime() {
    return this->_sonarCycle();
};

long SonarProximity::_sonarCycle() {
    digitalWrite(this->_pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->_pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_pingPin, LOW);
    return pulseIn(this->_echoPin, HIGH);
};