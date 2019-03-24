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
            printf("Incorrect Input. Enter a letter A-B. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b');
}

void newUserMenu()
{
    char* username_input = malloc(sizeof(char*));
    system("clear");
    printf("\n\nWELCOME!!\n\n");
    printf("Please create a username:\n");
    scanf("%s", username_input);
    username_input = strlwr(username_input);
    
    char* password_input =  malloc(sizeof(char*));
    printf("\n\nNow create a password (case sensitive):\n");
    scanf("%s", password_input);
    
    newUser(username_input, password_input);
    
    printf("\n\nUSER CREATED\n\n");
    system("clear");
    printf("\n\nWELCOME NEW USER!\n\n");
    initialMenu();
}

void loginMenu()
{
    system("clear");
    printf("\n\nMOVIE DATABASE LOGIN PAGE:\n\n");
    int userandPasswordFound = 0;
    do
    {
        char* username_input =  malloc(sizeof(char*));
        printf("\n\nUSERNAME:\n\n");
        scanf("%s",username_input);
        username_input = strlwr(username_input);
        char *password_input = malloc(sizeof(char*));
        printf("\n\nPASSWORD:\n\n");
        scanf("%s", password_input);
        
        FILE* fptr = fopen("UserInfo.txt", "r");
        char *line = malloc(sizeof(char *));
        int lineSize = 1024;
        int onlyUsernameIsFound = 0;
        int userandPasswordFound = 0;
        //fgets(line, lineSize, fptr);
        while (fgets(line, lineSize, fptr) != NULL)
        {
            char *copy = strdup(line);
            
            //remove the newline character
            copy[strlen(copy)-1] = 0;
            char *user_token = strtok(copy, " ");
            char *password_token = strtok(NULL, " ");
            
            if(strcmp(username_input, user_token) == 0 &&
               strcmp(password_input, password_token) == 0)
            {
                userandPasswordFound = 1;
                break;
            }
            if(strcmp(username_input, user_token) == 0 &&
               strcmp(password_input, password_token) != 0)
            {
                onlyUsernameIsFound = 1;
            }
        }
        if(userandPasswordFound == 1)
        {
            system("clear");
            printf("\n\nWELCOME BACK!!\n\n");
            initialMenu();
            break;
        }
        else if(onlyUsernameIsFound == 1)
        {
            printf("\n\nINCORRECT PASSWORD. TRY AGAIN\n\n");
        }
        else
        {
            printf("\n\nINCORRECT USERNAME AND PASSWORD. TRY AGAIN\n\n");
        }
    }while(userandPasswordFound != 1);
    
}

void initialMenu()
{
    char input;
    do
    {
        printf("Would you like to: \n A. Create a movie catolog \n"
               " B. Lookup a record \n C. Update a movie catolog \n"
               " D. Delete a movie catolog\n" );
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            createMenu();
        }
        else if(input == 'b')
        {
            retrieveMenu();
        }
        else if(input == 'c')
        {
            updateMenu();
        }
        else if(input == 'd')
        {
            deleteMenu();
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-D. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
    
}
void createMenu()
{
    char *catalogName = malloc(sizeof(char *));
    char input;
    do
    {
        printf("What would you like to name your catalog?");
        scanf("%s", catalogName);
        
        
        printf("What type of catalog would you like to create? \n"
               " A. Movie Catalog\n B. Actor Catalog \n"
               " C. Director/Writer Catalog");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            printf("Would you like to add a movie now?\n A. Yes\n B. No\n");
            scanf("%c",&input);
            input = tolower(input);
            if(input == 'a')
            {
                char *movieTitle = malloc(sizeof(char*));
                printf("Enter a movie title you would like to add\n");
                scanf("%s\n", movieTitle);
                
                //SearchTitleBasicBST
                //if(tree == NULL) readTitleBasics then search
                //else if(search not found) return error
                //else return correct search key and add to movie catolog
                
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
            printf("Enter a movie title you would like to add\n");
            scanf("%s\n", actor);
            
            //SearchNameBasicBST
            //if(tree == NULL) readNameBasics then search
            //else if(search not found) return error
            //else return correct search key and add to actor catolog
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
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}
void retrieveMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to retrieve? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            TAlt *alt = newAltTitle();
            alt = readAltTitlesFile(alt);
            printf("Alt Size: %d\n", alt->size);
            
            //storeAltTitleData(alt, alt->size);
        }
        else if(input == 'b')
        {
            TBasic *tBasic = newTitleBasics();
            tBasic = readTitleBasicsFile(tBasic);
            printf("TBasic Size: %d\n", tBasic->size);
            
        }
        else if(input == 'c')
        {
            TExecs *execs = newTitleExecs();
            execs = readTitleExecsFile(execs);
            printf("Exec Size: %d\n", execs->size);
            
        }
        else if(input == 'd')
        {
            TEpisode *episode = newTitleEpisode();
            episode = readTitleEpisodeFile(episode);
            printf("Episode Size: %d\n", episode->size);
            
        }
        else if(input == 'e')
        {
            TCrew *crew = newTitleCrew();
            crew = readTitleCrewFile(crew);
            printf("Crew Size: %d\n", crew->size);
            
        }
        else if(input == 'f')
        {
            TRating *rating = newTitleRating();
            rating = readTitleRatingFile(rating);
            printf("Rating Size: %d\n", rating->size);
            
        }
        else if(input == 'g')
        {
            NBasic *nameBasics = newNameBasics();
            nameBasics = readNameBasicsFile(nameBasics);
            printf("NBasic Size: %d\n", nameBasics->size);
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

int main()
{
    welcomeMenu();
    return 0;
}
