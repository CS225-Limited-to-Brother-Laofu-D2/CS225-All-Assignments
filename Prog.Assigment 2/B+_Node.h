#ifndef BPLUS_NODE
#define BPLUS_NODE

enum NODE_TYPE
{
    // the type of the node
	INTERNAL,   
	LEAF
}; 
enum SIBLING_DIRECTION
{
    // Sibling direction: left sibling, right sibling
	LEFT,
	RIGHT
}; 

const int ORDER = 5;					 	// Order of B+ tree (minimum number of small trees of non-root nodes)
const int MINNUM_KEY = ORDER - 1;		 	// Minimum number of keys
const int MAXNUM_KEY = 2 * ORDER - 1;	 	// Maximum number of keys
const int MINNUM_CHILD = MINNUM_KEY + 1; 	// Minimum number of child_trees
const int MAXNUM_CHILD = MAXNUM_KEY + 1; 	// maximum number of child_trees
const int MINNUM_LEAF = MINNUM_KEY;		 	// Minimum number of leaf keys
const int MAXNUM_LEAF = MAXNUM_KEY;		 	// Maximum number of leaf keys

// Node base class
template <typename KeyType, typename DataType>
class CNode
{
public:
	CNode();    // constrcutor
	virtual ~CNode();   // destructor

	NODE_TYPE getType() const;
	void setType(NODE_TYPE type);
	int getKeyNum() const;
	void setKeyNum(int n);
	KeyType getKeyValue(int i) const;
	void setKeyValue(int i, KeyType key);

	int getKeyIndex(KeyType key) const; // Find the index where the key value is stored in the node
	// Pure virtual functions that define interfaces
	virtual void removeKey(int keyIndex, int childIndex) = 0;																				  // Removes the key value from the node
	virtual void split(CNode *parentNode, int childIndex) = 0;																				  // Split node
	virtual void mergeChild(CNode<KeyType, DataType> *parentNode, CNode<KeyType, DataType> *childNode, int keyIndex) = 0;					  // merge nodes
	virtual void clear() = 0;																												  // Emptying the node also empties the subtree nodes that the node contains
	virtual void borrowFrom(CNode<KeyType, DataType> *destNode, CNode<KeyType, DataType> *parentNode, int keyIndex, SIBLING_DIRECTION d) = 0; // Borrow a key from a sibling
	virtual int getChildIndex(KeyType key, int keyIndex) = 0;																			      // Gets the child node pointer subscript based on the key value

protected:
	NODE_TYPE m_Type;
	int m_KeyNum;
	KeyType m_KeyValues[MAXNUM_KEY];
};

// Internal nodes
template <typename KeyType, typename DataType>
class CInternalNode : public CNode<KeyType, DataType>
{
public:
	CInternalNode();
	virtual ~CInternalNode();

	CNode<KeyType, DataType> *getChild(int i) const;
	void setChild(int i, CNode<KeyType, DataType> *child);

	void insert(int keyIndex, int childIndex, KeyType key, CNode<KeyType, DataType> *childNode);
	virtual void split(CNode<KeyType, DataType> *parentNode, int childIndex);
	virtual void mergeChild(CNode<KeyType, DataType> *parentNode, CNode<KeyType, DataType> *childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode<KeyType, DataType> *destNode, CNode<KeyType, DataType> *parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex);

private:
	CNode<KeyType, DataType> *m_Childs[MAXNUM_CHILD];
};

// leaf nodes
template <typename KeyType, typename DataType>
class CLeafNode : public CNode<KeyType, DataType>
{
    // Modify log TODO
    // #1. Write pour: Pour from overflow into main, in order!!
    // #2. Insert: if main + overflow capacity > The capacity of main is inserted into main, otherwise it is inserted into Overflow
    // #3. Change getData: before getting any data, pour
    // #4. Pour before changing setData: set any data
    // #5. Change getDataAddr to get the address of any data
    // #6. Change split: Before split, pour
    // #7. Change the mergeChild operation: Before merge, perform the pour operation
    // #8. Change removeKey: pour before removing any data
    // #9. Change clear: Pour before clear
    // #8. Change removeKey: pour before removing any data
    // #11. Pour before getChildIndex: get
    // #12. Change the constructor to overflow size 0
    // #13. Write sortOverflow: Sort keys and data in overflow array
    // #14. Print, pour

public:
	CLeafNode();
	virtual ~CLeafNode();

	CLeafNode<KeyType, DataType> *getLeftSibling() const;
	void setLeftSibling(CLeafNode<KeyType, DataType> *node);
	CLeafNode<KeyType, DataType> *getRightSibling() const;
	void setRightSibling(CLeafNode<KeyType, DataType> *node);
	DataType getData(int i);
	void setData(int i, const DataType &data);

	DataType *getDataAddr(int i);

	void mainInsert(KeyType key, const DataType data);
	void insert(KeyType key, const DataType data);
	virtual void split(CNode<KeyType, DataType> *parentNode, int childIndex);
	virtual void mergeChild(CNode<KeyType, DataType> *parentNode, CNode<KeyType, DataType> *childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode<KeyType, DataType> *destNode, CNode<KeyType, DataType> *parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex);

	// Actions related to Overflow Block
	void pour();
	void sortOverflow();
	void overflowInsert(KeyType key, const DataType data);

private:
	CLeafNode<KeyType, DataType> *m_LeftSibling;
	CLeafNode<KeyType, DataType> *m_RightSibling;
	DataType m_Data[MAXNUM_LEAF];

	// Additional Overflow Block
	KeyType m_keys_overflow[ORDER/2];
	DataType m_data_overflow[ORDER/2];
	int m_overflow_size;
};

#endif