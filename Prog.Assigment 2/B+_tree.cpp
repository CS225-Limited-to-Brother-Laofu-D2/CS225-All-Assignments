#pragma once
#include "B+_tree.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename KeyType, typename DataType>
CBPlusTree<KeyType, DataType>::CBPlusTree()
{
	m_Root = NULL;
	m_DataHead = NULL;
}

template <typename KeyType, typename DataType>
CBPlusTree<KeyType, DataType>::~CBPlusTree()
{
	clear();
}

template <typename KeyType, typename DataType>
bool CBPlusTree<KeyType, DataType>::insert(KeyType key, const DataType data)
{
	// cout << "check0" << endl;
	// Whether it already exists
	if (search(key))
	{
		// cout << "check1" << endl;
		return false;
	}
	// Find a leaf that can be inserted, or create a new leaf
	if (m_Root == NULL)
	{
		// cout << "check2" << endl;
		m_Root = new CLeafNode<KeyType, DataType>;
		m_DataHead = (CLeafNode<KeyType, DataType> *)m_Root;
		m_MaxKey = key;
	}
	if (m_Root->getKeyNum() >= MAXNUM_KEY) // The root is full, split
	{
		// cout << "check3" << endl;
		CInternalNode<KeyType, DataType> *newNode = new CInternalNode<KeyType, DataType>; // Create a new root node
		newNode->setChild(0, m_Root);
		m_Root->split(newNode, 0); // Leaf node splitting
		m_Root = newNode;		   // Update the root node pointer
	}
	if (key > m_MaxKey) // Update the maximum key value
	{
		// cout << "check4" << endl;
		m_MaxKey = key;
	}
	recursive_insert(m_Root, key, data);
	return true;
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::recursive_insert(CNode<KeyType, DataType> *parentNode, KeyType key, const DataType data)
{
	if (parentNode->getType() == LEAF) // Leaf node, directly inserted
	{
		// cout << "here" << endl;
		((CLeafNode<KeyType, DataType> *)parentNode)->insert(key, data);
	}
	else
	{
		// Find the child_Node
		int keyIndex = parentNode->getKeyIndex(key);
		int childIndex = parentNode->getChildIndex(key, keyIndex); // Child node pointer index
		CNode<KeyType, DataType> *childNode = ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex);
		if (childNode->getKeyNum() >= MAXNUM_LEAF) // The child_Nodes are full and need to be split
		{
			childNode->split(parentNode, childIndex);
			if (parentNode->getKeyValue(childIndex) <= key) // Determine the target child
			{
				childNode = ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex + 1);
			}
		}
		recursive_insert(childNode, key, data);
	}
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::clear()
{
	if (m_Root != NULL)
	{
		m_Root->clear();
		delete m_Root;
		m_Root = NULL;
		m_DataHead = NULL;
	}
}

template <typename KeyType, typename DataType>
bool CBPlusTree<KeyType, DataType>::search(KeyType key) const
{
	return recursive_search(m_Root, key);
}

template <typename KeyType, typename DataType>
bool CBPlusTree<KeyType, DataType>::recursive_search(CNode<KeyType, DataType> *pNode, KeyType key) const
{
	if (pNode == NULL) // Checks whether the node pointer is empty or whether the node is a leaf node
	{
		return false;
	}
	else
	{
		int keyIndex = pNode->getKeyIndex(key);
		int childIndex = pNode->getChildIndex(key, keyIndex); // Child node pointer index
		if (keyIndex < pNode->getKeyNum() && key == pNode->getKeyValue(keyIndex))
		{
			return true;
		}
		else
		{
			if (pNode->getType() == LEAF) // Check whether the node is a leaf node
			{
				return false;
			}
			else
			{
				return recursive_search(((CInternalNode<KeyType, DataType> *)pNode)->getChild(childIndex), key);
			}
		}
	}
}

template <typename KeyType, typename DataType>
DataType *CBPlusTree<KeyType, DataType>::getDataHandle(KeyType key) const
{
	return recursive_getDataHandle(m_Root, key);
}

