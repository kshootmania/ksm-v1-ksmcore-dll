#include <iostream>
#include "song_selection/list.hpp"

int main()
{
    SongSelection::List list("./song/", true);
    std::cout << list.getDebugString() << std::endl;
    return 0;
}
