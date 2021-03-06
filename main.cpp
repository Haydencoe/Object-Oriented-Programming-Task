// COEH-309219-CMP2090M-1 main.cpp : Defines the entry point for the console application.
//Hayden Coe 309219
//Object-Orinated Programming, CMP2090M-1

#include <tchar.h>
#include <sstream> 
#include <iostream> 
#include <fstream> 
#include <istream>
#include "BinaryImage.h"
#include "Matrix.h"

#undef main

using namespace std;

// Reads .txt files in R rows and C Columns to be stored in filename then converts it to a 1D array of doubles of size R*C
double* readText(const char *fileName, int sizeR, int sizeC);

void WritePGM(const char *filename, double *data, int sizeR, int sizeC, int Q); //Writes out the files

double sumSquaredDiffs(Matrix unshuffled, Matrix shuffled, int M, int N); //SSD method declaration

void NNS(BinaryImage unshuffled_image, BinaryImage shuffled_image); //NNS method declaration

void NC(BinaryImage unshuffled_image, BinaryImage shuffled_image); //NC method declaration


int main()
{
	bool run = true; 
	int userInterface = 0;
	
	int M = 512; 
	int N = 512;
	
	double* input_data = 0;
	double* noisy_image = 0;

	cout << endl;

	// .pgm image is stored in inputFileName
	 const char* inputFileName = "logo_shuffled.txt";
	 const char* inputFileName2 = "logo_with_noise.txt";

	
    input_data = readText(inputFileName, M, N); // Reads in shuffled logo .txt file
	cout << endl;
	noisy_image = readText(inputFileName2, M, N); // Reads in noisy logo .txt file
	cout << endl;
	

	// Store the images in Binary Images to be used in NNS later
	BinaryImage shuffledImage(M, N, input_data, 170);
	BinaryImage noisyImage(M, N, noisy_image, 170);


	// Runs the user interface in the program for the user to choose how to unshuffle.
	while (run)
	{
		cout << "How would you like to unshuffle the image?";
		cout << endl;
		cout << "1: for SSD" << endl << "2: for NC" << endl << "3: for Both" << endl << "0: to Exit" << endl;
		
		cin >> userInterface;
		switch (userInterface)
		{
		case 0:
			run = false;
			break;
		case 1:
			NNS(noisyImage, shuffledImage);//Calls NNS SSD
			break;
		case 2:
			NC(noisyImage, shuffledImage);//Calls NNS NC
			break;
		case 3:
			NNS(noisyImage, shuffledImage);//Calls NNS SSD
			NC(noisyImage, shuffledImage);//Calls NNS NC
			break;
		
		}
	}

	delete[] input_data;
	delete[] noisy_image;// clean memory

	cout << endl;
	cout << endl << "Please press the enter key to finish the program" << endl; //Exits the program
	cin.get();

	return 0;
}



// Read .txt file with image of size RxC, and converted to an array of doubles
double* readText(const char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int userTextDisplay = 0;
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		
		cout << "File: " << fileName << " opened successfully!" << endl;

		cout << endl;
		cout << "Would you like to display the converted data from: " << fileName << " on screen? ";
		cout << endl;
		cout << "1: for yes" << endl << "2: for No" << endl;
		cin >> userTextDisplay; 
		//Code to allow the user to display the converted that has been read in on screen
		switch (userTextDisplay)
		{
		case 1:
			cout << endl;
			cout << "The data that was read in from the text file: " << endl;
		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			
			
			cout << *(data + i) << ' '; 
			i++;
		}
		myfile.close();
	
		break;
		
		case 2:
			while (myfile.good())
			{
				if (i>sizeR*sizeC - 1) break;
				myfile >> *(data + i);
				i++;
			}
			myfile.close();

			break;

		}

	}

	else cout << "Unable to open file: " << fileName << ", something went wrong!" << endl; //Error reading in catching
	
	return data; //data read in returned
}


