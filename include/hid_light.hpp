#pragma once
#include <memory>
#include <hidapi.h>
#include "ksh/beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"

namespace ksmcore
{
    struct HidLightState;

    // Note: This class calls hid_init() in ctor and hid_exit() in dtor, so do not create multiple instances of this class.
    class HidLight
    {
    private:
        std::unique_ptr<HidLightState> m_state;

        hid_device * const m_pDevice;

    public:
        struct Color
        {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
        };

        HidLight();
        ~HidLight();

        // Set the color of all top lights
        void setTopLightColor(const Color & color);

        // Set the color of a single top light
        void setTopLightColor(int idx, const Color & color);

        // Set the color of all side lights
        void setSideLightColor(const Color & color);

        // Set the brightness of a single BT button light
        void setBTButtonBrightness(int idx, unsigned char brightness);

        // Set the brightness of a single FX button light
        void setFXButtonBrightness(int idx, unsigned char brightness);

        void update();
    };

}
