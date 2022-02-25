#include <stdlib.h>
#include <jsoncpp/json/json.h>
#include <future>

void returnAllSymbols(std::promise<std::vector<std::string>> && secondPromise,Json::Value jsonFile);
