#include <iostream>
#include <algorithm>
#include "Tree.h"
#include "Hash.h"
using Pair = std::pair<char,unsigned>;

int main(){
	Hash table;
	std::string testString = "ABRACADABRA";
	for(int i = 0; i < testString.size(); i++){
		table.add(testString[i]);
	}

	std::sort(table, table.begin(), table.end(), [](Hash a, Hash b){return a.getValue().second > b.getValue().second;});

	std::vector<Tree> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		std::cout<<(*it).first<<" "<<(*it).second<<std::endl;
		trees.push_back((*it));
	}
	return 0;
}