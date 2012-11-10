/**
* @file bournehwStarbucksApp.h
* CSE 274 - Fall 2012
*
* @author Harrison Bourne
* @date 2012-09-23
*
* @note This project satisfies goals A (US map), C (Starbucks regions),
* E (change in population, and F (people per Starbucks).
*/

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
	/**
	 *This function draws the the visual representations of which points correspond
	 *to each starbucks (this is displayed when the user presses c), the color
	 *regions which indicate the change in population (press e), and the color 
	 *regions which indicate people per starbucks (press f). This function performs
	 *get nearest for each pixle of the screen so it is rather slow.
	 *
	 *This satisfies goals C, E, and F.
	 *
	 **/
	void genRegions(Surface* regionsImage,Surface* popDifImage,Surface* ppsImage);
	/**
	 *This function reads the Census data from the .csv file. It performs get nearest
	 *on each for each Census data point so it is also rather slow.
	 **/
	void readCensus(string fileName);
	void mouseDown( MouseEvent event );	
	void keyDown( KeyEvent event );
	void update();
	void draw();
	/**
	 *This function reads the starbucks locations from the .csv file
	 **/
	void readStarbucks(string fileName);
	/**
	 *This function performs linear search on the array of starbucks 
	 *locations as a truth reference for the tree based search.
	 **/
	Entry* searchArray(double x, double y);
	/**
	 *This function prints out every entry in the array of starbucks
	 *locations to the console
	 */
	void printArr(Entry* arr, int n);

private:
	Surface* surface_;
	gl::Texture* mapImage_;
	gl::Texture* regionsImage_;
	gl::Texture* ppsImage_;
	gl::Texture* popDifImage_;

	bool regionFlag_;
	bool ppsFlag_;
	bool popDifFlag_;

	//Width and height of the screen
	static const int APP_WIDTH=800;
	static const int APP_HEIGHT=600;
	static const int OFFSET = 100;
	static const int X_BORDER = 70;
	static const int Y_BORDER = 50;
	static const int TEXTURE_SIZE=1024;
};
