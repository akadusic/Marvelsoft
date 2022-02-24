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
	//auto start = chrono::high_resolution_clock::now();
	promise<Value> firstPromise;
	future<Value> firstFuture = firstPromise.get_future();
	thread first(&parsiranjeJSONA,move(firstPromise));
	Value fajlJson = firstFuture.get();
	first.join();
	cout << fajlJson.size();
	/*vector<string> symbols = returnAllSymbols(fajlJson);	
	for(int i=0;i<symbols.size();i++){
		cout << symbols[i] << endl;
		cout << endl;
		cout << i << endl;
		vector<any> bigResult = AllNotestWithOneSymbol(symbols[i]);
		mainLogicFunction(bigResult);
		outputJsonFile(symbols[i]);	
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);
	cout << "Vrijeme trajanja programa je " << duration.count() << " of milliseconds!" << endl;*/
	
	//One possible solution with threading
	//promise<vector<any>> secondPromise;
	//promise<vector<string>> secondPromise;
	//future<vector<any>> secondFuture = secondPromise.get_future();
	//future<vector<string>> secondFuture = secondPromise.get_future();
	//thread firstThread(&returnAllSymbols,move(secondPromise),fajlJson);
	//thread second(&AllNotestWithOneSymbol,move(secondPromise),"ABBN");
	//vector<any> returningValue = firstFuture.get();
	//vector<string> symbols = secondFuture.get();
	//thread second(mainLogicFunction,ref(returningValue));
	//thread symbols(returnAllSymbols,ref(returningValue));
	//th.join();
	//second.join();
	//firstThread.join();
	//symbols.join();*/	
	return 0;
}
