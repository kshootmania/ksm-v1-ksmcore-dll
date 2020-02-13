#include "ksmcore.h"

#include <string>
#include <cstdint>
#include "game_system.hpp"

bool CreateGameSystem(const char *chartFilename, double initialMs, GameSystem **pRet)
{
    try
    {
        *pRet = new GameSystem(chartFilename, initialMs);
        return true;
    }
    catch (...)
    {
        delete *pRet;
        return false;
    }
}

void DestroyGameSystem(GameSystem *pGameSystem)
{
    delete pGameSystem;
}

void UpdateGameSystem(GameSystem *pGameSystem, double currentMs)
{
    pGameSystem->update(currentMs);
}

void GetCurrentCamValue(GameSystem *pGameSystem, CamParam camParam, double *pRet)
{
    switch (camParam)
    {
    case CAM_ZOOM_TOP:
        *pRet = pGameSystem->currentZoomTop();
        break;

    case CAM_ZOOM_BOTTOM:
        *pRet = pGameSystem->currentZoomBottom();
        break;

    case CAM_ZOOM_SIDE:
        *pRet = pGameSystem->currentZoomSide();
        break;

    case CAM_CENTER_SPLIT:
        *pRet = pGameSystem->currentCenterSplit();
        break;

    case CAM_MANUAL_TILT:
        *pRet = pGameSystem->currentManualTilt();
        break;
    }
}
