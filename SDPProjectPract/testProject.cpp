#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <queue>
#include "Tree.h"
#include "Hash.h"

struct Compare{
	bool operator()(Tree t1, Tree t2){
		if(t1.rootData().second == t2.rootData().second){
			return t1.rootData().first > t2.rootData().first;
		}
		return t1.rootData().second > t2.rootData().second;
	}
};

std::vector<unsigned char> binarySequence(map<char, string> codesTable, const string& str){
	std::vector<unsigned char> result;
	int counter = 0, k = 0;
	result.resize(k+1);
	for(int i = 0; i < str.size(); i++){
		string sequence = codesTable[str[i]];
		std::cout<<sequence<<" "<<str[i]<<std::endl;	
		for(int j = 0; j < sequence.size(); j++){
			std::cout<<sequence[j]<<std::endl;
			if(counter == 8){
				counter = 0;
				k++;
				result.resize(k+1);
			}
			result[k] |= (sequence[j] == '1') << (7 - counter);
			counter++;
		}
	}
	return result;
}

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

		trees.push(Tree(std::make_pair(char(), newRootData), 
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
	
	std::priority_queue<Tree, std::vector<Tree>, Compare> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		trees.push((*it));
	}

	Tree huffmanTree = buildHuffmanTree(trees);
	map<char, string> codesTable = huffmanTree.table();
	std::vector<unsigned char> v = binarySequence(codesTable, testString);

	std::cout<<"====================\n";
	for(std::vector<unsigned char>::iterator it = v.begin(); it != v.end(); it++){
		std::cout<<(int)(*it)<<std::endl;
	}
	std::cout<<"====================\n";

	std::ofstream f1 ("before.dot");
	huffmanTree.printDotty (f1);

	 huffmanTree.fillGaps (std::make_pair(char(), unsigned()),5);

	 std::ofstream f2 ("after.dot");
	huffmanTree.printDotty (f2);

	return 0;
}