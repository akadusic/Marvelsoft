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

/*Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}*/

void AllNotestWithOneSymbol(promise<vector<any>> && firstPromise){
	Value parsedDocument = parsiranjeJSONA("input.json");
	BID bidHelp;
	ASK askHelp;
	vector<BID> helpBids;
	vector<ASK> helpAsks;
	vector<vector<BID>> allBidsForOneSymbol;
	vector<vector<ASK>> allAsksForOneSymbol;
	BOOK helpBook;
	TRADE helpTrade;
	vector<any> booksAndTrades;
	for(Value::ArrayIndex i=0;i!=parsedDocument.size();i++){	
		if(parsedDocument[i]["book"]["symbol"]=="CIMB"){
			helpBook.symbol="CIMB";
			for(Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["bid"].size();j++){
				bidHelp.setCount(((parsedDocument[i]["book"]["bid"][j])["count"].asDouble()));
				bidHelp.setQuantity(((parsedDocument[i]["book"]["bid"][j])["quantity"].asDouble()));
				bidHelp.setPrice(((parsedDocument[i]["book"]["bid"][j])["price"].asDouble()));
				helpBids.push_back(bidHelp);
			}
			for(Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["ask"].size();j++){
				askHelp.setCount(((parsedDocument[i]["book"]["ask"][j])["count"].asDouble()));
				askHelp.setQuantity(((parsedDocument[i]["book"]["ask"][j])["quantity"].asDouble()));
				askHelp.setPrice(((parsedDocument[i]["book"]["ask"][j])["price"].asDouble()));
				helpAsks.push_back(askHelp);
			}
			helpBook.bids = helpBids;
			helpBook.asks = helpAsks;
			helpBids.clear();
			helpAsks.clear();
			any book = helpBook;
			booksAndTrades.push_back(book);   
		}
		if(parsedDocument[i]["trade"]["symbol"]=="CIMB"){
			helpTrade.symbol = "CIMB";
			helpTrade.quantity = parsedDocument[i]["trade"]["quantity"].asDouble();
			helpTrade.price = parsedDocument[i]["trade"]["price"].asDouble();
			any trade = helpTrade;
			booksAndTrades.push_back(trade);
		}
	}
	firstPromise.set_value(booksAndTrades);
	//return booksAndTrades;
}

