//
//  main.cpp
//  DS
//
//  Created by Ben Siso on 04/05/2018.
//  Copyright © 2018 Ben Siso. All rights reserved.
//

#include <iostream>
#include "AVL.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    const AVLNode<int, char> node1(2, 'a', NULL, NULL, NULL);
    const AVLNode<int,char> node2(3, 'b', NULL, NULL, NULL);
    const AVLNode<int,char> node3(4, 'c', NULL, NULL, NULL);
    const AVLNode<int,char> node4(5, 'd', NULL, NULL, NULL);
    const AVLNode<int,char> node5(12, 'e', NULL, NULL, NULL);
    const AVLNode<int,char> node6(1, 'f', NULL, NULL, NULL);
    const AVLNode<int,char> node7(9, '@', NULL, NULL, NULL);
//    const AVLNode<int,char> node8(10, '$', NULL, NULL, NULL);
//    const AVLNode<int,char> node9(11, 'x', NULL, NULL, NULL);
//    const AVLNode<int,char> node10(18, '$', NULL, NULL, NULL);
//    const AVLNode<int,char> node11(9, 'x', NULL, NULL, NULL);
//    const AVLNode<int,char> node12(10, 'x', NULL, NULL, NULL);
//
    //
    //    node1.setRNode(&node2);
    //
    //    if (node2 > node1) {
    //        cout << "yep" << endl;
    //    };
    //
    //
    //    cout << *(node1.getRNode()->getKey()) << endl;
    //    cout << (*(node1.getRNode()) == node2 ? "yes" : "no") << endl;
    
    
    AVL<int, char> tree;
    tree.insert(node1);
    tree.insert(node2);
    tree.insert(node3);
    tree.insert(node4);
    tree.insert(node5);
    tree.insert(node6);
    tree.insert(node7);
    tree.getHeightsofAllNodes(tree.getHead());
    std::cout << "--------------" << std::endl;
    tree.deleteNode(node6); //
    std::cout << "--------------" << std::endl;
    tree.getHeightsofAllNodes(tree.getHead());

    
    return 0;
}


