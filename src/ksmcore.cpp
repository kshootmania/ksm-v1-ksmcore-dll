#include "ksmcore.h"

#ifdef _MSC_VER
#pragma warning(disable:4514)
#pragma warning(disable:4711)
#endif

#include <string>
#include <cstring>
#include <cstdint>
#include "game_system.hpp"
#include "key_sound.hpp"

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

#include <stdio.h>
#include <errno.h>
#include <Windows.h>
#include <OleCtl.h>
#include <comdef.h>

void WinMessageBox(const std::string & str, const std::string & caption = "")
{
    MessageBoxA(NULL, str.c_str(), caption.c_str(), MB_OK);
}

void WinMessageBoxW(const WCHAR *str)
{
    MessageBoxW(NULL, str, L"", MB_OK);
}

void TryFopen(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        WinMessageBox("fopen failed!");
        return;
    }
    WinMessageBox("fopen success!");

    fseek(fp, 0, SEEK_END);
    int size = (int)ftell(fp);

    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, size);
    if (h == NULL)
    {
        WinMessageBox("GlobalAlloc failed!");
        fclose(fp);
        return;
    }
    WinMessageBox("GlobalAlloc success!");

    void *pBuf = GlobalLock(h);
    if (pBuf == NULL)
    {
        WinMessageBox("GlobalLock failed!");
        fclose(fp);
        GlobalFree(h);
        return;
    }
    WinMessageBox("GlobalLock success!");

    fseek(fp, 0, SEEK_SET);
    int a1 = fread((char *)pBuf, 1, size, fp);
    if (a1 <= 0)
    {
        WinMessageBox("fread failed!");
        fclose(fp);
        GlobalUnlock(h);
        GlobalFree(h);
        return;
    }
    WinMessageBox("fread success!");
    fclose(fp);
    GlobalUnlock(h);

    LPSTREAM pstm;
    {
        HRESULT hr = CreateStreamOnHGlobal(h, TRUE, &pstm);
        if (!SUCCEEDED(hr))
        {
            WinMessageBox("CreateStreamOnHGlobal failed!");
            GlobalFree(h);
            return;
        }
    }

    LPPICTURE gpPicture;
    {
        HRESULT hr = OleLoadPicture(pstm, size, FALSE, IID_IPicture, (LPVOID *)&gpPicture);
        if (!SUCCEEDED(hr))
        {
            WinMessageBox("OleLoadPicture failed!");
            WinMessageBox(std::to_string(hr));
            _com_error err(hr);
            const char *errMsg = (const char *)err.ErrorMessage();
            WinMessageBox(errMsg);
            GlobalFree(h);
            return;
        }
    }
    long hmWidth, hmHeight;
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);
    WinMessageBox(std::string("OleLoadPicture success! (") + std::to_string(hmWidth) + "x" + std::to_string(hmHeight) + ")");

    pstm->Release();
    gpPicture->Release();
    GlobalFree(h);
}
