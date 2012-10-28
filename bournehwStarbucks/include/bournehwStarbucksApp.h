#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
#include "bournehwStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;

class bournehwStarbucksApp : public AppBasic {
  public:
	Entry* starbucks_;
	int starbucksLen_;

	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void readStarbucks(string fileName);
	Entry* searchArray(double x, double y);
	void shuffle(Entry* arr, int n);
	void printArr(Entry* arr, int n);
	string foundLoc;
};
