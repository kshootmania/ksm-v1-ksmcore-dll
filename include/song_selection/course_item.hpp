#pragma once
#include <vector>
#include <string>
#include "ksh/chart.hpp"
#include "item.hpp"

namespace SongSelection
{

    class CourseItem : public AbstractItem
    {
    private:
        const std::string m_title;
        const std::vector<ksh::Chart> m_charts;

    public:
        explicit CourseItem(const std::string & kcoFilename)
        {
            // TODO: Load .kco file
        }

        virtual ~CourseItem() = default;
        
        virtual std::string getDebugString() const
        {
            return std::string("(course) ") + m_title;
        }
    };

}
