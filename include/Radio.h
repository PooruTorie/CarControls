//
// Created by paulm on 11.06.2024.
//

#ifndef AUTORADIO_RADIO_H
#define AUTORADIO_RADIO_H

#include "Arduino.h"

#include "defines.h"

class Radio {
private:
    int volumeUpPin;
    int volumeDownPin;
    int trackUpPin;
    int trackDownPin;
    int mutePin;
    bool muted;
public:
    Radio(int volumeUpPin, int volumeDownPin, int trackUpPin, int trackDownPin, int mutePin);

    void volumeUpStart() const;

    void volumeUpStop() const;

    void volumeDownStart() const;

    void volumeDownStop() const;

    void volumeUp() const;

    void volumeDown() const;

    void trackUp() const;

    void trackDown() const;

    void mute();

    void unmute();

    void setMute(bool mute);

    [[nodiscard]] bool isMuted() const;
};


#endif //AUTORADIO_RADIO_H
