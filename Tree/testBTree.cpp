#include <iostream>
#include "doctest.h"
#include "BTree.h"



TEST_CASE("create tree"){
	BTree<int> tree;
	SUBCASE("with insert"){
		CHECK(tree.insert(1, "R") == 0);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.insert(1, "") == 0);
	}
}

TEST_CASE("test counters"){
	BTree<int> tree;
	SUBCASE("count"){
		CHECK(tree.count() == 0);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.count() == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		CHECK(tree.count() == 7);
	}

	SUBCASE("count even nodes"){
		CHECK(tree.countEvens() == 0);	
		CHECK(tree.insert(1, "") == 1);

		CHECK(tree.countEvens() == 0);	
		
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		CHECK(tree.countEvens() == 3);	
	}

	SUBCASE("height of tree"){
		CHECK(tree.height() == 0);
		CHECK(tree.insert(1, "") == 1);

		CHECK(tree.height() == 1);
		
		CHECK(tree.insert(2, "L") == 1);
		
		CHECK(tree.height() == 2);
		
		CHECK(tree.insert(3, "R") == 1);
		
		CHECK(tree.height() == 2);
		
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		CHECK(tree.height() == 4);	
	}

	SUBCASE("count tree leaves"){
		CHECK(tree.countLeaves() == 0);

		CHECK(tree.insert(1, "") == 1);
		
		CHECK(tree.countLeaves() == 1);

		CHECK(tree.insert(2, "L") == 1);

		CHECK(tree.countLeaves() == 1);

		CHECK(tree.insert(3, "R") == 1);

		CHECK(tree.countLeaves() == 2);

		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);
		
		CHECK(tree.countLeaves() == 3);	
	}

	SUBCASE("max leaf"){
		//CHECK(tree.maxLeaf() == false);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.maxLeaf() == 1);	
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.maxLeaf() == 7);	
	}
}

TEST_CASE("get element of the tree"){
	BTree<int> tree;
	SUBCASE("getElement"){
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		CHECK(tree.getElement("RR") == 6);
		CHECK(tree.getElement("RRR") == 7);
		CHECK(tree.getElement("") == 1);
		//CHECK(tree.getElement("RD") == 1);
	}

	SUBCASE("list all leaves"){
		std::vector<int> testResult1 = {};
		std::vector<int> result1 = tree.listLeaves();
		CHECK(result1.size() == testResult1.size());
		CHECK(result1 == testResult1);
		CHECK(tree.insert(1, "") == 1);
		std::vector<int> testResult2 = {1};
		std::vector<int> result2 = tree.listLeaves();
		CHECK(result2.size() == testResult2.size());
		CHECK(result2 == testResult2);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		std::vector<int> testResult3 = {4, 5, 7};
		std::vector<int> result3 = tree.listLeaves();
		CHECK(result3.size() == testResult3.size());
		CHECK(result3 == testResult3);
	}

	/*SUBCASE("trace"){
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);

		std::string testResult = "RRR";
		std::string result = tree.findTrace(7);
		CHECK(result.size() == testResult.size());
		CHECK(result == testResult);
	}*/
}

TEST_CASE("check equal levels"){
	BTree<int> tree;
	SUBCASE("check for equal levels"){
		CHECK(tree.count() == 0);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.count() == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(10, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);
		CHECK(tree.insert(10, "LRR") == 1);
		CHECK(tree.insert(15, "LRRL") == 1);

		std::vector<std::unordered_set<int>> expectedResult = { {1}, {2, 10}, {4, 5, 6}, {7, 10}, {15}};
		std::vector<std::unordered_set<int>> result = tree.checkForEqualLevels();

		CHECK(tree.checkForEqualLevels() == expectedResult);
	}
}