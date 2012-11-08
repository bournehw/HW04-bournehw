#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(APP_WIDTH,APP_HEIGHT);
	(*settings).setResizable(false);
}

void bournehwStarbucksApp::setup()
{
	list = new bournehwStarbucks();
	readStarbucks("Starbucks_2006.csv");
	list->build(starbucks_,starbucksLen_);

	srand(time(NULL));
	list->assignColor(list->head_);

	Surface* blankMap = new Surface(loadImage(loadResource(RES_MAP)));
	mapImage_ = new gl::Texture(*blankMap);

	Surface* temp = new Surface(*blankMap);
	genRegions(temp);
	regionsImage_ = new gl::Texture(*blankMap);
}

void bournehwStarbucksApp::genRegions(Surface* surface){
	Vec2i pos;
	double mapX, mapY;
	Node* node;

	Area area(X_BORDER, Y_BORDER, APP_WIDTH-(OFFSET-X_BORDER), APP_HEIGHT-(OFFSET-Y_BORDER));
	Surface::Iter iter = surface->getIter(area);


	while( iter.line() ) {
		while( iter.pixel() ) {
			pos = iter.getPos();
			mapX = ((double)(pos.x-70))/((double)(APP_WIDTH-100));
			mapY = 1.0f - ((double)(pos.y-50))/((double)(APP_HEIGHT-100));

			node = list->search(mapX, mapY, list->head_, true);

			iter.r() = (node->color_.r+iter.r())/2;
			iter.g() = (node->color_.g+iter.g())/2;
			iter.b() = (node->color_.b+iter.b())/2;
		}
	}
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

	gl::color(Color(255,255,255));
	gl::draw(*regionsImage_);
	gl::color(Color(0,0,255));
	/*gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.481406177419355f+70,((float)APP_HEIGHT-100)*(1-0.99996564f)+50),2,0); //49.003646,-95.152817
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.270845967741936f+70,((float)APP_HEIGHT-100)*(1-0.29339484f)+50),2,0); //31.334871,-108.20755
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.012715241935484f+70,((float)APP_HEIGHT-100)*(1-0.71984972f)+50),2,0); //41.996243,-124.211655
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.449233516129032f+70,((float)APP_HEIGHT-100)*(1-0.0781242399999999f)+50),2,0); //25.953106,-97.147522
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.706932306451613f+70,((float)APP_HEIGHT-100)*(1-0.0488934f)+50),2,0); //25.222335,-81.170197
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.899569596774193f+70,((float)APP_HEIGHT-100)*(1-0.93831236f)+50),2,0); //47.457809,-69.226685
	gl::drawSolidCircle(Vec2f(((float)APP_WIDTH-100)*0.937312951612903f+707,((float)APP_HEIGHT-100)*(1-0.83174124f)+50),2,0); //44.793531,-66.886597*/
	list->draw(list->head_,APP_WIDTH,APP_HEIGHT);
}

CINDER_APP_BASIC( bournehwStarbucksApp, RendererGl )
