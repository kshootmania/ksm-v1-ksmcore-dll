#pragma once
#include <string_view>
#include "ksh/beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"
#include "scene/iscene.hpp"
#include "scene/play_scene/camera.hpp"

namespace ksmcore
{

    class PlayScene : public IScene
    {
    private:
        const ksh::PlayableChart m_chart;
        Camera m_camera;

    public:
        PlayScene(std::string_view chartFilename, Ms initialMs);
        ~PlayScene() = default;

        void update(Ms currentMs);

        const Camera & camera() const;
    };

}
