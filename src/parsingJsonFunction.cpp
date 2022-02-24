#include "../include/klase.hpp"
#include <future>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <fstream>

using namespace Json;

void parsiranjeJSONA(std::promise<Json::Value> && fourthPromise){
	std::ifstream loadJSON("../input.json");
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	//return realJSON;
	fourthPromise.set_value(realJSON);
}
