#include "header.h"

int main()
{
    int iUserChoice = 0;
    int iReturnValue = 0;
    int iNumberOfStudents = 0;

    while (iUserChoice != DP_EXIT_PROGRAM)
    {
        printf("\r\nLinkedList for Student Details:\r\n");
        printf("\r\n1. Create students\r\n");
        printf("\r\n2. Display students\r\n");
        printf("\r\n3. Insert student after rollNumber\r\n");
        printf("\r\n4. Delete student\r\n");
        printf("\r\n5. Search student\r\n");
        printf("\r\n6. Exit Program\r\n");

        do
        {
            /*Prompt user to enter choice*/
            fflush(stdin);
            printf("\r\nEnter your choice(1 - 6):\r\n");
            iReturnValue = scanf(" %d", &iUserChoice);

            /*Input validation for user choice*/

            /*Handle Input Other than Integer*/
            if (iReturnValue != 1)
            {
                printf("\r\nInvalid choice!Enter a Valid Choice(1-6).\r\n");

                /*Get the newline character*/
                while (getchar() != '\n')
                    ;
            }
            else
            {
                /*Check if the user choice is between choice range*/
                if ((iUserChoice < DP_CREATE_STUDENTS) || (iUserChoice > DP_EXIT_PROGRAM))
                {
                    printf("\r\nInvalid choice!Enter a Valid Choice(1-6).\r\n");
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

        case DP_DELETE_STUDENT:

            printf("\r\nYour Choice is %d: Delete student\r\n", iUserChoice);
            iReturnValue = DP_DeleteStudent();

            break;

        case DP_SEARCH_STUDENT:

            printf("\r\nYour Choice is %d: Search student\r\n", iUserChoice);
            iReturnValue = DP_SearchStudent();

            break;

        case DP_EXIT_PROGRAM:

            printf("\r\nYour Choice is %d: Exit Program\r\n", iUserChoice);
            printf("\nExiting Program.......\n");
            getch();

            iReturnValue = DP_FreeStudents();

            return DP_SUCCESS;

        default:

            printf("\nInvalid choice!\n");
            iReturnValue = DP_INVALID_INPUT;
        }

        if (iReturnValue != DP_SUCCESS)
        {
            iReturnValue = DP_PrintErrorMessage(iReturnValue);
            if (iReturnValue == DP_FAILURE)
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
* / Date         : 23/10/24
* / Brief        : Function to Create Database of student records for input number of students
* / param[in]    : in_iNumberOfStudents -  Number of students
* / Return       : DP_SUCCESS, DP_INVALID_NUMBER_STUDENTS, DP_NULL_POINTER_ACCESS,
DP_INVALID_NAME, DP_INVALID_ROLLNUMBER, DP_INVALID_DEPT_NAME.
*/

int DP_CreateStudents(int in_iNumberOfStudents)
{
    S_STUDENT *pSFirstStudent = NULL;
    S_STUDENT *pSLastStudent = NULL;
    S_STUDENT *pSTemp = NULL;
    S_STUDENT *pSNew = NULL;

    int iIterator = 0, iReturnValue = 0;

    if ((in_iNumberOfStudents < 1) || (in_iNumberOfStudents > DP_MAX_STUDENTS))
    {
        printf("\r\nInvalid Number of Students!Enter a Valid Number of Students(1 - %d)\r\n", DP_MAX_STUDENTS);
        getch();
        return DP_INVALID_NUMBER_STUDENTS;
    }

    /*Allocate Memory for First Student*/
    pSFirstStudent = (S_STUDENT *)malloc(sizeof(S_STUDENT) * in_iNumberOfStudents);
    if (pSFirstStudent == NULL)
    {
        return DP_MEM_ALLOCATION_FAILED;
    }

    iReturnValue = DP_GetValidName(pSFirstStudent->arr_cName);
    if (iReturnValue < DP_SUCCESS)
    {
        free(pSFirstStudent);
        pSFirstStudent = NULL;
        return DP_INVALID_NAME;
    }
    iReturnValue = DP_GetValidRollNo(pSFirstStudent->arr_cRollNumber);
    if (iReturnValue < DP_SUCCESS)
    {
        free(pSFirstStudent);
        pSFirstStudent = NULL;
        return DP_INVALID_ROLLNUMBER;
    }
    iReturnValue = DP_GetValidDepartment(pSFirstStudent->arr_cDepartmentName);
    if (iReturnValue < DP_SUCCESS)
    {
        free(pSFirstStudent);
        pSFirstStudent = NULL;
        return DP_INVALID_DEPT_NAME;
    }

    pSFirstStudent->pSNext = NULL;
    /*Set First and Last to First Student*/
    pSLastStudent = pSFirstStudent;

    /*Input Data for Each Student*/
    for (iIterator = 1; iIterator < in_iNumberOfStudents; iIterator++)
    {
        pSNew = (S_STUDENT *)malloc(sizeof(S_STUDENT));
        if (pSNew == NULL)
        {
            DP_FreeStudents();
            return DP_MEM_ALLOCATION_FAILED;
        }

        iReturnValue = DP_GetValidName(pSNew->arr_cName);
        if (iReturnValue < DP_SUCCESS)
        {
            free(pSNew);
            DP_FreeStudents();
            return DP_INVALID_NAME;
        }
        iReturnValue = DP_GetValidRollNo(pSNew->arr_cRollNumber);
        if (iReturnValue < DP_SUCCESS)
        {
            free(pSNew);
            DP_FreeStudents();
            return DP_INVALID_ROLLNUMBER;
        }
        iReturnValue = DP_GetValidDepartment(pSNew->arr_cDepartmentName);
        if (iReturnValue < DP_SUCCESS)
        {
            free(pSNew);
            DP_FreeStudents();
            return DP_INVALID_DEPT_NAME;
        }

        pSNew->pSNext = NULL;
        /*Link the New Student to the This*/
        pSLastStudent->pSNext = pSNew;
        /*Updatte Last Pointer*/
        pSLastStudent = pSNew;
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_DisplayStudents()
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to Display the student database
 * / Return       : DP_SUCCESS, DP_NULL_POINTER_ACCESS
 */

int DP_DisplayStudents()
{
    S_STUDENT *pSTemp = NULL;

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    pSTemp = pSFirstStudent;

    while (pSTemp != NULL)
    {
        printf("\nRoll number: %-10s\n", pSTemp->arr_cRollNumber);
        printf("Name: %-10s\n", pSTemp->arr_cName);
        printf("\rDepartment: %-10s\n", pSTemp->arr_cDepartmentName);

        /*Move to Next Student*/
        pSTemp = pSTemp->pSNext;
    }

    return DP_SUCCESS;
}

/*!
* / Function Name: DP_InsertAfterRollNo()
* / Author       : 3232
* / Date         : 23/10/24
* / Brief        : Function to Insert a student record after a specific roll number
* / Return       : DP_SUCCESS, DP_FAILURE, DP_NULL_POINTER_ACCESS, DP_MEM_ALLOCATION_FAILED,
DP_INVALID_NAME, DP_INVALID_ROLLNO, DP_INVALID_DEPT_NAME, DP_ROLLNO_NOT_FOUND
*/

int DP_InsertAfterRollNo()
{
    S_STUDENT *pSTemp = NULL;
    S_STUDENT *pSNew = NULL;
    int iReturnValue = 0;

    char cRollNumber[DP_MAX_STRING_LENGTH] = {0};

    while (1)
    {
        fflush(stdin);

        printf("\r\nEnter the roll number to insert after: \r\n");
        fgets(cRollNumber, DP_MAX_ROLLNO_LENGTH, stdin);

        cRollNumber[strcspn(cRollNumber, "\n\r")] = '\0';

        fflush(stdin);

        if (DP_IsValidRollNumber(cRollNumber) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nError: Invalid Roll Number. Only Digits Allowed.\r\n");
        }
    }

    pSTemp = pSFirstStudent;

    while (pSTemp != NULL)
    {
        /*Check if the roll number matches*/
        if (strcmp(cRollNumber, pSTemp->arr_cRollNumber) == 0)
        {
            pSNew = (S_STUDENT *)malloc(sizeof(S_STUDENT));
            if (pSNew == NULL)
            {
                free(pSNew);
                return DP_MEM_ALLOCATION_FAILED;
            }

            iReturnValue = DP_GetValidName(pSNew->arr_cName);
            if (iReturnValue < DP_SUCCESS)
            {
                free(pSNew);
                return DP_INVALID_NAME;
            }
            iReturnValue = DP_GetValidRollNo(pSNew->arr_cRollNumber);
            if (iReturnValue < DP_SUCCESS)
            {
                free(pSNew);
                return DP_INVALID_ROLLNUMBER;
            }
            iReturnValue = DP_GetValidDepartment(pSNew->arr_cDepartmentName);
            if (iReturnValue < DP_SUCCESS)
            {
                free(pSNew);
                return DP_INVALID_DEPT_NAME;
            }

            /*Link the New Student After the Matched Student*/
            pSNew->pSNext = pSTemp->pSNext;
            pSTemp->pSNext = pSNew;

            return DP_SUCCESS;
        }

        /*Move to the Next Student*/
        pSTemp = pSTemp->pSNext;
    }

    return DP_ROLLNO_NOT_FOUND;
}

/*!
 * / Function Name: DP_DeleteStudent()
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to delete a student record by roll number
 * / Return       : DP_SUCCESS, DP_ROLLNO_NOT_FOUND, DP_NULL_POINTER_ACCESS
 */

int DP_DeleteStudent()
{
    char cRollNumber[DP_MAX_STRING_LENGTH] = {0};

    S_STUDENT *pSPrev = NULL;
    S_STUDENT *pSTemp = NULL;

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    while (1)
    {
        fflush(stdin);

        printf("\r\nEnter the roll number to delete:\r\n");
        fgets(cRollNumber, DP_MAX_ROLLNO_LENGTH, stdin);

        cRollNumber[strcspn(cRollNumber, "\n\r")] = '\0';

        fflush(stdin);

        if (DP_IsValidRollNumber(cRollNumber) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nError: Invalid Roll Number. Only Digits Allowed.\r\n");
        }
    }

    pSTemp = pSFirstStudent;

    /*If the First Student Roll Number Matches*/
    if (strcmp(cRollNumber, pSFirstStudent->arr_cRollNumber) == 0)
    {
        /*Update head of linked list*/
        pSFirstStudent = pSFirstStudent->pSNext;

        /*free memory of deleted student*/
        free(pSTemp);
        pSTemp = NULL;
        return DP_SUCCESS;
    }

    /*Traverse the List to find the roll number*/
    while ((pSTemp != NULL) && (strcmp(cRollNumber, pSTemp->arr_cRollNumber) != 0))
    {
        pSPrev = pSTemp;
        pSTemp = pSTemp->pSNext;
    }

    /*Return if Roll number not found in the linkedlist*/
    if (pSTemp == NULL)
    {
        return DP_ROLLNO_NOT_FOUND;
    }

    /*Link the previous student to next*/
    pSPrev->pSNext = pSTemp->pSNext;
    /*free memory of the deleted student*/
    free(pSTemp);
    pSTemp = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_SearchStudent()
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to Search for a student record by roll number
 * / Return       : DP_SUCCESS, DP_FAILURE, DP_NULL_POINTER_ACCESS
 */

int DP_SearchStudent()
{
    S_STUDENT *pSTemp = NULL;

    char cRollNumber[DP_MAX_ROLLNO_LENGTH] = {0};

    if (pSFirstStudent == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    while (1)
    {
        fflush(stdin);
        printf("\r\nEnter the roll number to search:\r\n");
        fgets(cRollNumber, DP_MAX_ROLLNO_LENGTH, stdin);
        cRollNumber[strcspn(cRollNumber, "\n\r")] = '\0';

        if (DP_IsValidRollNumber(cRollNumber) == DP_SUCCESS)
        {
            break;
        }
        else
        {
            printf("\r\nError: Invalid Roll Number. Only Digits Allowed.\r\n");
        }
    }

    pSTemp = pSFirstStudent;

    while (pSTemp != NULL)
    {
        /*If roll number matches display the student data*/
        if (strcmp(cRollNumber, pSTemp->arr_cRollNumber) == 0)
        {
            printf("\r\nStudent found       : %s\r\n", pSTemp->arr_cName);
            printf("\r\nStudent Roll Number : %s\r\n", pSTemp->arr_cRollNumber);
            printf("\r\nStudent Department  : %s\r\n", pSTemp->arr_cDepartmentName);
            return DP_SUCCESS;
        }
        /*Move to the next student*/
        pSTemp = pSTemp->pSNext;
    }

    /*Return if roll number not found in the linkedlist*/
    return DP_ROLLNO_NOT_FOUND;
}

/*!
 * / Function Name: DP_GetValidName(char *out_pcName)
 * / Author       : 3232
 * / Date         : 23/10/24
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
            printf("\r\nInvalid Name. Only Alphabets Allowed.\r\n");
        }
    }
    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_GetValidRollNo(char *out_pcRoll)
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to Get Valid Roll Number
 * / param[out]   : out_pcRoll - Pointer to Roll Number
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
            printf("\r\nError: Invalid Roll Number. Only Digits Allowed.\r\n");
        }
    }

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_IsValidString(const char *in_pcName)
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to check if the Name is Valid.
 * / param[in]    : in_pcName - Pointer to Name
 * / Return       : DP_SUCCESS, DP_INVALID_NAME
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

    if (iStringLength >= DP_MAX_STRING_LENGTH)
    {
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
 * / Date         : 23/10/24
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
 * / Date         : 23/10/24
 * / Brief        : Function to Get Valid Department Name
 * / param[out]    : out_pcDepartment - Department Name
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
            printf("\r\nInvalid Department Name. Only Alphabets Allowed.\r\n");
        }
    }
    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_FreeStudents()
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to free dynamically allocated memory for students.
 * / Return       : DP_SUCCESS
 */

int DP_FreeStudents()
{
    S_STUDENT *pSTemp = NULL;
    S_STUDENT *pSNext = NULL;

    pSTemp = pSFirstStudent;

    while (pSTemp != NULL)
    {
        pSNext = pSTemp->pSNext;
        free(pSTemp);

        pSTemp = pSNext;
    }

    pSFirstStudent = NULL;
    pSLastStudent = NULL;

    return DP_SUCCESS;
}

/*!
 * / Function Name: DP_PrintErrorMessage(int in_iErrorCode)
 * / Author       : 3232
 * / Date         : 23/10/24
 * / Brief        : Function to print error message using returnvalue
 * / param[in]    : in_iErrorCode -  Return Value from function
 * / Return       : DP_SUCCESS, DP_FAILURE
 */

int DP_PrintErrorMessage(int in_iErrorCode)
{
    if ((in_iErrorCode == DP_NULL_POINTER_ACCESS) || (in_iErrorCode == DP_INVALID_INPUT))
    {
        switch (in_iErrorCode)
        {
        case DP_NULL_POINTER_ACCESS:
            printf("\nError: %d Null pointer access!\n", in_iErrorCode);
            break;
        case DP_INVALID_INPUT:
            printf("\nError: Invalid input!\n");
            break;
        case DP_INVALID_NUMBER_STUDENTS:
            printf("\r\nError: %d Invalid Number of Students!Enter a Valid Number of Students(1 - %d)\r\n", in_iErrorCode, DP_MAX_STUDENTS);
            break;
        case DP_MEM_ALLOCATION_FAILED:
            printf("\r\nError: %d Memory Allocation Failed.\r\n", in_iErrorCode);
            break;
        case DP_FAILURE:
            printf("\r\nError: %d Program Failed.\r\n", in_iErrorCode);
            break;
        case DP_INVALID_NAME:
            printf("\r\nError: %d Invalid Name! Enter a Valid Name\r\n", in_iErrorCode);
            break;
        case DP_INVALID_ROLLNUMBER:
            printf("\r\nError: %d Invalid RollNumber! Enter a Valid Roll Number.\r\n", in_iErrorCode);
        case DP_INVALID_DEPT_NAME:
            printf("\r\nError: %d Invalid Department Name! Enter a Valid Department Name\r\n", in_iErrorCode);
            break;
        case DP_ROLLNO_NOT_FOUND:
            printf("\r\nError: %d The Specified Roll Number Not Found in the List.\r\n", in_iErrorCode);
            break;
        default:
            printf("\r\nError: %d Unknown error occurred!\r\n", in_iErrorCode);
            break;
        }

        return DP_SUCCESS;
    }

    return DP_FAILURE;
}
