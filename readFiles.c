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
    altTitle->next = NULL;
    altTitle->parent = NULL;
    

	return altTitle;
}

//Constructor for TBasic structure
TBasic *newTitleBasics()
{
	TBasic *titleBasics = malloc(sizeof(TBasic));

	titleBasics->ID = (char*)malloc(sizeof(char*));
	titleBasics->titleType = (char*)malloc(sizeof(char*));
	titleBasics->primaryTitle = (char*)malloc(sizeof(char*));
	titleBasics->originalTitle = (char*)malloc(sizeof(char*));
	titleBasics->isAdult = 0; //non-adult;
	titleBasics->startYear = (char*)malloc(sizeof(char*));
	titleBasics->endYear = (char*)malloc(sizeof(char*));
	titleBasics->runtimeMinutes = 0;
    titleBasics->genres = (char**)malloc(3 * sizeof(char*));
    titleBasics->left = NULL;
    titleBasics->right = NULL;
    titleBasics->next = NULL;
    titleBasics->parent = NULL;

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
    execs->next = NULL;
    execs->parent = NULL;

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
    episode->next = NULL;
    episode->parent = NULL;

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
    crew->next = NULL;
    crew->parent = NULL;

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
    rating->next = NULL;
    rating->parent = NULL;

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
    nameBasics->next = NULL;
    nameBasics->parent = NULL;

	return nameBasics;
}

//reads in the title.akas TSV file and assigns the information to the
//corresponding variable
void readAltTitlesFile()
{
    TAlt *altTitle = newAltTitle();
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
        
        TAltDataBST(altTitle, altTitle->size);

		altTitle->size++;

		if(feof(fptr))
		{
			break;
		}
	}

	fclose(fptr);
}

//reads in the title.basics TSV file and assigns the information to the
//corresponding variable
void readTitleBasicsFile()
{
    printf("HERE 1\n");
    //TBasic *titleBasics;
    //TBasic *titleBasics = newTitleBasics(0);
    int size = 0;
	char *line = (char *)malloc(sizeof(char *));
    
	char *tab = "\t";
	int lineSize = 1024;

    //open the file
	FILE *fptr;
    fptr = fopen("title.basics.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
    //read in the header line (not used)
	fgets(line, lineSize, fptr);
    //while !EOF read a line and parse the data
	while (fgets(line, lineSize, fptr) != NULL)
	{
        //printf("line: %s\n", line);
        //titleBasics = newTitleBasics();
        char *copy = malloc(strlen(line)+1);
        copy = strndup(line, strlen(line)+1);
        //printf("strlen(line): %lu\n", strlen(line));
        //printf("strlen(copy): %lu\n", strlen(copy));
        //strcpy(copy, line);
        //printf("copy: %s\n", copy);
        
        TBasic *titleBasics = newTitleBasics();
        
        char *token = strtok(copy, tab);
        //printf("ID: %s\n", token);
        
        strcpy(titleBasics->ID, token);
        //=titleBasics->ID = token;
        
        token = strtok(NULL, tab);
        //printf("Title Type: %s\n", token);
        strcpy(titleBasics->titleType, token);
        //titleBasics->titleType = token;
        
        token = strtok(NULL, tab);
        //printf("Primary Title:%s\n", token);
        strcpy(titleBasics->primaryTitle, token);
        //titleBasics->primaryTitle = token;
        
        token = strtok(NULL, tab);
        //printf("Original Title%s\n", token);
        strcpy(titleBasics->originalTitle, token);
        //titleBasics->originalTitle = token;
        
        token = strtok(NULL, tab);
        //printf("IsAdult: %s\n", token);
        titleBasics->isAdult = atoi(token);
        
        
        token = strtok(NULL, tab);
        //printf("Start Year:%s\n", token);
        strcpy(titleBasics->startYear, token);
        //titleBasics->startYear = token;
        
        token = strtok(NULL, tab);
        //printf("End Year:%s\n", token);
        strcpy(titleBasics->endYear, token);
        //titleBasics->endYear = token;
        
        token = strtok(NULL, tab);
        //printf("Runtime Minutes:%s\n", token);
        titleBasics->runtimeMinutes = atoi(token);
        
        token = strtok(NULL, tab);
        //printf("Genres:%s\n", token);
        copy = strndup(token, strlen(token) +1);
        //parse the genre token by commas (there can be 0-3 genres
        char* subtoken = strtok(copy, ",");
        //printf("\t genre 0:%s\n", subtoken);
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
                //printf("\t genre %d:%s\n",i, subtoken);
                titleBasics->genres[i] = malloc(strlen(subtoken) + 1);
                strcpy(titleBasics->genres[i], subtoken);
            }
        }
        //store the record into a BST
        TBasicDataBST(titleBasics, size);
        
        //increase size
		size++;

		if(feof(fptr))
		{
			break;
		}
        //free(titleBasics);
	}
    //close file
	fclose(fptr);
    //free(line);
}

