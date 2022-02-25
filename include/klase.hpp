#include <iostream>
#include <jsoncpp/json/value.h>
#include <ostream>
#include <vector>
#include <jsoncpp/json/json.h>
#include <vector>
#include <boost/any.hpp>
#include <stdlib.h>
#include <algorithm>
#include <future>

class ColumnInTable {
		double count;
		
		double quantity;		
		
		double price;
	
	public:

		ColumnInTable(){
			count = 0;
			quantity = 0;
			price = 0;
		}

		ColumnInTable(double countVal, double quantityVal, double priceVal){
			count = countVal;
			quantity = quantityVal;
			price = priceVal;
		}

		virtual void print()=0;

		//Getters
		double getCount(){ return count; }
		
		double getQuantity(){ return quantity; }
		
		double getPrice(){ return price; }

		//Setters
		void setCount(double countValue){ count = countValue; }

		void setQuantity(double quantityValue){ quantity = quantityValue; }

		void setPrice(double priceValue){ price = priceValue; }
};

class BID : public ColumnInTable{
	
	public:
		void print(){
			std::cout << "Cout: " << getCount() << "Quantity: " << getQuantity() << " Price: " << getPrice() << "." << std::endl;
		}
		using ColumnInTable::ColumnInTable;
};

class ASK : public ColumnInTable{
	
	public:
		void print(){
			std::cout << "Cout: " << getCount() << " Quantity: " << getQuantity() << " Price: " << getPrice() << "." << std::endl;
		}
		using ColumnInTable::ColumnInTable;
};

class BOOK {
		std::string symbol;
		
		std::vector<BID> bids;
		
		std::vector<ASK> asks;
	
	public:
		std::string getSymbol(){ return symbol; }
		
		std::vector<BID> getBids(){ return bids; }
		
		std::vector<ASK> getAsks(){ return asks; }

		void setSymbol(std::string symbolVal){ symbol = symbolVal; }
		
		void setBids(std::vector<BID> bidsVal){ bids = bidsVal; }
		
		void setAsks(std::vector<ASK> asksVal){ asks = asksVal; }
		
		BOOK(){}
		
		BOOK(const BOOK& book){
			symbol = book.symbol;
			bids = book.bids;
			asks = book.asks;
		}
		
		BOOK operator=(const BOOK& book){
			symbol=book.symbol;
			bids=book.bids;
			asks=book.asks;
			return *this;
		}
		
		BOOK(std::string simbolVal):symbol(simbolVal){}
		
		BOOK(std::vector<BID> bidsVal):bids(bidsVal){}
		
		BOOK(std::vector<ASK> asksVal):asks(asksVal){}
};

class TRADE {
		std::string symbol;
		
		double quantity;
		
		double price;
	
	public:
		std::string getSymbol(){ return symbol; }
		
		double getQuantity(){ return quantity; }
		
		double getPrice(){ return price; }

		void setSymbol(std::string symbolVal){ symbol = symbolVal; }
		
		void setQuantity(double quantityVal){ quantity = quantityVal; }
		
		void setPrice(double priceVal){ price = priceVal; }
};
