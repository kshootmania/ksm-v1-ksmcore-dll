#include "song_selection/list.hpp"
#include "song_selection/song_item.hpp"
#include "song_selection/heading_item.hpp"

namespace SongSelection
{

    List::List(const fs::path & path, bool isRoot)
    {
        if (isRoot)
        {
            // Root directory ("song/")
            for (const auto & entry : fs::directory_iterator(path))
            {
                if (entry.is_directory())
                {
                    m_items.push_back(
                        std::make_unique<DirectoryItem>(entry.path().filename().u8string(), entry.path()) // TODO: Consider foldername.csv
                    );
                }
            }
        }
        else
        {
            // Package directory ("song/xxx/")
            for (const auto & entry : fs::directory_iterator(path))
            {
                bool subDirectoryHeadingAdded = false;
                if (entry.is_directory())
                {
                    auto songItem = std::make_unique<SongItem>(entry.path().u8string());
                    if (!songItem->empty())
                    {
                        // Chart(s) found
                        m_items.push_back(std::move(songItem));
                    }
                    else
                    {
                        // Chart not found
                        for (const auto & e : fs::directory_iterator(path))
                        {
                            if (e.is_directory())
                            {
                                // If the directory has only folders, recognize it as a sub-folder
                                if (!subDirectoryHeadingAdded)
                                {
                                    m_items.push_back(
                                        std::make_unique<HeadingItem>(entry.path().parent_path().filename().u8string()) // TODO: Consider foldername.csv
                                    );
                                    subDirectoryHeadingAdded = true;
                                }

                                auto subSongItem = std::make_unique<SongItem>(e.path().u8string());
                                if (!subSongItem->empty())
                                {
                                    m_items.push_back(std::move(subSongItem));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    std::string List::getDebugString() const
    {
        std::string ret;
        for (const auto & item : m_items)
        {
            ret += item->getDebugString() + "\n";
        }
        return ret;
    }

}
