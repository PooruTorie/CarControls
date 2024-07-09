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

int t;
RotaryEncoder::Direction currentDirection;

void loop() {
    encoder.tick();

    RotaryEncoder::Direction direction = encoder.getDirection();

    if (t > 200 || direction != RotaryEncoder::Direction::NOROTATION) {
        t = 0;
        if (currentDirection != direction) {
            if (direction == RotaryEncoder::Direction::CLOCKWISE) {
                if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
                    radio.volumeDownStop();
                }
                currentDirection = direction;
                radio.volumeUpStart();
            } else if (direction == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
                if (currentDirection == RotaryEncoder::Direction::CLOCKWISE) {
                    radio.volumeUpStop();
                }
                currentDirection = direction;
                radio.volumeDownStart();
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

    t++;
    delay(1);
}