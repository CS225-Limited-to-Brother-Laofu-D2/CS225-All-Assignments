


#include "B_tree.h"


BTreeNode::BTreeNode(void)
{
    keyNum = 0;
    parent = nullptr;
    leaf = true;
	int i;
	for (i = 0;i < child_max;i++)
	{
		pchild[i] = nullptr;
	}
	for (i = 0;i < key_max;i++)
	{
		keyvalue[i] = 0; // this is the nullptr is made for the Tuple*, it is value
	}
}


BTree::BTree(void)
{
   root = nullptr;
   return;
}


bool BTree::_insert(Tuple* value)
{
   if (contain(value))
   {
      return false;
   }
   else
   {
      if (root == nullptr)
      {
      	root = new BTreeNode();
      }
      if (root->keyNum == key_max)
      {
         BTreeNode* newnode = new BTreeNode();
         newnode->pchild[0] = root;
         newnode->leaf = false;
         SplitBlock(newnode,0,root);
         root = newnode;
      }
      Notfull_insert(root,value);
      return true;
   }
}
 
void BTree::SplitBlock(BTreeNode* node_parent,int child_index,BTreeNode* node_child)
{
   BTreeNode* node_right = new BTreeNode();
   node_right->leaf = node_child->leaf;
   node_right->keyNum = key_min;
   int i;

   for (i = 0;i < key_min;i++)
   {
      node_right->keyvalue[i] = node_child->keyvalue[i+child_min];
   }
   if (!node_child->leaf)
   {
      for (i = 0;i < child_min;i++)
      {
         node_right->pchild[i] = node_child->pchild[i+child_min];
         node_child->pchild[i+child_min]->parent = node_right->pchild[i];
      }
   }
   node_child->keyNum = key_min;
   for (i = node_parent->keyNum;i > child_index;i--)
   {
      node_parent->keyvalue[i] = node_parent->keyvalue[i-1];
      node_parent->pchild[i+1] = node_parent->pchild[i];
      node_child->pchild[i]->parent = node_parent->pchild[i+1];
   }
   node_parent->keyNum++;
   node_parent->pchild[child_index+1] = node_right;
   node_right->parent = node_parent->pchild[child_index+1];
   node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
   return;
}

void BTree::Notfull_insert(BTreeNode* node,Tuple* value)
{
   int node_keynum = node->keyNum;
   if (node->leaf)
   {
      while (node_keynum > 0 && value->get_registration() < node->keyvalue[node_keynum-1]->get_registration())
      {
      	node->keyvalue[node_keynum] = node->keyvalue[node_keynum-1];
      	--node_keynum;
      }
      	node->keyvalue[node_keynum] = value;
      	node->keyNum++;
   }
   else
   {
      while (node_keynum > 0 && value->get_registration() < node->keyvalue[node_keynum-1]->get_registration())
      {
      	--node_keynum;
      }
      BTreeNode* node_child = node->pchild[node_keynum];
      if (node_child->keyNum == key_max)
      {
      	SplitBlock(node,node_keynum,node_child);
      	if (value->get_registration() > node->keyvalue[node_keynum]->get_registration())
      	{
      	  	node_child = node->pchild[node_keynum+1];
      	}
      }
      Notfull_insert(node_child,value);
   }
}

bool BTree::contain(Tuple* value)
{
   if (_find(root,value) != nullptr) return true;
   return false;
}


BTreeNode* BTree::_find(BTreeNode* node,Tuple* value)
{
   if (node == nullptr)
   {
   	return nullptr;
   }
   else
   {
      int i;
      for (i = 0; i < node->keyNum ;i++)
   	{
   	   if (value->get_registration() <= node->keyvalue[i]->get_registration())
         {
            break; 
         }
   	}
      if (i < node->keyNum && value->get_registration() == node->keyvalue[i]->get_registration())
      {
         return node;
      }
      else
      {
         if (node->leaf) return nullptr;
         else return _find(node->pchild[i],value);
      }
   }
}


bool BTree::_delete(Tuple* value)
{
   if (!contain(value))
   {
      return false;
   }
   if (root->keyNum == 1)
   {
      if (root->leaf)
      {
         delete root;
         root = nullptr;
         return true;
      }
      else
      {
         BTreeNode* node_child1 = root->pchild[0];
         BTreeNode* node_child2 = root->pchild[1];
                
         if (node_child1->keyNum == key_min && node_child2->keyNum == key_min)
         {
            MergeBlock(root,0);
            delete root;
            root = node_child1;
         }
      }
   }
   BTree_deletebalance(root,value);
    return true;
}


