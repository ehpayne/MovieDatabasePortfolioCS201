/* Author: Elizabeth Payne
 * File: readFiles.c
 * Description: This code reads in all the data files and assigns the
 * information to the corresponding variables
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "readFiles.h"
#include "storeData.h"

//contains information for alternative (AKA) titles (all the different languages)
struct title_alternative
{
	char *ID;       // an alphanumeric unique identifier of the title
	int ordering;        // a number to uniquely ID rows for a given titleID
	char *title;         //the localized title
	char *region;        //the region for this version of the title
	char *language;		   //the language of the title
	char *type;          // enumerated set of attributes for the alternative title
	char *altAttributes; //an array of alternative attributes (if any)
	int isOriginalTitle; // boolean --> 0: Not original 1: Original
	int size;						 // number of rows in the file
    TAlt *left, *right;
};

//contains basic information for titles
struct title_basics
{
	char *ID;			      //unique identifier of the title
	char *titleType;          //the type.format of the title (e.g. movie, short, tv series, etc)
	char *primaryTitle;       //the more popular title
	char *originalTitle;      //original title in the original language
	int isAdult;							//boolean --> 0: non-adult title 1: adult title
	char *startYear;				  //represents the release year of a title (or start year for TV series)
	char *endYear;						//TV series end year (/N for all other title types)
	int runtimeMinutes;				//primary runtime of the title in minutes
	char **genres;						//includes up to three genres associated with the title
	int size;									//number of rows in the file
    TBasic *left, *right;
};

//contains the director and writer information for all the titles in IMDb
struct title_execs
{
	char *ID;			//alphanumeric unique identifier of the title
	char **directors;		//director(s) of the given title
	char **writers;			//writer(s) of the given title
	int size;						//number of rows in the file
    TExecs *left, *right;
};

//contains the TV episode information
struct title_episode
{
	char *ID;			      //alphanumeric identifier of the episode
	char *titleID;			        //alphanumeric identifier of the parent title (tv series title ID)
	int seasonNumber;						//season number of the episodeID
	int episodeNumber;					//episode number of the episodeID
	int size;										//number of rows in the file
    TEpisode *left, *right;
};

//contains the principal cast/crew for titles
struct title_crew
{
	char *ID;			 //alphanumeric unique identifier of the title
	int ordering;				 //a number to uniquely ID rows for a given titleID
	char *nameID;			   //alphanumeric unique identifier of the name/person
	char *category;			 //category of job the person was had
	char *job;					 //the specific job title the person had
	char *characterName; //the name of the character played (/N if not applicable)
	int size;						 //number of rows in the file
    TCrew  *left, *right;
};

//contains the IMDb rating and votes information for the titles
struct title_ratings
{
	char *ID;			      //alphanumeric unique identifier of the title
	double avgRating;					//weighted average of all the user ratings
	int numVotes;							//number of votes the title has received
	int size;									//number of rows in the file
    TRating *left, *right;
};

//contains the following information for names
struct name_basics
{
	char *ID;				           //alphanumeric unique identifier of the name/person
	char *primaryName;	           //name by which the person is most often credited
	char *birthYear;						   //YYYY
	char *deathYear;						   //YYYY (or /N if person is still alive)
	char **primeProfession;        //top-3 professions of the person
	char **knownForTitles;		     //array of titleIDs
	int size;											 //number of rows in the file
    NBasic *left, *right;
};



//Constructor for TAlt structure
TAlt * newAltTitle()
{
	TAlt* altTitle = malloc(sizeof(TAlt));

	altTitle->ID = "";
	altTitle->ordering = 0;
	altTitle->title = "";
	altTitle->region = "";
	altTitle->language = "";
	altTitle->type = "";
	altTitle->isOriginalTitle = 0;
	altTitle->size = 0;
    altTitle->left = NULL;
    altTitle->right = NULL;
    

	return altTitle;
}

//Constructor for TBasic structure
TBasic *newTitleBasics()
{
	TBasic *titleBasics = malloc(sizeof(TBasic));

	titleBasics->ID = "";
	titleBasics->titleType = "";
	titleBasics->primaryTitle = "";
	titleBasics->originalTitle = "";
	titleBasics->isAdult = 0; //non-adult;
	titleBasics->startYear = "YYYY";
	titleBasics->endYear = "YYYY";
	titleBasics->runtimeMinutes = 0;
	titleBasics->genres = NULL;
	titleBasics->size = 0;
    titleBasics->left = NULL;
    titleBasics->right = NULL;

	return titleBasics;
}

//Constructor for TExecs structure
TExecs *newTitleExecs()
{
	TExecs *execs = malloc(sizeof(TExecs));

	execs->ID = "";
	execs->directors = NULL;
	execs->writers = NULL;
	execs->size = 0;
    execs->left = NULL;
    execs->right = NULL;

	return execs;
}

//Constructor for TEpisode structure
TEpisode *newTitleEpisode()
{
	TEpisode *episode = malloc(sizeof(TEpisode));

	episode->ID = "";
	episode->titleID = "";
	episode->seasonNumber = 0;
	episode->episodeNumber = 0;
	episode->size = 0;
    episode->left = NULL;
    episode->right = NULL;

	return episode;
}

//Constructor for TCrew structure
TCrew *newTitleCrew()
{
	TCrew *crew = malloc(sizeof(TCrew));

	crew->ID = "";
	crew->ordering = 0;
	crew->nameID = "";
	crew->category = "";
	crew->job = "";
	crew->characterName = "";
	crew->size = 0;
    crew->left = NULL;
    crew->right = NULL;

	return crew;
}

//Constructor for TRating structure
TRating *newTitleRating()
{
	TRating *rating = malloc(sizeof(TRating));

	rating->ID = "";
	rating->avgRating = 0.0;
	rating->numVotes = 0;
	rating->size = 0;
    rating->left = NULL;
    rating->right = NULL;

	return rating;
}

//Constructor for NBasic structure
NBasic *newNameBasics()
{
	NBasic *nameBasics = malloc(sizeof(NBasic));

	nameBasics->ID = "";
	nameBasics->primaryName = "";
	nameBasics->birthYear = "YYYY";
	nameBasics->deathYear = "YYYY";
	nameBasics->primeProfession = NULL;
	nameBasics->knownForTitles = NULL;
	nameBasics->size = 0;
    nameBasics->left = NULL;
    nameBasics->right = NULL;

	return nameBasics;
}

//reads in the title.akas TSV file and assigns the information to the corresponding
//variable
TAlt* readAltTitlesFile(TAlt *altTitle)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;
    
   /* TBasic *tBasic = NULL;
    TExecs *execs = NULL;
    TEpisode *episode = NULL;
    TCrew *crew = NULL;
    TRating *rating = NULL;
    NBasic *nBasic = NULL;
    */
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
				altTitle->ID = token;
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
        //basicBSTInsert(altTitle, tBasic, execs, episode, crew, rating, nBasic altTitle->size);
		altTitle->size++;

		if(feof(fptr))
		{
			break;
		}

		storeAltTitles(altTitle);
        

	}

	fclose(fptr);
	return altTitle;
}

