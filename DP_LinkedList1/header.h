#ifndef HEADER_H
#define HEADER_H

// Pre-defined headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros for constants
#define DP_SUCCESS 0
#define DP_CREATE_DATABASE 1
#define DP_DISPLAY_STUDENTS 2
#define DP_INSERT_AFTER 3
#define DP_DELETE_STUDENT 4
#define DP_SEARCH_STUDENT 5
#define DP_EXIT_PROGRAM 6
#define DP_FAILURE -1
#define DP_NULL_POINTER_ACCESS -99
#define DP_INVALID_INPUT -98

// Structure declaration
typedef struct S_STUDENT
{
    char m_cName[50];
    char m_cRoll[10];
    struct S_STUDENT* pSNext;
}S_STUDENT;

// Function prototypes
int DP_CreateDatabase(int in_iCount);
int DP_DisplayDatabase();
int DP_InsertAfter();
int DP_DeleteRecord();
int DP_SearchRecord();
int DP_PrintErrorMessage(int in_iErrorCode);

#endif // HEADER_H
