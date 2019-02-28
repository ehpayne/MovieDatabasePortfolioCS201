/*
 * Author: Elizabeth Payne
 * File: readFiles.h
 * Description: This is the header file to read in all the data files and
 *							assign the information to the corresponding variable.
 */

#include <stdio.h>

typedef struct title_alternative TAlt;
typedef struct title_basics TBasic;
typedef struct title_execs TExecs;
typedef struct title_episode TEpisode;
typedef struct title_crew  TCrew;
typedef struct title_ratings TRating;
typedef struct name_basics NBasic;


//Constructors for data structures
extern TAlt *newAltTitle();
extern TBasic *newTitleBasics();
extern TExecs *newTitleExecs();
extern TEpisode *newTitleEpisode();
extern TCrew *newTitleCrew();
extern TRating *newTitleRating();
extern NBasic *newNameBasics();

//Reading in files
extern TAlt *readAltTitlesFile(TAlt *altTitle);
extern TBasic *readTitleBasicsFile(TBasic *titleBasics);
extern TExecs *readTitleExecsFile(TExecs *execs);
extern TEpisode *readTitleEpisodeFile(TEpisode *episode);
extern TCrew *readTitleCrewFile(TCrew *crew);
extern TRating *readTitleRatingFile(TRating *rating);
extern NBasic *readNameBasicsFile(NBasic *nameBasics);

//Storing the data
extern void storeAltTitles(TAlt *altTitle);
extern void storeTitleBasics(TBasic *titleBasics);
extern void storeTitleExecs(TExecs *execs);
extern void storeTitleEpisode(TEpisode *episode);
extern void storeTitleCrew(TCrew *crew);
extern void storeTitleRating(TRating *rating);
extern void storeNameBasics(NBasic *nameBasics);


