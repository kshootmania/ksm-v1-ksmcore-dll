#pragma once
#include <array>
#include <memory>
#include <cstddef>
#include "ksh/chart.hpp"
#include "item.hpp"

namespace SongSelection
{

    class SongItem : public AbstractItem
    {
    public:
        static constexpr std::size_t DIFFICULTY_COUNT = 4;

    private:
        const std::array<std::unique_ptr<const ksh::Chart>, DIFFICULTY_COUNT> m_charts;

    public:
        explicit SongItem(const fs::path & path);

        virtual ~SongItem() = default;

        bool empty() const;

        virtual std::string getDebugString() const;
    };

}
