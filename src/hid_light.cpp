#include "hid_light.hpp"

namespace ksmcore
{

    namespace
    {
        constexpr int kTopLightCount = 4;
        constexpr int kBTButtonCount = 4;
        constexpr int kFXButtonCount = 2;

        struct LightState
        {
            const unsigned char reportID = 0;
            HidLight::Color top[kTopLightCount];
            const HidLight::Color unused1;
            HidLight::Color side;
            const HidLight::Color unused2;
            const unsigned char unused3 = 0;
            const unsigned char unused4 = 0;
            const unsigned char unused5 = 0;
        };

        struct ButtonState
        {
            unsigned char bt[kBTButtonCount];
            unsigned char fx[kFXButtonCount];
            unsigned char start = 0;
        };

        hid_device *OpenDevice()
        {
            hid_device_info *pInfo = hid_enumerate(3727, 4376);
            while (pInfo)
            {
                if (pInfo->usage_page == 1 && pInfo->usage == 0)
                {
                    return hid_open_path(pInfo->path);
                }
                pInfo = pInfo->next;
            }

            return nullptr;
        }
    }

    struct HidLightState
    {
        LightState light;
        ButtonState button;
    };

    namespace
    {
        int WriteState(hid_device *pDevice, const HidLightState & state)
        {
            return hid_write(pDevice, reinterpret_cast<const unsigned char *>(&state), sizeof(state));
        }
    }

    HidLight::HidLight()
        : m_state(std::make_unique<HidLightState>())
        , m_pDevice(OpenDevice())
    {
    }

    void HidLight::setTopLightColor(const HidLight::Color & color)
    {
        for (int i = 0; i < kTopLightCount; ++i)
        {
            m_state->light.top[i] = color;
        }
    }

    void HidLight::setTopLightColor(int idx, const HidLight::Color & color)
    {
        if (idx < 0 || idx >= kTopLightCount)
        {
            // Ignore out-of-range index
            return;
        }

        m_state->light.top[idx] = color;
    }

    void HidLight::setSideLightColor(const HidLight::Color & color)
    {
        m_state->light.side = color;
    }

    void HidLight::setBTButtonBrightness(int idx, unsigned char brightness)
    {
        if (idx < 0 || idx >= kBTButtonCount)
        {
            // Ignore out-of-range index
            return;
        }

        m_state->button.bt[idx] = brightness;
    }

    void HidLight::setFXButtonBrightness(int idx, unsigned char brightness)
    {
        if (idx < 0 || idx >= kFXButtonCount)
        {
            // Ignore out-of-range index
            return;
        }

        m_state->button.fx[idx] = brightness;
    }

    void HidLight::update()
    {
        if (m_pDevice == nullptr)
        {
            return;
        }

        WriteState(m_pDevice, *m_state);
    }

}
