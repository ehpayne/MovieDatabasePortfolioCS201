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
extern void initialMenu(char *username);
extern void createMenu(char *username);
extern void retrieveMenu();
extern void updateMenu();
extern void deleteMenu();

//manipulate strings
extern char *strlwr(char *str);
extern char *appendFilename(char *str);
