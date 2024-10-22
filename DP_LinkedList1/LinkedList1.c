#include "header.h"

// Global pointers
S_STUDENT *pSFirst = NULL;
S_STUDENT *pSLast = NULL;

// Function to print error messages based on error codes
int DP_PrintErrorMessage(int in_iErrorCode)
{
    // Check if the input is valid
    if ((in_iErrorCode == DP_NULL_POINTER_ACCESS) || (in_iErrorCode == DP_INVALID_INPUT))
    {
        switch (in_iErrorCode)
        {
        case DP_NULL_POINTER_ACCESS:
            printf("\nError: Null pointer access!\n");
            break;
        case DP_INVALID_INPUT:
            printf("\nError: Invalid input!\n");
            break;
        default:
            printf("\nError: Unknown error occurred!\n");
            break;
        }

        return DP_SUCCESS; // Successfully printed error message
    }

    return DP_FAILURE; // Invalid error code provided
}

/**
 * @brief Creates a database of student records
 *
 * @param in_iCount Number of students
 * @return int DP_SUCCESS or DP_FAILURE
 */
int DP_CreateDatabase(int in_iCount)
{
    if (in_iCount <= 0)
    {
        return DP_INVALID_INPUT;
    }

    pSFirst = (S_STUDENT *)malloc(sizeof(S_STUDENT));
    if (!pSFirst)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    printf("\nEnter the first name of the student: ");
    scanf("%s", pSFirst->m_cName);
    printf("\nEnter the roll number of the student: ");
    scanf("%s", pSFirst->m_cRoll);
    pSFirst->pSNext = NULL;
    pSLast = pSFirst;

    for (int i = 1; i < in_iCount; i++)
    {
        S_STUDENT *pSNew = (S_STUDENT *)malloc(sizeof(S_STUDENT));
        if (!pSNew)
        {
            return DP_NULL_POINTER_ACCESS;
        }

        printf("\nEnter the first name of the student: ");
        scanf("%s", pSNew->m_cName);
        printf("\nEnter the roll number of the student: ");
        scanf("%s", pSNew->m_cRoll);
        pSNew->pSNext = NULL;
        pSLast->pSNext = pSNew;
        pSLast = pSNew;
    }

    return DP_SUCCESS;
}

/**
 * @brief Displays the student database
 *
 * @return int DP_SUCCESS or DP_FAILURE
 */
