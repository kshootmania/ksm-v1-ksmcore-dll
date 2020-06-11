#include "song_selection/song_item.hpp"

namespace SongSelection
{

    namespace
    {
        std::array<std::unique_ptr<ksh::Chart>, SongItem::DIFFICULTY_COUNT> loadCharts(const fs::path & path)
        {
            std::array<std::unique_ptr<ksh::Chart>, SongItem::DIFFICULTY_COUNT> charts;
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
    }

    SongItem::SongItem(const fs::path & path)
        : m_charts(loadCharts(path))
    {
    }

    bool SongItem::empty() const
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
    
    std::string SongItem::getDebugString() const
    {
        bool chartExists = false;
        std::string ret = "(song) ";
        for (const auto & chart : m_charts)
        {
            if (chart && chart->metaData.count("title") > 0 && chart->metaData.count("level") > 0)
            {
                ret += std::string("[") + chart->metaData.at("title") + " Lv" + chart->metaData.at("level") + "] ";
                chartExists = true;
            }
        }
        if (!chartExists)
        {
            ret = "[none] ";
        }
        return ret;
    }

}