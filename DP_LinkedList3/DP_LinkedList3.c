#include "header.h"

int main()
{
    int iUserChoice = 0, iReturnValue = 0, iNumberOfStudents = 0;
    int iPosition = 0;

    while (iUserChoice != DP_EXIT_PROGRAM)
    {
        printf("\r\nLinkedList for Student Details:\r\n");
        printf("\r\n1. Create students\r\n");
        printf("\r\n2. Display students\r\n");
        printf("\r\n3. Insert student after rollNumber\r\n");
        printf("\r\n4. Insert student in the beginning\r\n");
        printf("\r\n5. Insert student at the end\r\n");
        printf("\r\n6. Insert student before rollNumber\r\n");
        printf("\r\n7. Insert student at position\r\n");
        printf("\r\n8. Delete student\r\n");
        printf("\r\n9. Delete student at beginning\r\n");
        printf("\r\n10. Delete student at end\r\n");
        printf("\r\n11. Search student\r\n");
        printf("\r\n12. Display Student in Sorted Order.\r\n");
        printf("\r\n13. Exit Program\r\n");

        do
        {
            /*Prompt user to enter choice*/
            fflush(stdin);
            printf("\r\nEnter your choice(1 - 9):\r\n");
            iReturnValue = scanf(" %d", &iUserChoice);

            /*Input validation for user choice*/

            /*Handle Input Other than Integer*/
            if (iReturnValue != 1)
            {
                printf("\r\nInvalid choice!Enter a Valid Choice(1-9).\r\n");

                /*Get the newline character*/
                while (getchar() != '\n')
                    ;
            }
            else
            {
                /*Check if the user choice is between choice range*/
                if ((iUserChoice < DP_CREATE_STUDENTS) || (iUserChoice > DP_EXIT_PROGRAM))
                {
                    printf("\r\nInvalid choice!Enter a Valid Choice(1-9).\r\n");
                }
            }

        } while ((iReturnValue != 1) || (iUserChoice < DP_CREATE_STUDENTS) || (iUserChoice > DP_EXIT_PROGRAM));

        switch (iUserChoice)
        {

        case DP_CREATE_STUDENTS:

            printf("\r\nYour Choice is %d: Create Students\r\n", iUserChoice);
            do
            {
                fflush(stdin);
                /*Prompt user to enter number of students*/
                printf("\r\nEnter the number of students:\r\n");
                iReturnValue = scanf(" %d", &iNumberOfStudents);

                /*Input validation for number of students*/
                if (iReturnValue != 1)
                {
                    printf("\r\nInvalid Number of Students!Enter a Valid Number of Students(1 - %d)\r\n", DP_MAX_STUDENTS);
                    while (getchar() != '\n')
                        ;
                }
                else
                {
                    /*Check if the NumberOfStudents lies between valid range*/
                    if ((iNumberOfStudents < 1) || (iNumberOfStudents > DP_MAX_STUDENTS))
                    {
                        printf("\r\nInvalid Number of Students! Enter a Valid Number of Students(1 - %d)\r\n", DP_MAX_STUDENTS);
                    }
                    while (getchar() != '\n')
                        ;
                }

            } while ((iReturnValue != 1) || (iNumberOfStudents < 1) || (iNumberOfStudents > DP_MAX_STUDENTS));

            iReturnValue = DP_CreateStudents(iNumberOfStudents);

            break;

        case DP_DISPLAY_STUDENTS:

            printf("\r\nYour Choice is %d: Display students\r\n", iUserChoice);
            iReturnValue = DP_DisplayStudents();

            break;

        case DP_INSERT_AFTER:

            printf("\r\nYour Choice is %d: Insert student after rollNumber\r\n", iUserChoice);
            iReturnValue = DP_InsertAfterRollNo();

            break;

        case DP_INSERT_BEGIN:

            printf("\r\nYour Choice is %d: Insert student at the beginning of Linked List\r\n", iUserChoice);
            iReturnValue = DP_InsertBeginning();

            break;

        case DP_INSERT_END:

            printf("\r\nYour Choice is %d: Insert student at the end of Linked List\r\n", iUserChoice);
            iReturnValue = DP_InsertAtEnd();

            break;

        case DP_INSERT_BEFORE:

            printf("\r\nYour Choice is %d: Insert student before rollNumber\r\n", iUserChoice);
            iReturnValue = DP_InsertBeforeRollNo();

            break;

        case DP_INSERT_AT_POSITION:

            printf("\r\nYour Choice is %d: Insert student at position\r\n", iUserChoice);

            while (1)
            {
                fflush(stdin);

                printf("\r\nEnter the position to insert: \r\n");
                iReturnValue = scanf(" %d", &iPosition);

                fflush(stdin);

                if (iReturnValue != 1)
                {
                    printf("\r\nInvalid Position! Enter a Valid Position\r\n");
                }
                else
                {
                    if (iPosition < 0)
                    {
                        printf("\r\nInvalid Position! Enter a Valid Position\r\n");
                    }
                    else
                    {
                        break;
                    }
                }
            }

            iReturnValue = DP_InsertStudentAtPosition(iPosition);

        case DP_DELETE_STUDENT:

            printf("\r\nYour Choice is %d: Delete student\r\n", iUserChoice);
            iReturnValue = DP_DeleteStudent();

            break;

        case DP_DELETE_BEGIN:

            printf("\r\nYour Choice is %d: Delete student at beginning\r\n", iUserChoice);
            iReturnValue = DP_DeleteStudentBegin();

            break;

        case DP_DELETE_END:

            printf("\r\nYour Choice is %d: Delete student at end\r\n", iUserChoice);
            iReturnValue = DP_DeleteStudentEnd();

            break;

        case DP_SEARCH_STUDENT:

            printf("\r\nYour Choice is %d: Search student\r\n", iUserChoice);
            iReturnValue = DP_SearchStudent();

            break;

        case DP_DISPLAY_SORTED:

            printf("\r\nYour Choice is %d: Display Student in Sorted Order\r\n", iUserChoice);
            iReturnValue = DP_DisplaySorted();

            break;

        case DP_EXIT_PROGRAM:

            printf("\r\nYour Choice is %d: Exit Program\r\n", iUserChoice);
            printf("\nExiting Program.......\n");
            getch();

            iReturnValue = DP_FreeStudents();
            break;

        default:

            printf("\nInvalid choice!\n");
            iReturnValue = DP_INVALID_INPUT;
        }

        if (iReturnValue != DP_SUCCESS)
        {
            iReturnValue = DP_PrintErrorMessage(iReturnValue);
            if (iReturnValue != DP_SUCCESS)
            {
                printf("\r\nError Printing Error Message.\r\n");
                return DP_FAILURE;
            }
        }
    }

    return DP_SUCCESS;
}

