
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
    }
    
}

void deleteMovieCatalog(char *username, char *catalogName)
{
    MovieCatalog *tempCatalog = mCatalogNameList->headCatalog;
    MovieCatalog *back = NULL;
    while(tempCatalog != NULL)
    {
        back = tempCatalog;
        if(strcmp(tempCatalog->name, catalogName) == 0)
        {
            back->next = tempCatalog->next;
            tempCatalog->next = NULL;
            break;
        }
        tempCatalog = tempCatalog->next;
    }
    if(tempCatalog == NULL)
    {
        printf("Catalog was not found\n");
        initialMenu(username);
    }
    
}

void printInfo(char *username, int printType)
{
    
    if(printType == 0)
    {
        char *filename = appendFilename(username);
        FILE *fptr = fopen(filename, "a");
        
        if(mCatalogNameList == NULL)
        {
            fprintf(fptr, "####\n");
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
                printf( "####\n");
                tempCatalog = tempCatalog->next;
                
                
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
    
    if(fgets(title, lineSize, fptr) != NULL && strcmp(title, "####\n") == 0)
    {
        //do nothing
    }
    else
    {
        char *catalogName = malloc(sizeof(char *));
        do
        {
            fgets(catalogName, lineSize, fptr);
            while(fgets(title, lineSize, fptr) != NULL && strcmp(title, "####\n") != 0)
            {
                TBasic *movie = hashTableSEARCH(title);
                addMovieToCatalog(catalogName, movie);
            }
            if(feof(fptr))
            {
                break;
            }
        }while(fgets(catalogName, lineSize, fptr) != NULL);
    }
    fclose(fptr);
    
    //clear the log file once you read everything in
    fptr = fopen(filename, "w");
    fclose(fptr);
}

