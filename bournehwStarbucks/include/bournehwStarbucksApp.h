#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <string>
#include "bournehwStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class bournehwStarbucksApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
private:
	string foundLoc;
};
