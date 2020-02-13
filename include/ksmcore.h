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

class GameSystem;

DLL_EXPORT bool CreateGameSystem(const char *chartFilename, double initialMs, GameSystem **pRet);

DLL_EXPORT void DestroyGameSystem(GameSystem *pGameSystem);

DLL_EXPORT void UpdateGameSystem(GameSystem *pGameSystem, int currentMs);

DLL_EXPORT void GetCurrentCamValue(GameSystem *pGameSystem, CamParam camParam, double *pRet);

#undef DLL_EXPORT
