#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <queue>
#include "Tree.h"
#include "Hash.h"
Hash table;
Tree huffmanTree;

struct Compare{
	bool operator()(Tree t1, Tree t2){
		if(t1.rootData().second == t2.rootData().second){
			return t1.rootData().first > t2.rootData().first;
		}
		return t1.rootData().second > t2.rootData().second;
	}
};

dynamic_bitset<> bitsSequence(map<char, string> codesTable, const string& str) {
	dynamic_bitset<> result;
	int counter = 0, k = 0;
	//result.resize(k+1);
	for(int i = 0; i < str.size(); i++){
		string sequence = codesTable[str[i]];
		for(int j = 0; j < sequence.size(); j++){
			result.push_back((bool)(sequence[j] - '0'));
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

dynamic_bitset<> compress(const string& testString){
	for(int i = 0; i < testString.size(); i++){
		table.add(testString[i]);
	}
	
	std::priority_queue<Tree, std::vector<Tree>, Compare> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		trees.push((*it));
	}

	huffmanTree = buildHuffmanTree(trees);
	std::cout<<"====================\n";
	huffmanTree.print();
	std::cout<<"====================\n";
	map<char, string> codesTable = huffmanTree.table();
	return bitsSequence(codesTable, testString);
}

std::string decompress(const dynamic_bitset<>& bitset){
	return huffmanTree.getString(bitset);
}

int main(){

	std::string testString = "ABRACADABRA";
	dynamic_bitset<> compressed = compress(testString);
	string s;
	to_string(compressed, s);
	std::cout<<s<<std::endl;

	string decompressed = decompress(compressed);
	std::cout<<decompressed<<std::endl;

/*
	std::ofstream f1 ("before.dot");
	huffmanTree.printDotty (f1);

	 huffmanTree.fillGaps (std::make_pair(char(), unsigned()),5);

	 std::ofstream f2 ("after.dot");
	huffmanTree.printDotty (f2);*/

	return 0;
}