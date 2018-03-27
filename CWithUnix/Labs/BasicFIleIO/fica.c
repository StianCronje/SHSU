#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

//Initialize functions
void FormatAmmount(char* str, float val);
float CalculateTax(float p_ytd, float p_gross);


int main()
{
    //initialize variables
    const int colWidth = 8, colWidth2 = 12;
    int sentinel = -1, answer = 0, lineNum = 1;
    char response;
    float totalGross = 0, totalTax = 0;

    FILE *outFile;
    char outFileName[21];

    //prompt user for output file
    printf("Enter output file name: ");
    scanf("%s", outFileName);
    
    //check if file already exists and asks for user authorizations
    if((outFile = fopen(outFileName, "r")) != NULL)
    {
        printf("A file by that name already exists.\n");
        do
        {
            printf("Do you wish to override? [y/n]: ");
            scanf(" %c", &response);
        }
        while(toupper(response) != 'N' && toupper(response) != 'Y');
        
        if(toupper(response) == 'N')
        {
            printf("Exiting Program!\n");
            exit(1);
        }
    }

    //creates output file if it doesnt exist, or overwrite
    outFile = fopen(outFileName, "w");
    if (outFile == NULL)
    {
        printf("File could not be created.\n");
        printf("Exiting Program!\n");
        exit(1);
    }

    //Create Cover Page
    fprintf(outFile, "\n\n\n%46s\n\n", "Lab 1 Option A");
    fprintf(outFile, "%47s\n\n", "Christiaan Cronje");
    fprintf(outFile, "%48s\n\n", "Due: March 3, 2017");
    fprintf(outFile, "%53s\n\n", "Submitted: February 17, 2017");

    //Page Break
    fprintf(outFile, "\f");

    //Second Page Headers
    fprintf(outFile, "%34s", "SOME COMPANY");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(outFile, "%20d/%d/%d\n\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900);

    fprintf(outFile, "Line No.");
    fprintf(outFile, "%1s", "");
    fprintf(outFile, "%4s", "Emp No.");
    fprintf(outFile, "%2s", "");
    fprintf(outFile, "%-*s", colWidth, "Given");
    fprintf(outFile, "%-*s", colWidth, "Surname");
    fprintf(outFile, "%-*s", colWidth2, "YTD");
    fprintf(outFile, "%-*s", colWidth2, "Gross");
    fprintf(outFile, "%-*s\n\n", colWidth2, "FICA Tax");
        
    do
    {
        char fName[colWidth+1], lName[colWidth+1];
        int empNum;
        float ytd = 0, gross = 0, tax = 0;
        
        //prompt user for employee information
        printf("Please enter employee First and Last Name: ");
        scanf("%s", fName);
        scanf("%s", lName);
        printf("Please enter Employee Number: ");
        scanf("%d", &empNum);
        printf("Please enter Employee YTD: ");
        scanf("%f", &ytd);
        printf("Please enter Employee Gross Income: ");
        scanf("%f", &gross);

        //calculate tax
        tax = CalculateTax(ytd, gross);
        //accumulate totals
        totalGross += gross;
        totalTax += tax;

        //create formatted currency strings
        char ytd_string[colWidth+1];
        FormatAmmount(ytd_string, ytd);
        char gross_string[colWidth+1];
        FormatAmmount(gross_string,gross);
        char tax_string[colWidth+1];
        FormatAmmount(tax_string, tax);
        
        //write the enployee info to file
        fprintf(outFile, "%-4d", lineNum);
        fprintf(outFile, "%6s", "");
        fprintf(outFile, "%6d", empNum);
        fprintf(outFile, "%2s", "");
        fprintf(outFile, "%-*s", colWidth, fName);
        fprintf(outFile, "%-*s", colWidth, lName);
        fprintf(outFile, "%*s", colWidth2, ytd_string);
        fprintf(outFile, "%*s", colWidth2, gross_string);
        fprintf(outFile, "%*s\n", colWidth2, tax_string);
        lineNum++;
        
        //promt to repeat
        printf("Enter another employee? [y/n]: ");
        scanf(" %c", &response);
        if(toupper(response) == 'N')
        {
            answer = -1;
        }
    }while(sentinel != answer); //repeat if needed

    //Format total ammounts
    char tTax_string[21], tGross_string[21];
    FormatAmmount(tTax_string, totalTax);
    FormatAmmount(tGross_string, totalGross);

    //write totals to the file
    fprintf(outFile, "\n%32s%-10s%16s%12s\n", "", "Totals", tGross_string, tTax_string);

    //close output file
    fclose(outFile);

    return 0;
}

//using locale.h to format float to currency
void FormatAmmount(char* str, float val)
{
    setlocale(LC_NUMERIC, "");
    sprintf(str, "$%'.2f", val);
}


float CalculateTax(float p_ytd, float p_gross)
{
    float taxRate = 0.042;
    float owedTax = 0;
    if (p_ytd < 110100){
        if (p_ytd + p_gross <= 110100){
            //tax = total gross
            owedTax = p_gross * taxRate;
        }
        else{
            //tax = 110100 - ytd
            owedTax = (110100 - p_ytd) * taxRate;
        }
    }
    //else no tax

    return owedTax;
}

