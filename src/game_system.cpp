#include "game_system.hpp"
#include <algorithm>

constexpr Ms ZOOM_RELAXATION_TIME_LEGACY = 40.0; // ver <  1.67
constexpr Ms ZOOM_RELAXATION_TIME = 1.0;         // ver >= 1.67

namespace
{
    void updateWithRelaxationTime(double & value, double target, Ms relaxationTime, Ms deltaMs)
    {
        const double targetRate = std::min(deltaMs / relaxationTime, 1.0);
        value = value * (1.0 - targetRate) + target * targetRate;
    }
}

GameSystem::GameSystem(std::string_view chartFilename, Ms initialMs)
    : m_chart(chartFilename)
    , m_prevMs(initialMs)
    , m_prevMeasure(m_chart.beatMap().msToMeasure(initialMs))
    , m_zoomRelaxationTime(
        m_chart.isVersionNewerThanOrEqualTo(167)
            ? ZOOM_RELAXATION_TIME
            : ZOOM_RELAXATION_TIME_LEGACY)
    , m_currentZoomTop(m_chart.zoomTop().valueAt(m_prevMeasure))
    , m_currentZoomBottom(m_chart.zoomBottom().valueAt(m_prevMeasure))
    , m_currentZoomSide(m_chart.zoomSide().valueAt(m_prevMeasure))
    , m_currentCenterSplit(m_chart.centerSplit().valueAt(m_prevMeasure))
    , m_currentManualTilt(m_chart.manualTilt().valueAt(m_prevMeasure))
{
}

void GameSystem::update(Ms currentMs)
{
    const Measure currentMeasure = m_chart.beatMap().msToMeasure(currentMs);
    const Ms deltaMs = currentMs - m_prevMs;

    // Update camera zoom values
    const double targetZoomTop = m_chart.zoomTop().valueAt(currentMeasure);
    updateWithRelaxationTime(m_currentZoomTop, targetZoomTop, m_zoomRelaxationTime, deltaMs);
    const double targetZoomBottom = m_chart.zoomBottom().valueAt(currentMeasure);
    updateWithRelaxationTime(m_currentZoomBottom, targetZoomBottom, m_zoomRelaxationTime, deltaMs);
    const double targetZoomSide = m_chart.zoomSide().valueAt(currentMeasure);
    updateWithRelaxationTime(m_currentZoomSide, targetZoomSide, m_zoomRelaxationTime, deltaMs);

    // Update center_split values
    m_currentCenterSplit = m_chart.centerSplit().valueAt(currentMeasure);

    // Update manual tilt values
    m_currentManualTilt = m_chart.manualTilt().valueAt(currentMeasure);

    // Store current time and measure as previous ones
    m_prevMs = currentMs;
    m_prevMeasure = currentMeasure;
}

double GameSystem::currentZoomTop() const
{
    return m_currentZoomTop;
}

double GameSystem::currentZoomBottom() const
{
    return m_currentZoomBottom;
}

double GameSystem::currentZoomSide() const
{
    return m_currentZoomSide;
}

double GameSystem::currentCenterSplit() const
{
    return m_currentCenterSplit;
}

double GameSystem::currentManualTilt() const
{
    return m_currentManualTilt;
}
