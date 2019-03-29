/*
 * Author: Elizabeth Payne
 * File: readFiles.h
 * Description: This is the header file to read in all the data files and
 *							assign the information to the corresponding variable.
 */

#include <stdio.h>
#pragma once
typedef struct title_alternative TAlt;
typedef struct title_basics TBasic;
typedef struct title_execs TExecs;
typedef struct title_episode TEpisode;
typedef struct title_crew  TCrew;
typedef struct title_ratings TRating;
typedef struct name_basics NBasic;


//Constructors for data structures
extern TAlt *newAltTitle();
extern TBasic *newTitleBasics(int height, int balance);
extern TExecs *newTitleExecs();
extern TEpisode *newTitleEpisode();
extern TCrew *newTitleCrew();
extern TRating *newTitleRating();
extern NBasic *newNameBasics();


//Reading in files
extern void readAltTitlesFile();
extern void readTitleBasicsFile();
extern void readTitleExecsFile();
extern void readTitleEpisodeFile();
extern void readTitleCrewFile();
extern void readTitleRatingFile();
extern void readNameBasicsFile();


//contains information for alternative (AKA) titles (all the different languages)
struct title_alternative
{
    char *ID;       // an alphanumeric unique identifier of the title
    int ordering;        // a number to uniquely ID rows for a given titleID
    char *title;         //the localized title
    char *region;        //the region for this version of the title
    char *language;           //the language of the title
    char *type;          // enumerated set of attributes for the alternative title
    char *altAttributes; //an array of alternative attributes (if any)
    int isOriginalTitle; // boolean --> 0: Not original 1: Original
    int size;                         // number of rows in the file
    TAlt *left, *right, *next, *parent;
};

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
    int height;                                    //number of rows in the file
    int balance;
    TBasic *left, *right, *next, *parent;
};

//contains the director and writer information for all the titles in IMDb
struct title_execs
{
    char *ID;            //alphanumeric unique identifier of the title
    char **directors;        //director(s) of the given title
    char **writers;            //writer(s) of the given title
    int size;                        //number of rows in the file
    TExecs *left, *right, *next, *parent;
};

//contains the TV episode information
struct title_episode
{
    char *ID;                  //alphanumeric identifier of the episode
    char *titleID;                    //alphanumeric identifier of the parent title (tv series title ID)
    int seasonNumber;                        //season number of the episodeID
    int episodeNumber;                    //episode number of the episodeID
    int size;                                        //number of rows in the file
    TEpisode *left, *right, *next, *parent;
};

//contains the principal cast/crew for titles
struct title_crew
{
    char *ID;             //alphanumeric unique identifier of the title
    int ordering;                 //a number to uniquely ID rows for a given titleID
    char *nameID;               //alphanumeric unique identifier of the name/person
    char *category;             //category of job the person was had
    char *job;                     //the specific job title the person had
    char *characterName; //the name of the character played (/N if not applicable)
    int size;                         //number of rows in the file
    TCrew  *left, *right, *next, *parent;
};

//contains the IMDb rating and votes information for the titles
struct title_ratings
{
    char *ID;                  //alphanumeric unique identifier of the title
    double avgRating;                    //weighted average of all the user ratings
    int numVotes;                            //number of votes the title has received
    int size;                                    //number of rows in the file
    TRating *left, *right, *next, *parent;
};

//contains the following information for names
struct name_basics
{
    char *ID;                           //alphanumeric unique identifier of the name/person
    char *primaryName;               //name by which the person is most often credited
    char *birthYear;                           //YYYY
    char *deathYear;                           //YYYY (or /N if person is still alive)
    char **primeProfession;        //top-3 professions of the person
    char **knownForTitles;             //array of titleIDs
    int size;                                             //number of rows in the file
    NBasic *left, *right, *next, *parent;
};




