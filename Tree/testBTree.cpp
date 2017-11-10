#include <iostream>
#include "doctest.h"
#include "BTree.h"



TEST_CASE("create tree"){
	BTree<int> tree;
	SUBCASE("with insert"){
		CHECK(tree.count() == 0);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.count() == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.count() == 7);
		CHECK(tree.countEvens() == 3);	
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


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.count() == 7);
	}

	SUBCASE("count even nodes"){
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.countEvens() == 3);	
	}

	SUBCASE("height of tree"){
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.height() == 4);	
	}

	SUBCASE("count tree leaves"){
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.countLeaves() == 3);	
	}

	SUBCASE("max leaf"){
		CHECK(tree.insert(1, "") == 1);
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

TEST_CASE("create tree"){
	BTree<int> tree;
	SUBCASE("with insert"){
		CHECK(tree.count() == 0);
		CHECK(tree.insert(1, "") == 1);
		CHECK(tree.count() == 1);
		CHECK(tree.insert(2, "L") == 1);
		CHECK(tree.insert(3, "R") == 1);
		CHECK(tree.insert(4, "LL") == 1);
		CHECK(tree.insert(5, "LR") == 1);
		CHECK(tree.insert(6, "RR") == 1);
		CHECK(tree.insert(7, "RRR") == 1);


		CHECK(tree.insert(1, "RRRRLLLL") == 0);
		CHECK(tree.getElement("RR") == 6);
		CHECK(tree.getElement("RRR") == 7);
		CHECK(tree.getElement("") == 1);
	}
}