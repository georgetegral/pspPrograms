/*
Program Assignment: Program 2
Name:				Jorge René García Rosado
Date:				17/02/2020
Description:		This program reads a program and counts its size based on my personal counting standard and displays
part name, number of items for each part, part size and total size.
*/

/*
Listing contents:
	Program descriptions
	Listing contents
	Includes
	Source code in 2.cpp
		bool endsWith()
		int main()
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool endsWith(const string &mainStr, const string &toMatch) //FUNCTION >
{
	if(mainStr.size() >= toMatch.size() &&
	   mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
		return true;
	else
		return false;
} //< FUNCTION

int main(int argc, char *argv[]) //FUNCTION >
{
	ifstream program("3.cpp");
	string line;
	
	vector<string> parts;
	vector<int> numberOfItems;
	vector<int> partSize;
	int totalSize = 0;
	string previousLine = "";
	
	bool countLine = false;
	bool inComment = false;
	bool inPart = false;
	bool inItem = false;
	int partLines = 0;
	int partItems = 0;
	int numberOfParts = 0;
	
	bool inErased = false;
	bool inModified = false;
	bool inNew = false;
	bool inReused = false;
	
	int erasedNum = 0;
	int modifiedNum = 0;
	int newNum = 0;
	int reusedNum = 0;
	
	while(getline(program,line))
	{
		if(line.find_first_not_of(' ') != string::npos && line.find_first_not_of('\t') != string::npos) //Ignore line if it is empty space
		{
			
			if (line.find("//ERASED >") != string::npos && endsWith(line,"//ERASED >"))
			{
				countLine = false;
				inComment = true;
				inErased = true;
			}
			else if (line.find("/*") != string::npos && endsWith(line,"/*"))
			{
				countLine = false;
				inComment = true;
			}
			else if (previousLine.find("*/") != string::npos && endsWith(previousLine,"*/"))
			{
				if (line.find("/*") != string::npos && endsWith(line,"/*"))
				{
					countLine = false;
				}
				else if (line.find("//< ERASED") != string::npos && endsWith(line,"//< ERASED"))
				{
					countLine = false;
				}
				else if (line.find("//MODIFIED >") != string::npos && endsWith(line,"//MODIFIED >"))
				{
					countLine = false;
				}
				else if (line.find("//< MODIFIED") != string::npos && endsWith(line,"//< MODIFIED"))
				{
					countLine = false;
				}
				else{
					countLine = true;
				}
				inComment = false;
			}
			else if (previousLine.find("//< ERASED") != string::npos && endsWith(previousLine,"//< ERASED"))
			{
				if (line.find("/*") != string::npos && endsWith(line,"/*"))
				{
					countLine = false;
				}
				else if (line.find("//ERASED >") != string::npos && endsWith(line,"//ERASED >"))
				{
					countLine = false;
				}
				else if (line.find("//MODIFIED >") != string::npos && endsWith(line,"//MODIFIED >"))
				{
					countLine = false;
				}
				else if (line.find("//< MODIFIED") != string::npos && endsWith(line,"//< MODIFIED"))
				{
					countLine = false;
				}
				else{
					countLine = true;
				}
				inComment = false;
			}
			else if (line.find("//MODIFIED >") != string::npos && endsWith(line,"//MODIFIED >"))
			{
				countLine = false;
			}
			else if (line.find("//< MODIFIED") != string::npos && endsWith(line,"//< MODIFIED"))
			{
				countLine = false;
			}
			else if (line.find("//NEW >") != string::npos && endsWith(line,"//NEW >"))
			{
				countLine = false;
			}
			else if (line.find("//< NEW") != string::npos && endsWith(line,"//< NEW"))
			{
				countLine = false;
			}
			else if(!inComment){
				countLine = true;
			}
			
			if(line.find("//STRUCT >") != string::npos && endsWith(line,"//STRUCT >") && !inPart)
			{
				inPart = true;
				parts.push_back("Struct");
				numberOfParts++;
				partLines = 0;
				partItems = 0;
				
			}
			else if(line.find("//CLASS >") != string::npos && endsWith(line,"//CLASS >") && !inPart)
			{
				inPart = true;
				parts.push_back("Class");
				numberOfParts++;
				partLines = 0;
				partItems = 0;
				
			}
			else if(line.find("//FUNCTION >") != string::npos && endsWith(line,"//FUNCTION >") && !inPart)
			{
				inPart = true;
				parts.push_back("Function");
				numberOfParts++;
				partLines = 0;
				partItems = 0;
				
			}
			else if(line.find("//STRUCT >") != string::npos && endsWith(line,"//STRUCT >") && inPart && !inItem)
			{
				partItems++;
				inItem = true;
			}
			else if(line.find("//CLASS >") != string::npos && endsWith(line,"//CLASS >") && inPart && !inItem)
			{
				partItems++;
				inItem = true;
			}
			else if(line.find("//FUNCTION >") != string::npos && endsWith(line,"//FUNCTION >") && inPart && !inItem)
			{
				partItems++;
				inItem = true;
			}
			
			if(line.find("//< STRUCT") != string::npos && endsWith(line,"//< STRUCT") && inItem)
			{
				inItem = false;
			}
			else if(line.find("//< CLASS") != string::npos && endsWith(line,"//< CLASS") && inItem)
			{
				inItem = false;
			}
			else if(line.find("//< FUNCTION") != string::npos && endsWith(line,"//< FUNCTION") && inItem)
			{
				inItem = false;
			}
			else if(line.find("//< STRUCT") != string::npos && endsWith(line,"//< STRUCT") && inPart && !inItem)
			{
				numberOfItems.push_back(partItems);
				partSize.push_back(partLines+1);
				partLines = 0;
				inPart = false;
			}
			else if(line.find("//< CLASS") != string::npos && endsWith(line,"//< CLASS") && inPart && !inItem)
			{
				numberOfItems.push_back(partItems);
				partSize.push_back(partLines+1);
				partLines = 0;
				inPart = false;
			}
			else if(line.find("//< FUNCTION") != string::npos && endsWith(line,"//< FUNCTION") && inPart && !inItem)
			{
				numberOfItems.push_back(partItems);
				partSize.push_back(partLines+1);
				partLines = 0;
				inPart = false;
			}
			
			if(inNew)
			{
				if(line.find("//< NEW") != string::npos && endsWith(line,"//< NEW"))
				{
					
				} else
				{
					newNum++;
				}
			}
			else if(inModified)
			{
				if(line.find("//< MODIFIED") != string::npos && endsWith(line,"//< MODIFIED"))
				{
					
				} else
				{
					modifiedNum++;
				}
			}
			else if(inReused)
			{
				if(line.find("//< REUSED") != string::npos && endsWith(line,"//< REUSED"))
				{
					
				} else
				{
					reusedNum++;
				}
			}
			else if(inErased)
			{
				if((line.find("//< ERASED") != string::npos && endsWith(line,"//< ERASED")) || (line.find("//ERASED >") != string::npos && endsWith(line,"//ERASED >")) || line.find("/*") != string::npos || line.find("*/") != string::npos )
				{
					
				} else
				{
					erasedNum++;
					cout<<"ERASED: "<<line<<endl;
				}
			}
			
			if(previousLine.find("//NEW >") != string::npos && endsWith(previousLine,"//NEW >"))
			{
				inNew = true;
				newNum++;
			}
			else if(previousLine.find("//MODIFIED >") != string::npos && endsWith(previousLine,"//MODIFIED >"))
			{
				inModified = true;
				modifiedNum++;
			}
			else if(previousLine.find("//REUSED >") != string::npos && endsWith(previousLine,"//REUSED >"))
			{
				inReused = true;
				reusedNum++;
			}
			else if(previousLine.find("//ERASED >") != string::npos && endsWith(previousLine,"//ERASED >"))
			{
				inErased = true;
				if(line.find("/*") != string::npos && endsWith(line,"/*"))
				{
					
				}
				else
				{
					erasedNum++;
					cout<<"ERASED: "<<line<<endl;
				}
			}
			else if(line.find("//< NEW") != string::npos && endsWith(line,"//< NEW"))
			{
				inNew = false;
			}
			else if(line.find("//< MODIFIED") != string::npos && endsWith(line,"//< MODIFIED"))
			{
				inModified = false;
			}
			else if(line.find("//< REUSED") != string::npos && endsWith(line,"//< REUSED"))
			{
				inReused = false;
			}
			else if(line.find("//< ERASED") != string::npos && endsWith(line,"//< ERASED"))
			{
				inErased = false;
			}
			
			
			if(countLine)
			{
				totalSize++;
				if(inPart){
					partLines++;
				}
			}
			
			previousLine = line;
		}
		
	}
	cout<<"Total size: "<<totalSize<<endl;
	cout<<"-------------------"<<endl;
	for(int i=0;i<numberOfParts;i++){
		cout<<"Part: "<<parts[i]<<endl;
		cout<<"Number of items: "<<numberOfItems[i]<<endl;
		cout<<"Size of part: "<<partSize[i]<<endl;
		cout<<"-------------------"<<endl;
	}
	cout<<"NEW: "<<newNum<<endl;
	cout<<"MODIFIED: "<<modifiedNum<<endl;
	cout<<"REUSED: "<<reusedNum<<endl;
	cout<<"ERASED: "<<erasedNum<<endl;
	return 0;
} //< FUNCTION
