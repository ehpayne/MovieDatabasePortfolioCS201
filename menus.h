/*
 * Author: Elizabeth Payne
 * File: menus.h
 * Description: This is the header file that contains all the menus for the
 *              user interface.
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"
#include "hash.h"
#include "createUpdateDelete.h"
//Menus
extern void welcomeMenu();
extern void newUserMenu();
extern void newUser(char*username, char *password);
extern void loginMenu();
extern void initialMenu(char *username);
extern void initialMenuNewUser(char *username);
extern void createMenu(char *username);
extern void retrieveMenu(char *username);
extern void updateMenu(char *username);
extern void deleteMenu(char *username);
extern void movieTitleSearchMenu(char *username, char *catalogName, int searchType); //0 for catalog, 1 for search history
extern void movieInfoMenu(TBasic *movie);


//manipulate strings
extern char *strlwr(char *str);
extern char *appendFilename(char *str);
