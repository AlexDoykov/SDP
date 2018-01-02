#include<iostream>
#include "BinTree-is_BOT.h"
 
int main ()
{
    BinTree tree;
    tree.add(20, "");
    tree.add(10, "L");
    tree.add(5, "LL");
    tree.add(3, "LLL");
    tree.add(1, "LLLL");
    tree.add(4, "LLLR");
    tree.add(7, "LLR");
    tree.add(6, "LLRL");
    tree.add(8, "LLRR");
    tree.add(9, "LLRRR");
    tree.add(15, "LR");
    tree.add(13, "LRL");
    tree.add(12, "LRLL");
    tree.add(14, "LRLR");
    tree.add(18, "LRR");
    tree.add(17, "LRRL");
    tree.add(19, "LRRR");
    tree.add(25, "R");
    tree.add(23, "RL");
    tree.add(21, "RLL");
    tree.add(22, "RLLR");
    tree.add(24, "RLR");
    tree.add(26, "RR");
    tree.add(28, "RRR");
    tree.add(27, "RRRL");
    tree.add(19, "RRRR");

    std::cout<<tree.is_BOT()<<std::endl;
    return 0;
}