#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(APP_WIDTH,APP_HEIGHT);
	(*settings).setResizable(false);
}

void bournehwStarbucksApp::setup()
{	/*double x, y;
	int numCorrect = 0, n = 1000, nPoints = 100;
	Entry *nodeSlow, *nodeFast;
	boost::chrono::system_clock::time_point t;
	boost::chrono::duration<double> sumSlowT, sumFastT, slowT, fastT;*/
	surface_ = new Surface(TEXTURE_SIZE,TEXTURE_SIZE,false);
	mapImage_ = new Surface(loadImage(loadResource(RES_MAP)));

	list = new bournehwStarbucks();
	readStarbucks("Starbucks_2006.csv");
	list->build(starbucks_,starbucksLen_);

	/*srand (time(NULL));
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

	foundLoc = "";*/
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
	uint8_t* dataArray = (*surface_).getData();
}

void bournehwStarbucksApp::draw()
{

	gl::color(Color(255,255,255));
	gl::draw(*mapImage_);
	gl::color(Color(0,0,255));
	/*gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.481406177419355f+70,((float)APP_HEIGHT-100)*(1-0.99996564f)+50),2,0); //49.003646,-95.152817
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.270845967741936f+70,((float)APP_HEIGHT-100)*(1-0.29339484f)+50),2,0); //31.334871,-108.20755
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.012715241935484f+70,((float)APP_HEIGHT-100)*(1-0.71984972f)+50),2,0); //41.996243,-124.211655
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.449233516129032f+70,((float)APP_HEIGHT-100)*(1-0.0781242399999999f)+50),2,0); //25.953106,-97.147522
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.706932306451613f+70,((float)APP_HEIGHT-100)*(1-0.0488934f)+50),2,0); //25.222335,-81.170197
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.899569596774193f+70,((float)APP_HEIGHT-100)*(1-0.93831236f)+50),2,0); //47.457809,-69.226685
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.937312951612903f+707,((float)APP_HEIGHT-100)*(1-0.83174124f)+50),2,0); //44.793531,-66.886597*/
	list->draw(list->head_,APP_WIDTH,APP_HEIGHT,Color8u(255,0,0));
}

CINDER_APP_BASIC( bournehwStarbucksApp, RendererGl )
