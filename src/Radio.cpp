//
// Created by paulm on 11.06.2024.
//

#include "Radio.h"

Radio::Radio(int volumeUpPin, int volumeDownPin, int trackUpPin, int trackDownPin, int mutePin) {
    this->volumeUpPin = volumeUpPin;
    this->volumeDownPin = volumeDownPin;
    this->trackUpPin = trackUpPin;
    this->trackDownPin = trackDownPin;
    this->mutePin = mutePin;
    this->muted = false;

    pinMode(volumeUpPin, OUTPUT);
    pinMode(volumeDownPin, OUTPUT);
    pinMode(trackUpPin, OUTPUT);
    pinMode(trackDownPin, OUTPUT);
    pinMode(mutePin, OUTPUT);

    digitalWrite(volumeUpPin, LOW);
    digitalWrite(volumeDownPin, LOW);
    digitalWrite(trackUpPin, LOW);
    digitalWrite(trackDownPin, LOW);
    digitalWrite(mutePin, LOW);
}

void Radio::volumeUpStart() const {
    Serial.println("Volume up start");
    digitalWrite(volumeUpPin, HIGH);
}

void Radio::volumeUpStop() const {
    Serial.println("Volume up stop");
    digitalWrite(volumeUpPin, LOW);
}

void Radio::volumeUp() const {
    volumeUpStart();
    delay(100);
    volumeUpStop();
}

void Radio::volumeDownStart() const {
    Serial.println("Volume down start");
    digitalWrite(volumeDownPin, HIGH);
}

void Radio::volumeDownStop() const {
    Serial.println("Volume down stop");
    digitalWrite(volumeDownPin, LOW);
}

void Radio::volumeDown() const {
    volumeDownStart();
    delay(100);
    volumeDownStop();
}

void Radio::trackUp() const {
    Serial.println("Track up");
    digitalWrite(trackUpPin, HIGH);
    delay(100);
    digitalWrite(trackUpPin, LOW);
}

void Radio::trackDown() const {
    Serial.println("Track down");
    digitalWrite(trackDownPin, HIGH);
    delay(100);
    digitalWrite(trackDownPin, LOW);
}

void Radio::mute() {
    if (muted) {
        return;
    }
    Serial.println("Mute");
    digitalWrite(mutePin, HIGH);
    delay(100);
    digitalWrite(mutePin, LOW);
    muted = true;
}

void Radio::unmute() {
    if (!muted) {
        return;
    }
    Serial.println("Unmute");
    digitalWrite(mutePin, HIGH);
    delay(100);
    digitalWrite(mutePin, LOW);
    muted = false;
}

void Radio::setMute(bool state) {
    if (state) {
        mute();
    } else {
        unmute();
    }
}

bool Radio::isMuted() const {
    return muted;
}