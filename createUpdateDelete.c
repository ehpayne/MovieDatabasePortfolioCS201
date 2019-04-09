
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"
#include "hash.h"
#include "menus.h"
#include "createUpdateDelete.h"


MovieRecord *newMovieRecord(TBasic *movie)
{
    MovieRecord *record = malloc(sizeof(MovieRecord));
    record->movie = movie;
    record->next = NULL;
    
    return record;
}

MovieCatalog *newCatalog(char *name)
{
    MovieCatalog *catalog = malloc(sizeof(MovieCatalog));
    catalog->name = name;
    catalog->next = NULL;
    catalog->headMovie = NULL;
    
    return catalog;
}

void addMovieToCatalog(char *catalogName, TBasic *movie)
{
    MovieCatalog *catalog = addMovieCatalogToCatalogList(catalogName);
    MovieRecord *temp = catalog->headMovie;
    MovieRecord *back = NULL;
    if(temp == NULL)
    {
        catalog->headMovie = newMovieRecord(movie);
    }
    else
    {
        while (temp != NULL)
        {
            back = temp;
            //movie already in the list. break
            if(strcmp(temp->movie->ID, movie->ID) == 0)
            {
                break;
            }
            temp = temp->next;
        }
        back->next = newMovieRecord(movie);
    }
    
    
    
}

MovieCatalog *addMovieCatalogToCatalogList(char *newName)
{
    if( mCatalogNameList == NULL)
    {
        mCatalogNameList = malloc(sizeof(MovieCatalog));
        mCatalogNameList->headCatalog = newCatalog(newName);
        return mCatalogNameList->headCatalog;
    }
    else
    {
        MovieCatalog *temp = mCatalogNameList->headCatalog;
        MovieCatalog *back = NULL;
        
        while(temp != NULL)
        {
            back = temp;
            if(strcmp(temp->name, newName) == 0)
            {
                return temp;
            }
            temp = temp->next;
            
        }
        
        
        back->next = newCatalog(newName);
        return back->next;
    }
}

void updateMovieCatalog(char *username, char *catalogName, char *title)
{
    MovieCatalog *tempCatalog = mCatalogNameList->headCatalog;
    
    while(tempCatalog != NULL)
    {
        if(strcmp(tempCatalog->name, catalogName) == 0)
        {
            MovieRecord *tempMovie = tempCatalog->headMovie;
            MovieRecord *back = NULL;
            while (tempMovie != NULL)
            {
                back = tempMovie;
                if(strcmp(tempMovie->movie->primaryTitle, title) == 0)
                {
                    back->next = tempMovie->next;
                    tempMovie->next = NULL;
                    
                    break;
                }
                tempMovie = tempMovie->next;
            }
            break;
        }
        
        tempCatalog = tempCatalog->next;
        
    }
    if(tempCatalog == NULL)
    {
        printf("Catalog was not found\n");
        initialMenu(username);
        return;
    }
    
}

void deleteMovieCatalog(char *username, char *catalogName)
{
    MovieCatalog *tempCatalog = mCatalogNameList->headCatalog;
    MovieCatalog *back = NULL;
    //deleting the head or the only node
    if(tempCatalog != NULL && strcmp(tempCatalog->name, catalogName) == 0)
    {
        mCatalogNameList->headCatalog = tempCatalog->next;
        return;
    }
    while(tempCatalog != NULL && strcmp(tempCatalog->name, catalogName) != 0)
    {
        back = tempCatalog;
        tempCatalog = tempCatalog->next;
    }
    if(tempCatalog == NULL)
    {
        printf("Catalog was not found\n");
        initialMenu(username);
        return;
    }
    back->next = tempCatalog->next;
}

void printInfo(char *username, int printType)
{
    
    
    if(printType == 0)
    {
        char *filename = appendFilename(username);
        //clear the log file before you print
        FILE *fptr = fopen(filename, "w");
        if(mCatalogNameList == NULL)
        {
            //do nothing
        }
        else
        {
            MovieCatalog *tempCatalog = mCatalogNameList->headCatalog;
            while (tempCatalog != NULL)
            {
                fprintf(fptr,"%s\n", tempCatalog->name);
                MovieRecord *tempMovie = tempCatalog->headMovie;
                while(tempMovie != NULL)
                {
                    fprintf(fptr,"\t%s\n", tempMovie->movie->primaryTitle);
                    tempMovie = tempMovie->next;
                }
                fprintf(fptr, "####\n");
                tempCatalog = tempCatalog->next;
                
                
            }
        }
        fclose(fptr);
    }
    
    else
    {
        if(mCatalogNameList == NULL)
        {
            printf("No catalogs available\n");
        }
        else
        {
            MovieCatalog *tempCatalog = mCatalogNameList->headCatalog;
            while (tempCatalog != NULL)
            {
                printf("%s\n", tempCatalog->name);
                MovieRecord *tempMovie = tempCatalog->headMovie;
                while(tempMovie != NULL)
                {
                    printf("\t%s\n", tempMovie->movie->primaryTitle);
                    tempMovie = tempMovie->next;
                }
                
                tempCatalog = tempCatalog->next;
                printf( "####\n");
                
                
            }
        }
    }
}

void readInLogFile(char *username)
{
    char *filename = appendFilename(username);
    FILE *fptr = fopen(filename, "r");
    char *title = malloc(sizeof(char *));
    int lineSize = 250;
    char *titleCopy = malloc(sizeof(char*));
    
    char *catalogName = malloc(sizeof(char *));
    while(fgets(catalogName, lineSize, fptr) != NULL)
    {
        //fgets(catalogName, lineSize, fptr);
        char *catalogCopy = strdup(catalogName);
        catalogCopy[strlen(catalogCopy)-1] = 0;
        while(fgetc(fptr) != 0 && fgets(title, lineSize, fptr) != NULL && strcmp(title, "###\n") )
        {
            titleCopy = strdup(title);
            //remove the newline character
            titleCopy[strlen(titleCopy)-1] = 0;
            
            if(tBasicHashTable == NULL)
            {
                readTitleBasicsFile();
            }
            TBasic *movie = hashTableSEARCH(titleCopy);
            addMovieToCatalog(catalogCopy, movie);
        }
        if(feof(fptr))
        {
            break;
        }
    }
    fclose(fptr);
    
}

