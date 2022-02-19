void mainLogicFunction(const vector<any>& booksAndTrades){
    vector<any>::iterator it;
    vector<any>::iterator secondit = prev(it);
    for(it=booksAndTrades.begin();it!=booksAndTrades.end();it++){
        if(it->typeid().hash_code() == typeid(BOOK).hash_code() && secondit->typeid().hash_code() == typeid(BOOK).hashcode()){ //Ovo znaci da su oba BOOK
            if(it->bids.size() == secondit->bids.size()){
                for(int i=0;i<secondit->bids.size();i++){
                    if((secondit->bids)[i].quantity - (it->bids)[i].quantity > 0){
                        cout << "PASSIVE BUY " << razlika << "@" << cijena << endl;
                    } else if((secondit->bids)[i].quantity - (it->bids)[i].quantity < 0){
                        cout << "CANCELED " << kolicina << cijena << endl;
                    }
                }
            } else if(it->bids.size()!=second->it.bids.size()){
                vector<BOOK> difference;
                set_symmetric_difference(
                    (it->bids).begin(),(it->bids).end(),
                    (second->bids).begin(),(secondit->bids).end(),
                    back_inserter(difference));
                cout << "PASSIVE BUY " << difference[0].quantity << "@" << difference[0].price << endl;
            } // Isto dalje treba i za ask implementirati
        } else if(it->typeid().hash_code() == typeid(TRADE).hash_code() && secondit->typeid().hash_code() == typeid(BOOK).hashcode()){ //Ovo znaci da je prvi trade a drugi book
            if(it->price == secondit->bids[0].price ){
                cout << "AGGRESSIVE SELL " << it->quantiy << "@" << it->price << endl;
                secondit->bids[0].quantity = secondit->bids[0].quantity - it->quantity;
            } else if(it->price == second->asks[0].price){
                cout << "AGGRESSIVE BUY " << it->quantity << "@" << it->price << endl;
                secondit->asks[0].quantiy = secondit->asks[0].quantity - it->quantity;
            }
        } else if(it->typeid().hash_code() == typeid(BOOK).hash_code() && secondit->typeid().hash_code() == typeid(TRADE).hashcode()){ //Ovo znaci da je prvi book a drugi trade
            vector<any>::reverse_iterator reverseit;
            for(reverseit=it;it!=booksAndTrades.begin();reverseit--){
                if(reverseit->typeid().hash_code() == typeid(BOOK).hash_code()){
                    //radi logiku za books and books
                }
            }
        } else if(it->typeid().hash_code() == typeid(TRADE).hash_code() && secondit->typeid().hash_code() == typeid(TRADE).hashcode()){
            vector<any>::reverse_iterator = revIt;
            if(it->price == secondit->book[0].price){
                cout << "AGGRESSIVE SELL " << it->quantiy << "@" << it->price << endl;
                secondit->bids[0].quantity = secondit->bids[0].quantity - it->quantity; 
                for(revIt = it;revIt!=booksAndTrades.begin();revIt--){
                    //neka logika ovdje nisam dalje mogao da razmisljam 
                }
            }
        }
    }
}
