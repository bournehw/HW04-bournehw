#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::prepareSettings(Settings* settings){
	settings->setWindowSize(700,500);
	settings->setResizable(false);
	settings->setBorderless(true);
}

void bournehwStarbucksApp::setup()
{
	regionFlag_ = false;
	ppsFlag_ = false;
	popDifFlag_ = false;

	list = new bournehwStarbucks();
	readStarbucks("Starbucks_2006.csv");
	list->build(starbucks_,starbucksLen_);

	srand(time(NULL));
	list->assignColor(list->head_);

	Surface* blankMap = new Surface(loadImage(loadResource(RES_MAP)));
	mapImage_ = new gl::Texture(*blankMap);

	readCensus("Census_2000.csv");
	readCensus("Census_2010.csv");

	Surface* regionsImage = new Surface();
	Surface* popDifImage = new Surface();
	Surface* ppsImage = new Surface();
	*regionsImage = blankMap->clone();
	*popDifImage = blankMap->clone();
	*ppsImage = blankMap->clone();
	genRegions(regionsImage,popDifImage,ppsImage);
	regionsImage_ = new gl::Texture(*regionsImage);
	popDifImage_ = new gl::Texture(*popDifImage);
	ppsImage_ =  new gl::Texture(*ppsImage);

	delete regionsImage;
	delete popDifImage;
	delete ppsImage;
}

