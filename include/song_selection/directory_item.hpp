#pragma once
#include <string>
#include "ksh/chart.hpp"
#include "item.hpp"

namespace SongSelection
{

    class DirectoryItem : public AbstractItem
    {
    private:
        const std::string m_title;
        const fs::path m_path;

    public:
        DirectoryItem(const std::string & title, const fs::path & path)
            : m_title(title)
            , m_path(path)
        {
        }

        virtual ~DirectoryItem() = default;
    };

}
