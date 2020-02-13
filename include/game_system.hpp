#pragma once
#include <string_view>
#include "beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"

class GameSystem
{
private:
    const ksh::PlayableChart m_chart;
    const Ms m_zoomRelaxationTime;
    Ms m_prevMs;
    Measure m_prevMeasure;

    // TODO: Move these camera implementation to another class
    double m_currentZoomTop;
    double m_currentZoomBottom;
    double m_currentZoomSide;
    double m_currentCenterSplit;
    double m_currentManualTilt;

public:
    GameSystem(std::string_view chartFilename, Ms initialMs);
    ~GameSystem() = default;

    void update(Ms currentMs);

    // Returns current camera value
    double currentZoomTop() const;
    double currentZoomBottom() const;
    double currentZoomSide() const;
    double currentCenterSplit() const;
    double currentManualTilt() const;
};
