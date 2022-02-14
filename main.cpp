#include <cmath>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"
#include <vector>
#include <algorithm>

using namespace std;
using namespace Json;

Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}

vector<vector<BID>> konverzija(){
	Value parsedDocument = parsiranjeJSONA("pomocni.json");
	BID returnValue;
	vector<BID> bids = {};
	vector<vector<BID>> vectorOfBids;
	for(Value::ArrayIndex i=0; i!=parsedDocument.size();i++){
		for(Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["bid"].size();j++){
			returnValue.setCount(((parsedDocument[i]["book"]["bid"][j])["count"].asDouble()));
			returnValue.setQuantity(((parsedDocument[i]["book"]["bid"][j])["quantity"].asDouble()));
			returnValue.setPrice(((parsedDocument[i]["book"]["bid"][j])["price"].asDouble()));
			bids.push_back(returnValue);
		}
			vectorOfBids.push_back(bids);
	}
	return vectorOfBids;
}


int main(){	
	vector<vector<BID>> zapisi = konverzija();
	for(int k=1;k<zapisi.size();k++){

	
	if(zapisi[k].size() == zapisi[k-1].size()){
		for(int i=0;i<zapisi[k-1].size();i++){
			double quant = (zapisi[k-1])[i].getQuantity();
			double cijena = (zapisi[k-1])[i].getPrice();
			for(int j=0;j<zapisi[k].size();j++){
				if((zapisi[k])[j].getQuantity() != quant && (zapisi[k])[j].getPrice() == cijena){
					if((zapisi[k])[j].getQuantity()-quant > 0){
						cout << "PASSIVE BUY " << (zapisi[k])[j].getQuantity()-quant << "@" << cijena << endl;
					} else if((zapisi[k])[j].getQuantity()-quant < 0){
						cout << "CANCELED " << abs((zapisi[k])[j].getQuantity()-quant) << "@" << cijena << endl;
					}
				} 
			}
		}
	} else {
		vector<double> oldPrices;
		for(int i=0;i<zapisi[k-1].size();i++){
			oldPrices.push_back((zapisi[k-1])[i].getPrice());
		}
		for(int j=0;j<zapisi[k].size();j++){
			if(find(oldPrices.begin(),oldPrices.end(),(zapisi[k])[j].getPrice())==oldPrices.end()){
				cout << "PASSIVE BUY ZA " << (zapisi[k])[j].getQuantity() << "@" << (zapisi[k])[j].getPrice()<< endl;
			}
		}
	}
}


	return 0;
}
