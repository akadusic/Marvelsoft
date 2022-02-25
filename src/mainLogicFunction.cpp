#include "../include/klase.hpp"
#include <boost/any.hpp>
#include <fstream>
#include <functional>
#include <iostream>

using namespace std;

void mainLogicFunction(std::vector<boost::any>& booksAndTrades){
	std::vector<boost::any>::iterator it=booksAndTrades.begin();
	std::vector<boost::any>::iterator prev = it;
	advance(it,1);
	boost::any pomVar = *prev;
	BOOK forSymbol = boost::any_cast<BOOK>(pomVar);
	std::ofstream fileWithIntentions;
	fileWithIntentions.open(forSymbol.getSymbol()+".txt");
    for(; it != booksAndTrades.end(); it++, prev++ ){
        if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			
			// This is case when book come after book in json file	
			
			BOOK pomocnaPrev = boost::any_cast<BOOK>(*prev);
			BOOK pomocnaNext = boost::any_cast<BOOK>(*it);
			std::string fajlName = pomocnaNext.getSymbol();
			if(pomocnaNext.getBids().size() == pomocnaPrev.getBids().size()){
                for(int i=0;i<pomocnaPrev.getBids().size();i++){
                    if((pomocnaNext.getBids())[i].getQuantity() - (pomocnaPrev.getBids())[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.getBids())[i].getQuantity() - (pomocnaPrev.getBids())[i].getQuantity();
						fileWithIntentions << "PASSIVE BUY " << kolicina << "@" << pomocnaNext.getBids()[i].getPrice() << std::endl;
                    } else if((pomocnaNext.getBids())[i].getQuantity() - (pomocnaPrev.getBids())[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.getBids())[i].getQuantity() - (pomocnaPrev.getBids())[i].getQuantity();
						fileWithIntentions << "CANCELED BUY " << abs(kolicina) << pomocnaNext.getBids()[i].getPrice() << std::endl; 
                    }
                }
            } else if(pomocnaNext.getBids().size()!=pomocnaPrev.getBids().size()){
				std::vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.getBids().size();k++){
					oldPrices.push_back(pomocnaPrev.getBids()[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.getBids().size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.getBids()[j].getPrice())==oldPrices.end()){
						fileWithIntentions << "PASSIVE BUY " << pomocnaNext.getBids()[j].getQuantity() << "@" << pomocnaNext.getBids()[j].getPrice() << std::endl; 
					}
				}
			} 
			if(pomocnaNext.getAsks().size() == pomocnaPrev.getAsks().size()){
				for(int i=0;i<pomocnaPrev.getAsks().size();i++){
                    if((pomocnaNext.getAsks())[i].getQuantity() - (pomocnaPrev.getAsks())[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.getAsks())[i].getQuantity() - (pomocnaPrev.getAsks())[i].getQuantity();
						fileWithIntentions << "PASSIVE SELL " << kolicina << "@" << pomocnaNext.getAsks()[i].getPrice() << std::endl;
                    } else if((pomocnaNext.getAsks())[i].getQuantity() - (pomocnaPrev.getAsks())[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.getAsks())[i].getQuantity() - (pomocnaPrev.getAsks())[i].getQuantity();
						fileWithIntentions << "CANCELED BY " << abs(kolicina) << "@" << pomocnaNext.getAsks()[i].getPrice() << std::endl; 
                    }
                }
			} else if(pomocnaNext.getAsks().size()!=pomocnaPrev.getAsks().size()){
				std::vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.getAsks().size();k++){
					oldPrices.push_back(pomocnaPrev.getAsks()[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.getAsks().size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.getAsks()[j].getPrice())==oldPrices.end()){
						fileWithIntentions << "PASSIVE SELL " << pomocnaNext.getAsks()[j].getQuantity() << "@" << pomocnaNext.getAsks()[j].getPrice() << std::endl;
				}
			}
				
		}
		}
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			
			// This is case when trade come after book in json file

			BOOK bookPrev = boost::any_cast<BOOK>(*prev);
			TRADE tradeNext = boost::any_cast<TRADE>(*it);
			std::vector<double> oldPricesBids;
			std::vector<double> oldPricesAsks;
			for(int i=0;i<bookPrev.getBids().size();i++){
				oldPricesBids.push_back(bookPrev.getBids()[i].getPrice());
			}
			for(int i=0;i<oldPricesBids.size();i++){
				if(tradeNext.getPrice() == oldPricesBids[i]){
					fileWithIntentions << "AGGRESSIVE SELL " << tradeNext.getQuantity() << "@" << tradeNext.getPrice() << std::endl;
				}
			}
			for(int i=0;i<bookPrev.getAsks().size();i++){
				oldPricesAsks.push_back(bookPrev.getAsks()[i].getPrice());
			}
			for(int i=0;i<oldPricesAsks.size();i++){
				if(tradeNext.getPrice() == oldPricesAsks[i]){
					fileWithIntentions << "AGGRESSIVE BUY " << tradeNext.getQuantity() << "@" << tradeNext.getPrice() << std::endl;
				}
			}
		} 
		if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			
			// This is case when book come after trade in json file
			
			BOOK bookNext = boost::any_cast<BOOK>(*it);
			TRADE tradePrev = boost::any_cast<TRADE>(*prev);
			BOOK prevBook;
			auto reverse = it;
			for(;reverse--!=booksAndTrades.begin();){
				if(reverse->type().hash_code() == typeid(BOOK).hash_code()){
					boost::any realValue = *reverse;
					prevBook = boost::any_cast<BOOK>(realValue);	
					break;
				}
			}
			if(bookNext.getBids().size()==prevBook.getBids().size()){
				for(int i=0;i<prevBook.getBids().size();i++){
                    if((bookNext.getBids())[i].getQuantity() - (prevBook.getBids())[i].getQuantity() > 0){
						double kolicina = (bookNext.getBids())[i].getQuantity() - (prevBook.getBids())[i].getQuantity();
						fileWithIntentions << "PASSIVE BUY " << kolicina << "@" << bookNext.getBids()[i].getPrice() << std::endl;
                    } 
                }
			} else if(bookNext.getBids().size()!=prevBook.getBids().size()){
				//cout << "Ovdje je drugi uslov kada nisu iste duzine bids" << endl;
				std::vector<double> oldPrices;
				for(int k=0;k<prevBook.getBids().size();k++){
					oldPrices.push_back(prevBook.getBids()[k].getPrice());
				}
				for(int j=0;j<bookNext.getBids().size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.getBids()[j].getPrice())==oldPrices.end()){
						fileWithIntentions << "PASSIVE BUY " << bookNext.getBids()[j].getQuantity() << "@" << bookNext.getBids()[j].getPrice() << std::endl;
					}
				}
			} 
			if(bookNext.getAsks().size() == prevBook.getAsks().size()){
				for(int i=0;i<prevBook.getAsks().size();i++){
                    if((bookNext.getAsks())[i].getQuantity() - (prevBook.getAsks())[i].getQuantity()-tradePrev.getQuantity() >= 0){
						double kolicina = (bookNext.getAsks())[i].getQuantity() - (prevBook.getAsks())[i].getQuantity();
						fileWithIntentions << "PASSIVE SELL " << kolicina << "@" << bookNext.getAsks()[i].getPrice() << std::endl;
                    } 
                }
			} else if(bookNext.getAsks().size()!=prevBook.getAsks().size()){
				std::vector<double> oldPrices;
				for(int k=0;k<prevBook.getAsks().size();k++){
					oldPrices.push_back(prevBook.getAsks()[k].getPrice());
				}
				for(int j=0;j<bookNext.getAsks().size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.getAsks()[j].getPrice())==oldPrices.end()){
						fileWithIntentions << "PASSIVE SELL " << bookNext.getAsks()[j].getQuantity() << "@" << bookNext.getAsks()[j].getPrice() << std::endl;
					}
				}
			} 
		}
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			
			// This is case when trade come after trade in json file
			
			TRADE prevTrade = boost::any_cast<TRADE>(*prev);
			TRADE nextTrade = boost::any_cast<TRADE>(*it);
			BOOK prevBook;
			auto reverse = it;
			for(;reverse--!=booksAndTrades.begin();){
				if(reverse->type().hash_code() == typeid(BOOK).hash_code()){
					boost::any realValue = *reverse;
					prevBook = boost::any_cast<BOOK>(realValue);	
					break;
				}
			}
			std::vector<double> allBidsPrices,allAsksPrices;
			for(int i=0;i<prevBook.getBids().size();i++){
				allBidsPrices.push_back(prevBook.getBids()[i].getPrice());
			}
			for(int j=0;j<prevBook.getAsks().size();j++){
				allAsksPrices.push_back(prevBook.getAsks()[j].getPrice());
			}
			for(int i=0;i<allBidsPrices.size();i++){
				if(nextTrade.getPrice() == allBidsPrices[i]){
					fileWithIntentions << "AGGRESSIVE SELL " << nextTrade.getQuantity() << "@" << nextTrade.getPrice() << std::endl;
				} 
			}
			for(int j=0;j<allAsksPrices.size();j++){
				if(nextTrade.getPrice() == allAsksPrices[j]){
					fileWithIntentions << "AGGRESSIVE BUY " << nextTrade.getQuantity() << "@" << nextTrade.getPrice() << std::endl;
				}
			}
			
		}
	}
	fileWithIntentions.close();
}

