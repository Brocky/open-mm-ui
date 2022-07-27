#ifndef INC_UTIL_JSON_READER
#define INC_UTIL_JSON_READER

#include <vector>
#include <string>

#define JSONKEYSIZE	16
#define JSONSTRSIZE	128

std::vector<std::string> readPlainJSON(std::string path, std::vector<std::string> keys);

#endif
