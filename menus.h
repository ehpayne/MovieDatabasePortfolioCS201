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
extern void movieTitleSearchMenu(char *username);
extern void actorNameSearchMenu(char *username);
extern void directorNameSearchMenu(char *username);
extern void movieInfoMenu(TBasic *movie);
extern void actorInfoMenu(NBasic *actor);
extern void directorInfoMenu(TExecs *director);


//manipulate strings
extern char *strlwr(char *str);
extern char *appendFilename(char *str);
