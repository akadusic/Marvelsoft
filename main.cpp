#include <boost/property_tree/ptree_fwd.hpp>
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace boost::property_tree;

int main(){
	ptree root;
	read_json("pomocni.json",root);
	string knjiga = root.get<string>("book.symbol");
	cout << knjiga;
	return 0;
}
