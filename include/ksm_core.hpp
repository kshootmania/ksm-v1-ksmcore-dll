#pragma once

namespace ksmcore
{

    class KSMCore
    {
    public:
        KSMCore();
        ~KSMCore() = default;

        void update(double uptimeMs);
    };

}
