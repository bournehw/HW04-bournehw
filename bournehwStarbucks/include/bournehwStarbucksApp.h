#pragma once
#define BOOST_CHRONO_HEADER_ONLY

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/chrono.hpp"
#include <string>
#include "Resources.h"
#include "bournehwStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;

class bournehwStarbucksApp : public AppBasic {
  public:
	Entry* starbucks_;
	int starbucksLen_;
	bournehwStarbucks* list;

	void prepareSettings(Settings* settings);
	void setup();
	void genRegions(Surface* surface);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void readStarbucks(string fileName);
	Entry* searchArray(double x, double y);
	void printArr(Entry* arr, int n);
	string foundLoc;

private:
	Surface* surface_;
	gl::Texture* mapImage_;
	gl::Texture* regionsImage_;

	//Width and height of the screen
	static const int APP_WIDTH=800;
	static const int APP_HEIGHT=600;
	static const int OFFSET = 100;
	static const int X_BORDER = 70;
	static const int Y_BORDER = 50;
	static const int TEXTURE_SIZE=1024;
};
