/*****
 * Author   : Harrison Bourne
 * Date     : 2012-10-20
 */

#pragma once
#include "Starbucks.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class bournehwStarbucks : public Starbucks {
public:
	Entry* starbucks_;
	int starbucksLen_;

	bournehwStarbucks(string fileName);

	virtual void build(Entry* c, int n);
	
	virtual Entry* getNearest(double x, double y);

	void readStarbucks(string fileName);

	string printLocation(double x, double y);
};