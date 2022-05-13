#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include "B+_Node.cpp"
#include <vector>
using namespace std;

enum COMPARE_OPERATOR
{
	LT,
	LE,
	EQ,
	BE,
	BT,
	BETWEEN
}; // Comparison operator：<、<=、=、>=、>、<>
const int INVALID_INDEX = -1;

template <typename KeyType, typename DataType>
struct SelectResult
{
	int keyIndex;
	CLeafNode<KeyType, DataType> *targetNode;
};

template <typename KeyType, typename DataType>
class CBPlusTree
{
public:
	// Constructor & destructor
	CBPlusTree();
	~CBPlusTree();

	// interface
	bool insert(KeyType key, const DataType data);
	bool remove(KeyType key);
	bool update(KeyType oldKey, KeyType newKey);

	// Constant value query，compareOperator can be LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)
	vector<DataType> oneSideSelect(KeyType compareKey, int compareOpeartor) const;

	// Range query，BETWEEN
	vector<DataType> twoSideSelect(KeyType smallKey, KeyType largeKey) const;

	// search whether existence
	bool search(KeyType key) const;

	// Get a pointer to data for key
	DataType *getDataHandle(KeyType key) const;

	// clear
	void clear();

	// Print all keys (in tree form)
	void print() const;

	// Print all data
	void printData() const;

private:
	void recursive_insert(CNode<KeyType, DataType> *parentNode, KeyType key, const DataType data);
	void recursive_remove(CNode<KeyType, DataType> *parentNode, KeyType key);
	void printInConcavo(CNode<KeyType, DataType> *pNode, int count) const;
	bool recursive_search(CNode<KeyType, DataType> *pNode, KeyType key) const;
	void recursive_search(CNode<KeyType, DataType> *pNode, KeyType key, SelectResult<KeyType, DataType> &result);
	DataType *recursive_getDataHandle(CNode<KeyType, DataType> *pNode, KeyType key) const;
	void changeKey(CNode<KeyType, DataType> *pNode, KeyType oldKey, KeyType newKey);
	void search(KeyType key, SelectResult<KeyType, DataType> &result);
	void remove(KeyType key, DataType &dataValue);
	void recursive_remove(CNode<KeyType, DataType> *parentNode, KeyType key, DataType &dataValue);

private:
	CNode<KeyType, DataType> *m_Root;
	CLeafNode<KeyType, DataType> *m_DataHead;
	KeyType m_MaxKey; // The largest key in the B+ tree
};

#endif