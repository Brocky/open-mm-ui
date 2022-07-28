#include "Emu.h"

std::vector<std::string> config_keys = {
	"\"label\"",
    "\"icon\"",
    "\"iconsel\"",
    "\"launch\"",
    "\"rompath\"",
    "\"imgpath\"",
    "\"useswap\"",
	"\"shortname\"",
    "\"hidebios\"",
    "\"extlist\""
};

Emu::Emu(std::string config_path)
{
    this->config = readPlainJSON(config_path, config_keys);
}

GridItem Emu::toGridItem()
{
    return {this->config[EmuConfigKeys::IMG_PATH], this->config[EmuConfigKeys::LABEL]};
}
