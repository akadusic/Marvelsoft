#include "../include/klase.hpp"
#include <future>
#include <jsoncpp/json/value.h>
#include <vector>

void allNotesWithOneSymbol(std::promise<std::vector<boost::any>> && secondPromise,std::string symbol,Json::Value parsedDocument){	
	BID bidHelp;
	ASK askHelp;
	std::vector<BID> helpBids;
	std::vector<ASK> helpAsks;
	std::vector<std::vector<BID>> allBidsForOneSymbol;
	std::vector<std::vector<ASK>> allAsksForOneSymbol;
	BOOK helpBook;
	TRADE helpTrade;
	std::vector<boost::any> booksAndTrades;
	for(Json::Value::ArrayIndex i=0;i!=parsedDocument.size();i++){	
		if(parsedDocument[i]["book"]["symbol"]==symbol){
			helpBook.setSymbol(symbol);
			//helpBook.symbol = symbol;
			for(Json::Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["bid"].size();j++){
				bidHelp.setCount(((parsedDocument[i]["book"]["bid"][j])["count"].asDouble()));
				bidHelp.setQuantity(((parsedDocument[i]["book"]["bid"][j])["quantity"].asDouble()));
				bidHelp.setPrice(((parsedDocument[i]["book"]["bid"][j])["price"].asDouble()));
				helpBids.push_back(bidHelp);
			}
			for(Json::Value::ArrayIndex j=0;j!=parsedDocument[i]["book"]["ask"].size();j++){
				askHelp.setCount(((parsedDocument[i]["book"]["ask"][j])["count"].asDouble()));
				askHelp.setQuantity(((parsedDocument[i]["book"]["ask"][j])["quantity"].asDouble()));
				askHelp.setPrice(((parsedDocument[i]["book"]["ask"][j])["price"].asDouble()));
				helpAsks.push_back(askHelp);
			}
			helpBook.setBids(helpBids);
			helpBook.setAsks(helpAsks);
			//helpBook.bids = helpBids;
			//helpBook.asks = helpAsks;
			helpBids.clear();
			helpAsks.clear();
			boost::any book = helpBook;
			booksAndTrades.push_back(book);   
		}
		if(parsedDocument[i]["trade"]["symbol"]==symbol){
			helpTrade.setSymbol(symbol);
			helpTrade.setQuantity(parsedDocument[i]["trade"]["quantity"].asDouble());
			helpTrade.setPrice(parsedDocument[i]["trade"]["price"].asDouble());
			boost::any trade = helpTrade;
			booksAndTrades.push_back(trade);
		}
	}
	secondPromise.set_value(booksAndTrades);
	//return booksAndTrades;
}

