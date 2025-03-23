#ifndef AVL_DATABASE_HPP
#define AVL_DATABASE_HPP
#include <string>
#include <vector>
#include <queue>

class Record {
public:
    std::string key;

    int value;

    Record(const std::string& k, int v);
};

class AVLNode {
public:
    Record* record;
    AVLNode* left;
    AVLNode* right;

    int height;

    AVLNode(Record* r);
};

class AVLTree {
private:
    AVLNode* root;

    mutable int searchComparisonCount;  // For measuring search complexity

    int height(AVLNode* node);
    int nodeCount; //number of nodes in tree
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);

    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* help_insert(AVLNode* node, Record* record);
    AVLNode* help_deleting(AVLNode* node, const std::string& key, int value);
    AVLNode* help_to_search(AVLNode* node, const std::string& key, int value)const;
    AVLNode* minValueNode(AVLNode* node);

    friend class IndexedDatabase;

public:
    AVLTree();
    void insert(Record* record);
    Record* search(const std::string& key, int value)const;

    void deleteNode(const std::string& key, int value);

    int getNodeCount() const { return nodeCount; }
    int getLastSearchComparisons() const { return searchComparisonCount; }
    int countRecords() const;
};

class IndexedDatabase {
private:
    AVLTree index;

    void inorderHelper(AVLNode* node, std::vector<Record*>& result) const;
    void rangeQueryHelper(AVLNode* node, int start, int end, std::vector<Record*>& result) const;
    int calculateHeight(AVLNode* node) const;

public:
    void insert(Record* record);
    void deleteRecord(const std::string& key, int value);
    Record* search(const std::string& key, int value);
    
    std::vector<Record*> rangeQuery(int start, int end);
    std::vector<Record*> findKNearestKeys(int key, int k);
    std::vector<Record*> inorderTraversal();
    void clearDatabase();
    int countRecords();
    
    // New methods for testing
    int getSearchComparisons(const std::string& key, int value);
    int getTreeHeight() const;
};

#endif // AVL_DATABASE_HPP