// The function for the summed squared difference NNS.
void NNS(BinaryImage unshuffled_image, BinaryImage shuffled_image)
{
	// Empty image for overwriting and returning
	BinaryImage tempImage(512, 512);

	// Size of the matrix
	int M = 512;
	int N = 512;

	// Set of start/end values for the block from the unshuffled noisy_image
	int sColomnOne = 0;
	int sRowOne = 0;
	int counterOne = 0;

	// Set of values for the blocks from the shuffled_image
	int sColomnTwo = 0;
	int sRowTwo = 0;
	int counterTwo = 0;
	int tCount;


	for (int i = 0; i < 256; i++)
	{
		sColomnTwo = 0;
		sRowTwo = 0;

		// The best matching block based on the SSD value
		Matrix bestB;
		Matrix currentB;
		double SSD = 5000;
		double bestSumSD = 5000;
		int cPosition, rPosition; //coloumn and row position variables 
		tCount = 0;

		// if reached end of the row
		if (counterOne < 16)
		{
			// 272 for skipping 15 values to start new rows.
			for (int j = 0; j < 272; j++)
			{
				// if end of the colomn is reached
				if (counterTwo < 16)
				{
					// current block is compared to the noisy one
					currentB = shuffled_image.getBlock(sColomnTwo, sColomnTwo + 31, sRowTwo, sRowTwo + 31);
					SSD = sumSquaredDiffs(unshuffled_image.getBlock(sColomnOne, sColomnOne + 31, sRowOne, sRowOne + 31), currentB, 32, 32);

					// Move along
					sColomnTwo += 32;
					counterTwo++;
				}
				// start again
				else
				{
					counterTwo = 0;
					sColomnTwo = 0;
					sRowTwo += 32;

				}
				// The first comparision becomes the best block by default
				if (j == 0)
				{
					bestSumSD = SSD;
					bestB = currentB;
					cPosition = sColomnTwo;
					rPosition = sRowTwo;
				}
				
				// if better match
				if (SSD <= bestSumSD)
				{
					bestSumSD = SSD;
					bestB = currentB;
					cPosition = sColomnTwo;
					rPosition = sRowTwo;
				}
				tCount++;
			}
			
			tempImage.setBlock(bestB, sColomnOne, sRowOne); //tempImage storing

		}
		else
		{
			// The column resets move row along by increasing by 32
			counterOne = 0;
			sColomnOne = 0;
			sRowOne += 32;
		}
		counterOne++;
		sColomnOne += 32;
	}


	WritePGM("logo_unshuffled_SSD.pgm", tempImage.getData(), M, N, 1); //writes out the completed sorted image.
	
}

//	The code for the SSD takes the two blocks given then subracts one from the other one. 
double sumSquaredDiffs(Matrix unshuffled, Matrix shuffled, int M, int N)
{
	double SSD = 0;
	Matrix temp(32, 32);

	temp = unshuffled - shuffled;
	double* tempArray = temp.getData();
	for (int i = 0; i < M * N; i++)
	{
		double temp = (tempArray[i] * tempArray[i]);
		SSD += temp;
	}

	return SSD;//returns the sum of the squared values from the subtraction.
}


// The function for the Normalised Correlation NNS.
void NC(BinaryImage unshuffled_image, BinaryImage shuffled_image)
{
	int M = 512; 
	int N = 512;

	// Empty image for overwriting 
	BinaryImage returnImage(M, N);
	
	Matrix shuffBlock; 
	Matrix unshuffBlock;
	
	int sRow;
	int sColomn;

	double NC = -1; double current = 0;

	for (int cOne = 0; cOne < 512; cOne += 32)
		for (int cTwo = 0; cTwo < 512; cTwo += 32)
		{
			unshuffBlock = unshuffled_image.getBlock(cOne, cOne + 31, cTwo, cTwo + 31);
			NC = -1;
			
			for (int sOne = 0; sOne < 512; sOne += 32)
				
				for (int sTwo = 0; sTwo < 512; sTwo += 32)
				{
					shuffBlock = shuffled_image.getBlock(sOne, sOne + 31, sTwo, sTwo + 31);
					current = shuffBlock.NC(unshuffBlock);
					
					if (current > NC)
					{
						unshuffled_image.setBlock(shuffBlock, cOne, cTwo);
						sRow = cOne;
						sColomn = cTwo;

						NC = current; if (NC == 1) { break; }
					}
					
					if (NC == 1) { break; }
				}
			
		}
	
	WritePGM("logo_unshuffled_NC.pgm", unshuffled_image.getData(), M, N, 1); //writes out the completed sorted image.
	
}


// convert data from double to .pgm stored in filename read for viewing
void WritePGM(const char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i, j;
	unsigned char *image;
	ofstream myfile;

	j = 0;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];
    // converts the int values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC) * sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;//Cleans memory
	
	cout << filename << " file has been created and saved successfully!" << endl;
	cout << endl;
}

