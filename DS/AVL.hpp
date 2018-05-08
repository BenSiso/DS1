//
//  AVL.hpp
//  DS
//
//  Created by Ben Siso on 04/05/2018.
//  Copyright © 2018 Ben Siso. All rights reserved.
//


#ifndef AVL_hpp
#define AVL_hpp

#include <cstdio>
//  ------------------------------------- AVL node -------------------------------

/*
 * Comments:
 *  - Why should we have a pointer to "Key" in "AVLNode"?
 *  - Why isn't there a getKey/getValue method?
 *  - Is there a reason "operator==" is a friend function? We can use getKey instead
 *
 *  - in "getFather", changed return value from this->height to this->father
 *  - in a few of the get functions, changed return type
 *  - changed implementation of c'tor an copy c'tor (now using init. list)
 *  - simplified operator== & operator> functions
 *  - added protection in assignment method
 *  - revised operator== declarations (as friend function)
 */
template <class Key, class Value>
class AVLNode;

template <class Key, class Value>
bool operator==(const AVLNode<Key,Value>& firstNode, const AVLNode<Key,Value>& secondNode);

template<class Key , class Value>
class AVLNode {
    Key* key;
    Value* value;
    int height;
    AVLNode* father;
    AVLNode* rNode;
    AVLNode* lNode;
    
public:
    // c'tor
    AVLNode(const Key& key,const Value& value, AVLNode* lNode,AVLNode* rNode, AVLNode* father) :
    height(0), key(new Key(key)), value(new Value(value)), lNode(lNode), rNode(rNode), father(father) {}
    
    // copy c'tor
    AVLNode(const AVLNode& node) {
        AVLNode(node.key, node.value, node.lNode, node.rNode, node.father);
    }
    
    // d'tor
    ~AVLNode(){
        delete this->key;
        delete this->value;
    }
    
    // assignment
    AVLNode& operator=(const AVLNode& node) {
        
        if (*this == node) {
            return *this;
        }
        
        delete this->key;
        delete this->value;
        this->key = new Key(node.key);
        this->value = new Value(node.value);
        this->lNode = node.lNode;
        this->rNode = node.rNode;
        this->father = node.father;
        this->height = node.height;
        return *this;
    }
    
    // set father
    void setFather(AVLNode* newFather) {
        this->father = newFather;
    }
    // get father
    AVLNode* getFather() const {
        return this->father;
    }
    // set Height
    void setHeight(int newHeight) {
        this->height = newHeight;
    }
    // get Height
    int getHeight() const {
        return this->height;
    }
    // set left node
    void setLNode(AVLNode* lNode) {
        this->lNode = lNode;
    }
    // get left node
    AVLNode* getLNode() const {
        return this->lNode;
    }
    // set right node
    void setRNode(AVLNode* rNode) {
        this->rNode = rNode;
    }
    // get right node
    AVLNode* getRNode() const {
        return this->rNode;
    }
    // operator == equal
    friend bool operator==<Key, Value>(const AVLNode<Key,Value>& firstNode, const AVLNode<Key,Value>& secondNode);
    // operator >  bigger then
    bool operator>(const AVLNode& nodeToCompare) ;
    // rotations
    void LL(AVLNode* nodeB) {
        int heightofB = nodeB->height;
        AVLNode* nodeA = nodeB->lNode;
        nodeA->father = nodeB->father;
        nodeB->father = *nodeA;
        nodeB->lNode = nodeA->rNode;
        nodeA->rNode = *nodeB;
        nodeA->height = heightofB;
        nodeB->height = nodeB->rNode->height > nodeB->lNode->height ? 1 + nodeB->rNode->height : 1 + nodeB->lNode->height;
        
    }
    
    void LR(AVLNode* nodeC) {
         AVLNode* nodeA = nodeC->lNode;
         AVLNode* nodeB = nodeA->lNode;
         nodeA->rNode = nodeB->lNode;
         nodeC->lNode = nodeB->rNode;
         nodeB->lNode = nodeA;
         nodeB->rNode = nodeC;
         nodeB->father=nodeC->father;
         nodeA->father=nodeB;
         nodeC->father=nodeB;
         nodeB->height=nodeC->height;
         nodeA->height = nodeA->rNode->height > nodeA->lNode->height ? 1 + nodeA->rNode->height : 1 + nodeA->lNode->height;
         nodeC->height = nodeC->rNode->height > nodeC->lNode->height ? 1 + nodeC->rNode->height : 1 + nodeC->lNode->height;

    }
    
