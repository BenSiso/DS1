//
//  main.cpp
//  DS
//
//  Created by Ben Siso on 04/05/2018.
//  Copyright © 2018 Ben Siso. All rights reserved.
//

#include <iostream>
#include "AVL.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    AVLNode<int, int> nodeFirst(7,4,NULL,NULL,NULL);
    AVLNode<int, int> nodeSec(1,4,NULL,NULL,NULL);
    // check op : >
    if (nodeFirst > nodeSec) {
        std::cout << "true !!!!!!" << std::endl;
    } else {
        std::cout << "check op > !!!!!!" << std::endl;
    }
    // check op : 
    return 0;
}

