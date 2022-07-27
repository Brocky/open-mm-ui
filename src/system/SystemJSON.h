#ifndef INC_SYSTEM_JSON
#define INC_SYSTEM_JSON

#include <vector>
#include <string>
#include "../util/JSONReader.h"

enum JSONKeys {
    JSON_VOLUME,		// vol
    JSON_KEYMAP,		// keymap (unused)
    JSON_MUTE,		// mute
    JSON_BGM_VOLUME,	// bgmvol
    JSON_BRIGHTNESS,	// brightness
    JSON_LANGUAGE,		// language
    JSON_HIBERNATE_DELAY,	// hibernate
    JSON_LUMINATION,	// lumination
    JSON_HUE,		// hue
    JSON_SATURATION,	// saturation
    JSON_CONTRAST,		// contrast
    JSON_THEME,		// theme
    JSON_FONTSIZE,		// fontsize
    JSON_AUDIOFIX,		// audiofix
    JSON_VALUE_MAX,
};

class SystemJSON
{
private:
    SystemJSON() {};
    std::vector<std::string> jsonvalue;
public:
    static JSONKeys JsonValue;
    static const char filepath[];

    static SystemJSON *load();
    ~SystemJSON() {};
    std::string getThemePath();
};

#endif
