#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Probna {
	double count;
	double quantity;
	double price;
};

int main(){
	Probna jedan, dva, tri, cetiri, peti, sesti;
	
	jedan.count = 1;
	jedan.quantity = 1300;
	jedan.price = 50.10;
	
	dva.count = 1;
	dva.quantity = 900;
	dva.price = 50.12;
	
	tri.count = 3;
	tri.quantity = 1300;
	tri.price = 50.12;

	cetiri.count = 3;
	cetiri.quantity = 1530;
	cetiri.price = 50.12;

	peti.count = 1;
	peti.quantity = 4500;
	peti.price = 50.13;

	sesti.count = 1;
	sesti.quantity = 3200;
	sesti.price = 50.13;

	vector<Probna> prazan,prviV,drugiV,treciV, cetvrtiV, petiV, sestiV;
	//prazan.push_back({});
	cetvrtiV.push_back(cetiri);
	cetvrtiV.push_back(jedan);
	//cetvrtiV.push_back(jedan);
	petiV.push_back(peti);
	petiV.push_back(cetiri);
	petiV.push_back(jedan);

	sestiV.push_back(sesti);
	sestiV.push_back(cetiri);
	sestiV.push_back(jedan);
	
	prviV.push_back(jedan);
	
	drugiV.push_back(jedan);
	drugiV.push_back(dva);

	treciV.push_back(tri);
	treciV.push_back(jedan);

	vector<vector<Probna>> zapisi;

	zapisi.push_back(prviV);
	zapisi.push_back(drugiV);
	zapisi.push_back(treciV);
	zapisi.push_back(cetvrtiV);
	zapisi.push_back(petiV);
	zapisi.push_back(sestiV);
	for(int k=1;k<zapisi.size();k++){

	
	if(zapisi[k].size() == zapisi[k-1].size()){
		for(int i=0;i<zapisi[k-1].size();i++){
			double quant = (zapisi[k-1])[i].quantity;
			double cijena = (zapisi[k-1])[i].price;
			for(int j=0;j<zapisi[k].size();j++){
				if((zapisi[k])[j].quantity != quant && (zapisi[k])[j].price == cijena){
					if((zapisi[k])[j].quantity-quant > 0){
						cout << "PASSIVE BUY " << (zapisi[k])[j].quantity-quant << "@" << cijena << endl;
					} else if((zapisi[k])[j].quantity-quant < 0){
						cout << "CANCELED " << abs((zapisi[k])[j].quantity-quant) << "@" << cijena << endl;
					}
				} 
			}
		}
	} else {
		vector<double> oldPrices;
		for(int i=0;i<zapisi[k-1].size();i++){
			oldPrices.push_back((zapisi[k-1])[i].price);
		}
		for(int j=0;j<zapisi[k].size();j++){
			if(find(oldPrices.begin(),oldPrices.end(),(zapisi[k])[j].price)==oldPrices.end()){
				cout << "PASSIVE BUY ZA " << (zapisi[k])[j].quantity << "@" << (zapisi[k])[j].price << endl;
			}
		}
	}
}
}
