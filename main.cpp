#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"
#include "outputJsonFile.hpp"
#include "parsingJSON.hpp"
#include "allNotesWithOneSymbol.hpp"
#include "returnAllSymbols.hpp"
#include "mainLogicFunction.hpp"
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
	
	auto start = chrono::high_resolution_clock::now();	
	promise<Value> firstPromise;
	future<Value> firstFuture = firstPromise.get_future();
	thread first(&parsingJSON,move(firstPromise));
	Value fajlJson = firstFuture.get();
	first.join();

	promise<vector<string>> fifthPromise;
	future<vector<string>> fifthFuture = fifthPromise.get_future();
	thread fifth(&returnAllSymbols, move(fifthPromise), fajlJson);
	vector<string> symbols = fifthFuture.get();
	fifth.join();
	cout << "CALCULATING..." << endl;
	for(int i=0;i<symbols.size();i++){
		promise<vector<any>> secondPromise;
		future<vector<any>> secondFuture = secondPromise.get_future();
		thread second(&allNotesWithOneSymbol,move(secondPromise),symbols[i],fajlJson);
		vector<any> records = secondFuture.get();
		vector<any> otherRecs = records;
		second.join();

		thread third(&mainLogicFunction,ref(otherRecs));
		third.join();

		thread fourth(outputJsonFile,symbols[i],ref(fajlJson));
		fourth.join();
	}
	auto stop = chrono::high_resolution_clock::now();
	cout << "DONE!" << endl;
	auto numberOfMiliseconds = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Time of execution is " << numberOfMiliseconds.count() << " of milliseconds!" << endl;
}
