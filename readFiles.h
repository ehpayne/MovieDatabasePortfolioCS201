/*
 * Author: Elizabeth Payne
 * File: readFiles.h
 * Description: This is the header file to read in all the data files and
 *                            assign the information to the corresponding variable.
 */

#include <stdio.h>
#pragma once

typedef struct title_basics TBasic;
//contains basic information for titles
struct title_basics
{
    char *ID;                  //unique identifier of the title
    char *titleType;          //the type.format of the title (e.g. movie, short, tv series, etc)
    char *primaryTitle;       //the more popular title
    char *originalTitle;      //original title in the original language
    int isAdult;                            //boolean --> 0: non-adult title 1: adult title
    char *startYear;                  //represents the release year of a title (or start year for TV series)
    char *endYear;                        //TV series end year (/N for all other title types)
    int runtimeMinutes;                //primary runtime of the title in minutes
    char **genres;                        //includes up to three genres associated with the title
    TBasic *next;
};


//Constructors for data structures
extern TBasic *newTitleBasics(int balance);


//Reading in files
extern void readTitleBasicsFile();
