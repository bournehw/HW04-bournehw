#include "bournehwStarbucksApp.h"

void bournehwStarbucksApp::setup()
{
	bournehwStarbucks list = bournehwStarbucks("Starbucks_2006.csv");
	Entry* node = list.getNearest(0.50,0.40);
	foundLoc = node->identifier;
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
