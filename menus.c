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
#include "hash.h"
#include "readFiles.h"
#include "menus.h"
#include "createUpdateDelete.h"


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
    initialMenuNewUser(username_input);
}

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
void initialMenuNewUser(char *username)
{
    char input;
    do
    {
        printf("Would you like to: \n A. Create a catolog \n"
               " B. Lookup a record \n C. Exit the database\n" );
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
            retrieveMenu(username);
        }
        else if(input == 'c')
        {
            //the user wants to update
            printf("Thank you for using the Movie Database.\n Goodbye!\n");
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-C. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c');
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
        FILE* fptr = fopen("UserInfo.txt", "r");
        
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
        
        if(fptr == NULL)
        {
            printf("\n\nThere are no users. You must create a new user to proceed\n\n");
            newUserMenu();
            system("clear");
            initialMenu(username_input);
        }
        //search for the username or password in the UserInfo.txt file
        
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
               " D. Delete a catolog\n E. Exit the database\n" );
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
            retrieveMenu(username);
        }
        else if(input == 'c')
        {
            //the user wants to update
            updateMenu(username);
        }
        else if(input == 'd')
        {
            //the user wants to delete
            deleteMenu(username);
        }
        else if(input == 'e')
        {
            printf("Writing to your log file\n");
            printInfo(username, 0); //print to log file
            printf("Thank you for using the Movie Database.\n Goodbye!\n");
            
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-E. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e');
    
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
        
        
        if(input == 'a')
        {
            printf("Would you like to add a movie to your catalog now?\n"
                   " A. Yes\n B. No\n");
            scanf("%c",&input);
            scanf("%c",&input);
            input = tolower(input);
            if(input == 'a')
            {
                movieTitleSearchMenu(username, catalogName, 0);
            }
            else if(input == 'b')
            {
                initialMenu(username);
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
void retrieveMenu(char *username)
{
    char input;
    do
    {
        printf("What type of data would you like to lookup? \n"
               " A. Movie Title \n"
               " B. Directors/Writers \n"
               " C. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            movieTitleSearchMenu(username, "Search History", 1);
            
        }
        else if(input == 'b')
        {
            readTitleExecsFile();
        }
        else if(input == 'c')
        {
            readNameBasicsFile();
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c');
}

void updateMenu(char *username)
{
    char temp;
    char *catalogName = malloc(sizeof(char *));
    char *movieTitle = malloc(sizeof(char *));
    //if they want to update first, read from log file
    if(mCatalogNameList == NULL)
    {
        readInLogFile(username);
        //if there is nothing in the log file
        if(mCatalogNameList == NULL)
        {
            printf("Nothing to update\n");
            initialMenu(username);
        }
        else
        {
            printInfo(username, 1); //print to stdout
        }
    }
    else
    {
        printInfo(username, 1); //print to stdout
        
    }
    
    printf("Enter the name of the catalog you would like to update:\n");
    scanf("%c", &temp); //clear buffer by storing it into temp
    scanf("%[^\n]", catalogName);
    do
    {
        printf("Would you like to: \n"
               " A. Add a record to the catalog\n"
               " B. Delete a record from the catalog\n");
        scanf("%c", &temp);
        scanf("%c", &temp);
        if(temp == 'a')
        {
            movieTitleSearchMenu(username, catalogName, 0);
        }
        else if(temp == 'b')
        {
            printf("Enter the title of the movie you would like to delete from the catalog\n");
            updateMovieCatalog(username, catalogName, movieTitle);
        }
        else
        {
            printf("Incorrect Input. Please enter a letter from A-B. Try Again\n\n");
        }
        
    }while(temp != 'a' && temp != 'b');
    
}

void deleteMenu(char *username)
{
    char temp;
    char *catalogName = malloc(sizeof(char *));
    //char *movieTitle = malloc(sizeof(char *));
    //if they want to update first, read from log file
    if(mCatalogNameList == NULL)
    {
        readInLogFile(username);
        //if there is nothing in the log file
        if(mCatalogNameList == NULL)
        {
            printf("Nothing to delete.\n");
            initialMenu(username);
        }
        else
        {
            printInfo(username, 1); //print to stdout
        }
    }
    else
    {
        printInfo(username, 1); //print to stdout
        
    }
    
    printf("Enter the name of the catalog you would like to delete:\n");
    scanf("%c", &temp); //clear buffer by storing it into temp
    scanf("%[^\n]", catalogName);
    
    deleteMovieCatalog(username,catalogName);
    printf("Catalog was successfully deleted\n");
    initialMenu(username);
}
void movieTitleSearchMenu(char *username, char *catalogName, int searchType)
{
    char *movieTitle = malloc(sizeof(char*));
    char input;
    char temp;
    printf("Enter a movie title you would like to search for: \n");
    scanf("%c",&temp); //clear buffer by storing it into temp
    scanf("%[^\n]",movieTitle);
    if(tBasicHashTable == NULL)
    {
        readTitleBasicsFile();
    }
    TBasic * movie = hashTableSEARCH(movieTitle);;
    //searchTBasicBST(movieTitle);
    
    if(movie == NULL)
    {
        printf("Movie record not found.\n Would you like to search for another movie?\n"
               " A. Yes\n B. No\n");
        scanf("%c", &input);
        input = tolower(input);
        while(input == 'a')
        {
            char *movieTitle = malloc(sizeof(char*));
            printf("Enter a movie title you would like to search for:\n");
            scanf("%c",&temp); //clear buffer by storing it into temp
            scanf("%[^\n]",movieTitle);
            
            movie = hashTableSEARCH(movieTitle);
            
            if(movie == NULL)
            {
                printf("Movie record not found.\n"
                       "Would you like to try again or search for another movie?\n"
                       " A. Yes\n B. No\n");
                scanf("%c", &input);
                input = tolower(input);
            }
        }
        if(input == 'b')
        {
            initialMenu(username);
        }
    }
    else
    {
        printf("\n\nMovie found!\n");
        movieInfoMenu(movie);
        if(searchType == 0)
        {
            printf("Would you like to add this movie to your catalog?\n"
                   " A. Yes\n B. No\n");
            scanf("%c", &input);
            scanf("%c", &input);
            
            if(input == 'a')
            {
                addMovieToCatalog(catalogName, movie);
                printf("%s has been added to your %s catalog.\n", movieTitle, catalogName);
                initialMenu(username);
            }
            else if(input == 'b')
            {
                initialMenu(username);
            }
        }
        else
        {
            addMovieToCatalog(catalogName, movie);
            initialMenu(username);
        }
        
    }
}

void movieInfoMenu(TBasic *movie)
{
    printf("\n\nMovie Title: %s\n", movie->primaryTitle);
    printf("Movie Type: %s\n", movie->titleType);
    printf("Year Released: %s\n", movie->startYear);
    printf("Runtime (minutes): %d\n", movie->runtimeMinutes);
    char *isAdult;
    if(movie->isAdult == 0)
    {
        isAdult = "No";
    }
    else
    {
        isAdult = "Yes";
    }
    printf("Adult Movie?: %s\n", isAdult);
    printf("Genres: \n");
    for(int i = 0; i < 3; i++)
    {
        if(movie->genres[i] != NULL)
        {
            printf("\t%s", movie->genres[i]);
        }
        else
        {
            break;
        }
    }
    printf("\n");
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

