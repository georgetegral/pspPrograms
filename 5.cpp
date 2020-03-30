/*
Program Assignment: Program 5
Name:				Jorge René García Rosado
Date:				30/03/2020
Description:		This program integrates a fuction using Simpsons's rule with the t distribution as function, receiving a value of x and a value of Degres of Freedom (dof)
*/

/*
Listing contents:
Program descriptions
Listing contents
Includes
Source code in 5.cpp
	double gamma()
	double f()
	double getPValue()
	int main()
*/
//NEW >
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

double gamma(double x) //FUNCTION >
{
	if( x == 1.0 )
	{
		return 1;
	}
	else if (x == 0.5)
	{
		return sqrt(M_PI);
	}
	else
	{
		return (x-1)*gamma(x-1);
	}
} //< FUNCTION

double f(double x, double dof) //FUNCTION >
{
	double result = gamma((dof+1)/2);
	result = result / ( pow (dof *  M_PI, 0.5) * gamma(dof/2) );
	result =  result * pow ( 1 + (pow(x,2.0)/dof), ((dof+1)*-1)/2 );
	return result;
} //< FUNCTION

double getPValue(double w, double num_seg, double dof) //FUNCTION >
{
	double result = 0;
	double tmpVal = 0;
	result += (f(0,dof) * (w/3) );
	for(int i = 1; i <= num_seg - 1 ; i++)
	{
		if(i % 2 != 0)
		{
			tmpVal = (f(w * i,dof) * (w/3) * 4 );
			result+=tmpVal;
		}
		else
		{
			tmpVal = (f(w * i,dof) * (w/3) * 2 );
			result+=tmpVal;
		}
	}
	tmpVal = (f(w * num_seg,dof) * (w/3) );
	result += tmpVal;
	return result;
} //< FUNCTION

int main(int argc, char *argv[]) //FUNCTION >
{
	double p1;
	double p2;
	double diff;
	double x;
	double dof;
	double w;
	double num_seg = 10.0;
	double E = .00001;
	bool isValid = false;
	bool repeat = false;
	cout<<"What is the value of x?"<<endl;
	cin>>x;
	cout<<"What is the value for the degrees of freedom?"<<endl;
	cin>>dof;
	w = x / num_seg;
	while (!isValid)
	{
		if(!repeat)
		{
			p1 = getPValue(w,num_seg,dof);
		}
		num_seg = num_seg * 2;
		w = x / num_seg;
		p2 = getPValue(w,num_seg,dof);
		diff = abs(p1 - p2);
		if( diff < E )
		{
			isValid = true;
		}
		else 
		{
			repeat = true;
			p1 = p2;
		}
	}
	cout<<"P="<<p2<<endl;
	return 0;
} //< FUNCTION
//< NEW
