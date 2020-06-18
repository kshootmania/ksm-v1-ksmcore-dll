#include "key_sound.hpp"

namespace
{
    std::vector<HCHANNEL> loadChannels(HSAMPLE hSample, DWORD max)
    {
        std::vector<HCHANNEL> hChannels;
        hChannels.reserve(max);

        for (DWORD i = 0; i < max; ++i)
        {
            hChannels.push_back(BASS_SampleGetChannel(hSample, TRUE));
        }

        return hChannels;
    }
}

KeySound::KeySound(const std::string & filename, DWORD max)
    : m_hSample(BASS_SampleLoad(false, filename.c_str(), 0, 0, max, 0))
    , m_hChannels(loadChannels(m_hSample, max))
    , m_hChannelCursor(0)
{
}

KeySound::~KeySound()
{
    BASS_SampleFree(m_hSample);
}

void KeySound::play()
{
    // Not simply using BASS_SampleGetChannel and BASS_ChannelPlay
    // in order to give higher priority to later plays
    BASS_ChannelPlay(m_hChannels[m_hChannelCursor], TRUE);
    if (++m_hChannelCursor >= static_cast<DWORD>(m_hChannels.size()))
    {
        m_hChannelCursor = 0;
    }
}

void KeySound::stop()
{
    BASS_SampleStop(m_hSample);
}
