#pragma once
#include <array>
#include <optional>
#include <cstddef>
#include "ksh/chart.hpp"
#include "item.hpp"

namespace SongSelection
{

    class SongItem : public AbstractItem
    {
    private:
        constexpr std::size_t DIFFICULTY_COUNT = 4;
        const std::array<std::optional<ksh::Chart>, DIFFICULTY_COUNT> m_charts;

    public:
        SongItem() = default;
        virtual ~SongItem() = default;
    };

}
