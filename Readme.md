Author: Elizabeth Payne
Project: Movie Catalog

GitHub Repository: https://github.com/ehpayne/MovieDatabasePortfolioCS201.git
Data File Download Link: https://www.imdb.com/interfaces/
Video Tutorial: 

INSTRUCTIONS:
1. Download and decompress the zipped version of the portfolio from Blackboard
2.  In the same directory, download the title.basics.tsv file using the command curl -O https://datasets.imdbws.com/title.basics.tsv.gz
3.  Decompress the title.basics.tsv.gz
4. Run "make" to compile the project
5. Run "make test" to test the project
6. Run "make clean" to remove the executable



OVERVIEW:
This project is a movie database and it allows the user to create, retrieve, update, and delete
movie records to a catalog. The user is allowed multiple catalogs and is even provided with a search 
history. 

Each user gets his or her own log file and the user can access their old catalogs in future runs of the program

RUNTIME NOTE:
After entering a username and password, the user will have to wait for about 15-20 seconds for the file be read in
