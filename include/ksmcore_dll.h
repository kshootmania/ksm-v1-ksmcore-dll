// ksmcore_dll.h: DLL interface for K-Shoot Mania v1.xx
#pragma once

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C" __attribute__((visibility ("default")))
#endif

enum CamParam
{
    CAM_ZOOM_TOP = 0,
    CAM_ZOOM_BOTTOM,
    CAM_ZOOM_SIDE,
    CAM_CENTER_SPLIT,
    CAM_MANUAL_TILT,
};

namespace ksmcore
{
    class KSMCore;
    class GameSystem;
    class KeySound;
}

DLL_EXPORT int KSMCore_GetVersion();

DLL_EXPORT int KSMCore_Init(ksmcore::KSMCore **pRet);

DLL_EXPORT void KSMCore_Terminate(ksmcore::KSMCore *pKSMCore);

DLL_EXPORT void KSMCore_Update(ksmcore::KSMCore *pKSMCore, double uptimeMs);

// TODO: Add "KSMCore_" prefix to every function name

DLL_EXPORT int CreateGameSystem(const char *chartFilename, double initialMs, ksmcore::GameSystem **pRet);

DLL_EXPORT void DestroyGameSystem(ksmcore::GameSystem *pGameSystem);

DLL_EXPORT void UpdateGameSystem(ksmcore::GameSystem *pGameSystem, double currentMs);

DLL_EXPORT void GetCurrentCamValue(ksmcore::GameSystem *pGameSystem, CamParam camParam, double *pRet);

DLL_EXPORT int CreateKeySound(const char *filename, int max, ksmcore::KeySound **pRet);

DLL_EXPORT void DestroyKeySound(ksmcore::KeySound *pKeySound);

DLL_EXPORT void PlayKeySound(ksmcore::KeySound *pKeySound, double volume);

DLL_EXPORT int StartsWith(const char *pStr, const char *pHead);

#undef DLL_EXPORT
