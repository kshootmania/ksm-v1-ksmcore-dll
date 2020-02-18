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
        const std::string m_path;

    public:
        DirectoryItem(const std::string & title, const std::string & path)
            : m_title(title)
            , m_path(path)
        {
        }

        virtual ~DirectoryItem() = default;
    };

}