void bournehwStarbucksApp::genRegions(Surface* regionsImage,Surface* popDifImage,Surface* ppsImage){
	Vec2i pos;
	double mapX, mapY;
	Node* node, *prevNode = NULL;
	unsigned int color;
	int diff;

	Area area(X_BORDER, Y_BORDER, APP_WIDTH-(OFFSET-X_BORDER), APP_HEIGHT-(OFFSET-Y_BORDER));
	Surface::Iter iter = regionsImage->getIter(area);
	Surface::Iter iter2 = popDifImage->getIter(area);
	Surface::Iter iter3 = ppsImage->getIter(area);

	while(iter.line()&&iter2.line()&&iter3.line()) {
		while(iter.pixel()&&iter2.pixel()&&iter3.pixel()) {
			pos = iter.getPos();
			mapX = ((double)(pos.x-70))/((double)(APP_WIDTH-100));
			mapY = 1.0f - ((double)(pos.y-50))/((double)(APP_HEIGHT-100));

			node = list->search(mapX, mapY, list->head_, true);

			if(iter.r()<180&&iter.r()<180&&iter.r()<180){
				iter.r() = (node->color_.r+iter.r())/2;
				iter.g() = (node->color_.g+iter.g())/2;
				iter.b() = (node->color_.b+iter.b())/2;
			}else{
				iter.r() = node->color_.r;
				iter.g() = node->color_.g;
				iter.b() = node->color_.b;
			}

			if(prevNode==NULL||(prevNode->data_.identifier.compare(node->data_.identifier))!=0)
				prevNode = node;

			diff = ((long long)node->pop10)-((long long)node->pop00);
			if(diff<=0){
				color = ceil(((double)diff)/-5000*255);
				node->difColor_ = Color8u(color,0,0);
			}else{
				color = ceil(((double)diff)/((double)list->maxDif_)*255);
				node->difColor_ = Color8u(0,color,0);
			}

			if(iter2.r()<180&&iter2.r()<180&&iter2.r()<180){
				iter2.r() = (node->difColor_.r+iter2.r())/2;
				iter2.g() = (node->difColor_.g+iter2.g())/2;
				iter2.b() = (node->difColor_.b+iter2.b())/2;
			}else{
				iter2.r() = node->difColor_.r;
				iter2.g() = node->difColor_.g;
				iter2.b() = node->difColor_.b;
			}

			diff = list->maxPop00_-list->minPop00_;
			color =(((double)(node->pop00-list->minPop00_))/((double)diff))*255;
			node->ppsColor_ = Color8u(0,0,color);

			if(iter3.r()<180&&iter3.r()<180&&iter3.r()<180){
				iter3.r() = (node->ppsColor_.r+iter3.r())/2;
				iter3.g() = (node->ppsColor_.g+iter3.g())/2;
				iter3.b() = (node->ppsColor_.b+iter3.b())/2;
			}else{
				iter3.r() = node->ppsColor_.r;
				iter3.g() = node->ppsColor_.g;
				iter3.b() = node->ppsColor_.b;
			}
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

void bournehwStarbucksApp::readCensus(string fileName){
	ifstream fileIn;
	istringstream strStream;
	string str;
	unsigned int pop;
	double lat, lon;
	int diff;
	Node* node, *prevNode = NULL;

	fileIn.open(fileName,ifstream::in);
	
	if(!fileIn.is_open())
		starbucks_ =  NULL;

	while(!fileIn.eof()){
		getline(fileIn,str,'\r');
		if(!fileIn.eof()){
			strStream.str(str);
			strStream.ignore(256,',');
			strStream.ignore(256,',');
			strStream.ignore(256,',');
			strStream.ignore(256,',');

			strStream >> pop;
			strStream.ignore(256,',');
			strStream >> lat;
			strStream.ignore(256,',');
			strStream >> lon;
			strStream.clear();

			node = list->search(lat,lon,list->head_,true);

			if(prevNode==NULL||(prevNode->data_.identifier.compare(node->data_.identifier))!=0)
				prevNode = node;

			if(fileName.compare("Census_2000.csv")==0){
				node->pop00 += pop;
			}else{
				node->pop10 += pop;
			}

			if(list->maxPop00_<node->pop00)
				list->maxPop00_ = node->pop00;
			if(list->minPop00_>node->pop00)
				list->minPop00_ = node->pop00;

			if(list->maxPop10_<node->pop10)
				list->maxPop10_ = node->pop10;
			if(list->minPop10_>node->pop10)
				list->minPop10_ = node->pop10;
			
				diff = ((long long)node->pop10)-((long long)node->pop00);
				if(diff>list->maxDif_&&node->pop10!=0)
					list->maxDif_ = diff;
		}
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

void bournehwStarbucksApp::keyDown( KeyEvent event ) {
    if(event.getChar() == 'c')
		regionFlag_ = !regionFlag_;
	if(event.getChar() == 'e')
		popDifFlag_ = !popDifFlag_;
	if(event.getChar() == 'f')
		ppsFlag_ = !ppsFlag_;
}

void bournehwStarbucksApp::update()
{
}

void bournehwStarbucksApp::draw()
{
	Area area(X_BORDER, Y_BORDER, APP_WIDTH-(OFFSET-X_BORDER), APP_HEIGHT-(OFFSET-Y_BORDER));



	gl::color(Color(255,255,255));
	if(regionFlag_){
		gl::draw(*regionsImage_,area,Rectf(0,0,APP_WIDTH-OFFSET, APP_HEIGHT-OFFSET));
		list->draw(list->head_,APP_WIDTH,APP_HEIGHT);
	}else if(ppsFlag_){
		gl::draw(*ppsImage_,area,Rectf(0,0,APP_WIDTH-OFFSET, APP_HEIGHT-OFFSET));
		list->draw(list->head_,APP_WIDTH,APP_HEIGHT);
	}else if(popDifFlag_){
		gl::draw(*popDifImage_,area,Rectf(0,0,APP_WIDTH-OFFSET, APP_HEIGHT-OFFSET));
		list->draw(list->head_,APP_WIDTH,APP_HEIGHT);
	}else{
		gl::draw(*mapImage_,area,Rectf(0,0,APP_WIDTH-OFFSET, APP_HEIGHT-OFFSET));
		list->draw(list->head_,APP_WIDTH,APP_HEIGHT);
	}
}

CINDER_APP_BASIC( bournehwStarbucksApp, RendererGl )
