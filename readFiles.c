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
#include <stddef.h>
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
    titleBasics->genres = (char**)malloc(3 * sizeof(char*));
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
	execs->directors = (char**)malloc(40 * sizeof(char*));
	execs->writers = (char**)malloc(65 * sizeof(char*));
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
	nameBasics->primeProfession = (char**)malloc(3 * sizeof(char*));
	nameBasics->knownForTitles = (char**)malloc(4 * sizeof(char*));
	nameBasics->size = 0;
    nameBasics->left = NULL;
    nameBasics->right = NULL;

	return nameBasics;
}

//reads in the title.akas TSV file and assigns the information to the
//corresponding variable
TAlt* readAltTitlesFile(TAlt *altTitle)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;
    
    //open the file
	fptr = fopen("title.akas.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
    //read in the header line
	fgets(line, lineSize, fptr);
    
    //while !EOF get a line and parse the data
	while (fgets(line, lineSize, fptr) != NULL)
	{
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        altTitle->ID = token;
        
        token = strtok(NULL, tab);
        altTitle->ordering = atoi(token);
        
        token = strtok(NULL, tab);
        altTitle->title = token;
        
        token = strtok(NULL, tab);
        altTitle->region = token;
        
        token = strtok(NULL, tab);
        altTitle->language = token;
        
        token = strtok(NULL, tab);
        altTitle->type = token;
        
        token = strtok(NULL, tab);
        altTitle->altAttributes = token;
        
        token = strtok(NULL, tab);
        altTitle->isOriginalTitle = atoi(token);

		altTitle->size++;

		if(feof(fptr))
		{
			break;
		}
	}

	fclose(fptr);
	return altTitle;
}

