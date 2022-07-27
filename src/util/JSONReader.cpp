#include <vector>
#include <string>
#include <cstring>
#include "JSONReader.h"
#include "ExceptionCodes.h"

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

std::vector<std::string> readPlainJSON(std::string path, std::vector<std::string> keys) {

    FILE *fp;
    char key[256];
    char val[256];
    char *keyptr, *valptr;
    int f;
    std::vector<std::string> values;

    if ((fp = fopen(path.c_str(), "r"))) {
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
            for(std::size_t i = 0; i < keys.size(); ++i) {
                if (keys.at(i).compare(std::string(keyptr))) {
                    values.at(i) = std::string(valptr);
                    break;
                }
            }
            // reset key and value for nex trun
            key[0] = 0; val[0] = 0;
        }
        fclose(fp);
    } else {
        throw COULD_NOT_READ_JSON;
    }

    return values;
}
