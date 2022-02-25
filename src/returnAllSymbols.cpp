#include "../include/klase.hpp"
#include <future>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <vector>

void returnAllSymbols(std::promise<std::vector<std::string>> && fifthPromise, Json::Value jsonFile){
	std::vector<std::string> symbols = {};
	for(Json::Value::ArrayIndex i=0;i!=jsonFile.size();i++){
		std::string findedSymbol = jsonFile[i]["book"]["symbol"].asString();
		if(find(symbols.begin(),symbols.end(),findedSymbol)==symbols.end()){
			symbols.push_back(findedSymbol);	
		}
	}
	symbols.pop_back();
	//return symbols;
	fifthPromise.set_value(symbols);
}