void mainLogicFunction(vector<any>& booksAndTrades){
    vector<any>::iterator it=booksAndTrades.begin();
	vector<any>::iterator prev = it;
	advance(it,1);
    for(; it != booksAndTrades.end(); it++, prev++ ){
        if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
            //Ovdje je provjera kada su oba BOOK jedan za drugim u nizu
			BOOK pomocnaPrev = any_cast<BOOK>(*prev);
			BOOK pomocnaNext = any_cast<BOOK>(*it);
			if(pomocnaNext.bids.size() == pomocnaPrev.bids.size()){
                for(int i=0;i<pomocnaPrev.bids.size();i++){
                    if((pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity();
                        cout << "PASSIVE BUY " << kolicina << "@" << pomocnaNext.bids[i].getPrice() << endl;
                    } else if((pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity();
                        cout << "CANCELED BUY " << abs(kolicina) << "@" << pomocnaNext.bids[i].getPrice() << endl;
						// Ovdje je cancel u redu
                    }
                }
            } else if(pomocnaNext.bids.size()!=pomocnaPrev.bids.size()){
				vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.bids.size();k++){
					oldPrices.push_back(pomocnaPrev.bids[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.bids.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.bids[j].getPrice())==oldPrices.end()){
						cout << "PASSIE BUY " << pomocnaNext.bids[j].getQuantity() << "@" << pomocnaNext.bids[j].getPrice()<< endl;
					}
				}
			} 
			if(pomocnaNext.asks.size() == pomocnaPrev.asks.size()){
				for(int i=0;i<pomocnaPrev.asks.size();i++){
                    if((pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity();
                        cout << "PASSIVE SELL " << kolicina << "@" << pomocnaNext.asks[i].getPrice() << endl;
                    } else if((pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity();
                        cout << "CANCELED BY" << abs(kolicina) << "@" <<pomocnaNext.asks[i].getPrice() << endl;
						//Ovdje je cancel u redu
                    }
                }
			} else if(pomocnaNext.asks.size()!=pomocnaPrev.asks.size()){
				vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.asks.size();k++){
					oldPrices.push_back(pomocnaPrev.asks[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.asks.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.asks[j].getPrice())==oldPrices.end()){
						cout << "PASSIVE SELL " << pomocnaNext.asks[j].getQuantity() << "@" << pomocnaNext.asks[j].getPrice()<< endl;
					}
				}
			}
		} 
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			// Ovdje je provjera kada prvo book pa onda trade
			BOOK bookPrev = any_cast<BOOK>(*prev);
			TRADE tradeNext = any_cast<TRADE>(*it);
			vector<double> oldPricesBids;
			vector<double> oldPricesAsks;
			for(int i=0;i<bookPrev.bids.size();i++){
				oldPricesBids.push_back(bookPrev.bids[i].getPrice());
			}
			for(int i=0;i<oldPricesBids.size();i++){
				if(tradeNext.price == oldPricesBids[i]){
					cout << "AGGRESSIVE SELL " << tradeNext.quantity << "@" << tradeNext.price << endl;
				}
			}
			for(int i=0;i<bookPrev.asks.size();i++){
				oldPricesAsks.push_back(bookPrev.asks[i].getPrice());
			}
			for(int i=0;i<oldPricesAsks.size();i++){
				if(tradeNext.price == oldPricesAsks[i]){
					cout << "AGGRESSIVE BUY " << tradeNext.quantity << "@" << tradeNext.price << endl;
				}
			}
		} 
		if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			//Ovdje je provjera kad dodje trade pa onda book
			BOOK bookNext = any_cast<BOOK>(*it);
			TRADE tradePrev = any_cast<TRADE>(*prev);
			BOOK prevBook;
			auto reverse = it;
			for(;reverse--!=booksAndTrades.begin();){
				if(reverse->type().hash_code() == typeid(BOOK).hash_code()){
					any realValue = *reverse;
					prevBook = any_cast<BOOK>(realValue);	
					break;
				}
			}
			if(bookNext.bids.size()==prevBook.bids.size()){
				//cout << "Ovdje je prvi uslov kada su iste duzine bids" << endl;
				for(int i=0;i<prevBook.bids.size();i++){
                    if((bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity() > 0){
						double kolicina = (bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity();
                        cout << "PASSIVE BUY " << kolicina << "@" << bookNext.bids[i].getPrice() << endl;
                    } //else if((bookNext.bids)[i].getQuantity() + tradePrev.quantity < (prevBook.bids)[i].getQuantity()){
						//double kolicina = (prevBook.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity()-tradePrev.quantity;
                        //cout << "CANCELED BY" << kolicina << "@" << bookNext.bids[i].getPrice() << endl;
						//Ovdje je cancel takodjer u redu
                    //}
                }
			} else if(bookNext.bids.size()!=prevBook.bids.size()){
				//cout << "Ovdje je drugi uslov kada nisu iste duzine bids" << endl;
				vector<double> oldPrices;
				for(int k=0;k<prevBook.bids.size();k++){
					oldPrices.push_back(prevBook.bids[k].getPrice());
				}
				for(int j=0;j<bookNext.bids.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.bids[j].getPrice())==oldPrices.end()){
						cout << "PASSIVE BUY " << bookNext.bids[j].getQuantity() << "@" << bookNext.bids[j].getPrice()<< endl;
					}
				}
			} 
			if(bookNext.asks.size() == prevBook.asks.size()){
				//cout << "Ovdje je uslov kada su asks iste duzine" << endl;
				for(int i=0;i<prevBook.asks.size();i++){
                    if((bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity()-tradePrev.quantity >= 0){
						double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity();
                        cout << "PASSIVE SELL " << kolicina << "@" << bookNext.asks[i].getPrice() << endl;
                    } // else if((bookNext.asks)[i].getQuantity() + tradePrev.quantity < (prevBook.bids)[i].getQuantity()){
						//double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity()-tradePrev.quantity;
                        //cout << "CANCELED By" << kolicina << "@" << bookNext.asks[i].getPrice() << endl;
                    //}
                }
			} else if(bookNext.asks.size()!=prevBook.asks.size()){
				//cout << "Ovdje je uslov kada su asks razlicite duzine" << endl;
				vector<double> oldPrices;
				for(int k=0;k<prevBook.asks.size();k++){
					oldPrices.push_back(prevBook.asks[k].getPrice());
				}
				for(int j=0;j<bookNext.asks.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.asks[j].getPrice())==oldPrices.end()){
						cout << "PASSIVE SELL " << bookNext.asks[j].getQuantity() << "@" << bookNext.asks[j].getPrice()<< endl;
					}
				}
			} 
		}
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			TRADE prevTrade = any_cast<TRADE>(*prev);
			TRADE nextTrade = any_cast<TRADE>(*it);
			BOOK prevBook;
			auto reverse = it;
			for(;reverse--!=booksAndTrades.begin();){
				if(reverse->type().hash_code() == typeid(BOOK).hash_code()){
					any realValue = *reverse;
					prevBook = any_cast<BOOK>(realValue);	
					break;
				}
			}
			vector<double> allBidsPrices,allAsksPrices;
			for(int i=0;i<prevBook.bids.size();i++){
				allBidsPrices.push_back(prevBook.bids[i].getPrice());
			}
			for(int j=0;j<prevBook.asks.size();j++){
				allAsksPrices.push_back(prevBook.asks[j].getPrice());
			}
			for(int i=0;i<allBidsPrices.size();i++){
				if(nextTrade.price == allBidsPrices[i]){
					cout << "AGGRESSIVE SELL" << nextTrade.quantity << "@" << nextTrade.price << endl;
				} 
			}
			for(int j=0;j<allAsksPrices.size();j++){
				if(nextTrade.price == allAsksPrices[j]){
					cout << "AGGRESSIVE BUY " << nextTrade.quantity << "@" << nextTrade.price << endl;
				}
			}
			
		}
	}
}

int main(){
	//vector<any> result = AllNotestWithOneSymbol();
	//mainLogicFunction(result);
	
	//One possible solution
	promise<vector<any>> firstPromise;
	future<vector<any>> firstFuture = firstPromise.get_future();
	thread th(&AllNotestWithOneSymbol,move(firstPromise));
	vector<any> returningValue = firstFuture.get();
	thread second(mainLogicFunction,ref(returningValue));
	th.join();
	second.join();
	
	//secondPosible solution
	//future<vector<any>> result = async(&AllNotestWithOneSymbol);
	//vector<any> realRes = result.get();
	//thread th(&mainLogicFunction,&realRes);
	return 0;
}
