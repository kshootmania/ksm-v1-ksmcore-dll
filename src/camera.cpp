#include "play_scene.hpp"
#include <algorithm>

namespace ksmcore
{

    namespace
    {
        constexpr int ZOOM_RELAXATION_CHANGED_KSH_VERSION = 167;
        constexpr Ms ZOOM_RELAXATION_TIME_LEGACY = 40.0; // ver <  1.67
        constexpr Ms ZOOM_RELAXATION_TIME = 1.0;         // ver >= 1.67

        void updateWithRelaxationTime(double & value, double target, Ms relaxationTime, Ms deltaMs)
        {
            const double targetRate = std::min(deltaMs / relaxationTime, 1.0);
            value = value * (1.0 - targetRate) + target * targetRate;
        }
    }

    Camera::Camera(const ksh::PlayableChart *pChart, Ms initialMs)
        : m_pChart(pChart)
        , m_zoomRelaxationTime(
            pChart->isKshVersionNewerThanOrEqualTo(ZOOM_RELAXATION_CHANGED_KSH_VERSION)
                ? ZOOM_RELAXATION_TIME
                : ZOOM_RELAXATION_TIME_LEGACY)
        , m_prevMs(initialMs)
        , m_prevMeasure(m_pChart->beatMap().msToMeasure(initialMs))
        , m_currentZoomTop(m_pChart->zoomTop().valueAt(m_prevMeasure))
        , m_currentZoomBottom(m_pChart->zoomBottom().valueAt(m_prevMeasure))
        , m_currentZoomSide(m_pChart->zoomSide().valueAt(m_prevMeasure))
        , m_currentCenterSplit(m_pChart->centerSplit().valueAt(m_prevMeasure))
        , m_currentManualTilt(m_pChart->manualTilt().valueAt(m_prevMeasure))
    {
    }

    void Camera::update(Ms currentMs)
    {
        const Measure currentMeasure = m_pChart->beatMap().msToMeasure(currentMs);
        const Ms deltaMs = currentMs - m_prevMs;

        // Update camera zoom values
        const double targetZoomTop = m_pChart->zoomTop().valueAt(currentMeasure);
        updateWithRelaxationTime(m_currentZoomTop, targetZoomTop, m_zoomRelaxationTime, deltaMs);
        const double targetZoomBottom = m_pChart->zoomBottom().valueAt(currentMeasure);
        updateWithRelaxationTime(m_currentZoomBottom, targetZoomBottom, m_zoomRelaxationTime, deltaMs);
        const double targetZoomSide = m_pChart->zoomSide().valueAt(currentMeasure);
        updateWithRelaxationTime(m_currentZoomSide, targetZoomSide, m_zoomRelaxationTime, deltaMs);

        // Update center_split values
        m_currentCenterSplit = m_pChart->centerSplit().valueAt(currentMeasure);

        // Update manual tilt values
        m_currentManualTilt = m_pChart->manualTilt().valueAt(currentMeasure);

        // Store current time and measure as previous ones
        m_prevMs = currentMs;
        m_prevMeasure = currentMeasure;
    }

    double Camera::currentZoomTop() const
    {
        return m_currentZoomTop;
    }

    double Camera::currentZoomBottom() const
    {
        return m_currentZoomBottom;
    }

    double Camera::currentZoomSide() const
    {
        return m_currentZoomSide;
    }

    double Camera::currentCenterSplit() const
    {
        return m_currentCenterSplit;
    }

    double Camera::currentManualTilt() const
    {
        return m_currentManualTilt;
    }

}
