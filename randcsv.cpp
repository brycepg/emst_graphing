/*
 * randcsv.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: rick
 */

#include <time.h>
#include <random>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//seed random function
	srand(time(NULL));
	//create random number variable
	double number=0;
	//create matrix parameters
	int rows=0, cols=0, rangeMin=0, rangeMax=0;
	//name to save the CSV file under
	string fileName;

	//ask for and store data
	cout << "How many rows are there?: ";
	cin >> rows;
	cout << "How many columns are there?: ";
	cin >> cols;
	cout << "What is the minimum range of the data set?: ";
	cin >> rangeMin;
	cout << "What is the maximum range of the data set?: ";
	cin >> rangeMax;
	cout << "Enter a filename to save this data under: ";
	cin >> fileName;

	//add .csv to the end of the filename
	fileName = fileName + ".csv";

	//create a file to save data to
	ofstream outFile;
	outFile.open(fileName.c_str());

	//write comma separated values to file
	for(int count1 = 0; count1 < rows; count1++)
	{
		for(int count2 = 0; count2 < cols; count2++)
		{
			//store random value in the number variable
			number = rand() %(rangeMax-rangeMin) + rangeMin;
			//write the random number to file
			if(count2 == cols-1)
			{
				outFile << number;
			}
			else
			{
				outFile << number << ", ";
			}
		}
		if(count1<rows-1)
			outFile << endl;
	}
	outFile.close();
}
