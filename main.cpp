#include <cmath>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"
#include <vector>

using namespace std;
using namespace Json;

Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}

vector<BID> konverzija(){
	Value parsedDocument = parsiranjeJSONA("pomocni.json");
	BID returnValue;
	vector<double> counts;
	vector<BID> bids;
	for(Value::ArrayIndex i=0; i!=parsedDocument.size();i++){
		for(Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["bid"].size();j++){
			//counts.push_back(((parsedDocument[i]["book"]["bid"][j])["count"].asDouble()));
			returnValue.setCount(((parsedDocument[i]["book"]["bid"][j])["count"].asDouble()));
			returnValue.setQuantity(((parsedDocument[i]["book"]["bid"][j])["quantity"].asDouble()));
			returnValue.setPrice(((parsedDocument[i]["book"]["bid"][j])["price"].asDouble()));
			bids.push_back(returnValue);
		}
	}
	return bids;
}

//void logicForBid(vector<BID>& allJsonFiles){
//	for(int i=1;i<allJsonFiles.size();i++){
//		if(allJsonFiles[i].getPrice()==allJsonFiles[i-1].getPrice()){
//			cout << "Razlika u kolicini je " << abs(allJsonFiles[i].getQuantity()-allJsonFiles[i-1].getQuantity());
//		}
//	}
//}

int main(){	
	Value jsoncic = parsiranjeJSONA("pomocni.json");
	for(Value::ArrayIndex i=0;i!=jsoncic.size();i++){
		for(Value::ArrayIndex j=0;j!=jsoncic[i]["book"]["bid"].size();j++){
			//cout << jsoncic[i]["book"]["bid"].size() << endl;
			cout << (jsoncic[i]["book"]["bid"][j])["price"].asDouble() << " ";
		}
	}
	vector<BID> var = konverzija();
	for(int i=0;i<var.size();i++){
		var[i].print();
	}
	return 0;
}
