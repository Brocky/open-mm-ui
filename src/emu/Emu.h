#ifndef INC_EMU
#define INC_EMU

#include <vector>
#include <string.h>
#include "../theme/Theme.h"
#include "../util/JSONReader.h"

enum EmuConfigKeys {
    LABEL,
    ICON,
    ICON_SEL,
    LAUNCH,
    ROM_PATH,
    IMG_PATH,
    USE_SWAP,
    SHORT_NAME,
    HIDE_BIOS,
    EXT_LIST,
    num_values
};

class Emu
{
private:
    std::vector<std::string> config;
public:
    Emu(std::string config_path);
    ~Emu();
    GridItem toGridItem();
};

#endif
