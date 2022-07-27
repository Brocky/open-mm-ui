#include "Emu.h"

std::vector<std::string> config_keys = {
	"\"vol\"",
    "\"keymap\"",
    "\"mute\"",
    "\"bgmvol\"",
    "\"brightness\"",
    "\"language\"",
    "\"hibernate\"",
	"\"lumination\"",
    "\"hue\"",
    "\"saturation\"",
    "\"contrast\"",
    "\"theme\"",
    "\"fontsize\"",
    "\"audiofix\""
};

Emu::Emu(std::string config_path)
{
    this->config = readPlainJSON(config_path, config_keys);
}

GridItem Emu::toGridItem()
{
    return {this->config[EmuConfigKeys::IMG_PATH], this->config[EmuConfigKeys::LABEL]};
}
