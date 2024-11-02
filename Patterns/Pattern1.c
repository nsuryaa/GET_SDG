#include <stdio.h>
#include <curses.h>

int main()
{
    int iNumber = 5, iIterator1 = 0, iIterator2 = 0;

    for (iIterator1 = 1; iIterator1 < (iNumber * 2); iIterator1++)
    {
        for (iIterator2 = 1; iIterator2 < (iNumber * 2); iIterator2++)
        {
            if ((iIterator1 == iNumber) || ((iIterator1 == 1) && (iIterator2 == iNumber)) || ((iIterator1 == ((iNumber * 2) - 1)) && (iIterator2 == iNumber)))
            {
                printf("%d", iIterator2);
            }
            else if ((iIterator1 >= 2) && (iIterator1 <= (iNumber - 1)))
            {
                if ((iIterator2 >= (iNumber + 1 - iIterator1)) && (iIterator2 <= (iNumber - 1 + iIterator1)))
                {
                    printf("%d", iIterator2);
                }
                else
                {
                    printf(" ");
                }
            }
            else if ((iIterator1 > iNumber) && (iIterator1 < ((iNumber * 2) - 1)))
            {
                if ((iIterator2 >= (iIterator1 - iNumber + 1)) && (iIterator2 <= ((iNumber + (iNumber - 2)) - (iIterator1 - iNumber - 1))))
                {
                    printf("%d", iIterator2);
                }
                else
                {
                    printf(" ");
                }
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}