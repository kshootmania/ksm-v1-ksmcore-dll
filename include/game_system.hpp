#pragma once
#include <string_view>
#include "ksh/beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"
#include "camera.hpp"

namespace ksmcore
{

    class GameSystem
    {
    private:
        const ksh::PlayableChart m_chart;
        BGMPlayer m_bgmPlayer;
        Camera m_camera;

    public:
        GameSystem(std::string_view chartFilename, Ms initialMs);
        ~GameSystem() = default;

        void update(Ms currentMs);

        const Camera & camera() const;
    };

}
