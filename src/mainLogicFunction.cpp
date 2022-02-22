#include "../include/klase.hpp"

void mainLogicFunction(std::vector<boost::any>& booksAndTrades){
	std::vector<boost::any>::iterator it=booksAndTrades.begin();
	std::vector<boost::any>::iterator prev = it;
	advance(it,1);
    for(; it != booksAndTrades.end(); it++, prev++ ){
        if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
            //Ovdje je provjera kada su oba BOOK jedan za drugim u nizu
			BOOK pomocnaPrev = boost::any_cast<BOOK>(*prev);
			BOOK pomocnaNext = boost::any_cast<BOOK>(*it);
			if(pomocnaNext.bids.size() == pomocnaPrev.bids.size()){
                for(int i=0;i<pomocnaPrev.bids.size();i++){
                    if((pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity();
						std::cout << "PASSIVE BUY " << kolicina << "@" << pomocnaNext.bids[i].getPrice() << std::endl;
                    } else if((pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.bids)[i].getQuantity() - (pomocnaPrev.bids)[i].getQuantity();
                        std::cout << "CANCELED BUY " << abs(kolicina) << "@" << pomocnaNext.bids[i].getPrice() << std::endl;
						// Ovdje je cancel u redu
                    }
                }
            } else if(pomocnaNext.bids.size()!=pomocnaPrev.bids.size()){
				std::vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.bids.size();k++){
					oldPrices.push_back(pomocnaPrev.bids[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.bids.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.bids[j].getPrice())==oldPrices.end()){
						std::cout << "PASSIE BUY " << pomocnaNext.bids[j].getQuantity() << "@" << pomocnaNext.bids[j].getPrice()<< std::endl;
					}
				}
			} 
			if(pomocnaNext.asks.size() == pomocnaPrev.asks.size()){
				for(int i=0;i<pomocnaPrev.asks.size();i++){
                    if((pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity() > 0){
						double kolicina = (pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity();
						std::cout << "PASSIVE SELL " << kolicina << "@" << pomocnaNext.asks[i].getPrice() << std::endl;
                    } else if((pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity() < 0){
						double kolicina = (pomocnaNext.asks)[i].getQuantity() - (pomocnaPrev.asks)[i].getQuantity();
						std::cout << "CANCELED BY " << abs(kolicina) << "@" <<pomocnaNext.asks[i].getPrice() << std::endl;
						//Ovdje je cancel u redu
                    }
                }
			} else if(pomocnaNext.asks.size()!=pomocnaPrev.asks.size()){
				std::vector<double> oldPrices;
				for(int k=0;k<pomocnaPrev.asks.size();k++){
					oldPrices.push_back(pomocnaPrev.asks[k].getPrice());
				}
				for(int j=0;j<pomocnaNext.asks.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),pomocnaNext.asks[j].getPrice())==oldPrices.end()){
						std::cout << "PASSIVE SELL " << pomocnaNext.asks[j].getQuantity() << "@" << pomocnaNext.asks[j].getPrice()<< std::endl;
					}
				}
			}
		} 
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(BOOK).hash_code()){
			// Ovdje je provjera kada prvo book pa onda trade
			BOOK bookPrev = boost::any_cast<BOOK>(*prev);
			TRADE tradeNext = boost::any_cast<TRADE>(*it);
			std::vector<double> oldPricesBids;
			std::vector<double> oldPricesAsks;
			for(int i=0;i<bookPrev.bids.size();i++){
				oldPricesBids.push_back(bookPrev.bids[i].getPrice());
			}
			for(int i=0;i<oldPricesBids.size();i++){
				if(tradeNext.price == oldPricesBids[i]){
					std::cout << "AGGRESSIVE SELL " << tradeNext.quantity << "@" << tradeNext.price << std::endl;
				}
			}
			for(int i=0;i<bookPrev.asks.size();i++){
				oldPricesAsks.push_back(bookPrev.asks[i].getPrice());
			}
			for(int i=0;i<oldPricesAsks.size();i++){
				if(tradeNext.price == oldPricesAsks[i]){
					std::cout << "AGGRESSIVE BUY " << tradeNext.quantity << "@" << tradeNext.price << std::endl;
				}
			}
		} 
		if(it->type().hash_code() == typeid(BOOK).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
			//Ovdje je provjera kad dodje trade pa onda book
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
			if(bookNext.bids.size()==prevBook.bids.size()){
				//cout << "Ovdje je prvi uslov kada su iste duzine bids" << endl;
				for(int i=0;i<prevBook.bids.size();i++){
                    if((bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity() > 0){
						double kolicina = (bookNext.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity();
						std::cout << "PASSIVE BUY " << kolicina << "@" << bookNext.bids[i].getPrice() << std::endl;
                    } //else if((bookNext.bids)[i].getQuantity() + tradePrev.quantity < (prevBook.bids)[i].getQuantity()){
						//double kolicina = (prevBook.bids)[i].getQuantity() - (prevBook.bids)[i].getQuantity()-tradePrev.quantity;
                        //cout << "CANCELED BY" << kolicina << "@" << bookNext.bids[i].getPrice() << endl;
						//Ovdje je cancel takodjer u redu
                    //}
                }
			} else if(bookNext.bids.size()!=prevBook.bids.size()){
				//cout << "Ovdje je drugi uslov kada nisu iste duzine bids" << endl;
				std::vector<double> oldPrices;
				for(int k=0;k<prevBook.bids.size();k++){
					oldPrices.push_back(prevBook.bids[k].getPrice());
				}
				for(int j=0;j<bookNext.bids.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.bids[j].getPrice())==oldPrices.end()){
						std::cout << "PASSIVE BUY " << bookNext.bids[j].getQuantity() << "@" << bookNext.bids[j].getPrice()<< std::endl;
					}
				}
			} 
			if(bookNext.asks.size() == prevBook.asks.size()){
				//cout << "Ovdje je uslov kada su asks iste duzine" << endl;
				for(int i=0;i<prevBook.asks.size();i++){
                    if((bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity()-tradePrev.quantity >= 0){
						double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity();
						std::cout << "PASSIVE SELL " << kolicina << "@" << bookNext.asks[i].getPrice() << std::endl;
                    } // else if((bookNext.asks)[i].getQuantity() + tradePrev.quantity < (prevBook.bids)[i].getQuantity()){
						//double kolicina = (bookNext.asks)[i].getQuantity() - (prevBook.asks)[i].getQuantity()-tradePrev.quantity;
                        //cout << "CANCELED By" << kolicina << "@" << bookNext.asks[i].getPrice() << endl;
                    //}
                }
			} else if(bookNext.asks.size()!=prevBook.asks.size()){
				//cout << "Ovdje je uslov kada su asks razlicite duzine" << endl;
				std::vector<double> oldPrices;
				for(int k=0;k<prevBook.asks.size();k++){
					oldPrices.push_back(prevBook.asks[k].getPrice());
				}
				for(int j=0;j<bookNext.asks.size();j++){
					if(find(oldPrices.begin(),oldPrices.end(),bookNext.asks[j].getPrice())==oldPrices.end()){
						std::cout << "PASSIVE SELL " << bookNext.asks[j].getQuantity() << "@" << bookNext.asks[j].getPrice()<< std::endl;
					}
				}
			} 
		}
		if(it->type().hash_code() == typeid(TRADE).hash_code() && prev->type().hash_code() == typeid(TRADE).hash_code()){
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
			for(int i=0;i<prevBook.bids.size();i++){
				allBidsPrices.push_back(prevBook.bids[i].getPrice());
			}
			for(int j=0;j<prevBook.asks.size();j++){
				allAsksPrices.push_back(prevBook.asks[j].getPrice());
			}
			for(int i=0;i<allBidsPrices.size();i++){
				if(nextTrade.price == allBidsPrices[i]){
					std::cout << "AGGRESSIVE SELL" << nextTrade.quantity << "@" << nextTrade.price << std::endl;
				} 
			}
			for(int j=0;j<allAsksPrices.size();j++){
				if(nextTrade.price == allAsksPrices[j]){
					std::cout << "AGGRESSIVE BUY " << nextTrade.quantity << "@" << nextTrade.price << std::endl;
				}
			}
			
		}
	}
}