void BTree::MergeBlock(BTreeNode* node_parent,int child_index)
{
   BTreeNode* node_child1 = node_parent->pchild[child_index];
   BTreeNode* node_child2 = node_parent->pchild[child_index+1];
   
   node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
   node_child1->keyNum = key_max;
   int i;
   for (i = 0;i < key_min;i++)
   {
      node_child1->keyvalue[child_min+i] = node_child2->keyvalue[i];
   }
   
   if (!node_child1->leaf)
   {
      for (i = 0; i < child_min;i++)
      {
         node_child1->pchild[i+child_min] = node_child2->pchild[i];
      }
   }

   node_parent->keyNum--;
   for (i = child_index;i <  node_parent->keyNum;i++)
   {
      node_parent->keyvalue[i] = node_parent->keyvalue[i+1];
       
      node_parent->pchild[i+1] = node_parent->pchild[i+2];
   }
   delete node_child2;
   node_child2 = nullptr;
}

Tuple* BTree::getprev(BTreeNode* node)
{
   while (!node->leaf)
   {
      node = node->pchild[node->keyNum];
   }
   node->keyNum--;
   return node->keyvalue[node->keyNum-1];
}

Tuple* BTree::getnext(BTreeNode* node)
{

   while (!node->leaf)
   {
      node = node->pchild[0];
   }
   return node->keyvalue[0];
}

void BTree::BTree_deletebalance(BTreeNode* node,Tuple* value)
{
   int i;
     
   for(i = 0;i < node->keyNum && value->get_registration() > node->keyvalue[i]->get_registration();i++)
   {}
     
   if (i < node->keyNum && value->get_registration() == node->keyvalue[i]->get_registration())
   {
      
      if (node->leaf)
      {
         node->keyNum--;
           
         for (;i < node->keyNum;i++)
         {
            node->keyvalue[i] = node->keyvalue[i+1];
         }
         return;
      }
      else
      {
          
         BTreeNode* node_left = node->pchild[i];
          
         BTreeNode* node_right = node->pchild[i+1];
         if (node_left->keyNum >= child_min)
         {
            Tuple* prev_replace = getprev(node_left);
             
            BTree_deletebalance(node_left,prev_replace);
             
            node->keyvalue[i] = prev_replace;
            return;
         }
         else if (node_right->keyNum >= child_min)
         {
            Tuple* next_replace = getnext(node_right);
        
            BTree_deletebalance(node_right,next_replace);
           
            node->keyvalue[i] = next_replace;
            return;
         }
         else
         {
            
         MergeBlock(node,i);
           
         BTree_deletebalance(node_left,value);
         }
      }
   }
   else
   {
       
      BTreeNode* node_child = node->pchild[i];
      BTreeNode*  node_left = nullptr;
      BTreeNode*  node_right = nullptr;
      if (node_child->keyNum == key_min)
      {  
          
         if (i >0)
         {
            node_left = node->pchild[i-1];
         }
         if (i <= node->keyNum-1)
         {
            node_right = node->pchild[i+1];
         }
         int j;
           
         if (node_left && node_left->keyNum >= child_min)
         {   
                
            for (j = node_child->keyNum;j > 0; j--)
            {
               node_child->keyvalue[j] = node_child->keyvalue[j-1];
            }
            node_child->keyvalue[0] = node->keyvalue[i-1];
               
            if (!node_left->leaf)
            {
                
               for (j = node_child->keyNum+1;j > 0;j--)
               {
                  node_child->pchild[j-1]->parent = node_child->pchild[j]->parent;
                  node_child->pchild[j] = node_child->pchild[j-1];
 
               }
               node_left->pchild[node_left->keyNum]->parent =  node_child->pchild[0];
               node_child->pchild[0] = node_left->pchild[node_left->keyNum];
            }
            node_child->keyNum++;
            node->keyvalue[i-1] = node_left->keyvalue[node_left->keyNum-1];
            node_left->keyNum--;
         }
         else if (node_right && node_right->keyNum >= child_min)
         {
               
            node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
            node_child->keyNum++;
               
            node->keyvalue[i] = node_right->keyvalue[0];
            node_right->keyNum--;
               
            for (j = 0;j < node_right->keyNum;j++)
            {
               node_right->keyvalue[j] = node_right->keyvalue[j+1];
            }
            if (!node_right->leaf)
            {
               node_right->pchild[0]->parent = node_child->pchild[node_child->keyNum]->parent;
               node_child->pchild[node_child->keyNum] = node_right->pchild[0];
               for (j = 0;j < node_right->keyNum+1;j++)
               {
                  node_right->pchild[j+1]->parent = node_right->pchild[j]->parent;
                  node_right->pchild[j] = node_right->pchild[j+1];
 
               }
                 
            }
         }
         else if (node_left)
         {
            
            MergeBlock(node,i-1);
           
            node_child = node_left;
         }
         else if (node_right)
         {
            
            MergeBlock(node,i);
         }
      }
      BTree_deletebalance(node_child,value);
   }
}