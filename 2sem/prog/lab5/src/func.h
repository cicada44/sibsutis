#pragma once

void delinput(char del);
void input(char* s);
int allinput(char username[], char dir[], char paths[]);
int correctcheck(char* un, char* dir, char* paths);
int correctUnCheck(char* s);
int correctDirCheck(char* s);
int correctPathsCheck(char* s);
void process(char* s, char* dir, char d);
void remove_spaces(char* s);