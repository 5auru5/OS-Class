#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define REFSTRING_LENGTH 20  //sets the reference string length to 20
#define PAGES 5  //sets the page length to 5

void Optimal(int a[], int size, int frameNum) //this is the optimal alg
{
    int frame[frameNum];
    int i;
    int index = 0;
    int count;
    int j, k;
    int optimal;
    int fault = 0;
    bool page[PAGES];
    for (i = 0; i < PAGES; i++)
        page[i] = 0;
    for (i = 0; i < size; i++)
    {
        if (index < frameNum && !page[a[i]])
        {
            fault++;
            frame[index++] = a[i];
            page[a[i]] = 1;
        }
        else if (index >= frameNum && !page[a[i]])  //replacement branch
        {
            fault++;
            count = 0;
            bool checked[PAGES];
            for (j = 0; j < PAGES; j++)
                checked[j] = 0;
            for (j = i + 1;; j++)
            {
                if (count == frameNum || j == size)
                    break;
                if (page[a[j]] && !checked[a[j]])
                {
                    optimal = a[j];
                    checked[a[j]] = 1;
                    count++;
                }
            }
            printf("Replaced:  %d\n", optimal);
            page[optimal] = 0;
            for (k = 0; k < frameNum; k++)
            {
                if (frame[k] == optimal)
                    break;
            }
            frame[k] = a[i];
            page[a[i]] = 1;
        }
        for (int i = 0; i < index; i++)
            printf("%d ", frame[i]); //displays each line
        printf("\n"); 
    }
    int pageHits = REFSTRING_LENGTH - fault;
    printf("\nPage faults = %d\nPage hits = %d\n\n", fault, pageHits);
}
void LRU(int a[], int size, int frameNum)  //LRU alg
{
    int frame[frameNum];
    int i;
    int index = 0;
    int count;
    int j, k;
    int lru;
    int fault = 0;
    bool page[PAGES];
    for (i = 0; i < PAGES; i++)
        page[i] = 0;
    for (i = 0; i < size; i++)
    {
        if (index < frameNum && !page[a[i]])
        {
            fault++;
            frame[index++] = a[i];
            page[a[i]] = 1;
        }
        else if (index >= frameNum && !page[a[i]])  //if a replacement needs to be made
        {
            fault++;
            count = 0;
            bool checked[PAGES];
            for (j = 0; j < PAGES; j++)
                checked[j] = 0;
            for (j = i - 1;; j--)
            {
                if (count == frameNum || j < 0)
                    break;
                if (page[a[j]] && !checked[a[j]])
                {
                    lru = a[j];
                    checked[a[j]] = 1;
                    count++;
                }
            }
            printf("Replaced:  %d\n", lru);
            page[lru] = 0;
            for (k = 0; k < frameNum; k++)
            {
                if (frame[k] == lru)
                    break;
            }
            frame[k] = a[i];
            page[a[i]] = 1;
        }
        for (int i = 0; i < index; i++) //displays each line
            printf("%d ", frame[i]);
        printf("\n"); 
    }
    int pageHits = REFSTRING_LENGTH - fault;
    printf("\nPage faults = %d\nPage hit = %d\n\n", fault, pageHits);
}
int main()
{
    srand(time(NULL));
    int frameNum, i;
    printf("Enter frame number : ");
    scanf("%d", &frameNum);
    int arr[frameNum];
    bool page[PAGES];
    for (i = 0; i < PAGES; i++)
        page[i] = 0;
    int a[REFSTRING_LENGTH];
    for (i = 0; i < REFSTRING_LENGTH; i++)
    {
        a[i] = rand() % 5 + 1;
    }
    printf("Reference String: ");
    for (int i = 0; i < 20; i++) //prints the ref string
        printf("%d ", a[i]);
    printf("\n");
    printf("OPTIMAL:\n");
    Optimal(a, REFSTRING_LENGTH, frameNum);  //runs the optimal alg
    printf("LRU:\n");
    LRU(a, REFSTRING_LENGTH, frameNum); //runs the LRU alg
    return 0;
}