int DP_DisplayDatabase()
{
    if (pSFirst == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    S_STUDENT *pSTemp = pSFirst;
    while (pSTemp != NULL)
    {
        printf("\nRoll number: %s", pSTemp->m_cRoll);
        printf("\nFirst name: %s", pSTemp->m_cName);
        pSTemp = pSTemp->pSNext;
    }

    return DP_SUCCESS;
}

/**
 * @brief Inserts a student record after a specific roll number
 *
 * @return int DP_SUCCESS or DP_FAILURE
 */
int DP_InsertAfter()
{
    char cRoll[10];
    printf("\nEnter the roll number to insert after: ");
    scanf("%s", cRoll);

    S_STUDENT *pSTemp = pSFirst;
    while (pSTemp != NULL)
    {
        if (strcasecmp(cRoll, pSTemp->m_cRoll) == 0)
        {
            S_STUDENT *pSNew = (S_STUDENT *)malloc(sizeof(S_STUDENT));
            if (!pSNew)
            {
                return DP_NULL_POINTER_ACCESS;
            }

            printf("\nEnter the first name of the student: ");
            scanf("%s", pSNew->m_cName);
            printf("\nEnter the roll number of the student: ");
            scanf("%s", pSNew->m_cRoll);
            pSNew->pSNext = pSTemp->pSNext;
            pSTemp->pSNext = pSNew;
            return DP_SUCCESS;
        }
        pSTemp = pSTemp->pSNext;
    }

    return DP_FAILURE;
}

/**
 * @brief Deletes a student record by roll number
 *
 * @return int DP_SUCCESS or DP_FAILURE
 */
int DP_DeleteRecord()
{
    if (pSFirst == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    char cRoll[10];
    printf("\nEnter the roll number to delete: ");
    scanf("%s", cRoll);

    S_STUDENT *pSPrev = NULL;
    S_STUDENT *pSTemp = pSFirst;

    if (strcasecmp(cRoll, pSFirst->m_cRoll) == 0)
    {
        pSFirst = pSFirst->pSNext;
        free(pSTemp);
        return DP_SUCCESS;
    }

    while (pSTemp != NULL && strcasecmp(cRoll, pSTemp->m_cRoll) != 0)
    {
        pSPrev = pSTemp;
        pSTemp = pSTemp->pSNext;
    }

    if (pSTemp == NULL)
    {
        return DP_FAILURE;
    }

    pSPrev->pSNext = pSTemp->pSNext;
    free(pSTemp);

    return DP_SUCCESS;
}

/**
 * @brief Searches for a student record by roll number
 *
 * @return int DP_SUCCESS or DP_FAILURE
 */
int DP_SearchRecord()
{
    if (pSFirst == NULL)
    {
        return DP_NULL_POINTER_ACCESS;
    }

    char cRoll[10];
    printf("\nEnter the roll number to search: ");
    scanf("%s", cRoll);

    S_STUDENT *pSTemp = pSFirst;
    while (pSTemp != NULL)
    {
        if (strcasecmp(cRoll, pSTemp->m_cRoll) == 0)
        {
            printf("\nStudent found: %s", pSTemp->m_cName);
            return DP_SUCCESS;
        }
        pSTemp = pSTemp->pSNext;
    }

    return DP_FAILURE;
}

int main()
{
    int iUserChoice = 0;
    int iReturnValue = 0;
    int iSize = 0;

    while (iUserChoice != DP_EXIT_PROGRAM)
    {
        printf("\r\nMENU\r\n");
        printf("\r\n1. Create database\r\n");
        printf("\r\n2. Display database\r\n");
        printf("\r\n3. Insert record after another\r\n");
        printf("\r\n4. Delete record\r\n");
        printf("\r\n5. Search record\r\n");
        printf("\r\n6. Exit\r\n");

        do
        {
            fflush(stdin);
            printf("\r\nEnter your choice:\r\n");
            iReturnValue = scanf(" %d", &iUserChoice);

            if (iReturnValue != 1)
            {
                printf("\r\nInvalid choice! Please enter a valid option (1-6).\r\n");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                if ((iUserChoice < DP_CREATE_DATABASE) || (iUserChoice > DP_EXIT_PROGRAM))
                {
                    printf("\r\nInvalid choice! Please enter a valid option (1-6).\r\n");
                }
            }

        } while ((iReturnValue != 1) || (iUserChoice < DP_CREATE_DATABASE) || (iUserChoice > DP_EXIT_PROGRAM));

        switch (iUserChoice)
        {
        case DP_CREATE_DATABASE:
            printf("\r\nEnter the size of the database:\r\n");
            scanf("%d", &iSize);
            iReturnValue = DP_CreateDatabase(iSize);
            break;
        case DP_DISPLAY_STUDENTS:
            iReturnValue = DP_DisplayDatabase();
            break;
        case DP_INSERT_AFTER:
            iReturnValue = DP_InsertAfter();
            break;
        case DP_DELETE_STUDENT:
            iReturnValue = DP_DeleteRecord();
            break;
        case DP_SEARCH_STUDENT:
            iReturnValue = DP_SearchRecord();
            break;
        case DP_EXIT_PROGRAM:
            printf("\nExiting Program.......\n");
            getchar();
            return DP_SUCCESS;
        default:
            printf("\nInvalid choice!\n");
            iReturnValue = DP_INVALID_INPUT;
        }

        // Handle return values
        if (iReturnValue != DP_SUCCESS)
        {
            DP_PrintErrorMessage(iReturnValue);
        }
    }

    return DP_SUCCESS;
}
