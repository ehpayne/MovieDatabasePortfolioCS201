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

int defaultCapacity = 1000;

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
                printf("going left\n");
            }
            //if new node > temp, go right
            else if(strcmp(altTitleNode->ID, temp->ID) > 0)
            {
                temp = temp->right;
                printf("going right\n");
            }
            else
            {
                //linked list for duplicates
                temp = temp->next;
                printf("going next\n");
            }
        }
        //attach new node to correct place
        if(back == NULL)
        {
            tAltRoot = altTitleNode;
        }
        else
        {
            //if new node < back, attach new node to the left
            if(strcmp(altTitleNode->ID, back->ID) < 0)
            {
                back->left =altTitleNode;
                printf("ID: %s inserted LEFT\n", altTitleNode->ID);
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
void TBasicDataBST(TBasic* titleBasicsNode, int size)
{
    printf("ID: %s\n", titleBasicsNode->ID);
    if(size == 0)
    {
        printf("root\n");
        tBasicsRoot = titleBasicsNode;
    }
    else
    {
        TBasic *temp = tBasicsRoot;
        TBasic *back = NULL;
        
        //walk through the tree to find where the new node should go
        while(temp != NULL)
        {
            back = temp;
            //if new node < temp, go left
            if(strcmp(titleBasicsNode->ID, temp->ID) < 0)
            {
                temp = temp->left;
                printf("going left\n");
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
        if(back == NULL)
        {
            tBasicsRoot = titleBasicsNode;
        }
        else
        {
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
                printf("ID: %s is a duplicate\n", titleBasicsNode->ID);
            }
        }
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

void hashTable(char *ID, char *name, int size)
{
    
}

