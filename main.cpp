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
			helpTrade.count = parsedDocument[i]["trade"]["quantity"].asDouble();
			helpTrade.price = parsedDocument[i]["trade"]["price"].asDouble();
			any trade = helpTrade;
			booksAndTrades.push_back(trade);
		}
	}
	return booksAndTrades;
}

/*void myfunction(BOOK books){
	for(int i=0;i<books.bids.size();i++){ // Sve linije koje postoje u jednoj book
		//cout << books.bids[i].size()+books.asks[i].size() << endl;
		for(int k=1;k<books.bids[i].size()+books.asks[i].size();k++){ // svi zapisi u jednoj liniji i bids i books
			if(k<books.bids[i].size()){
				if((books.bids[i].size()) == books.bids[i-1].size()){
					for(int t=0;t<books.bids[i-1].size();t++){
						double quant = (books.bids[i-1])[t].getQuantity();
						double cijena = (books.bids[i-1])[t].getPrice();
						for(int j=0;j<books.bids[i].size();j++){
							if((books.bids[i])[j].getQuantity() != quant && (books.bids[i])[j].getPrice() == cijena){
								if((books.bids[i])[j].getQuantity()-quant > 0){
									cout << "PASSIVE BUY " << (books.bids[i])[j].getQuantity()-quant << "@" << cijena << endl;
								} else if((books.bids[i])[j].getQuantity()-quant < 0){
									cout << "CANCELED " << abs((books.bids[i])[j].getQuantity()-quant) << "@" << cijena << endl;
								}  
							} 
						} 
					}
			
				} else {
					vector<double> oldPrices;
					for(int t=0;i<books.bids[i-1].size();t++){
						oldPrices.push_back((books.bids[i-1])[t].getPrice());
					}
					for(int j=books.bids[i].size()-1;j>-1;j--){
						if(find(oldPrices.begin(),oldPrices.end(),(books.bids[i])[j].getPrice())==oldPrices.end()){
							cout << "PASSIVE BUY ZA " << (books.bids[i])[j].getQuantity() << "@" << (books.bids[i])[j].getPrice()<< endl;
						}
					}
				}
			} else if(k>=books.bids[i].size()) {
				//cout << "Usao u uslov barem jednom";
				if((books.asks[i].size()) == books.asks[i-1].size()){
					for(int t=0;t<books.asks[i-1].size();t++){
						double quant = (books.asks[i-1])[t].getQuantity();
						double cijena = (books.asks[i-1])[t].getPrice();
						for(int j=0;j<books.asks[i].size();j++){
							if((books.asks[i])[j].getQuantity() != quant && (books.asks[i])[j].getPrice() == cijena){
								if((books.asks[i])[j].getQuantity()-quant > 0){
									cout << "PASSIVE SELL " << (books.asks[i])[j].getQuantity()-quant << "@" << cijena << endl;
								} else if((books.asks[i])[j].getQuantity()-quant < 0){
									cout << "CANCELED " << abs((books.asks[i])[j].getQuantity()-quant) << "@" << cijena << endl;
								}  
							} 
						} 
					}
				} else {
					vector<double> oldPrices;
					for(int t=0;i<books.asks[i-1].size();t++){
						oldPrices.push_back((books.asks[i-1])[t].getPrice());
					}
					for(int j=books.asks[i].size()-1;j>-1;j--){
						if(find(oldPrices.begin(),oldPrices.end(),(books.asks[i])[j].getPrice())==oldPrices.end()){
							cout << "PASSIVE SELL ZA " << (books.asks[i])[j].getQuantity() << "@" << (books.asks[i])[j].getPrice()<< endl;
						}
					}
				}	
			}		
		}
	}
}*/

template <typename T>
bool is_type(any& any) {
	return ( !any.empty() && boost::any_cast<T>(&any) );
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
		} else if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			BOOK bookPrev = any_cast<BOOK>(*prev);
			TRADE tradeNext = any_cast<TRADE>(*it);
			if(tradeNext.price == bookPrev.bids[0].getPrice()){
				cout << "AGGRESSIVE SELL " << tradeNext.count << "@" << tradeNext.price << endl;
			} else if(tradeNext.price == bookPrev.asks[0].getPrice()){
				cout << "AGGRESSIVE BUY " << tradeNext.count << "@" << tradeNext.price << endl;
			}
		} else if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			cout << "Ovo je najtezi slucaj i treba obratiti paznju dobro " << endl;
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
