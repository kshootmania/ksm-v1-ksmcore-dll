#pragma once
#include "ksh/beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"

class Camera
{
private:
    const ksh::PlayableChart * const m_pChart;
    const Ms m_zoomRelaxationTime;
    Ms m_prevMs;
    Measure m_prevMeasure;

    double m_currentZoomTop;
    double m_currentZoomBottom;
    double m_currentZoomSide;
    double m_currentCenterSplit;
    double m_currentManualTilt;

public:
    Camera(const ksh::PlayableChart *pChart, Ms initialMs);
    ~Camera() = default;

    void update(Ms currentMs);

    // Returns current camera value
    double currentZoomTop() const;
    double currentZoomBottom() const;
    double currentZoomSide() const;
    double currentCenterSplit() const;
    double currentManualTilt() const;
};
