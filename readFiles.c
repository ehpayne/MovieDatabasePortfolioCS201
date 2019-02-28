/* Author: Elizabeth Payne
 * File: readFiles.c
 * Description: This code reads in all the data files and assigns the
 * information to the corresponding variables
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readFiles.h"

//contains information for alternative (AKA) titles (all the different languages)
struct title_alternative
{
	char *titleID;       // an alphanumeric unique identifier of the title
	int ordering;        // a number to uniquely ID rows for a given titleID
	char *title;         //the localized title
	char *region;        //the region for this version of the title
	char *language;		   //the language of the title
	char *type;          // enumerated set of attributes for the alternative title
	char *altAttributes; //an array of alternative attributes (if any)
	int isOriginalTitle; // boolean --> 0: Not original 1: Original
	int size;						 // number of rows in the file
};

//contains basic information for titles
struct title_basics
{
	char *titleID;			      //unique identifier of the title
	char *titleType;          //the type.format of the title (e.g. movie, short, tv series, etc)
	char *primaryTitle;       //the more popular title
	char *originalTitle;      //original title in the original language
	int isAdult;							//boolean --> 0: non-adult title 1: adult title
	char *startYear;				  //represents the release year of a title (or start year for TV series)
	char *endYear;						//TV series end year (/N for all other title types)
	int runtimeMinutes;				//primary runtime of the title in minutes
	char **genres;						//includes up to three genres associated with the title
	int size;									//number of rows in the file
};

//contains the director and writer information for all the titles in IMDb
struct title_execs
{
	char *titleID;			//alphanumeric unique identifier of the title
	char **directors;		//director(s) of the given title
	char **writers;			//writer(s) of the given title
	int size;						//number of rows in the file
};

//contains the TV episode information
struct title_episode
{
	char *episodeID;			      //alphanumeric identifier of the episode
	char *titleID;			        //alphanumeric identifier of the parent title (tv series title ID)
	int seasonNumber;						//season number of the episodeID
	int episodeNumber;					//episode number of the episodeID
	int size;										//number of rows in the file
};

//contains the principal cast/crew for titles
struct title_crew
{
	char *titleID;			 //alphanumeric unique identifier of the title
	int ordering;				 //a number to uniquely ID rows for a given titleID
	char *nameID;			   //alphanumeric unique identifier of the name/person
	char *category;			 //category of job the person was had
	char *job;					 //the specific job title the person had
	char *characterName; //the name of the character played (/N if not applicable)
	int size;						 //number of rows in the file
};

//contains the IMDb rating and votes information for the titles
struct title_ratings
{
	char *titleID;			      //alphanumeric unique identifier of the title
	double avgRating;					//weighted average of all the user ratings
	int numVotes;							//number of votes the title has received
	int size;									//number of rows in the file
};

//contains the following information for names
struct name_basics
{
	char *nameID;				           //alphanumeric unique identifier of the name/person
	char *primaryName;	           //name by which the person is most often credited
	char *birthYear;						   //YYYY
	char *deathYear;						   //YYYY (or /N if person is still alive)
	char **primeProfession;        //top-3 professions of the person
	char **knownForTitles;		     //array of titleIDs
	int size;											 //number of rows in the file
};

//Constructor for TAlt structure
TAlt * newAltTitle()
{
	TAlt* altTitle = malloc(sizeof(TAlt));

	altTitle->titleID = "";
	altTitle->ordering = 0;
	altTitle->title = "";
	altTitle->region = "";
	altTitle->language = "";
	altTitle->type = "";
	altTitle->isOriginalTitle = 0;
	altTitle->size = 0;

	return altTitle;
}

//Constructor for TBasic structure
TBasic *newTitleBasics()
{
	TBasic *titleBasics = malloc(sizeof(TBasic));

	titleBasics->titleID = "";
	titleBasics->titleType = "";
	titleBasics->primaryTitle = "";
	titleBasics->originalTitle = "";
	titleBasics->isAdult = 0; //non-adult;
	titleBasics->startYear = "YYYY";
	titleBasics->endYear = "YYYY";
	titleBasics->runtimeMinutes = 0;
	titleBasics->genres = NULL;
	titleBasics->size = 0;

	return titleBasics;
}

//Constructor for TExecs structure
TExecs *newTitleExecs()
{
	TExecs *execs = malloc(sizeof(TExecs));

	execs->titleID = "";
	execs->directors = NULL;
	execs->writers = NULL;
	execs->size = 0;

	return execs;
}

//Constructor for TEpisode structure
TEpisode *newTitleEpisode()
{
	TEpisode *episode = malloc(sizeof(TEpisode));

	episode->episodeID = "";
	episode->titleID = "";
	episode->seasonNumber = 0;
	episode->episodeNumber = 0;
	episode->size = 0;

	return episode;
}

//Constructor for TCrew structure
TCrew *newTitleCrew()
{
	TCrew *crew = malloc(sizeof(TCrew));

	crew->titleID = "";
	crew->ordering = 0;
	crew->nameID = "";
	crew->category = "";
	crew->job = "";
	crew->characterName = "";
	crew->size = 0;

	return crew;
}

//Constructor for TRating structure
TRating *newTitleRating()
{
	TRating *rating = malloc(sizeof(TRating));

	rating->titleID = "";
	rating->avgRating = 0.0;
	rating->numVotes = 0;
	rating->size = 0;

	return rating;
}

//Constructor for NBasic structure
NBasic *newNameBasics()
{
	NBasic *nameBasics = malloc(sizeof(NBasic));

	nameBasics->nameID = "";
	nameBasics->primaryName = "";
	nameBasics->birthYear = "YYYY";
	nameBasics->deathYear = "YYYY";
	nameBasics->primeProfession = NULL;
	nameBasics->knownForTitles = NULL;
	nameBasics->size = 0;

	return nameBasics;
}

//reads in the title.akas TSV file and assigns the information to the corresponding
//variable
TAlt* readAltTitlesFile(TAlt *altTitle)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.akas.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{

		//	printf("line:%s\n", line);
		for(int i = 0; i<8; i++)
		{
			char *token = strtok(line, tab);
			if(token == NULL)
			{
				break;
			}
			if(i == 0)
			{
				altTitle->titleID = token;
			}
			if(i == 1)
			{
				altTitle->ordering = atoi(token);
			}
			if(i == 2)
			{
				altTitle->title = token;
			}
			if(i == 3)
			{
				altTitle->region = token;
			}
			if(i == 4)
			{
				altTitle->language = token;
			}
			if(i == 5)
			{
				altTitle->type = token;		
			}
			if(i == 6)
			{	
				altTitle->altAttributes = token;
			}
			if(i == 7)
			{
				altTitle->isOriginalTitle = atoi(token);
			}
		}
		altTitle->size++;

		if(feof(fptr))
		{
			break;
		}

	}

	fclose(fptr);
	return altTitle;
}

TBasic *readTitleBasicsFile(TBasic *titleBasics)
{
	printf("at the beginning of the function\n");
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.basics.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	printf("opened the file\n");
	fgets(line, lineSize, fptr);
	printf("got the first line\n");
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{
		//printf("size: %d\n", titleBasics->size);
		//    printf("line:%s\n", line);
		for(int i = 0; i<9; i++)
		{
		//	printf("i = %d\n", i);
			char *token = strtok(line, tab);
			if(token == NULL)
			{
				break;
			}
			if(i == 0)
			{
				titleBasics->titleID = token;
			}
			if(i == 1)
			{
				titleBasics->titleType = token;
			}
			if(i == 2)
			{
				titleBasics->primaryTitle = token;
			}
			if(i == 3)
			{
				titleBasics->originalTitle = token;
			}
			if(i == 4)
			{
				titleBasics->isAdult = atoi(token);
			}
			if(i == 5)
			{
				titleBasics->startYear = token;
			}
			if(i == 6)
			{
				titleBasics->endYear = token;
			}
			if(i == 7)
			{
				titleBasics->runtimeMinutes = atoi(token);
			}
			if(i == 8)
			{
				/*for(int j = 0; j < 3; j++)
				{
					char* subtoken = strtok(token, ",");
					printf("%s\n", subtoken);
					while(subtoken != NULL)
					{
						titleBasics->genres[i] = subtoken;
					}
				}*/
			}

		}
		titleBasics->size++;

		if(feof(fptr))
		{
			break;
		}

	}

	fclose(fptr);
	return titleBasics;
}

int main()
{
	printf("here 1\n");
	TAlt *alt = newAltTitle();
	printf("here 2\n");
	TBasic *tBasic = newTitleBasics();
	printf("here 3\n");
	alt = readAltTitlesFile(alt);
	printf("here 4\n");
	tBasic = readTitleBasicsFile(tBasic);
	printf("here 5\n");
	printf("%s\n",alt->titleID);


	printf("Size: %d\n", alt->size);
	return 0;
}




