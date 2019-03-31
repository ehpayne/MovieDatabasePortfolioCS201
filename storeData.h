/*
 * Author: Elizabeth Payne
 * File: storeData.h
 * Description: This is the header file to store all the data that was read in in readFiles.c
 */
#pragma once
#include <stdio.h>
#include "readFiles.h"
TAlt *tAltRoot;
TBasic *tBasicsRoot;
TExecs *tExecsRoot;
NBasic *nBasicRoot;

//trees for storing structures
extern void TAltDataBST(TAlt *alt, int size);
extern void TBasicDataBST(TBasic *titleBasicsNode, int size);
extern void TExecsDataBST(TExecs *execsNode, int size);

//AVL Fixup Functions
extern void TBasic_RestoreAVL(TBasic *ancestor, TBasic *newNode);
extern void adjustBalancesTBasic(TBasic *end, TBasic *start);
extern void rightRotateTBasic(TBasic *node);
extern void leftRotateTBasic(TBasic *node);
extern void adjustLeftRightTBasic(TBasic *end, TBasic *start);
extern void adjustRightLeftTBasic(TBasic *end, TBasic *start);
extern void Print(TBasic *n);

//search BST
extern TBasic *searchTBasicBST(char *title);

//storing user data
void newUser(char *username, char *password);


