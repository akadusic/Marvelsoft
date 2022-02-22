#include "../include/klase.hpp"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <fstream>

using namespace Json;

Value parsiranjeJSONA(){
	std::ifstream loadJSON("../input.json");
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}