/*!
* / Function Name: DP_CreateStudents(int in_iNumberOfStudents)
* / Author       : 3232
* / Date         : 24/10/24
* / Brief        : Function to Create Database of student records for input number of students
* / param[in]    : in_iNumberOfStudents -  Number of students
* / Return       : DP_INVALID_NUMBER_STUDENTS, DP_MEM_ALLOCATION_FAILED, DP_INVALID_NAME,
DP_INVALID_ROLLNUMBER, DP_INVALID_DEPT_NAME, DP_CREATE_STUDENT_FAILED
*/

int DP_CreateStudents(int in_iNumberOfStudents)
{
    S_STUDENT *pSTempStudent = NULL;
    S_STUDENT *pSNewStudent = NULL;

    int iIterator = 0, iReturnValue = 0;

    if ((in_iNumberOfStudents < 1) || (in_iNumberOfStudents > DP_MAX_STUDENTS))
    {
        printf("\r\nInvalid Number of Students!Enter a Valid Number of Students(1 - %d)\r\n", DP_MAX_STUDENTS);
        getch();
        return DP_INVALID_NUMBER_STUDENTS;
    }

    iReturnValue = DP_CreateStudent(&pSFirstStudent);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_CREATE_STUDENT_FAILED;
    }

    pSFirstStudent->pSNext = NULL;
    /*Set First and Last to First Student*/
    pSLastStudent = pSFirstStudent;

    /*Input Data for Each Student*/
    for (iIterator = 1; iIterator < in_iNumberOfStudents; iIterator++)
    {
        iReturnValue = DP_CreateStudent(&pSNewStudent);
        if (iReturnValue < DP_SUCCESS)
        {
            return DP_CREATE_STUDENT_FAILED;
        }

        pSNewStudent->pSNext = NULL;
        /*Link the New Student*/
        pSLastStudent->pSNext = pSNewStudent;
        /*Update Last Pointer*/
        pSLastStudent = pSNewStudent;
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_DisplayStudents()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Display the student database
 * / Return       : DP_SUCCESS, DP_NULL_POINTER_ACCESS
 */

int DP_DisplayStudents()
{
    S_STUDENT *pSTempStudent = NULL;
    int iIterator = 0;

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    pSTempStudent = pSFirstStudent;

    while (pSTempStudent != NULL)
    {
        printf("\nRoll number: %-10s\n", pSTempStudent->arr_cRollNumber);
        printf("Name: %-10s\n", pSTempStudent->arr_cName);
        printf("\rDepartment: %-10s\n", pSTempStudent->arr_cDepartmentName);

        /*Move to Next Student*/
        pSTempStudent = pSTempStudent->pSNext;
        iIterator = iIterator + 1;
    }

    printf("\r\nNo of Students in the Linked List: %d\r\n", iIterator);

    return DP_SUCCESS;
}

/*!
* / Function Name: DP_InsertAfterRollNo()
* / Author       : 3232
* / Date         : 24/10/24
* / Brief        : Function to Insert a student record after a specific roll number
* / Return       : DP_MEM_ALLOCATION_FAILED, DP_INVALID_NAME, DP_INVALID_ROLLNUMBER,
DP_INVALID_DEPT_NAME, DP_SUCCESS, DP_ROLLNO_NOT_FOUND, DP_CREATE_STUDENT_FAILED
*/

int DP_InsertAfterRollNo()
{
    S_STUDENT *pSTempStudent = NULL;
    S_STUDENT *pSNewStudent = NULL;
    int iReturnValue = 0;

    char arr_cRollNumber[DP_MAX_STRING_LENGTH] = {0};

    iReturnValue = DP_GetValidRollNo(arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_INVALID_ROLLNUMBER;
    }

    pSTempStudent = pSFirstStudent;

    while (pSTempStudent != NULL)
    {
        /*Check if the roll number matches*/
        if (strcmp(arr_cRollNumber, pSTempStudent->arr_cRollNumber) == 0)
        {
            iReturnValue = DP_CreateStudent(&pSNewStudent);
            if (iReturnValue < DP_SUCCESS)
            {
                return DP_CREATE_STUDENT_FAILED;
            }

            /*Link the New Student After the Matched Student*/
            pSNewStudent->pSNext = pSTempStudent->pSNext;
            pSTempStudent->pSNext = pSNewStudent;

            return DP_SUCCESS;
        }

        /*Move to the Next Student*/
        pSTempStudent = pSTempStudent->pSNext;
    }

    return DP_ROLLNO_NOT_FOUND;
}

/*!
* / Function Name: DP_InsertBeforeRollNo()
* / Author       : 3232
* / Date         : 24/10/24
* / Brief        : Function to Insert a student record before a specific roll number
* / Return       : DP_MEM_ALLOCATION_FAILED, DP_INVALID_NAME, DP_INVALID_ROLLNUMBER,
DP_INVALID_DEPT_NAME, DP_SUCCESS, DP_ROLLNO_NOT_FOUND
*/

int DP_InsertBeforeRollNo()
{
    S_STUDENT *pSTempStudent = NULL;
    S_STUDENT *pSNewStudent = NULL;
    S_STUDENT *pSPrev = NULL;
    int iReturnValue = 0;

    char arr_cRollNumber[DP_MAX_STRING_LENGTH] = {0};

    iReturnValue = DP_GetValidRollNo(arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_INVALID_ROLLNUMBER;
    }

    if (pSFirstStudent == NULL)
    {
        return DP_ROLLNO_NOT_FOUND;
    }

    pSTempStudent = pSFirstStudent;

    /*Check if we need to insert in the beggining of the list*/
    if (strcmp(arr_cRollNumber, pSFirstStudent->arr_cRollNumber) == 0)
    {
        iReturnValue = DP_CreateStudent(&pSNewStudent);
        if (iReturnValue < DP_SUCCESS)
        {
            return DP_CREATE_STUDENT_FAILED;
        }

        /*Insert At Beginning*/
        pSNewStudent->pSNext = pSFirstStudent;

        pSFirstStudent = pSNewStudent;

        return DP_SUCCESS;
    }

    while (pSTempStudent != NULL)
    {
        if (strcmp(arr_cRollNumber, pSTempStudent->arr_cRollNumber) == 0)
        {
            iReturnValue = DP_CreateStudent(&pSNewStudent);
            if (iReturnValue < DP_SUCCESS)
            {
                return DP_CREATE_STUDENT_FAILED;
            }

            /*Link the new student before the matched student*/
            if (pSPrev != NULL)
            {
                pSPrev->pSNext = pSNewStudent;
            }

            pSNewStudent->pSNext = pSTempStudent;

            return DP_SUCCESS;
        }

        /*Move to the next student*/
        pSPrev = pSTempStudent;
        pSTempStudent = pSTempStudent->pSNext;
    }

    return DP_ROLLNO_NOT_FOUND;
}

/*!
* / Function Name: DP_InsertBeginning()
* / Author       : 3232
* / Date         : 24/10/24
* / Brief        : Function to Insert a student record at the beginning of the linked list
* / Return       : DP_MEM_ALLOCATION_FAILED, DP_INVALID_NAME, DP_INVALID_ROLLNUMBER,
DP_INVALID_DEPT_NAME, DP_SUCCESS
*/

int DP_InsertBeginning()
{
    /*Create a New Student*/
    S_STUDENT *pSNewStudent = NULL;
    int iReturnValue = 0;

    iReturnValue = DP_CreateStudent(&pSNewStudent);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_CREATE_STUDENT_FAILED;
    }

    /*Link the New Student with First Student*/
    pSNewStudent->pSNext = pSFirstStudent;

    /*Update the New Student as First Student*/
    pSFirstStudent = pSNewStudent;

    return DP_SUCCESS;
}

