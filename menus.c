/* Author: Elizabeth Payne
 * File: menus.c
 * Description: This code contains the menus for the user interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"
#include "storeData.h"
#include "menus.h"

//the welcomeMenu function is the startup page for the database
//it asks the user to either login or create a new user account
void welcomeMenu()
{
    char input;
    
    do
    {
        printf("\n\nWELCOME TO THE MOVIE DATABASE! \n\n");
        printf("Please select one of the following choices:\n");
        printf(" A. Create a new user account\n B. Login\n");
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            newUserMenu();
        }
        else if(input == 'b')
        {
            loginMenu();
        }
        else
        {
            //keep printing until correct input is entered
            printf("Incorrect Input. Enter a letter A-B. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b');
}

//the newUserMenu function asks the user to create a user name and password
//this data is then stored into the UserInfo.txt file and a username.log file
//is also created
void newUserMenu()
{
    char* username_input = malloc(sizeof(char*));
    char temp;
    system("clear");
    printf("\n\nWELCOME!!\n\n");
    printf("Please create a username:\n");
    scanf("%c",&temp); //clear buffer by storing it into temp
    scanf("%[^\n]",username_input);
    username_input = strlwr(username_input);
    
    char* password_input =  malloc(sizeof(char*));
    printf("\n\nNow create a password (case sensitive):\n");
    scanf("%c",&temp); //clear buffer by storing it into temp
    scanf("%[^\n]",password_input);
    
    newUser(username_input, password_input);
    
    printf("\n\nUSER CREATED\n\n");
    system("clear");
    printf("\n\nWELCOME NEW USER!\n\n");
    initialMenu(username_input);
}

//the loginMenu funciton asks the user to login to an existing user account
//if the user information entered is correct, the user can proceed
//else, they are asked to re-enter the correct information
void loginMenu()
{
    char temp;
    system("clear");
    printf("\n\nMOVIE DATABASE LOGIN PAGE:\n\n");
    int userandPasswordFound = 0; //FALSE
    do
    {
        //read in username
        char* username_input =  malloc(sizeof(char*));
        printf("\n\nUSERNAME:\n\n");
        scanf("%c",&temp); //clear buffer by storing it into temp
        scanf("%[^\n]",username_input);
        username_input = strlwr(username_input);
        
        //read in password
        char *password_input = malloc(sizeof(char*));
        printf("\n\nPASSWORD:\n\n");
        scanf("%c",&temp); //clear buffer by storing it into temp
        scanf("%[^\n]",password_input);
        
        //search for the username or password in the UserInfo.txt file
        FILE* fptr = fopen("UserInfo.txt", "r");
        if(fptr == NULL)
        {
            printf("\n\nThere are no users. You must create a new user to proceed\n\n");
            printf("Please create a username:\n");
            scanf("%c",&temp); //clear buffer by storing it into temp
            scanf("%[^\n]",username_input);
            username_input = strlwr(username_input);
            
            char* password_input =  malloc(sizeof(char*));
            printf("\n\nNow create a password (case sensitive):\n");
            scanf("%c",&temp); //clear buffer by storing it into temp
            scanf("%[^\n]",password_input);
            
            newUser(username_input, password_input);
            
            printf("\n\nUSER CREATED\n\n");
            system("clear");
            printf("\n\nWELCOME NEW USER!\n\n");
            initialMenu(username_input);
        }
        char *line = malloc(sizeof(char *));
        int lineSize = 1024;
        int onlyUsernameIsFound = 0; //FALSE
        int userandPasswordFound = 0; //FALSE
        
        //get a line fron UserInfo.txt and check to see if it matches user input
        while (fgets(line, lineSize, fptr) != NULL)
        {
            char *copy = strdup(line);
            
            //remove the newline character
            copy[strlen(copy)-1] = 0;
            char *user_token = strtok(copy, " ");
            char *password_token = strtok(NULL, " ");
            
            //if username and password found, break
            if(strcmp(username_input, user_token) == 0 &&
               strcmp(password_input, password_token) == 0)
            {
                userandPasswordFound = 1; //TRUE
                break;
            }
            //if only username is found, keep looking
            if(strcmp(username_input, user_token) != 0 &&
               strcmp(password_input, password_token) == 0)
            {
                onlyUsernameIsFound = 1;
            }
        }
        //if username and password are found, proceed
        if(userandPasswordFound == 1)
        {
            system("clear");
            printf("\n\nWELCOME BACK!!\n\n");
            initialMenu(username_input);
            break;
        }
        //if only username is found, notify user that password is incorrect
        //try again
        else if(onlyUsernameIsFound == 1)
        {
            printf("\n\nINCORRECT PASSWORD. TRY AGAIN\n\n");
        }
        //else notify user that username and password are incorrect, try again
        else
        {
            printf("\n\nINCORRECT USERNAME AND PASSWORD. TRY AGAIN\n\n");
        }
    }while(userandPasswordFound != 1);
    
}

//the initialMenu function asks the user if they want to create, update, or delete
//a catalog or if they want to lookup a record
void initialMenu(char *username)
{
    char input;
    do
    {
        printf("Would you like to: \n A. Create a catolog \n"
               " B. Lookup a record \n C. Update a catolog \n"
               " D. Delete a catolog\n" );
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            //the user wants to create
            createMenu(username);
        }
        else if(input == 'b')
        {
            //the user wants to lookup
            retrieveMenu();
        }
        else if(input == 'c')
        {
            //the user wants to update
            updateMenu();
        }
        else if(input == 'd')
        {
            //the user wants to delete
            deleteMenu();
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-D. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
    
}
void createMenu(char *username)
{
    char *catalogName = malloc(sizeof(char *));
    char input;
    char temp;
    do
    {
        printf("What type of catalog would you like to create? \n"
               " A. Movie Catalog\n B. Actor Catalog \n"
               " C. Director/Writer Catalog\n");
        scanf("%c",&input);
        scanf("%c",&input);
        
        input = tolower(input);
        
        
        printf("What would you like to name your catalog?\n");
        scanf("%c",&temp); //clear buffer by storing it into temp
        scanf("%[^\n]",catalogName);
        char *filename = appendFilename(username);
        FILE *fptr = fopen(filename, "a");
        fprintf(fptr, "%s\n", catalogName);
        fclose(fptr);
        if(input == 'a')
        {
            printf("Would you like to add a movie to your catalog now?\n"
                   " A. Yes\n B. No\n");
            scanf("%c",&input);
            scanf("%c",&input);
            input = tolower(input);
            if(input == 'a')
            {
                char *movieTitle = malloc(sizeof(char*));
                printf("Enter a movie title you would like to add\n");
                scanf("%c",&temp); //clear buffer by storing it into temp
                scanf("%[^\n]",movieTitle);
                
                //search hash table
                //if title is found, searchBST
                //if(tree == NULL) readTitleBasics then search
                //else if(search not found) return error
                //else return correct search key and add to movie catolog
                
            }
            else if(input == 'b')
            {
                break;
            }
            else
            {
                printf("Incorrect Input. Enter a letter A-B. Try Again\n\n");
            }
        }
        else if(input == 'b')
        {
            printf("Would you like to add a actor/actress now?\n"
                   " A. Yes\n B. No\n");
            scanf("%c",&input);
            input = tolower(input);
            
            char *actor = malloc(sizeof(char*));
            printf("Enter the name of an actor/actress you would like to add\n");
            scanf("%s\n", actor);
            
            //SearchNameBasicBST
            //if(tree == NULL) readNameBasics then search
            //else if(search not found) return error
            //else return correct search key and add to actor catolog
        }
        else if(input == 'c')
        {
            printf("Would you like to add a director/writer now?\n"
                   " A. Yes\n B. No\n");
            scanf("%c",&input);
            input = tolower(input);
            
            char *actor = malloc(sizeof(char*));
            printf("Enter a director/writer you would like to add\n");
            scanf("%s\n", actor);
            
            //SearchNameBasicBST
            //if(tree == NULL) readNameBasics then search
            //else if(search not found) return error
            //else return correct search key and add to actor catolog
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-C. Try Again.\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c');
}
void retrieveMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to lookup? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            readAltTitlesFile();
        }
        else if(input == 'b')
        {
            readTitleBasicsFile();
            
        }
        else if(input == 'c')
        {
            readTitleExecsFile();
            
        }
        else if(input == 'd')
        {
            readTitleEpisodeFile();
            
        }
        else if(input == 'e')
        {
            readTitleCrewFile();
            
        }
        else if(input == 'f')
        {
            readTitleRatingFile();
            
        }
        else if(input == 'g')
        {
            readNameBasicsFile();
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}

void updateMenu()
{
    char input;
    do
    {
        //open the log file
        //print out the user's catalogs
        //ask them what catalog they would like to update
        printf("What type of data would you like to update? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        
        if(input == 'a')
        {
            
        }
        else if(input == 'b')
        {
            
        }
        else if(input == 'c')
        {
            
        }
        else if(input == 'd')
        {
            
        }
        else if(input == 'e')
        {
            
        }
        else if(input == 'f')
        {
            
        }
        else if(input == 'g')
        {
            
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}

void deleteMenu()
{
    char input;
    do
    {
        //open the log file
        //print out the user's catalogs
        //ask them what catalog they would like to update
        printf("What type of data would you like to delete? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        
        if(input == 'a')
        {
            
        }
        else if(input == 'b')
        {
            
        }
        else if(input == 'c')
        {
            
        }
        else if(input == 'd')
        {
            
        }
        else if(input == 'e')
        {
            
        }
        else if(input == 'f')
        {
            
        }
        else if(input == 'g')
        {
            
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' &&
           input != 'd' && input != 'e' && input != 'f' && input != 'g');
}

char *strlwr(char *str)
{
    int size = strlen(str);
    for(int i = 0; i < size; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

//appendFilename adds .log to a filename
char *appendFilename(char *username)
{
    char*filename = malloc(strlen(username) + 4);
    for(int i = 0; i <strlen(username); i++)
    {
        filename[i] = username[i];
    }
    filename[strlen(username)] = '.';
    filename[strlen(username)+1] = 'l';
    filename[strlen(username)+2] = 'o';
    filename[strlen(username)+3] = 'g';
    
    return filename;
}

int main()
{
    welcomeMenu();
    return 0;
}
