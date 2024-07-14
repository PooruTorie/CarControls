#include "Arduino.h"

#include "defines.h"

#include "Radio.h"
#include "RotaryEncoder.h"

RotaryEncoder encoder(ENCODER_PIN_A, ENCODER_PIN_B, RotaryEncoder::LatchMode::FOUR3);
Radio radio(VOLUME_UP_PIN, VOLUME_DOWN_PIN, TRACK_UP_PIN, TRACK_DOWN_PIN, MUTE_PIN);

void setup() {
    Serial.begin(115200);

    Serial.println("Starting");
}

int t, buttonTime, buttonActive;
RotaryEncoder::Direction currentDirection;

void loop() {
    encoder.tick();

    RotaryEncoder::Direction direction = encoder.getDirection();
    bool buttonState = digitalRead(ENCODER_PIN_A);

    if (direction == RotaryEncoder::Direction::NOROTATION && buttonState) {
        if (buttonTime > 1) {
            buttonTime--;
        } else if (buttonTime == 1) {
            buttonActive = 2000;
        }
        buttonTime = 200;
    }

    if (t > 300 || direction != RotaryEncoder::Direction::NOROTATION) {
        t = 0;
        if (currentDirection != direction) {
            if (direction == RotaryEncoder::Direction::CLOCKWISE) {
                if (buttonActive > 0) {
                    radio.trackUp();
                } else {
                    if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
                        radio.volumeDownStop();
                    }
                    currentDirection = direction;
                    radio.volumeUpStart();
                }
            } else if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
                if (buttonActive > 0) {
                    radio.trackDown();
                } else {
                    if (currentDirection == RotaryEncoder::Direction::CLOCKWISE) {
                        radio.volumeUpStop();
                    }
                    currentDirection = direction;
                    radio.volumeDownStart();
                }
            } else {
                if (currentDirection == RotaryEncoder::Direction::CLOCKWISE) {
                    radio.volumeUpStop();
                    currentDirection = RotaryEncoder::Direction::NOROTATION;
                } else if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
                    radio.volumeDownStop();
                    currentDirection = RotaryEncoder::Direction::NOROTATION;
                }
            }
        }
    }

    if (buttonActive > 0) {
        buttonActive--;
    }

    t++;
    delay(1);
}