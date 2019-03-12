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

struct BSTree
{
    void *tNode;
    void *left, *right;
};
TreeNode *newTree()
{
    TreeNode *tree = malloc(sizeof(TreeNode));
    tree->tNode = NULL;
    tree->left = NULL;
    tree->right = NULL;
    
    return tree;
    
}
/*void basicBSTInsert(TAlt *altTitleNode, TBasic *basicTitleNode,
                    TExecs *execsNode, TEpisode *episodeNode,
                    TCrew *crewNode, TRating *ratingNode,
                    NBasic *basicNameNode, int size)
{
    if(altTitleNode != NULL)
    {
        
    }
    else if(basicTitleNode != NULL)
    {
        
    }
    else if(execsNode != NULL)
    {
        
    }
    else if(episodeNode != NULL)
    {
        
    }
    else if(
    TreeNode *treeNode = newTree();
    TreeNode *temp;
    TreeNode *back = NULL;
    
    if(node == NULL)
    {
        return;
    }
    if(size == 0) //root
    {
        treeNode->tNode = node;
    }
    else
    {
        temp = treeNode;
        while(temp != NULL)
        {
            back = temp;
            if(node->ID < temp->ID)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
 
    
    
}
*/
