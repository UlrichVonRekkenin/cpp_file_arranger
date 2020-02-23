#include <iostream>
#include "source/sorter.h"


int main(int argc, char* argv[])
{
    if (argc>1) {
        Sorter::sort(argv[1], argc==2 ? argv[2] : argv[1]);
    }
    else {
        std::cout << "Usage:\n\t sorter directory_/to_/sort [directory_/to_/move_/files]\n\n"
                     "Example 1:\n\tsorted ~/Downloads\n"
                     "move all files from '~/Downloads/` dir to the same folder "
                     "but files were arranged by folders.\n\n"
                     "Example 2:\n\tsorted ~/Downloads /path/to/other/folder\n"
                     "move all files from '~/Downloads/` dir to another folder.";
    }

    return 0;
}
