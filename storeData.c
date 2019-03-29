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

TAlt *tAltRoot;
TBasic *tBasicsRoot;
TExecs *tExecsRoot;



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

//TAltDataBST is a BST containing TAlt structures (duplicates are stored as a
//linked list
void TAltDataBST(TAlt* altTitleNode, int size)
{
    printf("ID: %s\n", altTitleNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tAltRoot = altTitleNode;
    }
    else
    {
        TAlt *temp = tAltRoot;
        TAlt *back = NULL;
        
        //walk through the tree to find where the new node should go
        while(temp != NULL)
        {
            back = temp;
            //if new node < temp, go left
            if(strcmp(altTitleNode->ID, temp->ID) < 0)
            {
               temp = temp->left;
                //printf("going left\n");
            }
            //if new node > temp, go right
            else if(strcmp(altTitleNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                //printf("going right\n");
            }
            else
            {
                //linked list for duplicates
                //printf("A: %s, T:%s\n\n", altTitleNode->ID, temp->ID);
                temp = temp->next;
                //printf("going next\n");
            }
        }
        //attach new node to correct place
        if(back == NULL)
        {
            tAltRoot = altTitleNode;
        }
        else
        {
            back = altTitleNode->parent;
            //if new node < back, attach new node to the left
            if(strcmp(altTitleNode->ID, back->ID) < 0)
            {
                back->left =altTitleNode;
                //printf("ID: %s inserted LEFT\n", altTitleNode->ID);
            }
            //if new node > back, attach new node to the right
            else if(strcmp(altTitleNode->ID, back->ID) > 0)
            {
                back->right = altTitleNode;
                printf("ID: %s inserted RIGHT\n", altTitleNode->ID);
            }
            else
            {
                //attach new node to the end of the linked list
                back->next = altTitleNode;
                printf("ID: %s is a duplicate\n", altTitleNode->ID);
            }
        }
    }
}

//TBasicDataBST is a BST containing TBAsic structures (duplicates are stored as a
//linked list
//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void TBasicDataBST(TBasic* titleBasicsNode, int size)
{
    if(size == 0)
    {
        tBasicsRoot = titleBasicsNode;
        
        printf("root: %s\n", tBasicsRoot->ID);
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
                printf("going right\n");
            }
            //else walk through the linked list
            else
            {
                //linked list for duplicates
                temp = temp->next;
                //printf("going next\n");
            }
            
        }
        //set the node's parent
        titleBasicsNode->parent = back;
        //attach new node to correct place
        //if new node < back, attach the new node to the left
        if(strcmp(titleBasicsNode->ID, back->ID) < 0)
        {
            back->left = titleBasicsNode;
            printf("ID: %s inserted LEFT\n", titleBasicsNode->ID);
        }
        //if the new node > back, attach the new node to the right
        else if(strcmp(titleBasicsNode->ID, back->ID) > 0)
        {
           
            back->right = titleBasicsNode;
            printf("ID: %s inserted RIGHT\n", titleBasicsNode->ID);
        }
        //else attach the new node to the end of the linked list
        else
        {
            back->next = titleBasicsNode;
            back = titleBasicsNode->parent;
            printf("ID: %s is a duplicate\n", titleBasicsNode->ID);
        }
        TBasic_RestoreAVL(ancestor, titleBasicsNode);
        printf("ROOT: %s\n", tBasicsRoot->ID);
        printf("NODE: %s\n", titleBasicsNode->ID);
        printf("root->balance = %d, parent->balance = %d\n", tBasicsRoot->balance,
               titleBasicsNode->parent->balance);
       
        
        printf("DONE INSERTING\n\n");
        
        //Print(titleBasicsNode);
    }
}
//TExecsDataBST is a BST containing TExecs structures (duplicates are stored as a
//linked list
void TExecsDataBST(TExecs* execsNode, int size)
{
    //printf("ID: %s\n", altTitleNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tExecsRoot = execsNode;
    }
    else
    {
        TExecs *temp = tExecsRoot;
        TExecs *back = NULL;
        
        //walk through the tree to find where the new node should go
        while(temp != NULL)
        {
            back = temp;
            //if new node < temp, go left
            if(strcmp(execsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                printf("going left\n");
            }
            //if the new node > temp, go right
            else if(strcmp(execsNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                printf("going right\n");
            }
            //else, the new node is a duplicate; walk through the linked list
            else
            {
                //linked list for duplicates
                temp = temp->next;
                printf("going next\n");
            }
        }
        if(back == NULL)
        {
            tExecsRoot = execsNode;
        }
        //attach the new node where it should go
        else
        {
            back = execsNode->parent;
            //if new node < back, attach left
            if(strcmp(execsNode->ID, back->ID) < 0)
            {
                back->left = execsNode;
                printf("ID: %s inserted LEFT\n", execsNode->ID);
            }
            //if new node > back, attach right
            else if(strcmp(execsNode->ID, back->ID) > 0)
            {
                back->right = execsNode;
                printf("ID: %s inserted RIGHT\n", execsNode->ID);
            }
            //else, the node is a duplicate; attach to the end of the linked list
            else
            {
                back->next = execsNode;
                printf("ID: %s is a duplicate\n", execsNode->ID);
            }
        }
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
//------------------------------------------------------------------
// Adjust the balance factor in all nodes from the inserted node's
//   parent back up to but NOT including a designated end node.
// @param end– last node back up the tree that needs adjusting
// @param start – node just inserted
//------------------------------------------------------------------
void adjusttBalancesTBasic(TBasic *end, TBasic *start)
{
    TBasic *temp = start->parent; // Set starting point at start's parent
    while(temp != end)
    {
        if(start->ID < temp->ID)
            temp->balance = 1;
        else
            temp->balance = -1;
        temp = temp->parent;
    } // end while
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void TBasic_RestoreAVL(TBasic *ancestor, TBasic *newNode)
{
    printf("in Restore\n");
    // Case 1: balance of all ancestors' is '0'
    if(ancestor == NULL)
    {
        printf("case 1\n");
        if(newNode->ID < tBasicsRoot->ID)       // newNode inserted to left of root
            tBasicsRoot->balance = 1;
        else
            tBasicsRoot->balance = -1;   // newNode inserted to right of root
        // Adjust the balance for all nodes from newNode back up to root
        adjusttBalancesTBasic(tBasicsRoot, newNode);
    }
    
    // Case 2: Insertion in opposite subtree of ancestor's balance factor, i.e.
    //  ancestor.balance = 1 AND  Insertion made in ancestor's right subtree
    //     OR
    //  ancestor.balance = -1 AND  Insertion made in ancestor's left subtree
    else if(((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->ID) > 0)) ||
            ((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->ID) < 0)))
    {
        printf("case 2\n");
        ancestor->balance = 0;
        // Adjust the balance for all nodes from newNode back up to ancestor
        adjusttBalancesTBasic(ancestor, newNode);
    }
    // Case 3: ancestor.balance = -1 and the node inserted is
    //      in the right subtree of ancestor's right child
    else if((ancestor->balance == -1) && (strcmp(newNode->ID, ancestor->right->ID) > 0))
    {
        printf("case 3\n");

        ancestor->balance = 0; // Reset ancestor's balance
        leftRotateTBasic(ancestor);       // Do single left rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        adjusttBalancesTBasic(ancestor->parent, newNode);
    }
    
    // Case 4: ancestor.balance is 1 and the node inserted is
    //      in the left subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) < 0))
    {
        printf("case 4\n");
        ancestor->balance = 0; // Reset ancestor's balance
        rightRotateTBasic(ancestor);       // Do single right rotation about ancestor
        // Adjust the balance for all nodes from newNode back up to ancestor's parent
        adjusttBalancesTBasic(ancestor->parent, newNode);
    }
    
    //Case 5: ancestor.balance is 1 and the node inserted is
    //      in the right subtree of ancestor's left child
    else if((ancestor->balance == 1) && (strcmp(newNode->ID, ancestor->left->ID) > 0))
    {
        printf("case 5\n");

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
        printf("case 6\n");

        // Perform double rotation (right then left)
        rightRotateTBasic(ancestor->right);
        leftRotateTBasic(ancestor);
        adjustRightLeftTBasic(ancestor, newNode);
    }
}

//http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code203_Tree.html
void rightRotateTBasic(TBasic *node)
{
    printf("ID: %s rotate RIGHT\n", node->ID);
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
    printf("ID: %s rotate LEFT\n", node->ID);
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
        node->parent->right = node;
    }
    else
    {
        node->parent->left = node;
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
        adjusttBalancesTBasic(end->parent->left, start);
    }
    else
    {
        end->balance = 0;
        end->parent->left->balance = 1;
        adjusttBalancesTBasic(end, start);
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
        adjusttBalancesTBasic(end->parent->right, start);
    }
    else
    {
        end->balance = 0;
        end->parent->right->balance = -1;
        adjusttBalancesTBasic(end, start);
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
               

