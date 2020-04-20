/*
Program Assignment: Program 6
Name:				Jorge René García Rosado
Date:				13/04/2020
Description:		This program integrates a fuction using Simpsons's rule with the t distribution as function, and estimating the value of x, receiving a value of p and a value of Degres of Freedom (dof)
*/

/*
Listing contents:
	Program descriptions
	Listing contents
	Includes
	Source code in 6.cpp
		double gamma()
		double f()
		double getPValue()
		double readDoubleValue()
		double isPositive()
		int main()
*/
//NEW >
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <iomanip>
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
double readDoubleValue(string txt) //FUNCTION >
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

double getP(double x, double dof)
{
	double p1;
	double p2;
	double diff;
	double w;
	double num_seg = 10.0;
	double E = .000000001;
	bool isValid = false;
	bool repeat = false;
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
	return p2;
}

int main(int argc, char *argv[]) //FUNCTION >
{
	double p = readDoubleValue("p");
	double dof = readDoubleValue("degrees of freedom");
	double e = 0.000000001;
	double x = 1;
	double delta = .5;
	int runs = 0;
	bool flag = true;
	bool prevSign;
	double pCalc = 0;
	double eCalc;
	
	while(flag)
	{
		pCalc = getP(x,dof);
		if(fabs(p - pCalc) <= e)
		{
			flag = false;
		}
		else
		{
			eCalc = p - pCalc;
			if(runs == 0)
			{
				if(pCalc < p)
				{
					x+=delta;
				}
				else
				{
					x-=delta;
				}
			}
			else
			{
				if(isPositive(eCalc) != prevSign)
				{
					delta = delta / 2;
				}
				if(pCalc < p)
				{
					x+=delta;
				}
				else
				{
					x-=delta;
				}
			}
			
			if(isPositive(eCalc))
			{
				prevSign = true;
			}
			else
			{
				prevSign = false;
			}
			
			runs++;
		}
	}
	cout<<"x = "<<x<<endl;
	return 0;
} //< FUNCTION
//< NEW
