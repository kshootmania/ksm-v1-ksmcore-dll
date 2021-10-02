// ksmcore.cpp: DLL interface for K-Shoot Mania v1.xx
#include "ksmcore_dll.h"

#include <string>
#include <cstring>
#include <cstdint>
#include "ksm_core.hpp"
#include "game_system.hpp"
#include "key_sound.hpp"

using namespace ksmcore;

namespace
{
    // Version of ksmcore-dll
    //   Examples:
    //     v1.70  => 1700
    //     v1.70b => 1702
    constexpr int kKSMCoreVersion = 1702;
}

int KSMCore_GetVersion()
{
    return kKSMCoreVersion;
}

int KSMCore_Init(ksmcore::KSMCore **pRet)
{
    pRet = nullptr;

    try
    {
        *pRet = new KSMCore;
        return 1;
    }
    catch (...)
    {
        delete *pRet;
        return 0;
    }
}

void KSMCore_Terminate(ksmcore::KSMCore *pKSMCore)
{
    delete pKSMCore;
}

void KSMCore_Update(ksmcore::KSMCore *pKSMCore, double uptimeMs)
{
    if (pKSMCore == nullptr)
    {
        return;
    }

    pKSMCore->update(uptimeMs);
}

int CreateGameSystem(const char *chartFilename, double initialMs, GameSystem **pRet)
{
    pRet = nullptr;

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

void DestroyGameSystem(GameSystem *pGameSystem)
{
    delete pGameSystem;
}

void UpdateGameSystem(GameSystem *pGameSystem, double currentMs)
{
    if (pGameSystem == nullptr)
    {
        return;
    }

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
    if (pKeySound == nullptr)
    {
        return;
    }

    pKeySound->play(volume);
}

int StartsWith(const char *pStr, const char *pHead)
{
    const auto headLength = std::strlen(pHead);
    return std::strlen(pStr) >= headLength && std::strncmp(pStr, pHead, headLength) == 0;
}
