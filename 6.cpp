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
//< NEW
//REUSED >
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
//< REUSED
//NEW >
double readValue(string txt) //FUNCTION >
{
	double val = 0;
	while (val<=0)
	{
		cout<<"What is the value of "<<txt<<" ?"<<endl;
		cin>>val;
		if(val<=0)
		{
			cout<<"The value of "<<txt<<" should be greater than 0"<<endl;
		}
	}
	return val;
} //< FUNCTION

bool isPositive(double num) //FUNCTION >
{
	if(num >= 0)
	{
		return true;
	}
	else if(num < 0)
	{
		return false;
	}
} //< FUNCTION

int main(int argc, char *argv[]) //FUNCTION >
{
	double p = readValue("p");
	double dof = readValue("degrees of freedom");
	double num_seg = 10;
	double x = 1;
	double E = 1;
	double eAbs = 1;
	double delta = .5;
	bool prevSign = true;
	bool firstRun = true;
	double w;
	double pCalc;
	while ( eAbs > .00001 )
	{
		w = x / num_seg;
		pCalc = getPValue(w,num_seg,dof);
		E = p - pCalc;
		eAbs = abs(p - pCalc);
		if( p != pCalc )
		{
			if(firstRun)
			{
				if(isPositive(E))
				{
					x = x + delta;
				}
				else
				{
					x = x - delta;
				}
				firstRun = false;
			}
			else
			{
				if(isPositive(E) != prevSign)
				{
					delta = delta / 2;
				}
				if(isPositive(E))
				{
					x = x + delta;
				}
				else
				{
					x = x - delta;
				}
			}
		}
	}
	cout<<"X= "<<x<<endl;
	return 0;
} //< FUNCTION
//< NEW
