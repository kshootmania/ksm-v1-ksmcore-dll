#include "game_system.hpp"
#include <string>

namespace ksmcore
{

    GameSystem::GameSystem(std::string_view chartFilename, Ms initialMs)
        : m_chart(chartFilename)
        , m_bgmPlayer(m_chart.metaData.count("m") ? m_chart.metaData.at("m") : std::string())
        , m_camera(&m_chart, initialMs)
    {
    }

    void GameSystem::update(Ms currentMs)
    {
        m_camera.update(currentMs);
    }

    const Camera & GameSystem::camera() const
    {
        return m_camera;
    }

}