    void RR(AVLNode* nodeB) {
        int heightofB = nodeB->height;
        AVLNode* nodeA = nodeB->rNode;
        nodeA->father = nodeB->father;
        nodeB->father = *nodeA;
        nodeB->rNode = nodeA->lNode;
        nodeA->lNode = *nodeB;
        nodeA->height = heightofB;
        nodeB->height = nodeB->rNode->height > nodeB->lNode->height ? 1 + nodeB->rNode->height : 1 + nodeB->lNode->height;
        
    }
    
    void RL(AVLNode* nodeC) {
        AVLNode* nodeA = nodeC->rNode;
        AVLNode* nodeB = nodeA->rNode;
        nodeA->lNode = nodeB->rNode;
        nodeC->rNode = nodeB->lNode;
        nodeB->rNode = nodeA;
        nodeB->lNode = nodeC;
        nodeB->father=nodeC->father;
        nodeA->father=nodeB;
        nodeC->father=nodeB;
        nodeB->height=nodeC->height;
        nodeA->height = nodeA->rNode->height > nodeA->lNode->height ? 1 + nodeA->rNode->height : 1 + nodeA->lNode->height;
        nodeC->height = nodeC->rNode->height > nodeC->lNode->height ? 1 + nodeC->rNode->height : 1 + nodeC->lNode->height;
        
    }
    
    int BF() {
        return lNode->height - rNode->height;
    }
    
    int numOfChildren() {
        if (lNode == NULL && rNode == NULL) {
            return 0;
        } else if (lNode != NULL && rNode != NULL) {
            return 2;
        } else return 1;
    }
    
    
};
// operator == compare nodes
template<class Key , class Value>
bool operator==(const AVLNode<Key,Value>& firstNode,const AVLNode<Key,Value>& secondNode ){
    return *firstNode.key == *secondNode.key;
}

// operator >  bigger then
template<class Key , class Value>
bool AVLNode<Key,Value>::operator>(const AVLNode& nodeToCompare){
    return *this->key > *nodeToCompare.key;
}

//  ------------------------------------- AVL TREE -------------------------------

/*
 * - Why use AVLResult? Why not use Try/Catch Mechanism?
 *
 * - added default c'tor
 * - refined "find" method: changed argument
 */
template<class Key , class Value>
class AVL {
    AVLNode<Key, Value>* head;
    int nodeCounter;
    int height;
    
public:
    enum AVLResult {ALREADYIN , SUCCESS , FAILURE,NOT_EXIST};
    
    // c'tor
    AVL() : nodeCounter(0), height(0), head(new AVLNode<Key, Value>(NULL,
                                                                    NULL,
                                                                    NULL,
                                                                    NULL,
                                                                    NULL)) {};
    
    explicit AVL(const AVLNode<Key,Value>& head) : nodeCounter(0), height(0), head(new AVLNode<Key, Value>(head)) {
        this->head->setFather(NULL);
        this->nodeCounter++;
    }
    
    // copy con'
    AVL(const AVL& avlTree) {
        //
    }
    // dest'
    ~AVL(){
        //
    }
    // set height
    void setHeight(int newHeight) {
        this->head->setHeight(newHeight);
        this->height = newHeight;
    }
    // get height
    int getHeight() {
        return this->height;
    }
    
    int caseForCorrection(AVLNode<Key,Value>& p, AVLNode<Key,Value>& v) {
        if (p.BF() == 2) { // (4)
            if (p.lNode->BF() >= 0) {
                LL(&p);
            } else if (p.lNode->BF() == -1) {
                LR(&p);
            }
            return 0;
        } else if (p.BF() == -2) {
            if (p.rNode <= 0) {
                RR(&p);
            } else if (p.rNode->BF() == 1) {
                RL(&p);
            }
            return 0;
        } else { // (5)
            v = p;
            return 1;
        }
    }
    
    // find func
    bool find(const AVLNode<Key, Value>& node) const {
        AVLNode<Key, Value>* current = head;
        int currentHeight = this->height;
        while (currentHeight != 0) {
            currentHeight--;
            if (*current > node) { // smaller
                current = current->getLNode();
            } else if (node > *current) { // bigger
                current= current->getRNode();
            } else {
                return true;
            }
        }
        
        return *current == node;
    }
    
