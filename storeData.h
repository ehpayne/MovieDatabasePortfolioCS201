/*
 * Author: Elizabeth Payne
 * File: storeData.h
 * Description: This is the header file to store all the data that was read in in readFiles.c
 */

#include <stdio.h>
#include "readFile.h"

//Storing the data
extern void basicBSTInsert(char *ID);
extern void storeAltTitles(TAlt *altTitle);
extern void storeTitleBasics(TBasic *titleBasics);
extern void storeTitleExecs(TExecs *execs);
extern void storeTitleEpisode(TEpisode *episode);
extern void storeTitleCrew(TCrew *crew);
extern void storeTitleRating(TRating *rating);
extern void storeNameBasics(NBasic *nameBasics);
