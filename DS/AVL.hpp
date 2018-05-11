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
    AVLNode(const Key& key, const Value& value, AVLNode* lNode,AVLNode* rNode, AVLNode* father) :
    height(0), key(new Key(key)), value(new Value(value)), lNode(lNode), rNode(rNode), father(father) {}
    
    // copy c'tor
    AVLNode(const AVLNode& node) : height(node.height), key(new Key(*node.key)), value(new Value(*node.value)), lNode(node.lNode), rNode(node.rNode), father(node.father) {}
    
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
        this->key = new Key(*node.key);
        this->value = new Value(*node.value);
        this->lNode = node.lNode;
        this->rNode = node.rNode;
        this->father = node.father;
        this->height = node.height;
        return *this;
    }
    
    Key* getKey() const {
        return this->key;
    }
    
    Value* getValue() const {
        return this->value;
    }
    
    void setKey(Key* key)  {
        delete this->key;
        this->key = new Key(*key);
    }
    
    void setValue(Value* value)  {
        delete this->value;
        this->value = new Value(*value);
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
    int getHeight() {
        return this->height;
    }
    // set left node
    void setLNode(AVLNode* lNode) {
        this->lNode = lNode;
    }
    // get left node
    AVLNode* getLNode() {
        return this->lNode;
    }
    // set right node
    void setRNode(AVLNode* rNode) {
        this->rNode = rNode;
    }
    // get right node
    AVLNode* getRNode() {
        return this->rNode;
    }
    
    int calculateHeight() { // 9.5 - ben - change lNode to this->lNode
        int lHeight = lNode == NULL ? -1 : lNode->height;
        int rHeight = rNode == NULL ? -1 : rNode->height;
        return 1 + (lHeight > rHeight ? lHeight : rHeight);
    }
    
    // operator == equal
    friend bool operator==<Key, Value>(const AVLNode<Key,Value>& firstNode, const AVLNode<Key,Value>& secondNode);
    // operator >  bigger then
    // rotations
    void LL() {
        int heightOfB = this->height;
        AVLNode* nodeA = this->lNode;
        if (this->father != NULL)  {
            if (this->father->rNode == this) {
                this->father->rNode = nodeA;
            } else {
                this->father->lNode = nodeA;
            }
        }
        nodeA->father = this->father;
        this->father = nodeA;
        this->lNode = nodeA->rNode;
        nodeA->rNode = this;
        this->height = this->calculateHeight();
        nodeA->height = nodeA->calculateHeight();
    }
    
    void LR() {
        this->lNode->RR();
        this->LL();
    }
    
    void RR() {
        //int heightofB = this->height;
        AVLNode* nodeA = this->rNode;
        if (this->father != NULL)  {
            if (this->father->rNode == this) {
                this->father->rNode = nodeA;
            } else {
                this->father->lNode = nodeA;
            }
        }
        nodeA->father = this->father;
        this->father = nodeA;
        this->rNode = nodeA->lNode;
        nodeA->lNode = this;
        this->height = this->calculateHeight();
        nodeA->height = nodeA->calculateHeight();
    }
    
    void RL() {
        this->rNode->LL();
        this->RR();
    }
    
    int BF() {
        int lHeight = lNode == NULL ? -1 : lNode->height;
        int rHeight = rNode == NULL ? -1 : rNode->height;
        return lHeight - rHeight;
    }
    
    int numOfChildren() {
        if (lNode == NULL && rNode == NULL) {
            return 0;
        } else if (lNode != NULL && rNode != NULL) {
            return 2;
        } else return 1;
    }
    
    
    bool operator>(const AVLNode& nodeToCompare){
        return *this->key > *nodeToCompare.key;
    }
    
    bool operator>(AVLNode& nodeToCompare) const {
        return *this->key > *nodeToCompare.key;
    }
    
};
// operator == compare nodes
template<class Key , class Value>
bool operator==(const AVLNode<Key,Value>& firstNode,const AVLNode<Key,Value>& secondNode ){
    return *firstNode.key == *secondNode.key;
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
    int thiscounter;
    int height;
    
public:
    enum AVLResult {ALREADYIN , SUCCESS , FAILURE,NOT_EXIST};
    
    // c'tor
    AVL() : thiscounter(0), height(0), head(NULL) {};
    
    //    explicit AVL(const AVLNode<Key,Value>& head) : thiscounter(0), height(0), head(new AVLNode<Key, Value>(head)) {
    //        this->head->setFather(NULL);
    //        this->thiscounter++;
    //    }
    
    // copy con'
    //    AVL(const AVL& avlTree) {
    //        //
    //    }
    // dest'
    
    void postOrderDelete(AVLNode<Key, Value>* head) {
        
        if (head == NULL) return;
        postOrderDelete(head->getLNode());
        postOrderDelete(head->getRNode());
        delete head;
    }
    
    ~AVL(){
        std::cout<< "tree des --- " << std::endl;
        postOrderDelete(head);
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
    
    
    //////////////////////// temporary methods //////////////////////////////////
    
    AVLNode<Key, Value>* getHead() {
        return head;
    };
    
    void getHeightsofAllNodes(AVLNode<Key, Value>* v) {
        if (v == NULL) return;
        std::cout <<  "h: " << v->getHeight() <<  ", key: " << *v->getKey() << std::endl;
        getHeightsofAllNodes(v->getLNode());
        getHeightsofAllNodes(v->getRNode());
    }
    
    /////////////////////////////////////////////////////////////////////////////
    
    int caseForCorrection(AVLNode<Key,Value>& p) {
        if (p.BF() == 2) { // (4)
            if (p.getLNode()->BF() >= 0) {
                p.LL();
            } else if (p.getLNode()->BF() == -1) {
                p.LR();
            }
            return 0;
        } else if (p.BF() == -2) {
            if (p.getRNode()->BF() <= 0) {
                p.RR();
            } else if (p.getRNode()->BF() == 1) {
                p.RL();
            }
            return 0;
        } else { // (5)
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
        
        if (current == NULL) return false;
        return *current == node;
    }
    
    // insert(x) function :
    AVLResult insert(const AVLNode<Key,Value>& node){
        
        
        AVLNode<Key, Value>* current = head;
        int maxHeight = height;
        
        if (thiscounter == 0) {
            head = new AVLNode<Key, Value>(node);
            thiscounter++;
            return SUCCESS;
        }
        
        // std::cout << *head->getKey() << std::endl;
        
        
        if (find(node)) {
            return ALREADYIN;
            /// throw ALREADY_IN;
        }
        
        AVLNode<Key, Value>*  newNode = new AVLNode<Key, Value>(node);
        if (*newNode->getKey() == 20) {
            std::cout << maxHeight << std::endl;
        }
        // find the the leaf
        while (maxHeight > 0){
            maxHeight--;
            if (*current > node) { // smaller
                if (current->getLNode() == NULL) break;
                current = current->getLNode();
            } else if (node > *current) { // bigger
                if (current->getRNode() == NULL) break;
                current = current->getRNode();
            }
        }
        
        // adding the node to  tree
        if (*current > node) {
            current->setLNode(newNode);
        } else {
            current->setRNode(newNode);
        }
        
        newNode->setFather(current);
        
        
        AVLNode<Key, Value>* p = newNode;
        AVLNode<Key, Value>* v = newNode;
        
        int result = 1;
        
        while (v != head) {
            //std::cout << *v->getKey() << std::endl;
            //std::cout << *v->getFather()->getKey() << std::endl;
            
            p = v->getFather(); // (1)
            if (p->getHeight() >= v->getHeight() + 1) break; // (2)
            p->setHeight(v->getHeight() + 1); // (3)
            if (result == 1) {
                result = caseForCorrection(*p);
            }
            
            if (head->getFather() != NULL) {
                head = head->getFather();
            }
            
            v->setHeight(v->calculateHeight());
            v = p;
            
        }
        
        height = head->getHeight();
        thiscounter++;
        
        return SUCCESS;
        
    }
    
    // delete(x)
    AVLResult deleteNode(const AVLNode<Key,Value>& node){
        if (!find(node)) {
            return NOT_EXIST;
        }
        AVLNode<Key, Value>* current = head;
        int maxHeight = this->height;
        bool pos = 0;
        // find the place that needed to delete
        while (maxHeight != 0){
            maxHeight--;
            if (*current > node) { // smaller
                current = current->getLNode();
                pos=0;
            } else if (node > *current) { // bigger
                current= current->getRNode();
                pos=1;
            } else {
                break; // found the node
            }
        }
        // handle case in which tree.size = 0;
        // pos = 1 -> v node on the right side
        // pos = 0 -> v node on the left side
        AVLNode<Key,Value>* v = current;
        if (v->numOfChildren() == 0) { // (1)
            if (pos) {
                v->getFather()->setRNode(NULL);
            } else {
                v->getFather()->setLNode(NULL);
            }
        } else if (v->numOfChildren() == 1) { // (2)
            if (pos) {
                v->getFather()->setRNode(v->getRNode() != NULL ?  v->getRNode() : v->getLNode());
                
            } else {
                v->getFather()->setLNode(v->getRNode() != NULL ?  v->getRNode() : v->getLNode());
            }
        } else { // (3)
            // found the w - following node
            AVLNode<Key,Value>* w = v->getRNode();
            while (w->numOfChildren() != 0 && (w->numOfChildren() == 2 || w->getRNode() == NULL)) {
                w = w->getLNode();
            }
            // (4) //  switch between nodes location on the tree , and ALSO updated the head if needed
            switchNodesLocation(v, w);
            v=w; // make (v) to point the new location
            // 5 // remove (v) from the tree
            if (v->numOfChildren() == 0) { // (1)
                v->getFather()->setRNode(NULL);
            }else if (v->numOfChildren()== 1) {
                v->getFather()->setLNode(v->getRNode());
                v->getRNode()->setFather(v->getFather());
            }
        }
        AVLNode<Key, Value>* current1 = v->getFather();
        delete v;
        thiscounter--;
        // updating the height of each node
        while (current1 != head) {
            int thisMaxHeight = returnMaxHeight(current1);
            current1->setHeight(thisMaxHeight); // (1)
            caseForCorrection(*current1); // (2)
            if (current1->getHeight() == thisMaxHeight) break;
            current1 = current1->getFather();
        }
        // current1->setHeight(current1->calculateHeight());
        return SUCCESS;
    }
    // 9/5 - ben - new function : return the max height / if no kids - return 0
    int returnMaxHeight(AVLNode<Key, Value>* node) {
        if (node == NULL) {
            return 0;
        }
        int lHeight = node->getLNode() == NULL ? -1 : node->getLNode()->getHeight();
        int rHeight = node->getRNode() == NULL ? -1 : node->getRNode()->getHeight();
        return 1 + (lHeight > rHeight ? lHeight : rHeight);
    }
     // 10/5 - ben - change nodes locations
    void switchNodesLocation(AVLNode<Key, Value>* first , AVLNode<Key, Value>* sec ){
        // check if null needed
        Key tempFirstKey(*(first->getKey()));
        Value tempFirstValue(*(first->getValue()));
        first->setKey(sec->getKey()); // free the OLD KEY data and allocate new space
        first->setValue(sec->getValue()); // free the OLD VALUE data and allocate new space
        sec->setKey(&tempFirstKey);
        sec->setValue(&tempFirstValue);
        
    }
};






#endif /* AVL_hpp */


