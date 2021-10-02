#include "scene/play_scene.hpp"

namespace ksmcore
{

    PlayScene::PlayScene(std::string_view chartFilename, Ms initialMs)
        : m_chart(chartFilename)
        , m_camera(&m_chart, initialMs)
    {
    }

    void PlayScene::update(Ms currentMs)
    {
        m_camera.update(currentMs);
    }

    const Camera & PlayScene::camera() const
    {
        return m_camera;
    }

}
