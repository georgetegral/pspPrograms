/*
Program Assignment: Program 4
Name:				Jorge René García Rosado
Date:				27/02/2020
Description:		This program reads two data sources with a number on each line, then calculates the standard deviation and makes ranges of stardard deviations ranging from
Very Small, Small, Medium, Large and Very Large
*/

/*
Listing contents:
	Program descriptions
	Listing contents
	Includes
	Source code in 4.cpp
		double getDataRow()
		double getAcum()
		double getAverage()
		double getAverageForEach()
		double getLn()
		double getLnMinusAvg()
		int main()
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

//REUSED >
vector<double> getDataRow() //FUNCTION >
{
	string name;
	string line;
	double value;
	vector<double> tmpVector;
	cout<<"What is the name of the datasource?"<<endl;
	cin>>name;
	ifstream program(name);
	while(getline(program,line))
	{
		value = atof(line.c_str());
		tmpVector.push_back(value);
	}
	return tmpVector;
} //< FUNCTION

double getAcum(vector<double> dataset) //FUNCTION >
{
	double acum = 0;
	for(int row=0;row<dataset.size();row++)
	{
		acum+=dataset[row];
	}
	return acum;
} //< FUNCTION

double getAverage(vector<double> dataset) //FUNCTION >
{
	return getAcum(dataset)/dataset.size();
} //< FUNCTION
//< REUSED

vector<double> getAverageForEach(vector<double> dataset1, vector<double> dataset2) //FUNCTION >
{
	double value = 0;
	vector<double> tmpVector;
	for(int row=0;row<dataset1.size();row++)
	{
		value = dataset1[row] / dataset2[row];
		tmpVector.push_back(value);
	}
	return tmpVector;
} //< FUNCTION

vector<double> getLn(vector<double> dataset) //FUNCTION >
{
	double value = 0;
	vector<double> tmpVector;
	for(int row=0;row<dataset.size();row++)
	{
		value = log(dataset[row]);
		tmpVector.push_back(value);
	}
	return tmpVector;
} //< FUNCTION

vector<double> getLnMinusAvg(vector<double> dataset,double avg) //FUNCTION >
{
	double value = 0;
	vector<double> tmpVector;
	for(int row=0;row<dataset.size();row++)
	{
		value = pow(dataset[row] - avg,2.0);
		tmpVector.push_back(value);
	}
	return tmpVector;
} //< FUNCTION

int main(int argc, char *argv[]) { //FUNCTION >
	
	vector<double> data1 = getDataRow();
	vector<double> data2 = getDataRow();
	vector<double> avgDatas = getAverageForEach(data1,data2);
	vector<double> lnAvgVector = getLn(avgDatas);
	double acumLn = getAcum(lnAvgVector);
	double avg = acumLn / data1.size();
	vector<double> lnMinusAvg = getLnMinusAvg(lnAvgVector,avg);
	double lnAvg = getAcum(lnMinusAvg);
	double var = lnAvg / (data1.size()-1);
	double stdDev = sqrt(var);
	
	const double euler = exp(1.0);
	
	double vs = pow(euler,avg - 2 * stdDev);
	double s = pow(euler,avg - stdDev);
	double m = pow(euler,avg);
	double l = pow(euler,avg + stdDev);
	double vl = pow(euler,avg + 2 * stdDev);
	
	cout<<"VS:"<<vs<<endl;
	cout<<"S:"<<s<<endl;
	cout<<"M:"<<m<<endl;
	cout<<"L:"<<l<<endl;
	cout<<"VL:"<<vl<<endl;
	
	return 0;
} //< FUNCTION

