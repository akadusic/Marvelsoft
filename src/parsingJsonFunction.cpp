#include "../include/klase.hpp"
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <fstream>

Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}
