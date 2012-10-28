#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::setup()
{
	bournehwStarbucks list = bournehwStarbucks();
	readStarbucks("Starbucks_2006.csv");
	shuffle(starbucks_, starbucksLen_);
	list.build(starbucks_,starbucksLen_);
	//list.printInOrder(list.head_);
	//printArr(starbucks_, starbucksLen_);

	double x, y;
	int numCorrect = 0, n = 1000;
	Entry *nodeSlow, *nodeFast;
	boost::posix_time::ptime t;
	boost::posix_time::time_duration sumSlowT, sumFastT;
	srand (time(NULL));
	for(int ii=0; ii<n; ++ii){
		 x = (double)rand()/(float)RAND_MAX;
		 y = (double)rand()/(float)RAND_MAX;

		 t = boost::posix_time::microsec_clock::local_time();
		 nodeSlow = searchArray(x,y);
		 sumSlowT += boost::posix_time::microsec_clock::local_time()-t;
		
		 t = boost::posix_time::microsec_clock::local_time();
		 nodeFast = list.getNearest(x,y);
		 sumFastT += boost::posix_time::microsec_clock::local_time()-t;

		 if(nodeSlow->identifier==nodeFast->identifier)
			 numCorrect++;
	}

	console() << "Slow Time:" << sumSlowT/n <<" Fast Time:" << sumFastT/n << " Percent Accurate:" << (numCorrect/n)*100 << endl;

	//boost::posix_time::ptime t = boost::posix_time::microsec_clock::local_time();
	//Entry* node = searchArray(0.50,0.40);
	//boost::p(osix_time::time_duration slowT = boost::posix_time::microsec_clock::local_time()-t;
	//console) << slowT << "\t" << node->identifier << "\tx=" << node->x << "\ty=" << node->y << endl;
	//foundLoc = node->identifier;
	foundLoc = "Fuck";
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

void bournehwStarbucksApp::shuffle(Entry* arr, int n){
	srand (time(NULL));
	int jj;
	if(n>1){
		for(int ii=0; ii<n; ++ii){
			jj = rand()%n;
			Entry temp = arr[jj];
			arr[jj] = arr[ii];
			arr[ii] = temp;
		}
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
