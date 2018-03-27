#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int(*compare) (struct employee, struct employee);
#include "PtrSortRecordsB.c"
#include "SortRecords.c"
#include "PtrSortRecordsC.c"
#include "TemplateSortRecords.cpp"

void PrintRecords(struct employee *emp, int count, FILE* output);


int main( int argc, char *argv[] )
{


    FILE *fileIn;              // Logical output file name in program.
    char fileInName[15];    // Actual path and file name on disk.

    FILE *fileOut;
    char fileOutName[20];

    if(argc >= 3)
    {
        strcpy(fileInName, argv[1]);
        strcpy(fileOutName, argv[2]);
    }
    else // else get input for file names
    {
        printf("%s", "Enter the name of the input file [max 15 characters]: ");
        scanf("%s", fileInName);
        printf("%s", "Enter the name of the file to hold the results [max 20 characters]: ");
        scanf("%s", fileOutName);
    }

    //try to open input file
    fileIn = fopen(fileInName, "r");
    if( fileIn == NULL ){ 
        printf("%s\n", "Input file does not exist! Program terminating.");
        exit(1);  // exit(0) indicates program success, exit(1) failure.
    }

    //try to open output file
    fileOut = fopen(fileOutName, "w+");
    if( fileOut == NULL ){
        printf("%s\n", "Could not create the output file! Program terminating.");
        exit(1);
    }

// Program Initializations
    struct employee records[50];

    int c = 0;
    // Obtain information from file and calculate the payroll.
    while(!feof(fileIn))
    {
        //get all info from input file
        fscanf(fileIn, "%s",  records[c].surname);
        fscanf(fileIn, "%s",  records[c].given);
        fscanf(fileIn, "%s",  records[c].dept);
        fscanf(fileIn, "%f",  &records[c].payRate);
        fscanf(fileIn, "%s",  records[c].eyeColor);
        c++;
    }
    int recordCnt = c;

    // Create data sets to be processed by functions
    // this will not override original copy
    struct employee dataD[50];
    memcpy(dataD, records, sizeof(records));
    struct employee dataC[50];
    memcpy(dataC, records, sizeof(records));
    struct employee dataB[50];
    memcpy(dataB, records, sizeof(records));
    struct employee dataA1[50];
    memcpy(dataA1, records, sizeof(records));
    struct employee dataA2[50];
    memcpy(dataA2, records, sizeof(records));

    //output raw data
    printf("\nUnsorted:\n");
    fprintf(fileOut, "Unsorted:\n");
    PrintRecords(records, recordCnt, fileOut);

    //sort data for D option
    SortRecords(dataD, recordCnt);
    // print sorted data
    printf("\nSorted D:\n");
    fprintf(fileOut, "\nSorted D:\n");
    PrintRecords(dataD, recordCnt, fileOut);

    // Create pointer array to sort using C option
    struct employee *ptrsC[50];
    for (int i = 0; i < recordCnt; ++i){ ptrsC[i] = &dataC[i]; }
        PtrSortRecordsC(ptrsC, recordCnt);
    printf("\nSorted C:\n");
    fprintf(fileOut, "\nSorted C:\n");
    PrintRecords(dataC, recordCnt, fileOut);

    // Create pointer array to sort using B option
    struct employee *ptrsB[50];
    for (int i = 0; i < recordCnt; ++i){ ptrsB[i] = &dataB[i]; }
        PtrSortRecordsC(ptrsB, recordCnt);
    printf("\nSorted B:\n");
    fprintf(fileOut, "\nSorted B:\n");
    PrintRecords(dataB, recordCnt, fileOut);

    // Template of type struct employee sorting A option by Surname. Uses cmpN to compare
    TemplateSortRecords<struct employee>(dataA1, recordCnt, cmpN);
    printf("\nTemplate Sorted A by Surname:\n");
    fprintf(fileOut, "\nTemplate Sorted A by Surname:\n");
    PrintRecords(dataA1, recordCnt, fileOut);

    // Template of type struct employee sorting A option by Department. Uses cmpD to compare
    TemplateSortRecords<struct employee>(dataA2, recordCnt, cmpD);
    printf("\nTemplate Sorted A by Department:\n");
    fprintf(fileOut, "\nTemplate Sorted A by Department:\n");
    PrintRecords(dataA2, recordCnt, fileOut);


    // Close files
    fclose(fileIn);
    fclose(fileOut);

    return 0;  // Indicate success to the runtime environment.
}

void PrintRecords(struct employee *emp, int count, FILE* output)
{
    for (int i = 0; i < count; i++)
    {
        printf("%-20s%-20s%-20s%-8.2f%-20s\n", emp[i].surname, emp[i].given, emp[i].dept, emp[i].payRate, emp[i].eyeColor);
        fprintf(output, "%-20s%-20s%-20s%-8.2f%-20s\n", emp[i].surname, emp[i].given, emp[i].dept, emp[i].payRate, emp[i].eyeColor);
    }
    return;
}