#pragma once

#ifdef _WIN32
#define DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define DLL_EXPORT extern "C" __attribute__((visibility ("default")))
#endif

// Version of ksmcore-dll
//   Examples:
//     v1.70  => 1700
//     v1.70b => 1702
static constexpr int KSMCORE_VERSION = 1702;

enum CamParam
{
    CAM_ZOOM_TOP = 0,
    CAM_ZOOM_BOTTOM,
    CAM_ZOOM_SIDE,
    CAM_CENTER_SPLIT,
    CAM_MANUAL_TILT,
};

class GameSystem;
class KeySound;

DLL_EXPORT int KSMCore_GetVersion();

DLL_EXPORT int CreateGameSystem(const char *chartFilename, double initialMs, GameSystem **pRet);

DLL_EXPORT void DestroyGameSystem(GameSystem *pGameSystem);

DLL_EXPORT void UpdateGameSystem(GameSystem *pGameSystem, double currentMs);

DLL_EXPORT void GetCurrentCamValue(GameSystem *pGameSystem, CamParam camParam, double *pRet);

DLL_EXPORT int CreateKeySound(const char *filename, int max, KeySound **pRet);

DLL_EXPORT void DestroyKeySound(KeySound *pKeySound);

DLL_EXPORT void PlayKeySound(KeySound *pKeySound, double volume);

DLL_EXPORT int StartsWith(const char *pStr, const char *pHead);

#undef DLL_EXPORT
