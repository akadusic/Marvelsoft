#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"

using namespace std;
using namespace Json;

Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}

BID konverzija(){
	Value koristit = parsiranjeJSONA("pomocni.json");
	BID zaVratit;
	//double broj = (koristit["book"]["bid"][0]).asDouble();
	zaVratit.setCount(koristit["book"]["bid"][0].asDouble());
	zaVratit.setQuantity(koristit["book"]["bid"][1].asDouble());
	zaVratit.setPrice(koristit["book"]["bid"][2].asDouble());
	return zaVratit;
}

int main(){
	//ifstream fajl("pomocni.json");
	//Json::Value fajlic;
	//Json::Reader reader;
	
	//reader.parse(fajl, fajlic);
	BID varijabla = konverzija();
	varijabla.print();
	//Value jsoncic = parsiranjeJSONA("pomocni.json");
	//cout << "Total json data is: \n" << jsoncic << endl;
	//cout << "Jedno ime samo je: " << jsoncic["book"]["bid"][0] << endl;
	//cout << "Jedno ime od jednog imena je " << fajlic["book"]["ask"] << endl;
	return 0;
}
