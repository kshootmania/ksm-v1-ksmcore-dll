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

        virtual std::string getDebugString() const
        {
            std::string ret = "(song) ";
            for (const auto & chart : m_charts)
            {
                if (chart.has_value() && chart->metaData.count("title") > 0 && chart->metaData.count("level") > 0)
                {
                    ret += std::string("[") + chart->metaData.at("title") + " Lv" + chart->metaData.at("level") + "] ";
                }
                else
                {
                    ret = "[none] ";
                }
            }
            return ret;
        }
    };

}
