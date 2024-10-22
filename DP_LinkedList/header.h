#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

#define DP_SUCCESS 0
#define DP_FAILURE -1

struct student{
char name[50];
char roll[10];
struct student *next;
};
struct student *first=NULL,*last=NULL,*k=NULL;