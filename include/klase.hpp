#include <iostream>

class ColumnInTable {
		
		double count = 0;
		
		double quantity = 0;
		
		double price = 0;
	
	public:

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
};

class ASK : public ColumnInTable{
	
	public:
		void print(){
			std::cout << "Prodavac zeli da proda " << getCount() << " tura dionica u kolicinama od " << getQuantity() << " komada po cijeni " << getPrice() << ".";
		}
};

