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
        static constexpr std::size_t DIFFICULTY_COUNT = 4;
        static std::array<std::unique_ptr<ksh::Chart>, DIFFICULTY_COUNT> loadCharts(const fs::path & path)
        {
            std::array<std::unique_ptr<ksh::Chart>, DIFFICULTY_COUNT> charts;
            for (const auto & e : fs::directory_iterator(path))
            {
                if (e.path().extension() == ".ksh") // TODO: Consider upper case in Windows
                {
                    auto chart = std::make_unique<ksh::Chart>(e.path().u8string());
                    charts[chart->difficultyIdx()] = std::move(chart);
                }
            }
            return std::move(charts);
        }

        const std::array<std::unique_ptr<ksh::Chart>, DIFFICULTY_COUNT> m_charts;

    public:
        explicit SongItem(const fs::path & path)
            : m_charts(loadCharts(path))
        {
        }

        virtual ~SongItem() = default;

        bool empty() const
        {
            bool ret = true;
            for (const auto & c : m_charts)
            {
                if (c)
                {
                    ret = false;
                    break;
                }
            }
            return ret;
        }

        virtual std::string getDebugString() const
        {
            std::string ret = "(song) ";
            for (const auto & chart : m_charts)
            {
                if (chart && chart->metaData.count("title") > 0 && chart->metaData.count("level") > 0)
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
