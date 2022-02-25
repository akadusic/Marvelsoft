#include "../include/klase.hpp"
#include <boost/any.hpp>
#include <fstream>
#include <future>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <thread>

void outputJsonFile(std::string symbol,Json::Value allRecords){
	std::ofstream ofstreamFile(symbol+".json");	
	Json::Value outputFileObj;
	Json::StyledWriter writer;
	for(Json::Value::iterator it=allRecords.begin();it!=allRecords.end();it++){
		if((*it)["book"]["symbol"]==symbol){
			ofstreamFile << writer.write(*it);
		}
	}
	ofstreamFile.close();
}
