#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "readFiles.h"
#include "hash.h"
#include "menus.h"

typedef struct TBasicMovie MovieRecord;

struct TBasicMovie
{
    TBasic *movie;
    MovieRecord *next;
};
typedef struct TBasicCatalog MovieCatalog;
struct TBasicCatalog
{
    char *name;
    MovieCatalog *next;
    MovieRecord *headMovie;
};

typedef struct MovieCatalogNameList MovieCatalogList;
struct MovieCatalogNameList
{
    MovieCatalog *headCatalog;
};
extern MovieCatalogList *mCatalogNameList;

//constructors
MovieRecord *newMovieRecord(TBasic *movie);
MovieCatalog *newMovieCatalog(char *newName);

//create, update, delete
void addMovieToCatalog(char *catalogName, TBasic *movie);
MovieCatalog *addMovieCatalogToCatalogList(char *newName);
void updateMovieCatalog(char *username, char *catalogName, char *title);
void deleteMovieCatalog(char *username,char *catalogName);

//working with the log file
void printInfo(char *username, int printType);
void readInLogFile(char *username);



