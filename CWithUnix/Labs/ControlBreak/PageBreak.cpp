/*
   in file PageBreak.cpp – Use of Microsoft C++ translator.
   This program demonstrates a page control break and
   some formatting.

   Author:  Sam The Man
   Date Written: January 15, 2020
   Last Modified:
      By:  D. Burris
	  Date:   February 23, 2021
	  Reason: Gross pay corrected to eliminate overtime.

  Open the report in a word processor such as MS-Word
  to print (allows for page breaks to occur, "Notepad" does not
  recognize "\f" ).  Set the font to a fixed point such as 
  Courier New with a point size of 10.
  
  Sample data is in file PageBreak.txt.
*/

#include <fstream.h>    // fstream.h contains file sequential IO methods.
#include <iostream.h>  // iostream.h contains keyboard / screen IO methods.
#include <stdlib.h>       // stdlib.h contains the exit method.
#include <iomanip.h>   // needed for setw 

int main( ){

	ifstream fileIn;              // Logical output file name in program.
	char fileInName[15];    // Actual path and file name on disk.

	ofstream fileOut;
	char fileOutName[20];

	fileOut.setf(ios::fixed);   //Print parameters in report file.
	fileOut.setf(ios::showpoint);
	fileOut.precision(2);

cout.setf(ios::fixed);     // Set the format for printing real numbers
	cout.setf(ios::showpoint);  // on the CRT.
	//cout.setf(ios::showpos); // Show sign of number.
	cout.precision(2);  //print with two digits to right of decimal point

	cout << "Enter the name of the input file [max 15 characters]: ";
	cin >> fileInName;
	fileIn.open( fileInName );
	if( fileIn.fail( ) ){ 
		cout << "Input file does not exist! Program terminating.";
		exit(1);  // exit(0) indicates program success, exit(1) failure.
	}

	cout << "Enter the name of the file to hold the results [max 20 characters]: ";
	cin >> fileOutName;
	fileOut.open( fileOutName );
	if( fileOut.fail( ) ){
		cout << "Could not create the output file! Program terminating.";
		exit(1);
	}

	cout << endl;

// Program Initializations
char givenName[10];  //First name
	char surname[10];    //Last name
	float hoursWkd, payrate, gross;
	int lineKt = 0;      //Line counter.
	int pageKt = 0;      //Page counter.
// Obtain information from file and calculate the payroll.
	while( fileIn >> givenName >> surname 
		>> payrate >> hoursWkd ){

		if(lineKt == 0 || lineKt == 5){ // Write page headings.
			pageKt++;
			fileOut <<"\f\n\n\t\t\tACME Tools\t\t\tPage "
			<< pageKt << "\n\n\n";
			fileOut << "     Given         Surname           Hours    Pay Rate       Gross\n\n";
			lineKt = 0;
		}
		
		gross = payrate * hoursWkd;
		lineKt++;

		//Print on screen.  This is not necessary and would not normally be done.
		cout << setw(15) << givenName;
		cout << setw(15) << surname;

		cout << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << hoursWkd;

		cout << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << payrate;

		cout << " $" << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << gross << endl;

		// Print to file. 
		fileOut << setw(15) << givenName;
		fileOut << setw(15) << surname;
		
		fileOut << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << hoursWkd;

		fileOut << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << payrate;

		fileOut << setw(12) 
		<< setiosflags(ios::right | ios:: adjustfield)
		<< setprecision(2) << gross << endl;


} // end while loop

fileIn.close( );
fileOut.close( );

return 0;  // Indicate success to the runtime environment.
}