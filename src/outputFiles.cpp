#include "../include/klase.hpp"
#include <boost/any.hpp>
#include <fstream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>

void outputJsonFile(std::string symbol){
	std::ofstream ofstreamFile(symbol+".json");
	Json::Value allRecords=parsiranjeJSONA();
	Json::Value outputFileObj;
	Json::StyledWriter writer;
	for(Json::Value::iterator it=allRecords.begin();it!=allRecords.end();it++){
		if((*it)["book"]["symbol"]==symbol){
			ofstreamFile << writer.write(*it);
		}
	}
	ofstreamFile.close();
}
