#pragma once
#include <memory>
#include "ksh/beat_map/beat_map.hpp"
#include "ksh/playable_chart.hpp"

struct hid_device;

namespace ksmcore
{

    // Note: This class does not call hid_init() and hid_exit(), so call them yourself.
    class HidLight
    {
    private:
        struct State;
        std::unique_ptr<State> m_state;

        const hid_device *m_pDevice;

    public:
        struct Color
        {
            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;
        };

        HidLight();
        ~HidLight() = default;

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
