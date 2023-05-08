#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include "bass.h"

namespace ksmcore
{

    class KeySound
    {
    private:
        const HSAMPLE m_hSample;

    public:
        KeySound(const std::string & filename, DWORD max); // Note: max must be between 1 and 65535
        ~KeySound();

        void play(double volume = 1.0);

        void stop();
    };

}
