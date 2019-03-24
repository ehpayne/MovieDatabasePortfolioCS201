/*
 * Author: Elizabeth Payne
 * File: menus.h
 * Description: This is the header file that contains all the menus for the
 *              user interface.
 */

//Menus
extern void welcomeMenu();
extern void newUserMenu();
extern void loginMenu();
extern void initialMenu();
extern void createMenu();
extern void retrieveMenu();
extern void updateMenu();
extern void deleteMenu();

extern char *strlwr(char *str);
extern int matchStrings(char *input, char *str);
