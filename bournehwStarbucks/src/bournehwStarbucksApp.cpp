#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::setup()
{	double x, y;
	int numCorrect = 0, n = 1000, nPoints = 100;
	Entry *nodeSlow, *nodeFast;
	boost::chrono::system_clock::time_point t;
	boost::chrono::duration<double> sumSlowT, sumFastT, slowT, fastT;

	bournehwStarbucks list = bournehwStarbucks();
	readStarbucks("Starbucks_2006.csv");
	list.build(starbucks_,starbucksLen_);

	srand (time(NULL));
	for(int jj=0; jj<n; ++jj){
		x = (double)rand()/(float)RAND_MAX;
		y = (double)rand()/(float)RAND_MAX;

		t = boost::chrono::system_clock::now();
		for(int ii=0; ii<n; ++ii){
			nodeSlow = searchArray(x,y);
		}
		slowT = boost::chrono::system_clock::now()-t;
		console() << "Slow time:" << slowT << flush;

		t = boost::chrono::system_clock::now();
		for(int ii=0; ii<n; ++ii){
			nodeFast = list.getNearest(x,y);
		}
		fastT = boost::chrono::system_clock::now()-t;
		console() << " Fast time:" << fastT << endl;
		if(nodeSlow->identifier==nodeFast->identifier)
			numCorrect++;
	}

	console() << "Slow Time:" << slowT/n <<" Fast Time:" << fastT/n << " Percent Accurate:" << (numCorrect/n)*100 << endl;

	foundLoc = "";
}

void bournehwStarbucksApp::readStarbucks(string fileName){
	ifstream fileIn;
	istringstream strStream;
	string str;
	int numItems=1;
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

Entry* bournehwStarbucksApp::searchArray(double x, double y){
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

void bournehwStarbucksApp::printArr(Entry* arr, int n){
	console() << "\n\nStart Array Output" << endl;
	for(int ii=0; ii<n; ++ii){
		console() << arr[ii].identifier << endl;
	}
}

void bournehwStarbucksApp::mouseDown( MouseEvent event )
{
}

void bournehwStarbucksApp::update()
{
}

void bournehwStarbucksApp::draw()
{
	Vec2f pos = Vec2f(10.0f,10.0f);
	Colorf  color = Color::white();
    Font font = Font( "ArialMT", 50 );

	gl::clear( Color( 0, 0, 0 ) ); 
	gl::drawString(foundLoc,pos,color,font);
	
}

CINDER_APP_BASIC( bournehwStarbucksApp, RendererGl )
