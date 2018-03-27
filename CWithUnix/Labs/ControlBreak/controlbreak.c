#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void NewPage(FILE *p_file, float *p_pgTotals[4], int *p_pgKnt, float *p_totals[4], int *p_lnKnt);
void PrintOpening(FILE *p_file, int *p_pgKnt);
void PrintClosing(FILE *p_file, float *p_pgTotals[3], int *p_pgKnt, float *p_totals[3], int numRecords);
void PrintDetailHeaders(FILE *p_file);
float CalculateGross(float p_rate, float p_hrs);
float CalculateFICA(float p_fica, float p_limit, float p_ytd, float p_gross);

int main( int argc, char *argv[] )
{
    FILE *fileIn;              // Logical output file name in program.
    char fileInName[15];    // Actual path and file name on disk.

    FILE *fileOut;
    char fileOutName[20];

    FILE *fileFica;
    char fileFicaName[15];

    const int strw15 = 11, strw12 = 12, maxLines = 4;
    float currFica = 0.071;
    float ficaLimit = 110100;

    // check if command line arguments were used for file names
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

    // get fica info file name and try to open it
    printf("%s", "Enter the FICA Info file name: ");
    scanf("%s", fileFicaName);
    fileFica = fopen(fileFicaName, "r");
    if( fileFica == NULL ){ 
        printf("%s\n", "FICA file does not exist! Program terminating.");
        exit(1);  // exit(0) indicates program success, exit(1) failure.
    }
    // get the fica rate
    fscanf(fileFica, "%f", &currFica);
    // get the fica limit
    fscanf(fileFica, "%f", &ficaLimit);

    printf("\n");

// Program Initializations
    int numRecords = 0;
    int id;
    char givenName[10];  //First name
    char surname[10];    //Last name
    char dept_old[10];  // previous dept name
    char dept[10];    //dept name
    float ytd = 0, hoursWkd = 0, payrate = 0, gross = 0, fica = 0, net = 0;
    int lineKt = 0;      //Line counter.
    int pageKt = 0;      //Page counter.
    float cumGross = 0, cumFica = 0, cumNet = 0; //cumulative totals
    float pgGross = 0, pgFica = 0, pgNet = 0; // page totals
    float deptGross = 0, deptFica = 0, deptNet = 0; // department totals

    // init float arrays to easily keep track of totals when passing between functions
    float *pgTotals[] = { &pgGross, &pgFica, &pgNet };
    float *cumTotals[] = { &cumGross, &cumFica, &cumNet };

    PrintOpening(fileOut, &pageKt);

    // Obtain information from file and calculate the payroll.
    while(!feof(fileIn))
    {
        //get all info from input file and add to running totals
        fscanf(fileIn, "%d", &id);
        fscanf(fileIn, "%s", givenName);
        fscanf(fileIn, "%s", surname);
        fscanf(fileIn, "%s", dept);
        fscanf(fileIn, "%f", &ytd);
        fscanf(fileIn, "%f", &payrate);
        fscanf(fileIn, "%f", &hoursWkd);

        // compare dept. names to find dept. end
        if(strcmp(dept, dept_old) && (deptGross != deptFica != deptNet != 0))
        {
            fprintf(fileOut, "\t\t\t%s\t    $%12.2f $%12.2f $%12.2f\n\n", "Department Totals:", deptGross, deptFica, deptNet);
            deptGross = deptFica = deptNet = 0;
        }
        strcpy(dept_old, dept);

        if(lineKt == maxLines)
        {
            NewPage(fileOut, pgTotals, &pageKt, cumTotals, &lineKt);
        }

        if(lineKt == 0)
            PrintDetailHeaders(fileOut);

        gross = CalculateGross(payrate, hoursWkd);
        pgGross += gross;
        deptGross += gross;

        fica = CalculateFICA(currFica, ficaLimit, ytd, gross);
        pgFica += fica;
        deptFica += fica;

        net = gross - fica;
        pgNet += net;
        deptNet += net;

        // Print line to file.
        fprintf(fileOut, "%-*d", 5, id);
        fprintf(fileOut, "%-*s", strw15, givenName);
        fprintf(fileOut, "%-*s", strw15, surname);
        fprintf(fileOut, "%-*s", 7, dept);
        fprintf(fileOut, " $%*.2f", strw12, ytd);
        fprintf(fileOut, " $%*.2f", strw12, gross);
        fprintf(fileOut, " $%*.2f", strw12, fica);
        fprintf(fileOut, " $%*.2f\n", strw12, net);

        lineKt++;
        numRecords++;
    }

    fprintf(fileOut, "\t\t\t%s\t    $%12.2f $%12.2f $%12.2f\n\n", "Department Totals:", deptGross, deptFica, deptNet);
    PrintClosing(fileOut, pgTotals, &pageKt, cumTotals, numRecords);

    // Close files
    fclose(fileIn);
    fclose(fileOut);
    fclose(fileFica);

    printf("%s\"%s\"\n", "Program has successfully completed and output results in ", fileOutName);

    return 0;  // Indicate success to the runtime environment.
}

