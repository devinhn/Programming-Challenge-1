#include "stdafx.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>


using namespace std;


//Function prototypes.
void initializeYearCount();
void printCounts();
void modeYears();


//Initialize year array for 1900-2000.
int yearCount[2][101];


int main()
{
	//Open data set.
	ifstream dataSet("C:\\Data\\data.txt");
	string lineInput;
	string name;	
	cout << "Loading file.\n";


	//Create array of years and their occurances.
	initializeYearCount();
	

	//Create structure to handle file contents.
	struct bio
	{
		string nameGiven;
		int birthYear;
		int deathYear;
	};

	bio Person;
	

	//Create array to store information in. This will be used to parse the file into the structure.
	string information[3];
	

		//Read file and assign attributes to Person structure.
		while (getline(dataSet, lineInput))		//Read each file line into lineInput.
		{
			stringstream ss(lineInput);			//Stream used to parse data.

			string token;
			for (int r = 0; r <= 3; r++)
			{
				while (getline(ss, token, ','))		//Loop used to parse data using comma as delimeter.
				{
					information[r] = token;		//Store each piece of information from file in a separate part of the array.
					r++;
				}

				//Pass file lines into structure.
				Person.nameGiven = information[0];		//Storing name from file; this is not used later, as it is not needed.

				stringstream convertbirthYear(information[1]);		//Stream to convert string from file read process to integer.
				convertbirthYear >> Person.birthYear;		//Storing birth year from file in structure.

				stringstream convertdeathYear(information[2]);		//Stream to convert string from file read process to integer.
				convertdeathYear >> Person.deathYear;		//Storing death year from file in structure.

			
				//Tally alive years for each line of the file.
				int aliveYear = Person.birthYear;

				for (aliveYear; aliveYear <= Person.deathYear; aliveYear++)
				{				
					for (int q=0; q <= 101; q++)
					{
						if (yearCount[1][q] == aliveYear)
						{
							yearCount[2][q]++;
						}
					}
				}
			}
		}
//Call the function to process data and determine mode of people alive, store appropriate years in an array, and print to screen.
	modeYears();

//Ask if user would like to see data output.
	bool showCount = false;
	while (showCount == false)
	{
		cout << "Would you like to see the count for each year from 1900 to 2000? (y/n) \n"; //Ask user for input
		char response;
		cin >> response;
		if (response == 'y' || response == 'Y') 
		{
			printCounts();
			showCount = true; //Cause exit of while loop
		}

		else if (response == 'n' || response == 'N')
		{
			showCount = true; //Cause exit of while loop
		}

		else
		{
			cout << "Please only enter y or n. \n";		//Error message if user input is unclear
		}
	}
	//Close data file
	dataSet.close();


	//Ask user to exit
	cout << "Close this window to exit.";
	system("pause>nul");
	

	return 0;
}


//Function to create array the array that is used for storing years and couning the number of people alive each year. 
void initializeYearCount()
{
	int year = 1900;
	int b = 0;

	for (b, year; b <= 100, year <= 2000; b++, year++)		//Loop fills the array. The variable b is used to keep track of the column.
	{
		yearCount[1][b] = year;		//Give each column a year from 1900 to 2000.
		yearCount[2][b] = 0;		//Set each column in the second row to 0 to ensure all counts start at 0.
	}
}


//Function to print the data of years and their respective counts.
void printCounts()
{
	cout << "Year\tNumber Alive\n";		//Used to align the data nicely.
	for (int w=0; w<=100; w++)
	cout << yearCount[1][w] << "\t" << yearCount[2][w] << "\n";		//Print the data from the storage array.
}


//Function used to calculate what years occured the most frequently (mode), and print the results.
void modeYears()
{
	int modeArray[101] = {0};		//Array to store years which had the highest count.
	
	int counter=0;		//Counter used to determine the array. This stores the highest count seen in the data set.

	//Get highest count
	for (int c = 0; c <= 100; c++)		//Run through the yearCount array to determine the highest count year(s).
	{
		if (yearCount[2][c] >= counter)		
		{
			counter = yearCount[2][c];		//Set the highest count.
		}
	}
	cout << "The following years each had " << counter << " people alive. \n";  //Report the number of times the mode year(s) occured.


	//Populate modeArray with years which match the mode count
	for (int d = 0; d <= 100; d++)		//Now that the mode is determined, this loop runs through the data again, only looking for
	{									//years that have the highest count (mode).

		if (yearCount[2][d] == counter)
		{
			modeArray[d] = yearCount[1][d];		//Stores highest frequency years in an array.
			cout << modeArray[d] << "\n";		//Prints array of highest frequency years to screen.
		}
	}
}