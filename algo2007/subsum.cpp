// algo.cpp : 169
//

#include "stdafx.h"
#include <vector>
#include <stdio.h>
#include <fstream>
#include "iostream"
#include <time.h>
#include <conio.h>
#include <time.h>
///////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////////////////
short				  *data;   // array of input data
size_t			  *indexes;// store the last storeVect pos where current number is found
size_t			  dataSize;// size of this array
short				  sum;	  //  required sum
size_t            elNum;  //  required elements number
std::vector <short> intVect;// vector for storing sums
std::vector <std::vector <short> >storeVect;//vector for storing in sum integers
char* backups[] = {"c:\\tmp\\backup.txt", "c:\\tmp\\backup2.txt"};
int lastBackup = 0;

///////////////////////////////////////////////////////////////////////
//read data from file
//---------------------------------
void readInfo(char* dataFileName, size_t iter)
{
	ifstream dataFile;
	if(dataFileName == NULL)
		dataFileName = "c:\\tmp\\data.txt";
	dataFile.open(dataFileName);
	ofstream	backup;
	if(iter == 1)
		backup.open(backups[lastBackup]);
	dataFile >> dataSize;
	data     = new short[dataSize];
	indexes  = new size_t[dataSize];
	if(iter == 1)
		backup  << 1 << " ";
	for(size_t i = 0; i < dataSize; i++)
	{
		dataFile   >> data[i];
		indexes[i] =  i;
		if(iter == 1)
			backup << i << " "; 
	}
	backup.close();
	dataFile.close();
}
/////////////////////////////////////////////////////////////
void countSum(size_t k)
{
	ofstream	backup;
	ifstream	fromBackup;
	if(k % 2 == 0)
	{
		backup.open(backups[0]);
		fromBackup.open(backups[1]);
		lastBackup = 1;
	}
	else
	{
		lastBackup = 0;
		backup.open(backups[1]);
		fromBackup.open(backups[0]);
	}
	short ind = (short)k + 1;
	backup << ind << " ";
	fromBackup >> ind;
	while(!fromBackup.eof())
	{
		string toFile = "";
		intVect.clear();
		for(size_t i = 0; i < k; i++)
		{
			fromBackup >> ind;
			intVect.push_back(ind);
		}
		for(size_t i = (size_t)intVect[k - 1] + 1; i < dataSize; i++)
		{
			for(size_t j = 0; j < k; j++)
			{
				backup << intVect[j] << " ";
				backup << i << " ";
			}
		}
	}
	if(k % 2 == 0)
		lastBackup = 0;
	else
		lastBackup = 1;
	backup.close();
	fromBackup.close();
}
////////////////////////////////////////////////////////////////
size_t restoreFromBackUp()
{
	ifstream readF;
	short iter = 1;
	short loc; 
	readF.open(backups[0]);
	if(readF.is_open())
	{
		readF >> iter;
	}
	readF.close();
	readF.open(backups[1]);
	if(readF.is_open())
	{
		readF >> (short)loc;
		if(iter > loc)
		{
			iter = loc;
			lastBackup = 1;
		}
	}
	readF.close();
	return (size_t)iter;
}
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	time_t seconds_start; //подсчёт времени
	time_t seconds_end;
	//prepair start data
	if(argc < 3)
	 {
		 printf("Error: application needs at least 2 args to work:\n1st - required sum\n2nd - elements number\n");
		return -1;
	}
	// first arg - sum; second - number of integers
	sum   = atoi(argv[1]);
	elNum = atoi(argv[2]);
	if(elNum <= 0)
	{
		printf("Error: elements number must be > 0\n");
		return -1;
	}
	seconds_start = time(NULL);
	size_t iter = restoreFromBackUp();
	readInfo((argc > 3) ? argv[3] : NULL, iter);
	if(elNum > dataSize)
	{
		printf("\nSet doesn't exist. You want to have %d elements in subset while there are only %d in set...\n", elNum, dataSize);
		return 0;
	}
	//-------------------------------------
	for(size_t k = iter; k < elNum; k++)
		countSum(k);
	
	delete indexes;
	bool end  = false;
	bool good = false;
	short num;
	ifstream	fromBackup;
	fromBackup.open(backups[lastBackup]);
	while(!end)
	{
		intVect.clear();
		long sumFrom = 0;
		for(size_t i = 0; i < elNum; i++)
		{
			fromBackup >> num;
			intVect.push_back(num);
			sumFrom += data[num];
		}
		if(sumFrom == sum)
			good = true;
		if(fromBackup.eof() || good)
			end = true;
	}
	fromBackup.close();
	if(good)
	{
		printf("\nSet exists: ");
		for(size_t j = 0; j < intVect.size(); j++)
			printf("%d ", data[intVect[j]]);
		printf("\n");
	}
	else
		printf("\nSet doesn't exist\n");
	delete data;
	seconds_end = time(NULL);
	cout<<"\nTime of Computation : " << seconds_end - seconds_start << endl;
	ifstream	f;
	f.open(backups[0]);
	f.close();
	f.open(backups[1]);
	f.close();
	
	return 0;
}
////////////////////////////////////////////////////////////////////
