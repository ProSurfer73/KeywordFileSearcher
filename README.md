# KeywordFileSearcher
Search easily for a keyword among a folder of text files.

Are you looking for a keyword inside a folder with a very large amount of souce code ?<br />
Windows search does not search accurately, and other search tool takes a lot of time to find something or are too complex to be used.<br />
Download and use KeywordFileSearcher.

4-step instructions :
1) Enter the directory path in which you would like to launch you search.
2) Enter the keyword(s) you are looking for.
3) Specify nothing to skip, or some file(s) extension(s) to keep only the files having th(is/ese) extension(s). For example you can specify ".c" to search only for c source. But you could also specify ".c" and ".h" to search only for C source and header files. 
4) Type "1+" to launch the search.

Here a few screenshots of the program in action :

![The program at launch.](https://github.com/ProSurfer73/KeywordFileSearcher/blob/main/screenshots/screenshot1.PNG)
![Occurence found !.](https://github.com/ProSurfer73/KeywordFileSearcher/blob/main/screenshots/screenshot2.PNG)
![Help menu.](https://github.com/ProSurfer73/KeywordFileSearcher/blob/main/screenshots/screenshot3.PNG)



Other cool features:<br />
A) Match for a keyword case insensitively by adding '#' at the beginning of the keyword. It means that "#keyword' will match the strings 'KEYword', 'KEYWORD' 'keyword', .. inside the files.<br />
B) Look for a keyword while ignoring spaces characters that may appear by adding '@' at the beginning of the keyword. "int main" will match "int     main', 'intmain', ect...

