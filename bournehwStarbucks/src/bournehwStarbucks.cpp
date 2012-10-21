#include "bournehwStarbucks.h"

bournehwStarbucks::bournehwStarbucks(string fileName){
	readStarbucks(fileName);
}

void bournehwStarbucks::build(Entry* c, int n){
}
	
Entry* bournehwStarbucks::getNearest(double x, double y){
	double difX, difY, newDistance;
	double oldDistance = numeric_limits<double>::max( );
	Entry* closest;

	for(int ii = 0; ii<starbucksLen_; ++ii){
		difX = starbucks_[ii].x-x;
		difY = starbucks_[ii].y-y;
		newDistance = sqrt(difX*difX + difY*difY);

		if(newDistance<oldDistance){
			closest = starbucks_+ii;
			oldDistance = newDistance;
		}
	}
	return closest;
}

void bournehwStarbucks::readStarbucks(string fileName){
	ifstream fileIn;
	istringstream strStream;
	string str;
	int numItems=1;
	double x, y;
	string name;

	fileIn.open(fileName,ifstream::in);
	
	if(!fileIn.is_open())
		starbucks_ =  NULL;

	while(!fileIn.eof()){
		string str;
		getline(fileIn,str,'\r');
		if(!fileIn.eof())
			numItems++;
	}

	starbucks_ = new Entry[numItems];
	starbucksLen_ = numItems;

	fileIn.clear();
	fileIn.seekg(0, ifstream::beg);

	for(int ii=0; ii<numItems; ++ii){
		//starbucks_[ii] = new Entry;
		getline(fileIn,str,'\r');
		strStream.str(str);

		getline(strStream,str,',');
		name = str;
		starbucks_[ii].identifier = str;

		getline(strStream,str,',');
		starbucks_[ii].x = lexical_cast<double>(str);

		getline(strStream,str,',');
		starbucks_[ii].y = lexical_cast<double>(str);
		strStream.clear();
	}
}

string bournehwStarbucks::printLocation(double x, double y){
	Entry* location = getNearest(x, y);
	return location->identifier;
}
