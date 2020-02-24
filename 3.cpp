/*
Program Assignment: Program 3
Name:				Jorge René García Rosado
Date:				24/02/2020
Description:		This program reads two data source with a number on each line, then reads an estimated proxy size to calculate linear regression parameters
*/

/*
Listing contents:
	Program descriptions
	Listing contents
	Includes
	Source code in 3.cpp
		double getDataRow()
		double getAcum()
		double getAverage()
		double getPow2()
		double multiplyDatasets()
		int main()
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

vector<double> data1;
vector<double> data2;
double estProxy;
double acumData1;
double acumData2;
int n;

double avgData1;
double avgData2;
double pow2Data1;
double pow2Data2;
double d1timesd2;

double b0;
double b1;
double rxy;
double r2;
double yk;

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

double getPow2(vector<double> dataset) //FUNCTION >
{
	double acum = 0;
	for(int row=0;row<dataset.size();row++)
	{
		acum += dataset[row] * dataset[row];
	}
	return acum;
} //< FUNCTION

double multiplyDatasets(vector<double> dataset1, vector<double> dataset2) //FUNCTION >
{
	double acum = 0;
	for(int row=0;row<dataset1.size();row++)
	{
		acum += dataset1[row] * dataset2[row];
	}
	return acum;
} //< FUNCTION

int main(int argc, char *argv[]) //FUNCTION >
{ 
	
	data1 = getDataRow();
	data2 = getDataRow();
	cout<<"What is the estimated proxy size?"<<endl;
	cin>>estProxy;
	n=data1.size();
	avgData1 = getAverage(data1);
	avgData2 = getAverage(data2);
	acumData1 = getAcum(data1);
	acumData2 = getAcum(data2);
	pow2Data1 = getPow2(data1);
	pow2Data2 = getPow2(data2);
	d1timesd2 = multiplyDatasets(data1,data2);
	
	b1 = ((d1timesd2)-(n*avgData1*avgData2))/((pow2Data1)-(n*(avgData1*avgData1))); //OK
	b0 = avgData2 - b1*avgData1;
	rxy = n*(d1timesd2)-(acumData1 * acumData2);
	rxy = rxy / ( sqrt((n*pow2Data1 - pow(acumData1,2.0) ) * (n*pow2Data2 - pow(acumData2,2.0))) );
	r2 = pow(rxy,2.0);
	yk = b0 + b1*estProxy;
	
	cout<<setw(15)<<"b0"<<setw(15)<<"b1"<<setw(15)<<"rx,y"<<setw(15)<<"r2"<<setw(15)<<"yk"<<endl<<endl;
	cout<<setw(15)<<b0<<setw(15)<<b1<<setw(15)<<rxy<<setw(15)<<r2<<setw(15)<<yk<<endl;
	
	return 0;
} //< FUNCTION
