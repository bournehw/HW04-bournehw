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
	Node* parent_;
	Entry data_;

	Node(Entry data);
};

class bournehwStarbucks : public Starbucks {
public:
	Node* head_;

	bournehwStarbucks();
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Node* insert(Entry* data, Node* r, bool xLevel);
	void printInOrder(Node* r);

private:
	Node* search(double x, double y, Node* r, bool xLevel);
	Node* checkOther(double x, double y, Node* r, bool xLevel, bool goLeft);

};