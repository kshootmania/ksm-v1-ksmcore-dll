#pragma once
#include <vector>
#include <string>
#include "bass.h"

namespace ksmcore
{

    class BGMPlayer
    {
    private:
        const std::vector<HSTREAM> m_hStreams;

    public:
        BGMPlayer(const std::string & filename);
        ~BGMPlayer();

        void play();
    };

}