    // insert(x) function :
    AVLResult insert(const AVLNode<Key,Value>& node){
        AVLNode<Key, Value>* current = head;
        int maxHeight = this->height;
        if (find(node)) {
            return ALREADYIN;
            /// throw ALREADY_IN;
        }
        
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(node);
        // find the the leaf
        while (maxHeight != 0){
            maxHeight--;
            if (*current > node) { // smaller
                current = current->getLNode();
            } else if (node > *current) { // bigger
                current= current->getRNode();
            }
        }
        // upadate node's fields before adding to the tree
        newNode->setFather(current);
        newNode->setHeight(0); /// shouldn't it be -1?
        newNode->setLNode(NULL);
        newNode->setRNode(NULL);

        // adding the node to  tree
        if (*current > node) {
            current->setLNode(newNode);
        } else {
            current->setRNode(newNode);
        }

        AVLNode<Key, Value>* p = newNode;
        AVLNode<Key, Value>* v = newNode;
        
        while (v != head) {
            p = v->getFather(); // (1)
            if (p->getHeight() >= v->getHeight() + 1) break; // (2)
            p->setHeight(v->getHeight() + 1); // (3)
            int result = caseForCorrection(p, v);
            if (!result) break;

        }
        
        
    }
    // delete(x)
    AVLResult deleteNode(const AVLNode<Key,Value>& node){
        if (find(node) == false ) {
            return NOT_EXIST;
        }
        AVLNode<Key, Value>* current = head;
        int maxHeight = this->height;
        bool pos = 0;
        
        while (maxHeight != 0){
            maxHeight--;
            if (current > node) { // smaller
                current = current->getLNode();
                pos=0;
            } else if (node > current) { // bigger
                current= current->getRNode();
                pos=1;
            }
        }
            
            // handle case in which tree.size = 0;
            AVLNode<Key,Value>* v = current;
            if (v->numOfChildren() == 0) { // (1)
                if (pos) {
                    v->getFather()->getRNode() = NULL;
                } else {
                    v->getFather()->getLNode() = NULL;
                }
            } else if (v->numOfChildren() == 1) { // (2)
                if (pos) {
                    v->getFather()->getRNode() = v->getRNode() != NULL ?  v->getRNode() : v->getLNode();
                } else {
                    v->getFather()->getLNode() = v->getRNode() != NULL ?  v->getRNode() : v->getLNode();
                }
            } else { // (3)
                AVLNode<Key,Value>* w = v->getRNode();
                while (w->numOfChildren() != 0 && (w->numOfChildren() == 2 || w->getRNode() == NULL)) {
                    w = w->getLNode();
                }
                
                /// (4) ///
                AVLNode<Key,Value>* temp = w;
                w = v;
                v = temp;
                
                ////////////////// (5) ///////////////////////
                if (v->numOfChildren() == 0) { // (1)
                    if (pos) {
                        v->getFather()->getRNode() = NULL;
                    } else {
                        v->getFather()->getLNode() = NULL;
                    }
                } else if (v->numOfChildren() == 1) { // (2)
                    if (pos) {
                        v->getFather()->getRNode() = v->getRNode() != NULL ?  v->getRNode() : v->getLNode();
                    } else {
                        v->getFather()->getLNode() = v->getRNode() != NULL ?  v->getRNode() : v->getLNode();
                    }
                }
            }
        
        AVLNode<Key, Value>* current1 = v->getFather();
        AVLNode<Key, Value>* current2 = v->getFather();
        delete v;
        
        while (current1 != head) {
            int maxHeight = current1->lNode->getHeight() > current1->rNode->getHeight() ? current1->lNode->getHeight() + 1 : current1->rNode->getHeight() + 1;
            current1->setHeight(maxHeight); // (1)
            caseForCorrection(*current1, *current2); // (2)
            if (current1->getHeight() == maxHeight) break; // (3)
            current1 = current1->getFather();
            
        }
            
        }
//        // if on a leaf : "merge trees no needed
//        if (current->getFather()->getLNode() == node ){
//            // update the father height
//            if (current->getFather()->getRNode()== NULL) {
//                current->getFather()->setHeight(current->getFather()->getHeight() - 1);
//            }
//            current->getFather()->setLNode(NULL);
//        } else {
//            // update the father height
//            if (current->getFather()->getLNode() == NULL) {
//                current->getFather()->setHeight(current->getFather()->getHeight() - 1);
//            }
//            current->getFather()->setRNode(NULL);
//        }
//        delete current;
//        return SUCCESS;
    // rotationL - make a rotation LEFT
    // rotationR - make a rotation RIGHT
    //fixTree - fix the tree to be AVL tree again.
    //
    
    
    
};






#endif /* AVL_hpp */