/*!
* / Function Name: DP_InsertAtEnd()
* / Author       : 3232
* / Date         : 24/10/24
* / Brief        : Function to Insert a student at the end of the linked list
* / Return       : DP_MEM_ALLOCATION_FAILED, DP_INVALID_NAME, DP_INVALID_ROLLNUMBER,
DP_INVALID_DEPT_NAME, DP_SUCCESS
*/

int DP_InsertAtEnd()
{
    S_STUDENT *pSNewStudent = NULL;
    S_STUDENT *pSTempStudent = NULL;
    int iReturnValue = 0;

    iReturnValue = DP_CreateStudent(&pSNewStudent);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_CREATE_STUDENT_FAILED;
    }

    /*Set new student next to NULL*/
    pSNewStudent->pSNext = NULL;

    /*Check if First Student is NULL*/
    if (pSFirstStudent == NULL)
    {
        /*No Element Present in the Linked List Set the First Student as New Student*/
        pSFirstStudent = pSNewStudent;
    }
    else
    {
        /*Set the temp student as first student*/
        pSTempStudent = pSFirstStudent;

        /*Traverse Linked List until pSTempStudent->pSNext not NULL*/
        while (pSTempStudent->pSNext != NULL)
        {
            pSTempStudent = pSTempStudent->pSNext;
        }

        pSTempStudent->pSNext = pSNewStudent;
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_InsertStudentAtPosition(int in_iPosition)
 * / Author       : 3232
 * / Date         : 25/10/24
 * / Brief        : Function to insert a student at a specific position in the linked list
 * / Return       : DP_SUCCESS, DP_NULL_POINTER_ACCESS, DP_MEM_ALLOCATION_FAILED, DP_INVALID_POSITION
 */

int DP_InsertStudentAtPosition(int in_iPosition)
{
    S_STUDENT *pSNewStudent = NULL;
    S_STUDENT *pSCurrent = NULL;
    S_STUDENT *pSPrev = NULL;
    int iCount = 1, iReturnValue = 0; // Position starts from 1 (i.e., first element has position 1)

    // Create the new student node
    iReturnValue = DP_CreateStudent(&pSNewStudent);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_CREATE_STUDENT_FAILED;
    }

    // Check if position is valid (position > 0)
    if (in_iPosition < 0)
    {
        return DP_INVALID_POSITION;
    }

    // If inserting at the head (position 1)
    if (in_iPosition == 1)
    {
        pSNewStudent->pSNext = pSFirstStudent;
        pSFirstStudent = pSNewStudent;
        return DP_SUCCESS;
    }

    // Traverse to find the position
    pSCurrent = pSFirstStudent;
    while ((pSCurrent != NULL) && (iCount < in_iPosition))
    {
        pSPrev = pSCurrent;
        pSCurrent = pSCurrent->pSNext;
        iCount++;
    }

    // If the position is beyond the last node
    if (iCount != in_iPosition)
    {
        return DP_INVALID_POSITION;
    }

    // Insert the new node at the found position
    pSPrev->pSNext = pSNewStudent;
    pSNewStudent->pSNext = pSCurrent;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_DeleteStudent()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to delete a student record by roll number
 * / Return       : DP_NULL_POINTER_ACCESS, DP_SUCCESS, DP_ROLLNO_NOT_FOUND
 */

int DP_DeleteStudent()
{
    S_STUDENT *pSPrev = NULL;
    S_STUDENT *pSTempStudent = NULL;
    int iReturnValue = 0;

    char arr_cRollNumber[DP_MAX_STRING_LENGTH] = {0};

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    iReturnValue = DP_GetValidRollNo(arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_INVALID_ROLLNUMBER;
    }

    pSTempStudent = pSFirstStudent;

    /*If the First Student Roll Number Matches*/
    if (strcmp(arr_cRollNumber, pSFirstStudent->arr_cRollNumber) == 0)
    {
        /*Update head of linked list*/
        pSFirstStudent = pSFirstStudent->pSNext;

        /*free memory of deleted student*/
        free(pSTempStudent);
        pSTempStudent = NULL;
        return DP_SUCCESS;
    }

    /*Traverse the List to find the roll number*/
    while ((pSTempStudent != NULL) && (strcmp(arr_cRollNumber, pSTempStudent->arr_cRollNumber) != 0))
    {
        pSPrev = pSTempStudent;
        pSTempStudent = pSTempStudent->pSNext;
    }

    /*Return if Roll number not found in the linkedlist*/
    if (pSTempStudent == NULL)
    {
        return DP_ROLLNO_NOT_FOUND;
    }

    /*Link the previous student to next*/
    pSPrev->pSNext = pSTempStudent->pSNext;
    /*free memory of the deleted student*/
    free(pSTempStudent);
    pSTempStudent = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_DeleteStudentEnd()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to delete a student in the end of linkedlist
 * / Return       : DP_NULL_POINTER_ACCESS, DP_SUCCESS, DP_ROLLNO_NOT_FOUND
 */

int DP_DeleteStudentEnd()
{
    /*TempStudent for storing deleted student at the end*/
    S_STUDENT *pSTempStudent = NULL;
    S_STUDENT *pSPrev = NULL;

    /*List is Empty*/
    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    /*Assign Temp to First Student*/
    pSTempStudent = pSFirstStudent;

    if (pSTempStudent->pSNext == NULL)
    {
        /*Only one student is present in linked list*/
        free(pSTempStudent);
        pSTempStudent = NULL;
        pSFirstStudent = NULL;

        return DP_SUCCESS;
    }

    while (pSTempStudent->pSNext != NULL)
    {
        pSPrev = pSTempStudent;
        pSTempStudent = pSTempStudent->pSNext;
    }

    /*Unlink the Last Student*/

    pSPrev->pSNext = NULL;

    /*free memory of the deleted student*/
    free(pSTempStudent);
    pSTempStudent = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_DeleteStudentBegin()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to delete a student at the beginning of the linked list
 * / Return       : DP_NULL_POINTER_ACCESS, DP_SUCCESS, DP_ROLLNO_NOT_FOUND
 */

int DP_DeleteStudentBegin()
{
    /*TempStudent for storing deleted student at the beginning*/
    S_STUDENT *pSTempStudent = NULL;

    /*List is Empty*/
    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    /*Store the student in the beginning in temp student*/
    pSTempStudent = pSFirstStudent;

    /*Update the first student to first student of next*/
    pSFirstStudent = pSFirstStudent->pSNext;
    /*free memory of the deleted student*/
    free(pSTempStudent);
    pSTempStudent = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_SearchStudent()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Search for a student record by roll number
 * / Return       : DP_SUCCESS, DP_ROLLNO_NOT_FOUND, DP_NULL_POINTER_ACCESS
 */

int DP_SearchStudent()
{
    S_STUDENT *pSTempStudent = NULL;
    int iReturnValue = 0;

    char arr_cRollNumber[DP_MAX_ROLLNO_LENGTH] = {0};

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    iReturnValue = DP_GetValidRollNo(arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        return DP_INVALID_ROLLNUMBER;
    }

    pSTempStudent = pSFirstStudent;

    while (pSTempStudent != NULL)
    {
        /*If roll number matches display the student data*/
        if (strcmp(arr_cRollNumber, pSTempStudent->arr_cRollNumber) == 0)
        {
            printf("\r\nStudent found       : %s\r\n", pSTempStudent->arr_cName);
            printf("\r\nStudent Roll Number : %s\r\n", pSTempStudent->arr_cRollNumber);
            printf("\r\nStudent Department  : %s\r\n", pSTempStudent->arr_cDepartmentName);
            return DP_SUCCESS;
        }

        /*Move to the next student*/
        pSTempStudent = pSTempStudent->pSNext;
    }

    /*Return if roll number not found in the linkedlist*/
    return DP_ROLLNO_NOT_FOUND;
}

/*!
 * / Function Name: DP_DisplaySorted()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Display the students in sorted order
 * / Return       : DP_SUCCESS, DP_NULL_POINTER_ACCESS
 */

int DP_DisplaySorted()
{
    S_STUDENT *pSInner = NULL;
    S_STUDENT *pSOuter = NULL;

    char arr_cTempName[DP_MAX_STRING_LENGTH] = {0};
    char arr_cTempRollNumber[DP_MAX_ROLLNO_LENGTH] = {0};
    char arr_cTempDepartmentName[DP_MAX_STRING_LENGTH] = {0};
    int iIterator = 0;

    /*No students present in the linked list*/
    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    /*Bubble Sort for sorting students according to roll number*/
    for (pSOuter = pSFirstStudent; pSOuter != NULL; pSOuter = pSOuter->pSNext)
    {
        for (pSInner = pSOuter->pSNext; pSInner != NULL; pSInner = pSInner->pSNext)
        {
            // if(strcmp(pSOuter->arr_cRollNumber, pSInner->arr_cRollNumber) > 0)

            if (atoi(pSOuter->arr_cRollNumber) > atoi(pSInner->arr_cRollNumber))
            {
                /*Swap student name*/
                strcpy(arr_cTempName, pSOuter->arr_cName);
                strcpy(pSOuter->arr_cName, pSInner->arr_cName);
                strcpy(pSInner->arr_cName, arr_cTempName);

                /*Swap roll number*/
                strcpy(arr_cTempRollNumber, pSOuter->arr_cRollNumber);
                strcpy(pSOuter->arr_cRollNumber, pSInner->arr_cRollNumber);
                strcpy(pSInner->arr_cRollNumber, arr_cTempRollNumber);

                /*Swap department name*/
                strcpy(arr_cTempDepartmentName, pSOuter->arr_cDepartmentName);
                strcpy(pSOuter->arr_cDepartmentName, pSInner->arr_cDepartmentName);
                strcpy(pSInner->arr_cDepartmentName, arr_cTempDepartmentName);
            }
        }
    }

    pSOuter = pSFirstStudent;

    while (pSOuter != NULL)
    {
        printf("\nRoll number: %-10s\n", pSOuter->arr_cRollNumber);
        printf("Name: %-10s\n", pSOuter->arr_cName);
        printf("\rDepartment: %-10s\n", pSOuter->arr_cDepartmentName);

        /*Move to Next Student*/
        pSOuter = pSOuter->pSNext;
        iIterator = iIterator + 1;
    }

    printf("\r\nNo of Students in the Linked List: %d\r\n", iIterator);

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_CreateStudent(S_STUDENT **out_pSNewStudent)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to create new student and get valid name, roll number and department.
 * / param[out]   : out_pSNewStudent - New Student
 * / Return       : DP_SUCCESS, DP_ROLLNO_NOT_FOUND, DP_NULL_POINTER_ACCESS
 */

int DP_CreateStudent(S_STUDENT **out_pSStudent)
{
    int iReturnValue = 0;

    *out_pSStudent = (S_STUDENT *)malloc(sizeof(S_STUDENT));
    if (*out_pSStudent == NULL)
    {
        DP_FreeStudents();
        return DP_MEM_ALLOCATION_FAILED;
    }

    iReturnValue = DP_GetValidName((*out_pSStudent)->arr_cName);
    if (iReturnValue < DP_SUCCESS)
    {
        free(*out_pSStudent);
        *out_pSStudent = NULL;
        DP_FreeStudents();
        return DP_INVALID_NAME;
    }
    iReturnValue = DP_GetValidRollNo((*out_pSStudent)->arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        free(*out_pSStudent);
        *out_pSStudent = NULL;
        DP_FreeStudents();
        return DP_INVALID_ROLLNUMBER;
    }
    iReturnValue = DP_GetValidDepartment((*out_pSStudent)->arr_cDepartmentName);
    if (iReturnValue < DP_SUCCESS)
    {
        free(*out_pSStudent);
        *out_pSStudent = NULL;
        DP_FreeStudents();
        return DP_INVALID_DEPT_NAME;
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_GetValidName(char *out_pcName)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Get Valid Name
 * / param[out]   : out_pcName - Pointer to Name
 * / Return       : DP_SUCCESS
 */

int DP_GetValidName(char *out_pcName)
{
    /*Check if the Pointer is NULL*/
    if (out_pcName == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    while (1)
    {
        fflush(stdin);

        /*Prompt user to enter student name*/
        printf("\r\nEnter Student Name: \r\n");
        fgets(out_pcName, DP_MAX_STRING_LENGTH, stdin);

        /*Null-terminate the student name*/
        out_pcName[strcspn(out_pcName, "\n\r")] = '\0';

        fflush(stdin);

        /*Check if name contains only alphabet and space*/
        if (DP_IsValidString(out_pcName) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nInvalid Name. Only Alphabets Allowed. Only %d Characters\r\n", (DP_MAX_STRING_LENGTH - 1));
        }
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_GetValidRollNo(char *out_pcRollNumber)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Get Valid Roll Number
 * / param[out]   : out_pcRollNumber - Pointer to Roll Number
 * / Return       : DP_SUCCESS
 */

int DP_GetValidRollNo(char *out_pcRollNumber)
{
    if (out_pcRollNumber == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    while (1)
    {
        fflush(stdin);

        printf("\r\nEnter Student RollNumber: \r\n");
        fgets(out_pcRollNumber, DP_MAX_ROLLNO_LENGTH, stdin);

        out_pcRollNumber[strcspn(out_pcRollNumber, "\n\r")] = '\0';

        fflush(stdin);

        /*Check if roll number is valid*/
        if (DP_IsValidRollNumber(out_pcRollNumber) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nError: Invalid Roll Number. Only Positive Digits Allowed. Only %d Digits.\r\n", DP_MAX_ROLLNO_LENGTH);
        }
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_IsValidString(const char *in_pkcString)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to check if the Name is Valid.
 * / param[in]    : in_pkcString - Pointer to Name
 * / Return       : DP_SUCCESS, DP_INVALID_NAME, DP_INVALID_STRING
 */

int DP_IsValidString(const char *in_pkcString)
{
    int iIterator = 0;
    int iStringLength = 0;

    if (in_pkcString == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    iStringLength = strlen(in_pkcString);

    if (iStringLength >= (DP_MAX_STRING_LENGTH - 1))
    {
        return DP_INVALID_NAME;
    }

    while (in_pkcString[iIterator] != '\0')
    {
        if ((!isalpha(in_pkcString[iIterator])) && (!isspace(in_pkcString[iIterator])))
        {
            return DP_INVALID_NAME;
        }
        iIterator++;
    }
    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_IsValidRollNumber(const char *in_pcRollNumber)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to check if the roll number is valid
 * / param[in]    : in_pkcRollNumber - Pointer to Roll Number
 * / Return       : DP_SUCCESS, DP_INVALID_ROLLNUMBER, DP_NULL_POINTER_ACCESS
 */

int DP_IsValidRollNumber(const char *in_pkcRollNumber)
{
    int iIterator = 0;

    if (in_pkcRollNumber == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    if (strlen(in_pkcRollNumber) >= (DP_MAX_ROLLNO_LENGTH - 1))
    {
        return DP_INVALID_ROLLNUMBER;
    }

    while (in_pkcRollNumber[iIterator] != '\0')
    {
        if (!isdigit(in_pkcRollNumber[iIterator]))
        {
            return DP_INVALID_ROLLNUMBER;
        }
        iIterator++;
    }
    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_GetValidDepartment(char *out_pcDepartment)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to Get Valid Department Name
 * / param[out]   : out_pcDepartment - Department Name
 * / Return       : DP_SUCCESS
 */

int DP_GetValidDepartment(char *out_pcDepartment)
{
    if (out_pcDepartment == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    while (1)
    {
        fflush(stdin);

        printf("\r\nEnter Department Name: \r\n");
        fgets(out_pcDepartment, DP_MAX_STRING_LENGTH, stdin);

        out_pcDepartment[strcspn(out_pcDepartment, "\n\r")] = '\0';

        fflush(stdin);

        /*Check if Dept name is Valid*/
        if (DP_IsValidString(out_pcDepartment) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nInvalid Department Name. Only Alphabets Allowed. Only %d Characters.\r\n", DP_MAX_STRING_LENGTH);
        }
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_FreeStudents()
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to free dynamically allocated memory for students.
 * / Return       : DP_SUCCESS
 */

int DP_FreeStudents()
{
    S_STUDENT *pSTempStudent = NULL;
    S_STUDENT *pSNext = NULL;

    pSTempStudent = pSFirstStudent;

    while (pSTempStudent != NULL)
    {
        pSNext = pSTempStudent->pSNext;
        free(pSTempStudent);
        pSTempStudent = NULL;

        pSTempStudent = pSNext;
    }

    pSFirstStudent = NULL;
    pSLastStudent = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_PrintErrorMessage(int in_iErrorCode)
 * / Author       : 3232
 * / Date         : 24/10/24
 * / Brief        : Function to print error message using returnvalue
 * / param[in]    : in_iErrorCode -  Return Value from function
 * / Return       : DP_SUCCESS, DP_FAILURE
 */

int DP_PrintErrorMessage(int in_iErrorCode)
{
    switch (in_iErrorCode)
    {
    case DP_NULL_POINTER_ACCESS:
        printf("\nError: %d Null pointer accessed!\n", in_iErrorCode);
        break;
    case DP_INVALID_INPUT:
        printf("\nError: Invalid Choice! Enter a Valid Choice from(1 - 6).\n");
        break;
    case DP_INVALID_NUMBER_STUDENTS:
        printf("\r\nError: %d Invalid Number of Students!Enter a Valid Number of Students(1 - %d)\r\n", in_iErrorCode, DP_MAX_STUDENTS);
        break;
    case DP_MEM_ALLOCATION_FAILED:
        printf("\r\nError: %d Memory Allocation Failed.Failed to Allocate Memory for Student.\r\n", in_iErrorCode);
        break;
    case DP_FAILURE:
        printf("\r\nError: %d Program Failed with Error.\r\n", in_iErrorCode);
        break;
    case DP_INVALID_NAME:
        printf("\r\nError: %d Invalid Name! Enter a Valid Name\r\n", in_iErrorCode);
        break;
    case DP_INVALID_ROLLNUMBER:
        printf("\r\nError: %d Invalid RollNumber! Enter a Valid Positive Roll Number.\r\n", in_iErrorCode);
    case DP_INVALID_DEPT_NAME:
        printf("\r\nError: %d Invalid Department Name! Enter a Valid Department Name\r\n", in_iErrorCode);
        break;
    case DP_ROLLNO_NOT_FOUND:
        printf("\r\nError: %d The Entered Roll Number Not Found in the Linked List.\r\n", in_iErrorCode);
        break;
    case DP_CREATE_STUDENT_FAILED:
        printf("\r\nError: %d Failed to create student!\r\n", in_iErrorCode);
        break;
    case DP_INVALID_POSITION:
        printf("\r\nError: %d Invalid Position. Enter a Valid Position.\r\n", in_iErrorCode);
        break;
    default:
        printf("\r\nError: %d Unknown error occurred!\r\n", in_iErrorCode);
        break;
    }

    return DP_SUCCESS;
}
