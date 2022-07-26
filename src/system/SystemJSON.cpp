#include "SystemJSON.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "ExceptionCodes.h"

const char jsonkeyname[JSONKeys::JSON_VALUE_MAX][JSONKEYSIZE] = {
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

const char SystemJSON::filepath[] = "/appconfigs/system.json";

//
//	Trim Strings for reading json
//
char* trimstr(char* str, uint32_t first) {
	char *firstchar, *firstlastchar, *lastfirstchar, *lastchar;
	uint32_t i;

	firstchar = firstlastchar = lastfirstchar = lastchar = 0;

	for (i=0; i<strlen(str); i++) {
		if ((str[i]!='\r')&&(str[i]!='\n')&&(str[i]!=' ')&&(str[i]!='\t')&&
		    (str[i]!='{')&&(str[i]!='}')&&(str[i]!=',')) {
			if (!firstchar) {
				firstchar = &str[i];
				lastfirstchar = &str[i];
			}
			if (i) {
				if ((str[i-1]=='\r')||(str[i-1]=='\n')||(str[i-1]==' ')||(str[i-1]=='\t')||
				    (str[i-1]=='{')||(str[i-1]=='}')||(str[i-1]==',')) {
					lastfirstchar = &str[i];
				}
			}
			if (str[i] == '"') {
				for (i++; i<(strlen(str)-1); i++) {
					if ((str[i]=='\r')||(str[i]=='\n')||(str[i]=='"')) break;
				}
			}
			lastchar = &str[i];
		} else {
			if (!firstlastchar) {
				firstlastchar = lastchar;
			}
		}
	}
	if (first) {
		lastfirstchar = firstchar;
		lastchar = firstlastchar;
	}
	if (lastchar) {
		lastchar[1] = 0;
	}
	if (lastfirstchar) return lastfirstchar;
	return 0;
}

SystemJSON *SystemJSON::load() {
    SystemJSON *self = new SystemJSON;

    FILE *fp;
	char key[256];
	char val[256];
	char *keyptr, *valptr;
	int f;
	uint32_t i;

	if ((fp = fopen(SystemJSON::filepath, "r"))) {
		key[0] = 0;
        val[0] = 0;

        // Search for key value pairs until file ends
		while ((f = fscanf(fp, "%255[^:]:%255[^\n]\n", key, val)) != EOF) {
            if (!f) {
			    // if no pair was found, check if we reached EOF
                if (fscanf(fp, "%*[^\n]\n") == EOF) break; //stop processing
                continue;
            }

            // if key is empty after trim, continue search
			if (!(keyptr = trimstr(key, 0))) continue;
            // if val is empty after trim, set empty
			if (!(valptr = trimstr(val, 1))) { val[0] = 0; valptr = val; }
			// look for key index and copy value once found
            for (i=0; i<JSONKeys::JSON_VALUE_MAX; i++) {
				if (!strcmp(keyptr, jsonkeyname[i])) {
					strncpy(self->jsonvalue[i], valptr, JSONSTRSIZE-1);
					break;
				}
			}
            // reset key and value for nex trun
			key[0] = 0; val[0] = 0;
		}
		fclose(fp);
	} else {
        throw COULD_NOT_READ_SYSTEMJSON;
    }

    return self;
}

std::string SystemJSON::getThemePath() {
    std::string path = std::string(this->jsonvalue[JSONKeys::JSON_THEME]);
    path.erase(std::remove(path.begin(), path.end(), '\"'), path.end());
    return path;
}
