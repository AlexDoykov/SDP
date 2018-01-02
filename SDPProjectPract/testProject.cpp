#include <iostream>
#include "Tree.h"
#include "Hash.h"

int main(){
	Hash table;
	std::string testString = "ABRACADABRA";
	for(int i = 0; i < testString.size(); i++){
		table.add(testString[i]);
	}

	table.sort();

	std::vector<Tree> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		trees.push_back((*it));
	}
	
	std::vector<Tree>::iterator it;
	while(trees.size() > 1){
		it = trees.begin();
		std::vector<Tree>::iterator oldIt = it;
		Tree tree1 = (*it);
		Tree tree2 = (*(++it));

		
		unsigned newRootData = tree1.rootData() + tree2.rootData();

		trees.erase(trees.begin());
		trees.erase(trees.begin());
		trees.insert(trees.begin(), Tree(std::make_pair(char(), newRootData), 
										tree1, tree2));
	}

	std::cout<<"====================\n";
	(*trees.begin()).print();
	std::cout<<"====================\n";

	return 0;
}