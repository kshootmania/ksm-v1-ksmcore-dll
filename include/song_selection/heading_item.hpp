#pragma once
#include <string>
#include "item.hpp"

namespace SongSelection
{

    class HeadingItem : public AbstractItem
    {
    private:
        const std::string m_title;

    public:
        explicit HeadingItem(const std::string & title)
            : m_title(title)
        {
        }

        virtual ~HeadingItem() = default;
        
        std::string title() const
        {
            return m_title;
        }
        
        virtual std::string getDebugString() const
        {
            return std::string("(heading) ") + m_title;
        }
    };

}