void NewPage(FILE *p_file, float *p_pgTotals[3], int *p_pgKnt, float *p_totals[3], int *p_lnKnt)
{
    //add cumulative totals
    for (int i = 0; i < 3; i++)
    {
        *p_totals[i] += *p_pgTotals[i];
    }

    //create page footer
    fprintf(p_file, "\n\t\t\t\t%s\t    $%12.2f $%12.2f $%12.2f\n", "Page Totals:", *p_pgTotals[0], *p_pgTotals[1], *p_pgTotals[2]);
    fprintf(p_file, "\t\t\t\t\t\t\t\t\t\t\t%s%d", "Page ", *p_pgKnt);

    fprintf(p_file, "\f");
    *p_pgKnt += 1;
    *p_lnKnt = 0;

    //reset page totals
    for (int i = 0; i < 3; i++)
    {
        *p_pgTotals[i] = 0;
    }

    // new page with header info
    // fprintf(p_file, "%s", "\n\n\t\t\t\t\tACME Sports Inc.\n\n\n");
    // fprintf(p_file, "%s", "Emp# Given      Surname    Dept.             YTD         Gross          FICA           Net\n\n");
}

// title page and first detail headers
void PrintOpening(FILE *p_file, int *p_pgKnt)
{
    fprintf(p_file, "%s", "\n\n\n\n\t\t\t\t\tACME Sports Inc.\n");
    fprintf(p_file, "%s", "\n\n\t\t\t\"We are the best, you use the best!\"\n");

    fprintf(p_file, "\f");
    *p_pgKnt += 1;
    // fprintf(p_file, "%s", "\n\n\t\t\t\t\tACME Sports Inc.\n\n\n");
    // fprintf(p_file, "%s", "Emp# Given      Surname    Dept.             YTD         Gross          FICA           Net\n\n");
}



void PrintClosing(FILE *p_file, float *p_pgTotals[3], int *p_pgKnt, float *p_totals[3], int p_records)
{
    if(*p_pgTotals[0] != *p_pgTotals[1] != *p_pgTotals[2] != 0)
    {
        // add totals
        for (int i = 0; i < 3; i++)
        {
            *p_totals[i] += *p_pgTotals[i];
        }

        // print final page footer
        fprintf(p_file, "\n\t\t\t\t%s\t    $%12.2f $%12.2f $%12.2f\n", "Page Totals:", *p_pgTotals[0], *p_pgTotals[1], *p_pgTotals[2]);
        fprintf(p_file, "\t\t\t\t\t\t\t\t\t\t\t%s%d", "Page ", *p_pgKnt);
    }

    fprintf(p_file, "\f");

    //reset page totals 
    for (int i = 0; i < 3; i++)
    {
        *p_pgTotals[i] = 0;
    }

    // new page and print summary text
    *p_pgKnt += 1;
    fprintf(p_file, "%s", "\n\n\t\t\t\t\tReport Summary.\n\n\n");
    fprintf(p_file, "%s%d\n", "Records Processed: ", p_records);
    fprintf(p_file, "%-15s$%12.2f\n", "Total Gross: ", *p_totals[0]);
    fprintf(p_file, "%-15s$%12.2f\n", "Total Net: ", *p_totals[1]);
    fprintf(p_file, "%-15s$%12.2f\n", "Total FICA: ", *p_totals[2]);
    fprintf(p_file, "\t\t\t\t\t\t\t\t\t\t\t%s%d", "Page ", *p_pgKnt);
}

void PrintDetailHeaders(FILE *p_file)
{
    fprintf(p_file, "%s", "\n\n\t\t\t\t\tACME Sports Inc.\n\n\n");
    fprintf(p_file, "%s", "Emp# Given      Surname    Dept.             YTD         Gross          FICA           Net\n\n");    
}

float CalculateGross(float p_rate, float p_hrs)
{
    float total = 0;
    //pay for time
    total += p_rate * p_hrs;

    // plus half
    if(p_hrs > 40)
        total += (p_hrs - 40) * p_rate * 0.5;

    return total;
}

float CalculateFICA(float p_fica, float p_limit, float p_ytd, float p_gross)
{
    float owedTax = 0;
    if (p_ytd < p_limit){
        if (p_ytd + p_gross <= p_limit){
            //tax = total gross
            owedTax = p_gross * p_fica;
        }
        else{
            //tax = 110100 - ytd
            owedTax = (p_limit - p_ytd) * p_fica;
        }
    }
    //else no tax

    return owedTax;
}