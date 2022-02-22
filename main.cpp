#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"
#include <vector>
#include <algorithm>
#include <boost/any.hpp>
#include <iterator>
#include <thread>
#include <future>

using namespace std;
using namespace Json;
using namespace boost;

int main(){
	Value fajlJson = parsiranjeJSONA();
	vector<string> symbols = returnAllSymbols(fajlJson);	
	for(int i=0;i<symbols.size();i++){
		cout << symbols[i] << endl;
		cout << endl;
		cout << i << endl;
		vector<any> bigResult = AllNotestWithOneSymbol(symbols[i]);
		mainLogicFunction(bigResult);
		outputJsonFile(symbols[i]);	
	}
	//One possible solution
	//promise<vector<any>> firstPromise;
	//future<vector<any>> firstFuture = firstPromise.get_future();
	//thread th(&AllNotestWithOneSymbol,move(firstPromise));
	//vector<any> returningValue = firstFuture.get();
	//thread second(mainLogicFunction,ref(returningValue));
	//thread symbols(returnAllSymbols,ref(returningValue));
	//th.join();
	//second.join();
	//symbols.join();	
	return 0;
}