//reads in the title.crew TSV file and assigns the information to the
//corresponding variable
void readTitleExecsFile()
{
    TExecs *execs = newTitleExecs();
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
    //get the header line (useless data)
	fgets(line, lineSize, fptr);
	
    //while !EOF get a line and parse the data based on tabs
	while (fgets(line, lineSize, fptr) != NULL)
	{
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        execs->ID = token;
        
        char *d_token = strtok(NULL, tab);
        char *w_token = strtok(NULL, tab);
        
        copy = strdup(d_token);
        //parse the director token based on commas
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
        //parse the writers token based on commas
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
        //store the record in a BST
		TExecsDataBST(execs, execs->size);
        //printf("HERE!\n");
        //increase size
		execs->size++;
        
		if(feof(fptr))
		{
			break;
		}
        
	}
    //close the file
	fclose(fptr);
}
//reads in the title.episode TSV file and assigns the information to the
//corresponding variable
void readTitleEpisodeFile()
{
    TEpisode *episode = newTitleEpisode();
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.episode.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
    //get the header line (not used)
	fgets(line, lineSize, fptr);
	//printf("line:%s\n", line);
    
    //while !EOF, get a line and parse the data based on tabs
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

        //store the record in a BST
        //TEpisodeDataBST(episode, episode->size);
        
        //increase the size
		episode->size++;

		if(feof(fptr))
		{
			break;
		}
	}
    //close the file
	fclose(fptr);
}
//reads in the title.principals TSV file and assigns the information to the
//corresponding variable
void readTitleCrewFile()
{
    TCrew *crew = newTitleCrew();
	char *line = malloc(sizeof(char *));
	char *tab = "\t";
	int lineSize = 1024;

	FILE *fptr;

	fptr = fopen("title.principals.tsv", "r");
	if(fptr == NULL)
	{
		perror("Error: ");
	}
    //get the header line (not used)
	fgets(line, lineSize, fptr);
	
    //while !EOF, get a line and parse the data based on the tabs
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
        
        //Store the data in a BST
        //TCrewDataBST(crew, crew->size);
        
        //increase size
		crew->size++;

		if(feof(fptr))
		{
			break;
		}
	}
    //close the file
	fclose(fptr);
}
//reads in the title.ratings TSV file and assigns the information to the
//corresponding variable
void readTitleRatingFile()
{
    TRating *rating = newTitleRating();
    char *line = malloc(sizeof(char *));
    char *tab = "\t";
    int lineSize = 1024;
    
    FILE *fptr;
    
    fptr = fopen("title.ratings.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    //get the header line (not used)
    fgets(line, lineSize, fptr);
    
    //while !EOF, get a line and parse the data based on tabs
    while (fgets(line, lineSize, fptr) != NULL)
    {
        char *copy = strdup(line);
        
        char *token = strtok(copy, tab);
        rating->ID = token;
        
        token = strtok(copy, tab);
        rating->avgRating = atof(token);
        
        token = strtok(copy, tab);
        rating->numVotes = atoi(token);
        
        //store the record in a BST
        //TRatingDataBST(rating, rating->size);
        
        //increase the size
        rating->size++;
        
        if(feof(fptr))
        {
            break;
        }
    }
    //close the file
    fclose(fptr);
}
//reads in the name.basics TSV file and assigns the information to the
//corresponding variable
void readNameBasicsFile()
{
    NBasic *nameBasics = newNameBasics();
    char *line = malloc(sizeof(char *));
    char *tab = "\t";
    int lineSize = 1024;
    
    FILE *fptr;
    
    fptr = fopen("name.basics.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    //get the header line (not used)
    fgets(line, lineSize, fptr);
    
    //while !EOF, get a line and parse the data based on tabs
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
        
        //parse the profession token by commas (there can be 1-3 professions)
        //printf("profession token: %s\n", copy);
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
        
        //parse the "known for titles" token based on commas (there can be 1-4)
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
        //Store the record in a BST
        //NBasicDataBST(nameBasics, nameBasics->size);
        
        //increase size
        nameBasics->size++;
        
        if(feof(fptr))
        {
            break;
        }
    }
    //close file
    fclose(fptr);
}

