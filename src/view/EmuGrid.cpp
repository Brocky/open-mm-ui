#include <string.h>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include "EmuGrid.h"
namespace fs = std::filesystem;

const std::string emu_path = "/mnt/SDCARD/Emu";

void EmuGrid::buildIndex()
{
    for (const auto &entry : fs::directory_iterator(emu_path)) {
        if (!entry.is_directory()) {
            continue;
        }
        
        std::string name = entry.path().stem().string();
        this->items.push_back({this->getIconPath(name), name});
    }
}

std::string EmuGrid::getIconPath(std::string name)
{
    // transform name to lower case
    std::for_each(
        name.begin(),
        name.end(),
        [](char &c){
            c = std::tolower(c);
        }
    );
    return "/mnt/SDCARD/Icons/" + name + ".png";
}

EmuGrid::~EmuGrid()
{
    this->items.clear();
}