TBasic *readTitleBasicsFile(TBasic *titleBasics)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;
    fptr = fopen("title.basics.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{
		//printf("line:%s\n", line);
		for(int i = 0; i<9; i++)
		{
			//printf("i = %d\n", i);
			char *token = strtok(line, tab);
			if(token == NULL)
			{
				break;
			}
			if(i == 0)
			{
				titleBasics->ID = token;
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

		storeTitleBasics(titleBasics);

	}

	fclose(fptr);
	return titleBasics;
}

TExecs *readTitleExecsFile(TExecs *execs)
{

	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.crew.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{

		//    printf("line:%s\n", line);
		for(int i = 0; i<3; i++)
		{

			char *token = strtok(line, tab);
			if(i == 0)
			{
				execs->ID = token;
			}
			if(i == 1)
			{
				//assign directors to execs->directors
			}
			if(i == 2)
			{
				//assign writers to execs->writers
			}
		}
		execs->size++;

		if(feof(fptr))
		{
			break;
		}

		storeTitleExecs(execs);
	}

	fclose(fptr);
	return execs;
}

TEpisode *readTitleEpisodeFile(TEpisode *episode)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.episode.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{

		//    printf("line:%s\n", line);
		for(int i = 0; i<4; i++)
		{

			char *token = strtok(line, tab);
			if(i == 0)
			{
				episode->ID = token;
			}
			if(i == 1)
			{
				episode->titleID = token;
			}
			if(i == 2)
			{
				episode->seasonNumber = atoi(token);
			}
			if(i == 3)
			{
				episode->episodeNumber = atoi(token);
			}
		}
		episode->size++;

		if(feof(fptr))
		{
			break;
		}

		storeTitleEpisode(episode);
	}

	fclose(fptr);
	return episode;
}