template <typename KeyType, typename DataType>
DataType *CBPlusTree<KeyType, DataType>::recursive_getDataHandle(CNode<KeyType, DataType> *pNode, KeyType key) const
{
	// cout << "first" << endl;
	if (pNode == NULL) // Checks whether the node pointer is empty or whether the node is a leaf node
	{
		return nullptr;
	}

	int keyIndex = pNode->getKeyIndex(key);
	int childIndex = pNode->getChildIndex(key, keyIndex); // Child node pointer index

	// cout << "second" << endl;
	if (pNode->getType() == LEAF)
	{
		// ((CLeafNode<KeyType, DataType> *)pNode)->pour();

		// cout << "now \"pnode\" points to a leaf." << endl;
		// cout << "key to get handle: " << key << endl;
		// cout << "keyindex: " << keyIndex << endl;
		// cout << "childindex: " << childIndex << endl;
		// cout << "pNode->getKeyNum(): " << pNode->getKeyNum() << endl;
		// cout << "pNode->getKeyValue(keyIndex): " << pNode->getKeyValue(keyIndex) << endl;

		if (keyIndex < pNode->getKeyNum() && key == pNode->getKeyValue(keyIndex))
		{
			// cout << "third" << endl;
			return ((CLeafNode<KeyType, DataType> *)pNode)->getDataAddr(childIndex);
		}
		else
		{
			// cout << "fourth" << endl;
			return nullptr;
		}
	}
	else
		// cout << "\"pnode\" still points to an internal node." << endl;

	return recursive_getDataHandle(((CInternalNode<KeyType, DataType> *)pNode)->getChild(childIndex), key);
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::print() const
{
	cout << endl;
	cout << endl;
	cout << "Now print the keys in tree form:" << endl
		 << endl;
	printInConcavo(m_Root, 10);
	cout << endl;
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::printInConcavo(CNode<KeyType, DataType> *pNode, int count) const
{
	if (pNode->getType() == LEAF)
		((CLeafNode<KeyType, DataType> *)pNode)->pour();
	if (pNode != NULL)
	{
		int i, j;
		for (i = 0; i < pNode->getKeyNum(); ++i)
		{
			if (pNode->getType() != LEAF)
			{
				printInConcavo(((CInternalNode<KeyType, DataType> *)pNode)->getChild(i), count - 2);
			}
			for (j = count; j >= 0; --j)
			{
				cout << "---";
			}
			cout << pNode->getKeyValue(i) << endl;
		}
		if (pNode->getType() != LEAF)
		{
			printInConcavo(((CInternalNode<KeyType, DataType> *)pNode)->getChild(i), count - 2);
		}
	}
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::printData() const
{
	cout << endl;
	cout << "Now print all the data stored in B+ tree:" << endl
		 << endl;
	CLeafNode<KeyType, DataType> *itr = m_DataHead;
	itr->pour();
	while (itr != NULL)
	{
		cout << "block size: " << itr->getKeyNum() << endl;
		cout << "[ ";
		for (int i = 0; i < itr->getKeyNum(); ++i)
		{
			cout << itr->getData(i) << " , ";
		}
		cout << " ]" << endl;
		itr = itr->getRightSibling();
	}
	cout << endl;
}

template <typename KeyType, typename DataType>
bool CBPlusTree<KeyType, DataType>::remove(KeyType key)
{
	if (!search(key)) // does not exist
	{
		return false;
	}
	if (m_Root->getKeyNum() == 1) // Special case handling
	{
		if (m_Root->getType() == LEAF)
		{
			clear();
			return true;
		}
		else
		{
			CNode<KeyType, DataType> *pChild1 = ((CInternalNode<KeyType, DataType> *)m_Root)->getChild(0);
			CNode<KeyType, DataType> *pChild2 = ((CInternalNode<KeyType, DataType> *)m_Root)->getChild(1);
			if (pChild1->getKeyNum() == MINNUM_KEY && pChild2->getKeyNum() == MINNUM_KEY)
			{
				pChild1->mergeChild(m_Root, pChild2, 0);
				delete m_Root;
				m_Root = pChild1;
			}
		}
	}
	recursive_remove(m_Root, key);
	return true;
}

// Number of keys contained in parentNode > MINNUM_KEY
template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::recursive_remove(CNode<KeyType, DataType> *parentNode, KeyType key)
{
	int keyIndex = parentNode->getKeyIndex(key);
	int childIndex = parentNode->getChildIndex(key, keyIndex); // Child node pointer index
	if (parentNode->getType() == LEAF)						   // Find the target leaf node
	{
		if (key == m_MaxKey && keyIndex > 0)
		{
			m_MaxKey = parentNode->getKeyValue(keyIndex - 1);
		}
		parentNode->removeKey(keyIndex, childIndex); // delet directly
		// If the key value exists in the internal node, the internal node should be replaced accordingly
		if (childIndex == 0 && m_Root->getType() != LEAF && parentNode != m_DataHead)
		{
			changeKey(m_Root, key, parentNode->getKeyValue(0));
		}
	}
	else // Internal nodes
	{
		cout << "call" << endl;
		CNode<KeyType, DataType> *pChildNode = ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex); // The child root node containing the key
		if (pChildNode->getKeyNum() == MINNUM_KEY)																	   // If the number of keywords in the system reaches the lower limit, perform related operations
		{
			CNode<KeyType, DataType> *pLeft = childIndex > 0 ? ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex - 1) : NULL;						 // Left sibling node
			CNode<KeyType, DataType> *pRight = childIndex < parentNode->getKeyNum() ? ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex + 1) : NULL; // Right sibling node
			// Let's think about borrowing from a sibling
			if (pLeft && pLeft->getKeyNum() > MINNUM_KEY) // The left sibling can be borrowed
			{
				pChildNode->borrowFrom(pLeft, parentNode, childIndex - 1, LEFT);
			}
			else if (pRight && pRight->getKeyNum() > MINNUM_KEY) // The right sibling can be borrowed
			{
				pChildNode->borrowFrom(pRight, parentNode, childIndex, RIGHT);
			}
			// The left and right sibling nodes cannot be borrowed. Consider merging
			else if (pLeft) // Merge with left brother
			{
				pLeft->mergeChild(parentNode, pChildNode, childIndex - 1);
				pChildNode = pLeft;
			}
			else if (pRight) // Merge with the right brother
			{
				pChildNode->mergeChild(parentNode, pRight, childIndex);
			}
		}
		recursive_remove(pChildNode, key);
	}
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::changeKey(CNode<KeyType, DataType> *pNode, KeyType oldKey, KeyType newKey)
{
	if (pNode != NULL && pNode->getType() != LEAF)
	{
		int keyIndex = pNode->getKeyIndex(oldKey);
		if (keyIndex < pNode->getKeyNum() && oldKey == pNode->getKeyValue(keyIndex)) // found
		{
			pNode->setKeyValue(keyIndex, newKey);
		}
		else // continue to search
		{
			changeKey(((CInternalNode<KeyType, DataType> *)pNode)->getChild(keyIndex), oldKey, newKey);
		}
	}
}

template <typename KeyType, typename DataType>
bool CBPlusTree<KeyType, DataType>::update(KeyType oldKey, KeyType newKey)
{
	if (search(newKey)) // Check whether the updated key already exists
	{
		return false;
	}
	else
	{
		int dataValue;
		remove(oldKey, dataValue);
		if (dataValue == INVALID_INDEX)
		{
			return false;
		}
		else
		{
			return insert(newKey, dataValue);
		}
	}
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::remove(KeyType key, DataType &dataValue)
{
	if (!search(key)) // does not exist
	{
		dataValue = INVALID_INDEX;
		return;
	}
	if (m_Root->getKeyNum() == 1) // Special case handling
	{
		if (m_Root->getType() == LEAF)
		{
			dataValue = ((CLeafNode<KeyType, DataType> *)m_Root)->getData(0);
			clear();
			return;
		}
		else
		{
			CNode<KeyType, DataType> *pChild1 = ((CInternalNode<KeyType, DataType> *)m_Root)->getChild(0);
			CNode<KeyType, DataType> *pChild2 = ((CInternalNode<KeyType, DataType> *)m_Root)->getChild(1);
			if (pChild1->getKeyNum() == MINNUM_KEY && pChild2->getKeyNum() == MINNUM_KEY)
			{
				pChild1->mergeChild(m_Root, pChild2, 0);
				delete m_Root;
				m_Root = pChild1;
			}
		}
	}
	recursive_remove(m_Root, key, dataValue);
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::recursive_remove(CNode<KeyType, DataType> *parentNode, KeyType key, DataType &dataValue)
{
	int keyIndex = parentNode->getKeyIndex(key);
	int childIndex = parentNode->getChildIndex(key, keyIndex); // Child node pointer index
	if (parentNode->getType() == LEAF)						   // Find the target leaf node
	{
		if (key == m_MaxKey && keyIndex > 0)
		{
			m_MaxKey = parentNode->getKeyValue(keyIndex - 1);
		}
		dataValue = ((CLeafNode<KeyType, DataType> *)parentNode)->getData(keyIndex);
		parentNode->removeKey(keyIndex, childIndex); // delet directly
		// If the key value exists in the internal node, the internal node should be replaced accordingly
		if (childIndex == 0 && m_Root->getType() != LEAF && parentNode != m_DataHead)
		{
			changeKey(m_Root, key, parentNode->getKeyValue(0));
		}
	}
	else // Internal nodes
	{
		CNode<KeyType, DataType> *pChildNode = ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex); // The child root node containing the key
		if (pChildNode->getKeyNum() == MINNUM_KEY)																	   // If the number of keywords in the system reaches the lower limit, perform related operations
		{
			CNode<KeyType, DataType> *pLeft = childIndex > 0 ? ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex - 1) : NULL;						 // Left sibling node
			CNode<KeyType, DataType> *pRight = childIndex < parentNode->getKeyNum() ? ((CInternalNode<KeyType, DataType> *)parentNode)->getChild(childIndex + 1) : NULL; // Right sibling node
			// Let's think about borrowing from a sibling
			if (pLeft && pLeft->getKeyNum() > MINNUM_KEY) // The left sibling can be borrowed
			{
				pChildNode->borrowFrom(pLeft, parentNode, childIndex - 1, LEFT);
			}
			else if (pRight && pRight->getKeyNum() > MINNUM_KEY) // The right sibling can be borrowed
			{
				pChildNode->borrowFrom(pRight, parentNode, childIndex, RIGHT);
			}
			// The left and right sibling nodes cannot be borrowed. Consider merging
			else if (pLeft) // Merge with left brother
			{
				pLeft->mergeChild(parentNode, pChildNode, childIndex - 1);
				pChildNode = pLeft;
			}
			else if (pRight) // Merge with right brother
			{
				pChildNode->mergeChild(parentNode, pRight, childIndex);
			}
		}
		recursive_remove(pChildNode, key, dataValue);
	}
}

template <typename KeyType, typename DataType>
vector<DataType> CBPlusTree<KeyType, DataType>::oneSideSelect(KeyType compareKey, int compareOpeartor) const
{
	vector<DataType> results;
	if (m_Root != NULL)
	{
		if (compareKey > m_MaxKey) // Compare keys greater than the largest in the B+ tree
		{
			if (compareOpeartor == LE || compareOpeartor == LT)
			{
				for (CLeafNode<KeyType, DataType> *itr = m_DataHead; itr != NULL; itr = itr->getRightSibling())
				{
					for (int i = 0; i < itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
				}
			}
		}
		else if (compareKey < m_DataHead->getKeyValue(0)) // Compare keys that are less than the smallest in the B+ tree
		{
			if (compareOpeartor == BE || compareOpeartor == BT)
			{
				for (CLeafNode<KeyType, DataType> *itr = m_DataHead; itr != NULL; itr = itr->getRightSibling())
				{
					for (int i = 0; i < itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
				}
			}
		}
		else // The comparison key is in the B+ tree
		{
			SelectResult<KeyType, DataType> result;
			search(compareKey, result);
			switch (compareOpeartor)
			{
			case LT:
			case LE:
			{
				CLeafNode<KeyType, DataType> *itr = m_DataHead;
				int i;
				while (itr != result.targetNode)
				{
					for (i = 0; i < itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
					itr = itr->getRightSibling();
				}
				for (i = 0; i < result.keyIndex; ++i)
				{
					results.push_back(itr->getData(i));
				}
				if (itr->getKeyValue(i) < compareKey ||
					(compareOpeartor == LE && compareKey == itr->getKeyValue(i)))
				{
					results.push_back(itr->getData(i));
				}
			}
			break;
			case EQ:
			{
				if (result.targetNode->getKeyValue(result.keyIndex) == compareKey)
				{
					results.push_back(result.targetNode->getData(result.keyIndex));
				}
			}
			break;
			case BE:
			case BT:
			{
				CLeafNode<KeyType, DataType> *itr = result.targetNode;
				if (compareKey < itr->getKeyValue(result.keyIndex) ||
					(compareOpeartor == BE && compareKey == itr->getKeyValue(result.keyIndex)))
				{
					results.push_back(itr->getData(result.keyIndex));
				}
				int i;
				for (i = result.keyIndex + 1; i < itr->getKeyNum(); ++i)
				{
					results.push_back(itr->getData(i));
				}
				itr = itr->getRightSibling();
				while (itr != NULL)
				{
					for (i = 0; i < itr->getKeyNum(); ++i)
					{
						results.push_back(itr->getData(i));
					}
					itr = itr->getRightSibling();
				}
			}
			break;
			default: // Range queries
				break;
			}
		}
	}
	sort<vector<DataType>::iterator>(results.begin(), results.end());
	return results;
}

template <typename KeyType, typename DataType>
vector<DataType> CBPlusTree<KeyType, DataType>::twoSideSelect(KeyType smallKey, KeyType largeKey) const
{
	vector<DataType> results;
	if (smallKey <= largeKey)
	{
		SelectResult<KeyType, DataType> start, end;
		search(smallKey, start);
		search(largeKey, end);
		CLeafNode<KeyType, DataType> *itr = start.targetNode;
		int i = start.keyIndex;
		if (itr->getKeyValue(i) < smallKey)
		{
			++i;
		}
		if (end.targetNode->getKeyValue(end.keyIndex) > largeKey)
		{
			--end.keyIndex;
		}
		while (itr != end.targetNode)
		{
			for (; i < itr->getKeyNum(); ++i)
			{
				results.push_back(itr->getData(i));
			}
			itr = itr->getRightSibling();
			i = 0;
		}
		for (; i <= end.keyIndex; ++i)
		{
			results.push_back(itr->getData(i));
		}
	}
	sort<vector<DataType>::iterator>(results.begin(), results.end());
	return results;
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::search(KeyType key, SelectResult<KeyType, DataType> &result)
{
	recursive_search(m_Root, key, result);
}

template <typename KeyType, typename DataType>
void CBPlusTree<KeyType, DataType>::recursive_search(CNode<KeyType, DataType> *pNode, KeyType key, SelectResult<KeyType, DataType> &result)
{
	// cout << "check0" << endl;
	int keyIndex = pNode->getKeyIndex(key);
	int childIndex = pNode->getChildIndex(key, keyIndex); // Child node pointer index
	if (pNode->getType() == LEAF)
	{
		result.keyIndex = keyIndex;
		result.targetNode = (CLeafNode<KeyType, DataType> *)pNode;
		return;
	}
	else
	{
		recursive_search(((CInternalNode<KeyType, DataType> *)pNode)->getChild(childIndex), key, result);
	}
}