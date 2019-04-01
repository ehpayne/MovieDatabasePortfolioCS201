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
#include "hash.h"


//Constructor for TBasic structure
TBasic *newTitleBasics(int balance)
{
    TBasic *titleBasics = malloc(sizeof(TBasic));
    titleBasics->ID = NULL;
    titleBasics->titleType = NULL;
    titleBasics->primaryTitle = NULL;
    titleBasics->originalTitle = NULL;
    titleBasics->isAdult = 0; //non-adult;
    titleBasics->startYear = NULL;
    titleBasics->endYear = NULL;
    titleBasics->runtimeMinutes = 0;
    titleBasics->genres = malloc(3 * sizeof(char*));
    //titleBasics->balance = balance;
    //titleBasics->left = NULL;
    //titleBasics->right = NULL;
    titleBasics->next = NULL;
    //titleBasics->parent = NULL;
    return titleBasics;
}


//reads in the title.basics TSV file and assigns the information to the
//corresponding variable
void readTitleBasicsFile()
{
    TBasic *titleBasics;
    //printf("^^^^^^^^^^^^^^^^READ FILE^^^^^^^^^^^^^^^^^\n");
    int size = 0;
    int balance = 0;
    int lineSize = 3000;
    char *line = malloc(lineSize * sizeof(char));
    
    char *tab = "\t";
    
    
    //open the file
    FILE *fptr = fopen("title.basics.tsv", "r");
    if(fptr == NULL)
    {
        perror("Error: ");
    }
    //read in the header line (not used)
    fgets(line, lineSize, fptr);
    //printf("HERE 3\n");
    //while !EOF read a line and parse the data
    while (fgets(line, lineSize, fptr) != NULL)
    {
        //printf("^^^^^^^^^^^^^^^^READ FILE^^^^^^^^^^^^^^^^^\n");
        //printf("HERE 4\n");
        //printf("line: %s\n", line);
        //printf("HERE 5\n");
        char *copy = strndup(line, strlen(line)+1);
        //printf("HERE 6\n");
        titleBasics = newTitleBasics(balance);
        //printf("HERE 7\n");
        
        //ID
        char *token = strtok(copy, tab);
        //printf("ID: %s\n", token);
        titleBasics->ID = strndup(token, strlen(token)+1);
        //printf("HERE 8\n");
        
        //Title Type
        token = strtok(NULL, tab);
        //printf("TOKEN: %s\n", token);
        if(strcmp(token, "tvEpisode") == 0)
        {
            //printf("SKIPPED EPISODE\n");
            continue;
        }
        //printf("Title Type: %s\n", token);
        titleBasics->titleType = strndup(token, strlen(token)+1);
        
        //Primary Title
        token = strtok(NULL, tab);
        //printf("Primary Title: %s\n", token);
        titleBasics->primaryTitle = strndup(token, strlen(token)+1);
        
        //Original Title
        token = strtok(NULL, tab);
        //printf("Original Title: %s\n", token);
        titleBasics->originalTitle = strndup(token, strlen(token)+1);
        
        //Is Adult
        token = strtok(NULL, tab);
        //printf("IsAdult: %s\n", token);
        titleBasics->isAdult = atoi(token);
        
        //Start Year
        token = strtok(NULL, tab);
        //printf("Start Year:%s\n", token);
        titleBasics->startYear = strndup(token, strlen(token)+1);
        
        //End Year
        token = strtok(NULL, tab);
        //printf("End Year:%s\n", token);
        titleBasics->endYear = strndup(token, strlen(token)+1);
        
        //Runtime Minutes
        token = strtok(NULL, tab);
        //printf("Runtime Minutes:%s\n", token);
        titleBasics->runtimeMinutes = atoi(token);
        
        token = strtok(NULL, tab);
        //printf("Genres:%s\n", token);
        //remove the newline character at the end of the line
        token[strlen(token)-1] = '\0';
        copy = strndup(token, strlen(token) +1);
        
        //parse the genre token by commas (there can be 0-3 genres
        char* subtoken = strtok(copy, ",");
        
        //printf("\t genre 0:%s\n", subtoken);
        titleBasics->genres[0] = strndup(subtoken, (strlen(subtoken) + 1));
        //printf("STRCPY: strlen(subtoken): %lu, strlen(genre[0]): %lu\n",
        //strlen(subtoken),strlen(titleBasics->genres[0]));
        for(int i = 1; i <=2; i++)
        {
            subtoken = strtok(NULL, ",");
            if(subtoken == NULL)
            {
                //printf ("   genre loop terminated.");
                break;
            }
            else
            {
                //printf("\t genre %d:%s\n",i, subtoken);
                
                titleBasics->genres[i] = strndup(subtoken, (strlen(subtoken) + 1));
                //printf("STRCPY: strlen(subtoken): %lu, strlen(genre[%d]): %lu\n", strlen(subtoken), i, strlen(titleBasics->genres[i]));
            }
        }
        
        
        //printf("Storing\n");
        //store the record into a BST
        
        TBasic_hashTableINSERT(size, titleBasics);
        //TBasicDataBST(titleBasics, size);
        
        //printf("Successful Store\n");
        //increase size
        size++;
        
        if(feof(fptr))
        {
            break;
        }
    }
    //printf("SIZE: %d\n", size);
    //close file
    fclose(fptr);
    free(line);
}
