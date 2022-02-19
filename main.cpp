#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include "include/klase.hpp"
#include <vector>
#include <algorithm>
#include <boost/any.hpp>
#include <iterator>

using namespace std;
using namespace Json;
using namespace boost;

Value parsiranjeJSONA(string jsonName){
	ifstream loadJSON(jsonName);
	Value realJSON;
	Reader reader;
	reader.parse(loadJSON,realJSON);
	return realJSON;
}

vector<any> AllNotestWithOneSymbol(){
	Value parsedDocument = parsiranjeJSONA("first.json");
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
		if(parsedDocument[i]["book"]["symbol"]=="ABBN"){
			helpBook.symbol="ABBN";
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
		if(parsedDocument[i]["trade"]["symbol"]=="ABBN"){
			helpTrade.symbol = "ABBN";
			helpTrade.quantity = parsedDocument[i]["trade"]["quantity"].asDouble();
			helpTrade.price = parsedDocument[i]["trade"]["price"].asDouble();
			any trade = helpTrade;
			booksAndTrades.push_back(trade);
		}
	}
	return booksAndTrades;
}

void realFunction(vector<any>& events){
	vector<any>::iterator it=events.begin();
	for(;it!=events.end();it++){
		if(it->type().hash_code() == typeid(BOOK).hash_code()){
			BOOK Book = any_cast<BOOK>(*it);
			cout << "Odavdje je nova knjiga" << endl;
			cout << Book.symbol << endl;
			for(int i=0;i<Book.bids.size();i++){
				cout << "Ovo je za jednu book" << endl;
				cout << "Count je "<< Book.bids[i].getCount() << endl;
				cout << "Cijena je " << Book.bids[i].getPrice() << endl;
				cout << "Kolicina je " << Book.bids[i].getQuantity() << endl;
				cout << endl;
			}
		} else if(it->type().hash_code() == typeid(TRADE).hash_code()){
			cout << "Ovo su sve trades" << endl;
		}
	}
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
                        cout << "CANCELED " << kolicina << pomocnaNext.bids[i].getPrice() << endl;
                    }
                }
            } else if(pomocnaNext.bids.size()!=pomocnaPrev.bids.size()){
				vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.bids.size();k++){
					oldPrices.push_back(pomocnaPrev.bids[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.bids.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.bids[j].getPrice())==oldPrices.end()){
						cout << "PASSIVE BUY " << pomocnaNext.bids[j].getQuantity() << "@" << pomocnaNext.bids[j].getPrice()<< endl;
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
                        cout << "CANCELED " << kolicina << pomocnaNext.asks[i].getPrice() << endl;
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
		} else if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			// Ovdje je provjera kada prvo book pa onda trade
			BOOK bookPrev = any_cast<BOOK>(*prev);
			TRADE tradeNext = any_cast<TRADE>(*it);
			if(tradeNext.price == bookPrev.bids[0].getPrice()){
				bookPrev.bids[0].setQuantity(bookPrev.bids[0].getQuantity()-tradeNext.quantity);
				cout << "AGGRESSIVE SELL " << tradeNext.quantity << "@" << tradeNext.price << endl;
			} else if(tradeNext.price == bookPrev.asks[0].getPrice()){
				bookPrev.asks[0].setQuantity(bookPrev.asks[0].getQuantity()-tradeNext.quantity);
				cout << "AGGRESSIVE BUY " << tradeNext.quantity << "@" << tradeNext.price << endl;
			}
		} else if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			//Ovdje je provjera kad dodje trade pa onda book
			BOOK bookNext = any_cast<BOOK>(*it);
			TRADE tradePrev = any_cast<TRADE>(*prev);
			BOOK prevBook;
			auto reverse = it;
			for(;reverse--!=booksAndTrades.begin();){
				if(reverse->type().hash_code() == typeid(BOOK).hash_code()){
					prevBook = any_cast<BOOK>(*reverse);	
					break;
				}
			}
			if(bookNext.bids.size()==prevBook.bids.size()){
				//cout << "Ovdje je prvi uslov kada su iste duzine bids" << endl;
				for(int i=0;i<prevBook.bids.size();i++){
                    if((bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity() > 0){
						double kolicina = (bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity();
                        cout << "PASSIVE BUY " << kolicina << "@" << bookNext.bids[i].getPrice() << endl;
                    } else if((bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity() < 0){
						double kolicina = (bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity();
                        cout << "CANCELED " << kolicina << bookNext.bids[i].getPrice() << endl;
                    }
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
                    if((bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity() > 0){
						double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity();
                        cout << "PASSIVE SELL " << kolicina << "@" << bookNext.asks[i].getPrice() << endl;
                    } else if((bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity() < 0){
						double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity();
                        cout << "CANCELED " << kolicina << bookNext.asks[i].getPrice() << endl;
                    }
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
	}
}

int main(){
	vector<any> hopeLast = AllNotestWithOneSymbol();
	//any var = hopeLast[7];
	//assert(is_type<TRADE>(var));
	//realFunction(hopeLast);
	mainLogicFunction(hopeLast);
	//if(var.type().hash_code() == typeid(TRADE).hash_code()){
	//	TRADE varijabla = any_cast<TRADE>(var);
	//	cout << "Desila se trgovina i prodato je " << varijabla.count << " kolicina po cijeni" << varijabla.price << endl;
	//}
	//for(int i=0;i<firstBook.bids.size();i++){
	//	for(int j=0;j<firstBook.bids[i].size();++j){
	//		firstBook.bids[i][j].print();
	//	}
	//}
	//for(int i=0;i<firstBook.asks.size();i++){
	//	for(int k=0;k<firstBook.asks[i].size();k++){
	//		firstBook.asks[i][k].print();
	//	}
	//}
	//comparisonOfBidsFunction(firstBook);
	//comparisonOfBidsFunction(zapisi);
	//comparisionOfAsksFunction(asksNotes);
	//comparisonOfBidsFunction(zapisi);
	return 0;
}