TCrew *readTitleCrewFile(TCrew *crew)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.principals.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
	while (fgets(line, lineSize, fptr) != NULL)
	{

		//    printf("line:%s\n", line);
		for(int i = 0; i<6; i++)
		{

			char *token = strtok(line, tab);
			if(i == 0)
			{
				crew->ID = token;
			}
			if(i == 1)
			{
				crew->ordering = atoi(token);
			}
			if(i == 2)
			{
				crew->nameID = token;
			}
			if(i == 3)
			{
				crew->category = token;
			}
			if(i == 4)
			{
				crew->job = token;
			}
			if(i == 5)
			{
				crew->characterName = token;
			}
		}
		crew->size++;

		if(feof(fptr))
		{
			break;
		}

		storeTitleCrew(crew);
	}

	fclose(fptr);
	return crew;
}

TRating *readTitleRatingFile(TRating *rating)
{
    
    char *line = malloc(sizeof(char *));
    char *tab = "\t";
    int lineSize = 1024;
    
    FILE *fptr;
    
    fptr = fopen("title.ratings.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    fgets(line, lineSize, fptr);
    //printf("line:%s\n", line);
    while (fgets(line, lineSize, fptr) != NULL)
    {
        
        //    printf("line:%s\n", line);
        for(int i = 0; i<3; i++)
        {
            
            char *token = strtok(line, tab);
            if(i == 0)
            {
                rating->ID = token;
            }
            if(i == 1)
            {
                rating->avgRating = atof(token);
            }
            if(i == 2)
            {
                rating->numVotes = atoi(token);
            }
        }
        rating->size++;
        
        if(feof(fptr))
        {
            break;
        }
        
        storeTitleRating(rating);
    }
    
    fclose(fptr);
    return rating;
}

NBasic *readNameBasicsFile(NBasic *nameBasics)
{
    char *line = malloc(sizeof(char *));
    char *tab = "\t";
    int lineSize = 1024;
    
    FILE *fptr;
    
    fptr = fopen("title.principals.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    fgets(line, lineSize, fptr);
    //printf("line:%s\n", line);
    while (fgets(line, lineSize, fptr) != NULL)
    {
        
        //    printf("line:%s\n", line);
        for(int i = 0; i<6; i++)
        {
            
            char *token = strtok(line, tab);
            if(i == 0)
            {
                nameBasics->ID = token;
            }
            if(i == 1)
            {
                nameBasics->primaryName = token;
            }
            if(i == 2)
            {
                nameBasics->birthYear = token;
            }
            if(i == 3)
            {
                nameBasics->deathYear = token;
            }
            if(i == 4)
            {
                //assign pramary profession to nameBasics->primeProfession
            }
            if(i == 5)
            {
                //assign known for titles to nameBasics->knownForTitles
            }
        }
        nameBasics->size++;
        
        if(feof(fptr))
        {
            break;
        }
        
        storeNameBasics(nameBasics);
    }
    
    fclose(fptr);
    return nameBasics;
}

void storeAltTitles(TAlt *altTitles)
{

}

void storeTitleBasics(TBasic *titleBasics)
{

}

void storeTitleExecs(TExecs *execs)
{

}

void storeTitleEpisode(TEpisode *episode)
{

}

void storeTitleCrew(TCrew *crew)
{

}

void storeTitleRating(TRating *rating)
{

}

void storeNameBasics(NBasic *nameBasics)
{

}
void initialMenu()
{
    char input;
    do
    {
        printf("Would you like to: \n A. Create a record \n B. Retrieve a record \n "
               "C. Update a record \n D. Delete a record\n" );
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
            printf("Incorrect Input. Try Again\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'e' && input != 'f' && input != 'g');
    
}
void createMenu()
{
    char input;
    do
    {
        printf("What type of record would you like to create?: \n A. Alternative Titles \n"
               " B. Basic Title Info \n C. Directors/Writers \n D. Episode Info \n E. Title Actors/Crew \n F. Rating Info\n"
               " G. Name Info\n");
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
            printf("Incorrect Input. Try Again.\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'e' && input != 'f' && input != 'g');
}
void retrieveMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to access? \n A. Alternative Titles \n B. Basic Title Info \n C. Directors/Writers \n"
               " D. Episode Info \n E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
        scanf("%c",&input);
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            TAlt *alt = newAltTitle();
            alt = readAltTitlesFile(alt);
            printf("Alt Size: %d\n", alt->size);
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
            printf("Incorrect Input. Try Again.\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'e' && input != 'f' && input != 'g');
}

void updateMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to update? \n A. Alternative Titles \n B. Basic Title Info \n C. Directors/Writers \n"
               " D. Episode Info \n E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Try Again.\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'e' && input != 'f' && input != 'g');
}

void deleteMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to delete? \n A. Alternative Titles \n B. Basic Title Info \n C. Directors/Writers \n"
               " D. Episode Info \n E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Try Again.\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd' && input != 'e' && input != 'f' && input != 'g');
}

int main()
{
    initialMenu();
    return 0;
}




