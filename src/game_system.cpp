#include "game_system.hpp"

GameSystem::GameSystem(std::string_view chartFilename, Ms initialMs)
    : m_chart(chartFilename)
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
