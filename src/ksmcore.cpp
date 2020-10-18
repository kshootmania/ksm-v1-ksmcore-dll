// ksmcore.cpp: DLL interface for K-Shoot Mania v1.xx
#include "ksmcore.h"

#include <string>
#include <cstring>
#include <cstdint>
#include "game_system.hpp"
#include "key_sound.hpp"

using namespace ksmcore;

int CreateGameSystem(const char *chartFilename, double initialMs, GameSystem **pRet)
{
    try
    {
        *pRet = new GameSystem(chartFilename, initialMs);
        return 1;
    }
    catch (...)
    {
        delete *pRet;
        return 0;
    }
}

int KSMCore_GetVersion()
{
    return KSMCORE_VERSION;
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
    const auto & camera = pGameSystem->camera();
    switch (camParam)
    {
    case CAM_ZOOM_TOP:
        *pRet = camera.currentZoomTop();
        break;

    case CAM_ZOOM_BOTTOM:
        *pRet = camera.currentZoomBottom();
        break;

    case CAM_ZOOM_SIDE:
        *pRet = camera.currentZoomSide();
        break;

    case CAM_CENTER_SPLIT:
        *pRet = camera.currentCenterSplit();
        break;

    case CAM_MANUAL_TILT:
        *pRet = camera.currentManualTilt();
        break;
    }
}

int CreateKeySound(const char *filename, int max, KeySound **pRet)
{
    try
    {
        *pRet = new KeySound(filename, static_cast<DWORD>(max));
        return 1;
    }
    catch (...)
    {
        delete *pRet;
        return 0;
    }
}

void DestroyKeySound(KeySound *pKeySound)
{
    delete pKeySound;
}

void PlayKeySound(KeySound *pKeySound, double volume)
{
    pKeySound->play(volume);
}

int StartsWith(const char *pStr, const char *pHead)
{
    const auto headLength = std::strlen(pHead);
    return std::strlen(pStr) >= headLength && std::strncmp(pStr, pHead, headLength) == 0;
}
