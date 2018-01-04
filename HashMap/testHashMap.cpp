#include <iostream>
#include "doctest.h"
#include "HashMap.h"
#include <vector>
#include <algorithm>
#define MAXN 100

unsigned hashFunction(std::string key){
	unsigned hash = 0, j = 0;
	while(j < key.size()){
		hash += key[j] * (j + 1);
		j++;
	}

	return hash;
}

unsigned hashFunctionCollisionTest(std::string key){
	return key.length();
}

TEST_CASE("create hash map"){
	/*SUBCASE("constructor"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
	}

	SUBCASE("add element"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		hMap.add("Peshoo", 81513);
		hMap.add("Gosho", 77666);
		//hMap.prettyPrint();

		hMap.add("Peshoo", 9999);
		//hMap.prettyPrint();
	}*/

	SUBCASE("add element with collision"){
		//std::cout<<"collision\n";
		HashMap<std::string, unsigned> hMap(hashFunctionCollisionTest, 250);
		hMap.add("Peshoo", 81513);
		hMap.add("Goshoo", 77666);
		//hMap.prettyPrint();

		hMap.add("Peshoo", 9999);
		/*hMap.prettyPrint();
		std::cout<<"\nsize: ";
		std::cout<<hMap.size();*/
	}

	/*SUBCASE("efficiency"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		hMap.add("Peshoo", 81513);
		hMap.add("Gosho", 77666);

		hMap.add("Peshoo", 9999);
		std::cout<<hMap.efficiency()<<std::endl;
	}

	SUBCASE("ostream"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		hMap.add("Peshoo", 81513);
		hMap.add("Gosho", 77666);

		hMap.add("Peshoo", 9999);
		//std::cout<<hMap;
	}
*/
	/*SUBCASE("find same words"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		std::string text1[MAXN], text2[MAXN];
		int n, m;
		std::cin>>n;
		for(int i = 0; i < n; i++){
			std::cin>>text1[i];
		}

		std::cin>>m;
		for(int i = 0; i < m; i++){
			std::cin>>text2[i];
		}
		for(unsigned i = 0; i < n; i++){
			if(text1[i][0] == '('){
				text1[i].erase(text1[i].begin());
			}

			if(text1[i][text1[i].length() - 1] == ')' || text1[i][text1[i].length() - 1] == ',' || text1[i][text1[i].length() - 1] == '.'){
				text1[i].erase((text1[i].end() - 1));
			}
			hMap.add(text1[i], 1);
		}
		int result  = 0;
		for(unsigned i = 0; i < m; i++){
			std::cout<<text2[i]<<std::endl;
			if(text2[i][0] == '('){
				text2[i].erase(text2[i].begin());
			}

			if(text2[i][text2[i].length() - 1] == ')' || text2[i][text2[i].length() - 1] == ',' || text2[i][text2[i].length() - 1] == '.'){
				text2[i].erase((text2[i].end() - 1));
			}
			
			if(hMap.take(text2[i]) == 1){
				//std::cout<<text2[i]<<std::endl;
				result += 1;
			}
		}
			std::cout<<"here\n";
		//std::cout<<result;
	}*/


	/*SUBCASE("find same unique words"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		std::string text1[MAXN], text2[MAXN];
		int n, m;
		std::cin>>n;
		for(int i = 0; i < n; i++){
			std::cin>>text1[i];
		}

		std::cin>>m;
		for(int i = 0; i < m; i++){
			std::cin>>text2[i];
		}
		for(unsigned i = 0; i < n; i++){
			if(text1[i][0] == '('){
				text1[i].erase(text1[i].begin());
			}

			if(text1[i][text1[i].length() - 1] == ')' || text1[i][text1[i].length() - 1] == ',' || text1[i][text1[i].length() - 1] == '.'){
				text1[i].erase((text1[i].end() - 1));
			}
			hMap.add(text1[i], 1);
		}

		HashMap<std::string, unsigned> hMap2(hashFunction, 250);
		for(unsigned i = 0; i < m; i++){
			if(text2[i][0] == '('){
				text2[i].erase(text2[i].begin());
			}

			if(text2[i][text2[i].length() - 1] == ')' || text2[i][text2[i].length() - 1] == ',' || text2[i][text2[i].length() - 1] == '.'){
				text2[i].erase((text2[i].end() - 1));
			}
	
			if(hMap.take(text2[i]) == 1){
				hMap2.add(text2[i], 1);
			}
		}

		std::cout<<hMap2.size();
	}*/

	SUBCASE("find same unique words"){
		HashMap<std::string, unsigned> hMap(hashFunction, 250);
		std::string text1[MAXN];
		int n;
		std::cin>>n;
		for(int i = 0; i < n; i++){
			std::cin>>text1[i];
		}

		for(unsigned i = 0; i < n; i++){
			if(text1[i][0] == '('){
				text1[i].erase(text1[i].begin());
			}

			if(text1[i][text1[i].length() - 1] == ')' || text1[i][text1[i].length() - 1] == ',' || text1[i][text1[i].length() - 1] == '.'){
				text1[i].erase((text1[i].end() - 1));
			}

			if(hMap.take(text1[i]) == -1){
				hMap.add(text1[i], 1);
			}else{
				hMap.add(text1[i], hMap.take(text1[i]) + 1);
			}
		}

		std::cout<<hMap.mostCommonWord()<<std::endl;
	}
}