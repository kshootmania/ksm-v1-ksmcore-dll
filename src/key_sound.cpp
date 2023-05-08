#include "key_sound.hpp"

namespace ksmcore
{
    KeySound::KeySound(const std::string & filename, DWORD max)
        : m_hSample(BASS_SampleLoad(false, filename.c_str(), 0, 0, max, BASS_SAMPLE_OVER_POS))
    {
    }

    KeySound::~KeySound()
    {
        BASS_SampleFree(m_hSample);
    }

    void KeySound::play(double volume)
    {
        const auto hChannel = BASS_SampleGetChannel(m_hSample, 0);
        BASS_ChannelSetAttribute(hChannel, BASS_ATTRIB_VOL, static_cast<float>(volume));
        BASS_ChannelPlay(hChannel, TRUE);
    }

    void KeySound::stop()
    {
        BASS_SampleStop(m_hSample);
    }

}
