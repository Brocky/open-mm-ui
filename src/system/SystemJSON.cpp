#include "SystemJSON.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>

std::vector<std::string> jsonkeyname = {
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

std::string SystemJSON::filepath = "/appconfigs/system.json";

SystemJSON *SystemJSON::load() {
    SystemJSON *self = new SystemJSON;

	self->jsonvalue = readPlainJSON(self->filepath, jsonkeyname);
	return self;
}

std::string SystemJSON::getThemePath() {
    std::string path = this->jsonvalue.at(JSONKeys::JSON_THEME);
    path.erase(std::remove(path.begin(), path.end(), '\"'), path.end());
    return path;
}
