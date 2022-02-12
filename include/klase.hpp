#include <iostream>

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
			std::cout << "Kupac zeli da kupi " << getCount() << " tura dionica u kolicinama od " << getQuantity() << " komada po cijeni " << getPrice() << ".";
		}
		using ColumnInTable::ColumnInTable;
};

class ASK : public ColumnInTable{
	
	public:
		void print(){
			std::cout << "Prodavac zeli da proda " << getCount() << " tura dionica u kolicinama od " << getQuantity() << " komada po cijeni " << getPrice() << ".";
		}
		using ColumnInTable::ColumnInTable;
};

