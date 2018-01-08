#include <iostream>
#include <queue>
#include "Tree.h"
#include "Hash.h"

/*string binarySequence(const Tree& tree, const string& str){
	if(str.size() == 0){
		return "";
	}

	return tree.trace(str[0]) + 
			binarySequence(tree, str.erase(str.begin()));
}*/

struct Compare{
	bool operator()(Tree t1, Tree t2){
		if(t1.rootData().second == t2.rootData().second){
			return t1.rootData().first > t2.rootData().first;
		}
		return t1.rootData().second > t2.rootData().second;
	}
};

Tree buildHuffmanTree(std::priority_queue<Tree, std::vector<Tree>, Compare> trees){
	while(trees.size() > 1){
		std::priority_queue<Tree, std::vector<Tree>, Compare> print = trees;
		while(!print.empty()){
			std::cout<<"("<<print.top().rootData().second<<" "<<print.top().rootData().first<<") ";
			print.pop();
		}
		std::cout<<std::endl;
		Tree tree1 = trees.top();
		trees.pop();
		Tree tree2 = trees.top();
		trees.pop();
		
		unsigned newRootData = tree1.rootData().second + tree2.rootData().second;

		trees.push(Tree(std::make_pair(0, newRootData), 
										tree1, tree2));

	}
	return trees.top();
}

int main(){
	Hash table;
	std::string testString = "ABRACADABRA";
	for(int i = 0; i < testString.size(); i++){
		table.add(testString[i]);
	}
	
	//std::vector<Tree> trees;
	std::priority_queue<Tree, std::vector<Tree>, Compare> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		trees.push((*it));
	}

	Tree huffmanTree = buildHuffmanTree(trees);
	//binarySequence(tree, testString);

	std::cout<<"====================\n";
	huffmanTree.print();
	std::cout<<"====================\n";

	return 0;
}