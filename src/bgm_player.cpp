#include "bgm_player.hpp"

namespace ksmcore
{

    BGMPlayer::BGMPlayer(const std::string & filename)
        , m_hStreams(/* TODO: create stream */)
    {
    }

    BGMPlayer::~BGMPlayer()
    {
        for (const auto & hStream : m_hStreams)
        {
            BASS_StreamFree(hStream);
        }
    }

    void BGMPlayer::play()
    {
        BASS_ChannelPlay(m_hChannels[m_hChannelCursor], TRUE);
    }

}
