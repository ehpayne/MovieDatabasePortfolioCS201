/* Author: Elizabeth Payne
 * File: main.c
 * Description: This code is the main function for the project
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "hash.h"
#include "menus.h"
#include "readFiles.h"
#include "createUpdateDelete.h"

HTable *tBasicHashTable = NULL;
MovieCatalogList *mCatalogNameList = NULL;

int main()
{
    
    welcomeMenu();
    return 0;
}

