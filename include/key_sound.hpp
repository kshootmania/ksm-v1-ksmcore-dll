#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include "bass.h"

class KeySound
{
private:
    const HSAMPLE m_hSample;
    const std::vector<HCHANNEL> m_hChannels;
    DWORD m_hChannelCursor;

public:
    KeySound(const std::string & filename, DWORD max); // Note: max must be between 1 and 65535
    ~KeySound();

    void play(double volume = 1.0);

    void stop();
};
