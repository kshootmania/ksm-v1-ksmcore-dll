#pragma once
#include <memory>
#include <vector>
#include <filesystem>
#include "item.hpp"
#include "directory_item.hpp"

namespace SongSelection
{
    using fs = std::filesystem;

    class List
    {
    private:
        std::vector<std::unique_ptr<AbstractItem>> m_items; // TODO: Make this const

    public:
        explicit List(const fs::path & path, bool isRoot);

        ~List() = default;
    };

}
