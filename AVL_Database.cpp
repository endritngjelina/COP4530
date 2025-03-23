//Endrit Ngjelina U43630372
#include "AVL_Database.hpp"
#include <algorithm>
#include <vector>

Record::Record(const std::string& k, int v) : key(k), value(v) {}   //record class

AVLNode::AVLNode(Record* r) : record(r), left(nullptr), right(nullptr), height(1) {}    //AVLNode class

AVLTree::AVLTree() : root(nullptr), nodeCount(0) {} //AVLTree class

void IndexedDatabase::inorderHelper(AVLNode* node, std::vector<Record*>& result) const {
    if (node) {
        inorderHelper(node->left, result);
        result.push_back(node->record);
        inorderHelper(node->right, result);
    }
}

//extra
void IndexedDatabase::rangeQueryHelper(AVLNode* node, int start, int end, std::vector<Record*>& result) const { //find records within a range
    if (!node) return;  //if node is null (base case)
    
    if (start < node->record->value)rangeQueryHelper(node->left, start, end, result);   //if node value  greater than start search left subtree
    
    if (node->record->value >= start && node->record->value <= end)result.push_back(node->record);  //if node value within range add to result
    
    if (end > node->record->value) rangeQueryHelper(node->right, start, end, result);   //if node value less than end search right subtree
}

std::vector<Record*> IndexedDatabase::rangeQuery(int start, int end) {  //perform range query & initializes result vector
    std::vector<Record*> result;
    rangeQueryHelper(index.root, start, end, result);
    return result;
}

void IndexedDatabase::clearDatabase() { //function to clear database
    index.root = nullptr;   //root to null
}

int IndexedDatabase::calculateHeight(AVLNode* node) const { //calculate height of node
    if (!node) return 0;
    return std::max(calculateHeight(node->left), calculateHeight(node->right)) + 1;
}

int IndexedDatabase::getTreeHeight() const {    //get height of tree
    return calculateHeight(index.root);
}

int IndexedDatabase::getSearchComparisons(const std::string& key, int value) {
    index.searchComparisonCount = 0;  //reset counter
    Record* result = search(key, value);  //update searchComparisonCount
    return index.searchComparisonCount;
}

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) node->height = 1 + std::max(height(node->left), height(node->right));
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {//right rotation on node y, use for AVL balancing if left subtree too heavy
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;   //rotation
    y->left = T2;

    updateHeight(y);    //update heights of affected nodes
    updateHeight(x);
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {//left rotation on node x, use for AVL balancing if right subtree too heavy
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;    //rotation
    x->right = T2;

    updateHeight(x);    //update heights of affected nodes
    updateHeight(y);
}

void AVLTree::insert(Record* record) {  //insert record to tree
    root = help_insert(root, record);
}

AVLNode* AVLTree::help_insert(AVLNode* node, Record* record) { //function for recursive insertion, does BST insertion & balance tree
    if (!node) {    //if node null, create new node (base case)
        nodeCount++;
        return new AVLNode(record);
    }

    if (record->value < node->record->value) node->left = help_insert(node->left, record); //BST insert

    else if (record->value > node->record->value) node->right = help_insert(node->right, record);
    updateHeight(node);

    int balance = getBalance(node);  //balance factor to check if node is unbalanced

    //unbalanced
    if (balance < -1 && record->value > node->right->record->value)return rotateLeft(node); // right right case
    return node;
}

Record* AVLTree::search(const std::string& key, int value) const {  //reset counter @ start of search
    searchComparisonCount = 0; 
    AVLNode* foundNode = help_to_search(root, key, value);
    
    if(foundNode) return foundNode->record;
    
    return new Record("", 0);   //empty record if not found
}

AVLNode* AVLTree::help_to_search(AVLNode* node, const std::string& key, int value) const {    //function for recursive search, updates search comparison count for analysis
    if (!node) return nullptr;
    
    searchComparisonCount++; //increment counter for each node visited
    
    if (value == node->record->value && key == node->record->key) return node;
    
    if (value < node->record->value) return help_to_search(node->left, key, value);
    
    else return help_to_search(node->right, key, value);
}

void AVLTree::deleteNode(const std::string& key, int value) {   //deleting node
    root = help_deleting(root, key, value);
}

AVLNode* AVLTree::help_deleting(AVLNode* node, const std::string& key, int value) {  //function to recursive deletion, BST deletion and rebalances tree
    if (!node) return node;
    
    if (value < node->record->value) node->left = help_deleting(node->left, key, value); //tree delete
    
    else if (value > node->record->value) node->right = help_deleting(node->right, key, value);
    
    else if (!node->left || !node->right) nodeCount--;
    return node;
}

void IndexedDatabase::insert(Record* record) {  //indexedDatabase implementated
    index.insert(record);
}

Record* IndexedDatabase::search(const std::string& key, int value) {
    return index.search(key, value);
}

void IndexedDatabase::deleteRecord(const std::string& key, int value) {
    index.deleteNode(key, value);
}

int IndexedDatabase::countRecords() {
    return index.countRecords();
}

int AVLTree::countRecords() const {
    return nodeCount;
}