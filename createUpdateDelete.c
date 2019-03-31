
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
    //printf("ADDING MOVIE\n");
    MovieCatalog *catalog = addMovieCatalogToCatalogList(catalogName);
   // printf("ADDING CATALOG\n");
    MovieRecord *temp = catalog->headMovie;
    MovieRecord *back = NULL;
    if(temp == NULL)
    {
        //printf("FIRST CATALOG. ADDING TO HEAD\n");
        catalog->headMovie = newMovieRecord(movie);
    }
    else
    {
        //printf("WALKING DOWN LINKED LIST\n");
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
        //printf("DONE\n");
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

void printInfoToLogFile(char *username)
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
}

