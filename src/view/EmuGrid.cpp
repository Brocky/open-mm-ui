#include <string.h>
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
        std::string conf_path = entry.path().string() + "config.json";
        this->items.push_back(new Emu(conf_path));
    }
}

EmuGrid::~EmuGrid()
{
    this->items.clear();
}
