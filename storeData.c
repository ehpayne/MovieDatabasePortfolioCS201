/* Author: Elizabeth Payne
 * File: readFiles.c
 * Description: This code reads in all the data files and assigns the
 * information to the corresponding variables
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readFiles.h"
#include "storeData.h"
#include "hash.h"

TAlt *tAltRoot;
TBasic *tBasicsRoot;
TExecs *tExecsRoot;
NBasic *nBasicRoot;



//newUser creates a file containing all usernames and passwords
void newUser(char *username, char *password)
{
    //file containing all user information
    FILE *fptr = fopen("UserInfo.txt", "a");
    //file print username and password
    fprintf(fptr, "%s %s\n", username, password);
    fclose(fptr);
    
    //creating a file for a user (username.log)
    char*filename = malloc(strlen(username) + 4);
    for(int i = 0; i <strlen(username); i++)
    {
        filename[i] = username[i];
    }
    filename[strlen(username)] = '.';
    filename[strlen(username)+1] = 'l';
    filename[strlen(username)+2] = 'o';
    filename[strlen(username)+3] = 'g';
    
    FILE* fptr2 = fopen(filename, "a");
    fclose (fptr2);
}


//TBasicDataBST is a BST containing TBAsic structures (duplicates are stored as a
//linked list
//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void TBasicDataBST(TBasic* titleBasicsNode, int size)
{
    //printf("++++++++++++++++BST+++++++++++++++++\n");
    if(size == 0)
    {
        tBasicsRoot = titleBasicsNode;
        //insert root into hash table
        hashTableINSERT(size, titleBasicsNode->primaryTitle, titleBasicsNode->ID);
        
        //printf("root: %s\n", tBasicsRoot->ID);
    }
    else
    {
        TBasic *temp = tBasicsRoot;
        TBasic *back = NULL;
        TBasic *ancestor = NULL;
        //printf("A: %s, T:%s\n\n", titleBasicsNode->ID, temp->ID);
        //walk through the tree to find where the new node should go
        while(temp != NULL)
        {
            
            back = temp;
            
            if(temp->balance != 0)
            {
                ancestor = temp;
                //printf("ANCESTOR: %s\n\n", ancestor->ID);
            }
            //if new node < temp, go left
            if(strcmp(titleBasicsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                //printf("going left\n");
            }
            //if new node > temp, go right
            else if(strcmp(titleBasicsNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                //printf("going right\n");
            }
            //else walk through the linked list
            else
            {
                //linked list for duplicates
                temp = temp->next;
               // printf("going next\n");
            }
            
        }
        //set the node's parent
        titleBasicsNode->parent = back;
        //attach new node to correct place
        //if new node < back, attach the new node to the left
        if(strcmp(titleBasicsNode->ID, back->ID) < 0)
        {
            back->left = titleBasicsNode;
            //printf("ID: %s inserted LEFT\n", titleBasicsNode->ID);
        }
        //if the new node > back, attach the new node to the right
        else if(strcmp(titleBasicsNode->ID, back->ID) > 0)
        {
           
            back->right = titleBasicsNode;
            //printf("ID: %s inserted RIGHT\n", titleBasicsNode->ID);
        }
        //else attach the new node to the end of the linked list
        else
        {
            back = titleBasicsNode->parent;
            //printf("ID: %s is a duplicate\n", titleBasicsNode->ID);
        }
        TBasic_RestoreAVL(ancestor, titleBasicsNode);
        //insert the primary title and titleID into the hash table
        hashTableINSERT(size, titleBasicsNode->primaryTitle, titleBasicsNode->ID);
       // printf("ROOT: %s\n", tBasicsRoot->ID);
        //printf("NODE: %s\n", titleBasicsNode->ID);
        //printf("root->balance = %d, parent->balance = %d\n", tBasicsRoot->balance,
               //titleBasicsNode->parent->balance);
       
        
        //printf("DONE INSERTING %d\n\n", size);
        
        //Print(titleBasicsNode);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// Adjust the balance factor in all nodes from the inserted node's
//   parent back up to but NOT including a designated end node.
// @param end– last node back up the tree that needs adjusting
// @param start – node just inserted
//------------------------------------------------------------------
void adjustBalancesTBasic(TBasic *end, TBasic *start)
{
    TBasic *temp = start->parent; // Set starting point at start's parent
    while(temp != end)
    {
        if(strcmp(start->ID, temp->ID) < 0)
            temp->balance = 1;
        else
            temp->balance = -1;
        temp = temp->parent;
    } // end while
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void TBasic_RestoreAVL(TBasic *ancestor, TBasic *newNode)
{
    //printf("---------------------AVL---------------------\n");
    //printf("in Restore\n");
    // Case 1: balance of all ancestors' is '0'
    if(ancestor == NULL)
    {
        //printf("case 1\n");
        if(strcmp(newNode->ID, tBasicsRoot->ID) < 0)       // newNode inserted to left of root
            tBasicsRoot->balance = 1;
        else
            tBasicsRoot->balance = -1;   // newNode inserted to right of root
        // Adjust the balance for all nodes from newNode back up to root
        adjustBalancesTBasic(tBasicsRoot, newNode);
    }
    
    // Case 2: Insertion in opposite subtree of ancestor's balance factor, i.e.
    //  ancestor.balance = 1 AND  Insertion made in ancestor's right subtree
    //     OR
    //  ancestor.balance = -1 AND  Insertion made in ancestor's left subtree
    else if(((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->ID) > 0)) ||
            ((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->ID) < 0)))
    {
        //printf("case 2\n");
        ancestor->balance = 0;
        // Adjust the balance for all nodes from newNode back up to ancestor
        adjustBalancesTBasic(ancestor, newNode);
    }
    // Case 3: ancestor.balance = -1 and the node inserted is
    //      in the right subtree of ancestor's right child
    else if((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->right->ID) > 0))
    {
        //printf("case 3\n");

        ancestor->balance = 0; // Reset ancestor's balance
        leftRotateTBasic(ancestor);       // Do single left rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        // adjustBalancesTBasic(ancestor->parent, newNode);
    }
    
    // Case 4: ancestor.balance is 1 and the node inserted is
    //      in the left subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) < 0))
    {
        //printf("case 4\n");
        ancestor->balance = 0; // Reset ancestor's balance
        rightRotateTBasic(ancestor);       // Do single right rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        //adjustBalancesTBasic(ancestor->parent, newNode);
    }
    
    //Case 5: ancestor.balance is 1 and the node inserted is
    //      in the right subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) > 0))
    {
        //printf("case 5\n");

        // Perform double rotation (left, then right)
        leftRotateTBasic(ancestor->left);
        rightRotateTBasic(ancestor);
        // Adjust the balance for all nodes from newNode back up to ancestor
        adjustLeftRightTBasic(ancestor, newNode);
    }
    
    //Case 6: ancestor.balance is -1 and the node inserted is
    //      in the left subtree of ancestor's right child
    else
    {
        //printf("case 6\n");

        // Perform double rotation (right then left)
        rightRotateTBasic(ancestor->right);
        leftRotateTBasic(ancestor);
        adjustRightLeftTBasic(ancestor, newNode);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void rightRotateTBasic(TBasic *node)
{
    //printf("ID: %s rotate RIGHT\n", node->ID);
    //pointer to node's right child
    TBasic *leftChild = node->left;
    node->left = leftChild->right;
    
    if(leftChild->left != NULL)
    {
        leftChild->left->parent = node;
    }
    
    //keep track of the root of the tree
    if(node->parent == NULL)
    {
        tBasicsRoot = leftChild;
        leftChild->parent = NULL;
        
    }
    else if(node->parent->right == node)
    {
        node->parent->right = leftChild;
    }
    else
    {
        node->parent->left = leftChild;
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void leftRotateTBasic(TBasic *node)
{
    //printf("ID: %s rotate LEFT\n", node->ID);
    //pointer to node's right child
    TBasic *rightChild = node->right;
    //node's right child pointer now points to rightChild's left child
    node->right = rightChild->left;
    //make sure rightChild->left's parent pointer points to node
    if(rightChild->left != NULL)
    {
        rightChild->left->parent = node;
    }
    //keeping track of the root
    if(node->parent == NULL)
    {
        tBasicsRoot = rightChild;
        rightChild->parent = NULL;
    }
    
    //keep track of node's parent
    else if(node->parent->right == node)
    {
        node->parent->right = rightChild;
    }
    else
    {
        node->parent->left = rightChild;
    }
}


//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// adjustLeftRightTBasic()
// end = last node in the tree that needs adjusting
// start = node just inserted
//------------------------------------------------------------------
void adjustLeftRightTBasic(TBasic *end, TBasic *start)
{
    if(end == tBasicsRoot)
        end->balance = 0;
    else if(strcmp(start->ID, end->parent->ID) < 0)
    {
        end->balance = -1;
        adjustBalancesTBasic(end->parent->left, start);
    }
    else
    {
        end->balance = 0;
        end->parent->left->balance = 1;
        adjustBalancesTBasic(end, start);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// adjustRightLeftTBasic
// @param end- last node back up the tree that needs adjusting
// @param start - node just inserted
//------------------------------------------------------------------
void adjustRightLeftTBasic(TBasic *end, TBasic *start)
{
    if(end == tBasicsRoot)
        end->balance = 0;
    else if(strcmp(start->ID, end->parent->ID) > 0)
    {
        end->balance = 1;
        adjustBalancesTBasic(end->parent->right, start);
    }
    else
    {
        end->balance = 0;
        end->parent->right->balance = -1;
        adjustBalancesTBasic(end, start);
    }
}

TBasic *searchTBasicBST(char* title)
{
    TBasic *temp = tBasicsRoot;
    while (temp != NULL)
    {
        if(strcmp(title, temp->ID) < 0)
        {
            temp = temp->left;
        }
        else if(strcmp(title, temp->ID) > 0)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->next;
        }
    }
    return temp;
}

/*
//TBasicDataBST is a BST containing TBAsic structures (duplicates are stored as a
//linked list
//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void NBasicDataBST(NBasic* nameBasicsNode, int size)
{
    //printf("++++++++++++++++BST+++++++++++++++++\n");
    if(size == 0)
    {
        nBasicsRoot = nameBasicsNode;
        //insert root into hash table
        hashTableINSERT(size, nameBasicsNode->primaryName, nameBasicsNode->ID);
        
        //printf("root: %s\n", tBasicsRoot->ID);
    }
    else
    {
        NBasic *temp = tBasicsRoot;
        NBasic *back = NULL;
        NBasic *ancestor = NULL;
        //printf("A: %s, T:%s\n\n", titleBasicsNode->ID, temp->ID);
        //walk through the tree to find where the new node should go
        while(temp != NULL)
        {
            
            back = temp;
            
            if(temp->balance != 0)
            {
                ancestor = temp;
                //printf("ANCESTOR: %s\n\n", ancestor->ID);
            }
            //if new node < temp, go left
            if(strcmp(nameBasicsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                //printf("going left\n");
            }
            //if new node > temp, go right
            else if(strcmp(nameBasicsNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                //printf("going right\n");
            }
            //else walk through the linked list
            else
            {
                //linked list for duplicates
                temp = temp->next;
                // printf("going next\n");
            }
            
        }
        //set the node's parent
        nameBasicsNode->parent = back;
        //attach new node to correct place
        //if new node < back, attach the new node to the left
        if(strcmp(nameBasicsNode->ID, back->ID) < 0)
        {
            back->left = nameBasicsNode;
            //printf("ID: %s inserted LEFT\n", titleBasicsNode->ID);
        }
        //if the new node > back, attach the new node to the right
        else if(strcmp(nameBasicsNode->ID, back->ID) > 0)
        {
            
            back->right = nameBasicsNode;
            //printf("ID: %s inserted RIGHT\n", titleBasicsNode->ID);
        }
        //else attach the new node to the end of the linked list
        else
        {
            back = nameBasicsNode->parent;
            //printf("ID: %s is a duplicate\n", titleBasicsNode->ID);
        }
        NBasic_RestoreAVL(ancestor, nameBasicsNode);
        //insert the primary title and titleID into the hash table
        hashTableINSERT(size, nameBasicsNode->primaryTitle, nameBasicsNode->ID);
        // printf("ROOT: %s\n", tBasicsRoot->ID);
        //printf("NODE: %s\n", titleBasicsNode->ID);
        //printf("root->balance = %d, parent->balance = %d\n", tBasicsRoot->balance,
        //titleBasicsNode->parent->balance);
        
        
        //printf("DONE INSERTING %d\n\n", size);
        
        //Print(titleBasicsNode);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// Adjust the balance factor in all nodes from the inserted node's
//   parent back up to but NOT including a designated end node.
// @param end– last node back up the tree that needs adjusting
// @param start – node just inserted
//------------------------------------------------------------------
void adjustBalancesNBasic(NBasic *end, NBasic *start)
{
    TBasic *temp = start->parent; // Set starting point at start's parent
    while(temp != end)
    {
        if(strcmp(start->ID, temp->ID) < 0)
            temp->balance = 1;
        else
            temp->balance = -1;
        temp = temp->parent;
    } // end while
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void TBasic_RestoreAVL(NBasic *ancestor, NBasic *newNode)
{
    //printf("---------------------AVL---------------------\n");
    //printf("in Restore\n");
    // Case 1: balance of all ancestors' is '0'
    if(ancestor == NULL)
    {
        //printf("case 1\n");
        if(strcmp(newNode->ID, nBasicsRoot->ID) < 0)       // newNode inserted to left of root
            nBasicsRoot->balance = 1;
        else
            tBasicsRoot->balance = -1;   // newNode inserted to right of root
        // Adjust the balance for all nodes from newNode back up to root
        adjustBalancesTBasic(nBasicsRoot, newNode);
    }
    
    // Case 2: Insertion in opposite subtree of ancestor's balance factor, i.e.
    //  ancestor.balance = 1 AND  Insertion made in ancestor's right subtree
    //     OR
    //  ancestor.balance = -1 AND  Insertion made in ancestor's left subtree
    else if(((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->ID) > 0)) ||
            ((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->ID) < 0)))
    {
        //printf("case 2\n");
        ancestor->balance = 0;
        // Adjust the balance for all nodes from newNode back up to ancestor
        adjustBalancesTBasic(ancestor, newNode);
    }
    // Case 3: ancestor.balance = -1 and the node inserted is
    //      in the right subtree of ancestor's right child
    else if((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->right->ID) > 0))
    {
        //printf("case 3\n");
        
        ancestor->balance = 0; // Reset ancestor's balance
        leftRotateNBasic(ancestor);       // Do single left rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        // adjustBalancesTBasic(ancestor->parent, newNode);
    }
    
    // Case 4: ancestor.balance is 1 and the node inserted is
    //      in the left subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) < 0))
    {
        //printf("case 4\n");
        ancestor->balance = 0; // Reset ancestor's balance
        rightRotateNBasic(ancestor);       // Do single right rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        //adjustBalancesTBasic(ancestor->parent, newNode);
    }
    
    //Case 5: ancestor.balance is 1 and the node inserted is
    //      in the right subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) > 0))
    {
        //printf("case 5\n");
        
        // Perform double rotation (left, then right)
        leftRotateNBasic(ancestor->left);
        rightRotateNBasic(ancestor);
        // Adjust the balance for all nodes from newNode back up to ancestor
        adjustLeftRightNBasic(ancestor, newNode);
    }
    
    //Case 6: ancestor.balance is -1 and the node inserted is
    //      in the left subtree of ancestor's right child
    else
    {
        //printf("case 6\n");
        
        // Perform double rotation (right then left)
        rightRotateNBasic(ancestor->right);
        leftRotateNBasic(ancestor);
        adjustRightLeftNBasic(ancestor, newNode);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void rightRotateNBasic(NBasic *node)
{
    //printf("ID: %s rotate RIGHT\n", node->ID);
    //pointer to node's right child
    NBasic *leftChild = node->left;
    node->left = leftChild->right;
    
    if(leftChild->left != NULL)
    {
        leftChild->left->parent = node;
    }
    
    //keep track of the root of the tree
    if(node->parent == NULL)
    {
        nBasicsRoot = leftChild;
        leftChild->parent = NULL;
        
    }
    else if(node->parent->right == node)
    {
        node->parent->right = leftChild;
    }
    else
    {
        node->parent->left = leftChild;
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void leftRotateNBasic(NBasic *node)
{
    //printf("ID: %s rotate LEFT\n", node->ID);
    //pointer to node's right child
    NBasic *rightChild = node->right;
    //node's right child pointer now points to rightChild's left child
    node->right = rightChild->left;
    //make sure rightChild->left's parent pointer points to node
    if(rightChild->left != NULL)
    {
        rightChild->left->parent = node;
    }
    //keeping track of the root
    if(node->parent == NULL)
    {
        nBasicsRoot = rightChild;
        rightChild->parent = NULL;
    }
    
    //keep track of node's parent
    else if(node->parent->right == node)
    {
        node->parent->right = rightChild;
    }
    else
    {
        node->parent->left = rightChild;
    }
}


//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// adjustLeftRightTBasic()
// end = last node in the tree that needs adjusting
// start = node just inserted
//------------------------------------------------------------------
void adjustLeftRightNBasic(NBasic *end, NBasic *start)
{
    if(end == nBasicsRoot)
        end->balance = 0;
    else if(strcmp(start->ID, end->parent->ID) < 0)
    {
        end->balance = -1;
        adjustBalancesNBasic(end->parent->left, start);
    }
    else
    {
        end->balance = 0;
        end->parent->left->balance = 1;
        adjustBalancesNBasic(end, start);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// adjustRightLeftTBasic
// @param end- last node back up the tree that needs adjusting
// @param start - node just inserted
//------------------------------------------------------------------
void adjustRightLeftNBasic(NBasic *end, NBasic *start)
{
    if(end == nBasicsRoot)
        end->balance = 0;
    else if(strcmp(start->ID, end->parent->ID) > 0)
    {
        end->balance = 1;
        adjustBalancesNBasic(end->parent->right, start);
    }
    else
    {
        end->balance = 0;
        end->parent->right->balance = -1;
        adjustBalancesNBasic(end, start);
    }
}

NBasic *searchNBasicBST(char* title)
{
    TBasic *temp = nBasicsRoot;
    while (temp != NULL)
    {
        if(strcmp(title, temp->ID) < 0)
        {
            temp = temp->left;
        }
        else if(strcmp(title, temp->ID) > 0)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->next;
        }
    }
    return temp;
}

//------------------------------------------------------------------
// Print()
// Perform a recursive traversal to print the tree
//------------------------------------------------------------------
void Print(TBasic *n)
{
    if(n != NULL)
    {
        printf("Node: %s Balance: %d\n", n->ID, n->balance);
        if(n->left != NULL)
        {
            printf("\t moving left\n");
            Print(n->left);
            printf("Returning to node: %s from its left subtree\n", n->ID);
        }
        else
        {
            printf("\t left subtree is empty\n");
        }
        printf("Node: %s Balance: %d\n", n->ID, n->balance);
        if(n->right != NULL)
        {
            printf("\t moving right\n");
            Print(n->right);
            printf("Returning to Node: %s from its' right subtree\n", n->ID);
        }
        else
        {
            printf("\t right subtree is empty\n");
        }
    }
}
     */

