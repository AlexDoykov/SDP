#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <queue>
#include <cstring>
#include "Tree.h"
#include "Hash.h"
//Tree huffmanTree;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::priority_queue;

struct Compare{
	bool operator()(Tree t1, Tree t2){
		return t1.rootData().second > t2.rootData().second;
	}
};

Tree buildHuffmanTree(priority_queue<Tree, vector<Tree>, Compare> trees){
	while(trees.size() > 1){
		priority_queue<Tree, vector<Tree>, Compare> print = trees;
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

void fillTable(const string& testString, Hash& table){
	//cout<<testString.size()<<endl;
	for(int i = 0; i < testString.size(); i++){
		table.add(testString[i]);
	}
}

Tree compress(const Hash& table){	
	priority_queue<Tree, vector<Tree>, Compare> trees;
	for(Hash::Iterator it = table.begin(); it != table.end(); ++it){
		trees.push((*it));
	}

	return buildHuffmanTree(trees);
}

Tree createTreeFromFile(const string& treeString, unsigned start, unsigned end){
	int bracketDiff = 0;
	int i = start;

	for(; i < end; i++){
		if(treeString[i] == '('){
			bracketDiff -= 1;
		}
		if(treeString[i] == ')'){
			bracketDiff += 1;
		}
		if(treeString[i] == ')' && bracketDiff == -1){
			int k = i + 1;
			string number;
			while(treeString[k] >= '0' && treeString[k] <= '9'){
				number += treeString[k];
				k++;
			}
			i += number.size()-1;
			if(treeString[i+2] ==','){
				return Tree(std::make_pair(treeString[i+4], atoi(number.c_str())), 
					createTreeFromFile(treeString, start + 1, i-1), 
					createTreeFromFile(treeString, i + 6, end-1));
			}else{
				return Tree(std::make_pair(char(), atoi(number.c_str())), 
					createTreeFromFile(treeString, start + 1, i), 
					createTreeFromFile(treeString, i + 2, end-1));
			}
		}
	}
	return Tree();
}

string insertIntoString(string file, const string& addition){
	for(int i = 0; i < file.size(); i++){
		if(file[i] == '.'){
			file.insert(i, addition);
			break;
		}
	}
	return file;
}

void compressMode(string inputFileName, string outputFileName){
	std::fstream input;
	input.open(inputFileName, std::ios::in);

	string inputString;
	Hash table;
	string inputFileStrings;

	while(getline(input, inputString)){
/*		if(!inputFileStrings.empty()){
			inputString.insert(inputString.end(), '\n');
		}*/
		inputFileStrings += inputString;
		//inputFileStrings += '\n';
		fillTable(inputString, table);
		inputString.clear();
	}
	input.close();

	/*for(auto elem : table){
		cout<<elem.first<<" "<<elem.second<<endl;
	}*/
	Tree huffmanTree = compress(table);

	std::fstream printTree;
	string outputFileTreeName = insertIntoString(outputFileName, "Tree");
	printTree.open(outputFileTreeName, std::ios::out);
	printTree << huffmanTree;
	printTree.close();

	map<char, string> codesTable = huffmanTree.table();
	/*for(auto code : codesTable){
		cout<<code.first<<" "<<code.second<<endl;
	}
*/
	std::fstream printBinarySequence;
	printBinarySequence.open(outputFileName, std::ios::out);
	for(char str : inputFileStrings){
		printBinarySequence << codesTable[str];
	}
	printBinarySequence.close();
}

void decompressMode(string inputFileName, string outputFileName){
	std::fstream input;
	string inputFileTreeName = insertIntoString(inputFileName, "Tree");
	input.open(inputFileTreeName, std::ios::in);
	string treeString;
	getline(input, treeString);
	input.close();

	Tree huffmanTree = createTreeFromFile(treeString, 0, treeString.size());
	//huffmanTree.print();
	string binarySequence;
	input.open(inputFileName, std::ios::in);
	getline(input, binarySequence);
	input.close();
	dynamic_bitset<> temp;
	for(auto ch : binarySequence){
		temp.push_back(ch - '0');
	}
	std::fstream output;
	output.open(outputFileName, std::ios::out);
	output<<huffmanTree.getString(temp);
	output.close();
}

int main(int argc, char *argv[]){
	string mode, inputFileName, outputFileName;
	if(argc < 6){
		cout<<"Not enough arguments.\n";
		return 0;
	}
	if(argc > 7){
		cout<<"Too many arguments.\n";
		return 0;
	}


	for(int i = 0; i < argc; i++){
		if(std::strcmp(argv[i],"-c") == 0 || std::strcmp(argv[i], "-d")  == 0){
			mode.assign(argv[i]);
		}

		if(std::strcmp(argv[i], "-i") == 0){
			i++;
			inputFileName.assign(argv[i]);
		}

		if(std::strcmp(argv[i], "-o") == 0){
			outputFileName.assign(argv[i + 1]);
		}
	}

	if(mode.empty() || inputFileName.empty() || outputFileName.empty()){
		cout<<"Please enter correct commands\n";
		return 0;
	}


	if(mode == "-c"){
		compressMode(inputFileName, outputFileName);
	}else{
		decompressMode(inputFileName, outputFileName);
	}

	return 0;
}