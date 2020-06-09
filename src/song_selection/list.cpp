#include "song_selection/list.hpp"

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
                if (entry.is_directory())
                {
                    // Song directory
                    for (const auto & e : fs::directory_iterator(path))
                    {
                        if (e.is_directory())
                        {
                            // TODO: Insert sub-directory
                        }
                        else if (e.path().extension() == ".ksh") // TODO: Consider upper case
                        {
                            // TODO: Insert SongItem
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
