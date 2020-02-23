#include "../source/sorter.h"
#include <fstream>


int main()
{
    namespace fs = std::filesystem;

    fs::create_directories("sandbox");
    std::ofstream("sandbox/file.txt");
    std::ofstream("sandbox/file.iso");
    std::ofstream("sandbox/file.mp4");
    std::ofstream("sandbox/homeless.foo");

    Sorter::sort("sandbox", "sandbox");
}