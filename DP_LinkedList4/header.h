#ifndef STUDENT_HEADER_H
#define STUDENT_HEADER_H

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DP_SUCCESS 0
#define DP_CREATE_STUDENTS 1
#define DP_DISPLAY_STUDENTS 2
#define DP_INSERT_AFTER 3
#define DP_INSERT_BEGIN 4
#define DP_INSERT_END 5
#define DP_INSERT_BEFORE 6
#define DP_DELETE_STUDENT 7
#define DP_DELETE_BEGIN 8
#define DP_DELETE_END 9
#define DP_SEARCH_STUDENT 10
#define DP_DISPLAY_SORTED 11
#define DP_EXIT_PROGRAM 12
#define DP_MAX_STRING_LENGTH 21
#define DP_MAX_ROLLNO_LENGTH 13
#define DP_MAX_STUDENTS 60
#define DP_FAILURE -1
#define DP_NULL_POINTER_ACCESS -99
#define DP_INVALID_INPUT -98
#define DP_INVALID_NUMBER_STUDENTS -97
#define DP_MEM_ALLOCATION_FAILED -96
#define DP_INVALID_NAME -95
#define DP_INVALID_ROLLNUMBER -94
#define DP_INVALID_DEPT_NAME -93
#define DP_ROLLNO_NOT_FOUND -92
#define DP_CREATE_STUDENT_FAILED -91

typedef struct S_STUDENT
{
    char arr_cName[DP_MAX_STRING_LENGTH];
    char arr_cRollNumber[DP_MAX_ROLLNO_LENGTH];
    char arr_cDepartmentName[DP_MAX_STRING_LENGTH];
    struct S_STUDENT *pSNext;
} S_STUDENT;

/*First and Last Student in Linked List*/
S_STUDENT *pSFirstStudent = NULL;
S_STUDENT *pSLastStudent = NULL;

int DP_CreateStudents(int in_iNumberOfStudents);
int DP_DisplayStudents();
int DP_InsertAfterRollNo();
int DP_InsertBeforeRollNo();
int DP_InsertBeginning();
int DP_InsertAtEnd();
int DP_DeleteStudent();
int DP_DeleteStudentBegin();
int DP_DeleteStudentEnd();
int DP_SearchStudent();
int DP_DisplaySorted();
int DP_PrintErrorMessage(int in_iErrorCode);
int DP_IsValidString(const char *in_pkcString);
int DP_IsValidRollNumber(const char *in_pkcRoll);
int DP_GetValidName(char *out_pcName);
int DP_GetValidRollNo(char *out_pcRollNumber);
int DP_GetValidDepartment(char *out_pcDepartment);
int DP_CreateStudent(S_STUDENT **out_pSStudent);
int DP_FreeStudents();

#endif
