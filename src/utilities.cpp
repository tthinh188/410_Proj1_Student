/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

std::vector<process_stats> pStats;
//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	pStats.clear();
	std::string line;
	fstream myfile;
//	string file;
//	file = "./src/";
//	file.append(filename);
	myfile.open(filename);
	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	else{
		if (ignoreFirstRow){
			getline(myfile, line);
		}
		while (!myfile.eof()){
			getline(myfile, line);
			std::vector<std::string> splitLine;
			stringstream ss(line);
			while (ss.good()){
				string substr;
				getline(ss,substr, CHAR_TO_SEARCH_FOR);
				if(substr != ""){
				splitLine.push_back(substr);
				}
			}
			if (splitLine.size() == 4){
				process_stats processStat;
				processStat.io_time = stoi(splitLine.back());
				splitLine.pop_back();
				processStat.cpu_time = stoi(splitLine.back());
				splitLine.pop_back();
				processStat.start_time = stoi(splitLine.back());
				splitLine.pop_back();
				processStat.process_number = stoi(splitLine.back());
				splitLine.pop_back();
				pStats.push_back(processStat);
			}
		}
	}

	myfile.close();
	return SUCCESS;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	process_stats temp;
	switch(mySortOrder){
	case PROCESS_NUMBER:
		for (int i = 0; i < pStats.size(); i++){
			for(int j=i+1;j< pStats.size();j++)
				{
					if(pStats[i].process_number > pStats[j].process_number){
						temp  =pStats[i];
						pStats[i]=pStats[j];
						pStats[j]=temp;
					}
				}
		}
		break;
	case START_TIME:
		for (int i = 0; i < pStats.size(); i++){
			for(int j=i+1;j< pStats.size();j++)
				{
					if(pStats[i].start_time > pStats[j].start_time)
					{
						temp  = pStats[i];
						pStats[i]= pStats[j];
						pStats[j]= temp;
					}
				}
		}
		break;
	case CPU_TIME:
		for (int i = 0; i < pStats.size(); i++){
			for(int j=i+1;j< pStats.size();j++)
				{
					if(pStats[i].cpu_time > pStats[j].cpu_time)
					{
						temp  =pStats[i];
						pStats[i]=pStats[j];
						pStats[j]=temp;
					}
				}
		}
		break;
	default:
		for (int i = 0; i < pStats.size(); i++){
			for(int j=i+1;j < pStats.size();j++)
				{
					if(pStats[i].io_time > pStats[j].io_time)
					{
						temp  =pStats[i];
						pStats[i]=pStats[j];
						pStats[j]=temp;
					}
				}
		}
		break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	myFirst = pStats.front();
	pStats.erase(pStats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return pStats.size();
}