//reads in the title.basics TSV file and assigns the information to the
//corresponding variable
TBasic *readTitleBasicsFile(TBasic *titleBasics)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

    //open the file
	FILE *fptr;
    fptr = fopen("title.basics.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
    //read in the header line
	fgets(line, lineSize, fptr);
    
    //while !EOF read a line and parse the data
	while (fgets(line, lineSize, fptr) != NULL)
	{
        char *copy = strdup(line);
        char *token = strtok(copy, tab);
        titleBasics->ID = token;
        
        token = strtok(NULL, tab);
        titleBasics->titleType = token;
        
        token = strtok(NULL, tab);
        titleBasics->primaryTitle = token;
        
        token = strtok(NULL, tab);
        titleBasics->originalTitle = token;
        
        token = strtok(NULL, tab);
        titleBasics->isAdult = atoi(token);
        
        token = strtok(NULL, tab);
        titleBasics->startYear = token;
        
        token = strtok(NULL, tab);
        titleBasics->endYear = token;
        
        token = strtok(NULL, tab);
        titleBasics->runtimeMinutes = atoi(token);
        
        token = strtok(NULL, tab);
        copy = strdup(token);
        
        char* subtoken = strtok(copy, ",");
        titleBasics->genres[0] = malloc(strlen(subtoken) + 1);
        strcpy(titleBasics->genres[0], subtoken);

        for(int i = 1; i <=2; i++)
        {
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                break;
            }
            else
            {
                titleBasics->genres[i] = malloc(strlen(subtoken) + 1);
                strcpy(titleBasics->genres[i], subtoken);
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

TExecs *readTitleExecsFile(TExecs *execs)
{
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;
    //open the file
	fptr = fopen("title.crew.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
	fgets(line, lineSize, fptr);
	
	while (fgets(line, lineSize, fptr) != NULL)
	{
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        execs->ID = token;
        
        char *d_token = strtok(NULL, tab);
        char *w_token = strtok(NULL, tab);
        
        copy = strdup(d_token);
        
        //printf("directors token: %s\n", copy);
        char* subtoken = strtok(copy, ",");
        execs->directors[0] = malloc(strlen(subtoken) + 1);
        strcpy(execs->directors[0], subtoken);
        //printf("subtoken 0: %s\n", subtoken);
        
        for(int i = 1; i <=40; i++)
        {
            
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                
                break;
            }
            else
            {
                //printf("subtoken %d: %s\n", i, subtoken);
                execs->directors[i] = malloc(strlen(subtoken) + 1);
                strcpy(execs->directors[i], subtoken);
            }
        }

        copy = strdup(w_token);
        //printf("here 4\n");
        //printf("writers token: %s\n", copy);
        subtoken = strtok(copy, ",");
        execs->writers[0] = malloc(strlen(subtoken) + 1);
        strcpy(execs->writers[0], subtoken);
        //printf("subtoken 0: %s\n", subtoken);
        
        for(int i = 1; i <=65; i++)
        {
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                break;
            }
            else
            {
                //printf("subtoken %d: %s\n", i, subtoken);
                execs->writers[i] = malloc(strlen(subtoken) + 1);
                strcpy(execs->writers[i], subtoken);
            }
        }
		
        //printf("HERE!\n");
		execs->size++;

		if(feof(fptr))
		{
			break;
		}

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
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        episode->ID = token;
        
        token = strtok(copy, tab);
        episode->titleID = token;
        
        token = strtok(copy, tab);
        episode->seasonNumber = atoi(token);
        
        token = strtok(copy, tab);
        episode->episodeNumber = atoi(token);

		episode->size++;

		if(feof(fptr))
		{
			break;
		}
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
	
	while (fgets(line, lineSize, fptr) != NULL)
	{
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        crew->ID = token;
        
        token = strtok(copy, tab);
        crew->ordering = atoi(token);
        
        token = strtok(copy, tab);
        crew->nameID = token;
        
        token = strtok(copy, tab);
        crew->category = token;
        
        token = strtok(copy, tab);
        crew->characterName = token;
        
		crew->size++;

		if(feof(fptr))
		{
			break;
		}
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
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        rating->ID = token;
        
        token = strtok(copy, tab);
        rating->avgRating = atof(token);
        
        token = strtok(copy, tab);
        rating->numVotes = atoi(token);
        
        rating->size++;
        
        if(feof(fptr))
        {
            break;
        }
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
    
    fptr = fopen("name.basics.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    fgets(line, lineSize, fptr);
    
    while (fgets(line, lineSize, fptr) != NULL)
    {
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        nameBasics->ID = token;
        
        token = strtok(copy, tab);
        nameBasics->primaryName = token;
        
        token = strtok(copy, tab);
        nameBasics->birthYear = token;
        
        token = strtok(copy, tab);
        nameBasics->deathYear = token;
        
        char *p_token = strtok(NULL, tab);
        char *k_token = strtok(NULL, tab);
        
        copy = strdup(p_token);
        
        //printf("directors token: %s\n", copy);
        char* subtoken = strtok(copy, ",");
        nameBasics->primeProfession[0] = malloc(strlen(subtoken) + 1);
        strcpy(nameBasics->primeProfession[0], subtoken);
        //printf("subtoken 0: %s\n", subtoken);
        
        for(int i = 1; i <=2; i++)
        {
            
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                
                break;
            }
            else
            {
                //printf("subtoken %d: %s\n", i, subtoken);
                nameBasics->primeProfession[i] = malloc(strlen(subtoken) + 1);
                strcpy(nameBasics->primeProfession[i], subtoken);
            }
        }
        
        copy = strdup(k_token);
        //printf("here 4\n");
        printf("known for titles token: %s\n", copy);
        subtoken = strtok(copy, ",");
        nameBasics->knownForTitles[0] = malloc(strlen(subtoken) + 1);
        strcpy(nameBasics->knownForTitles[0], subtoken);
        printf("subtoken 0: %s\n", subtoken);
        
        for(int i = 1; i <=3; i++)
        {
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                break;
            }
            else
            {
                printf("subtoken %d: %s\n", i, subtoken);
                nameBasics->knownForTitles[i] = malloc(strlen(subtoken) + 1);
                strcpy(nameBasics->knownForTitles[i], subtoken);
            }
        }
        
        nameBasics->size++;
        
        if(feof(fptr))
        {
            break;
        }
    }
    
    fclose(fptr);
    return nameBasics;
}
void welcomeMenu()
{
    char input;
    
    do
    {
        printf("\n\nWELCOME TO THE MOVIE DATABASE! \n\n");
        printf("Please select one of the following choices:\n");
        printf(" A. Create a new user account\n B. Login\n");
        scanf("%c",&input);
        input = tolower(input);
        if(input == 'a')
        {
            newUserMenu();
        }
        else if(input == 'b')
        {
            loginMenu();
        }
        else
        {
            printf("Incorrect Input. Enter a letter A-B. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b');
}

void newUserMenu()
{
    char* username_input = malloc(sizeof(char*));
    printf("\n\nWELCOME!!\n\n");
    printf("Please create a username:\n");
    scanf("%s", username_input);
    username_input = strlwr(username_input);
    
    char* password_input =  malloc(sizeof(char*));
    printf("\n\nNow create a password (case sensitive):\n");
    scanf("%s", password_input);

    newUser(username_input, password_input);
    
    initialMenu();
}

void loginMenu()
{
    int userandPasswordFound = 0;
    do
    {
        char* username_input =  malloc(sizeof(char*));
        printf("\nUSERNAME:\n\n");
        scanf("%s",username_input);
        username_input = strlwr(username_input);
        char *password_input = malloc(sizeof(char*));
        printf("\n\nPASSWORD:\n");
        scanf("%s", password_input);
        
        FILE* fptr = fopen("UserInfo.txt", "r");
        char *line = malloc(sizeof(char *));
        int lineSize = 1024;
        int onlyUsernameIsFound = 0;
        int userandPasswordFound = 0;
        //fgets(line, lineSize, fptr);
        while (fgets(line, lineSize, fptr) != NULL)
        {
            char *copy = strdup(line);
            
            //remove the newline character
            copy[strlen(copy)-1] = 0;
            char *user_token = strtok(copy, " ");
            char *password_token = strtok(NULL, " ");

            if(strcmp(username_input, user_token) == 0 &&
               strcmp(password_input, password_token) == 0)
            {
                userandPasswordFound = 1;
                break;
            }
            if(strcmp(username_input, user_token) == 0 &&
               strcmp(password_input, password_token) != 0)
            {
                onlyUsernameIsFound = 1;
            }
        }
        if(userandPasswordFound == 1)
        {
            printf("USER FOUND!!\n\n");
            initialMenu();
        }
        else if(onlyUsernameIsFound == 1)
        {
            printf("INCORRECT PASSWORD. TRY AGAIN\n\n");
        }
        else
        {
            printf("INCORRECT USERNAME AND PASSWORD. TRY AGAIN\n\n");
        }
    }while(userandPasswordFound != 1);
    
}

void initialMenu()
{
    char input;
    do
    {
        printf("Would you like to: \n A. Create a record \n"
               " B. Retrieve a record \n C. Update a record \n"
               " D. Delete a record\n" );
        scanf("%c",&input);
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
            printf("Incorrect Input. Enter a letter A-D. Try Again\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
    
}
void createMenu()
{
    char input;
    do
    {
        printf("What type of record would you like to create? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}
void retrieveMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to retrieve? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}

void updateMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to update? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n");
            
        }
    }while(input != 'a' && input != 'b' && input != 'c' && input != 'd'
           &&input != 'e' && input != 'f' && input != 'g');
}

void deleteMenu()
{
    char input;
    do
    {
        printf("What type of data would you like to delete? \n"
               " A. Alternative Titles \n B. Basic Title Info \n"
               " C. Directors/Writers \n D. Episode Info \n"
               " E. Title Actors/Crew \n F. Rating Info \n G. Name Info\n");
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
            printf("Incorrect Input. Enter a letter A-G. Try Again.\n");
        }
    }while(input != 'a' && input != 'b' && input != 'c' &&
           input != 'd' && input != 'e' && input != 'f' && input != 'g');
}

char *strlwr(char *str)
{
    int size = strlen(str);
    for(int i = 0; i < size; i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main()
{
    welcomeMenu();
    return 0;
}




