/*****
 * Author   : Harrison Bourne
 * Date     : 2012-10-20
 */

#pragma once
#include "Starbucks.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <climits>
#include <boost/lexical_cast.hpp>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost;

class Node{
public:
	Node* left_;
	Node* right_; 
	Entry data_;
	Color8u color_;
	Color8u difColor_;
	Color8u ppsColor_;
	unsigned int pop00;
	unsigned int pop10;

	Node(Entry data);
	~Node();
};

class bournehwStarbucks : public Starbucks {
public:
	Node* head_;
	unsigned int maxPop00_;
	unsigned int maxPop10_;
	unsigned int minPop00_;
	unsigned int minPop10_;
	int maxDif_;
	int minDif_;

	bournehwStarbucks();
	~bournehwStarbucks();

	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	void printInOrder(Node* r);
	void draw(Node* r, int mapW, int mapH);
	Node* search(double x, double y, Node* r, bool xLevel);
	void assignColor(Node* r);

private:
	Node* checkOther(double x, double y, Node* r, bool xLevel, bool goLeft);
	Node* insert(Entry* data, Node* r, bool xLevel);
	void shuffle(Entry* arr, int n);
};