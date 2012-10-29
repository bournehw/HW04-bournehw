#include "bournehwStarbucks.h"

Node::Node(Entry data){
	data_ = data;
	left_ = NULL;
	right_ = NULL;
}

Node::~Node(void){
	delete &data_;
	delete left_;
	delete right_;
	left_ = NULL;
	right_ = NULL;
}

bournehwStarbucks::bournehwStarbucks(){
	head_ = NULL;
}

bournehwStarbucks::~bournehwStarbucks(){
	delete head_;
	head_ = NULL;
}

void bournehwStarbucks::build(Entry* c, int n){
	shuffle(c, n);
	head_ = new Node(c[0]);
	for(int ii=1; ii<n; ++ii){
		insert(&c[ii], head_, true);
	}
}

Node* bournehwStarbucks::insert(Entry* data, Node* r, bool xLevel){
	if(r==NULL) return new Node(*data);
	if(xLevel){
		if(data->x<r->data_.x){
			r->left_ = insert(data,r->left_,false);
		}else{
			r->right_ = insert(data,r->right_,false);
		}
	}else{
		if(data->y<r->data_.y){
			r->left_ = insert(data,r->left_,true);
		}else{
			r->right_ = insert(data,r->right_,true);
		}
	}
	return r;
}

void bournehwStarbucks::printInOrder(Node* r){
	if(r==NULL) return;
	printInOrder(r->left_);
	console() << r->data_.identifier <<endl;
	printInOrder(r->right_);
}

Entry* bournehwStarbucks::getNearest(double x, double y){
	Node* node = search(x, y, head_, true);
	return &(node->data_);
}

Node* bournehwStarbucks::search(double x, double y, Node* r, bool xLevel){
	Node *candidate, *candidate2;
	bool wentLeft;
	double difX, difY, distance, distance2;
	if(r==NULL)
		return NULL;

	difX = r->data_.x-x;
	difY = r->data_.y-y;
	distance = sqrt(difX*difX+difY*difY);

	if(distance<=0.00001)
		return r;

	if(xLevel){
		if(x<r->data_.x){
			candidate = search(x, y, r->left_, !xLevel);
			wentLeft = true;
		}else{
			candidate = search(x, y, r->right_, !xLevel);
			wentLeft = false;
		}
	}else{
		if(y<r->data_.y){
			candidate = search(x, y, r->left_, !xLevel);
			wentLeft = true;
		}else{
			candidate = search(x, y, r->right_, !xLevel);
			wentLeft = false;
		}
	}

	if(candidate==NULL){
		candidate = checkOther(x, y, r, !xLevel, !wentLeft);
	}else{
		difX = candidate->data_.x-x;
		difY = candidate->data_.y-y;
		distance = sqrt(difX*difX+difY*difY);

		if(xLevel&&abs(r->data_.x-x)<distance){
			candidate2 = checkOther(x, y, r, !xLevel, !wentLeft);

			difX = candidate2->data_.x-x;
			difY = candidate2->data_.y-y;
			distance2 = sqrt(difX*difX+difY*difY);

			if(distance2<distance)
				candidate = candidate2;
		}else if(!xLevel&&abs(r->data_.y-y)<distance){
			candidate2 = checkOther(x, y, r, !xLevel, !wentLeft);

			difX = candidate2->data_.x-x;
			difY = candidate2->data_.y-y;
			distance2 = sqrt(difX*difX+difY*difY);

			if(distance2<distance)
				candidate = candidate2;
		}
	}
	
	difX = candidate->data_.x-x;
	difY = candidate->data_.y-y;
	distance = sqrt(difX*difX+difY*difY);

	difX = r->data_.x-x;
	difY = r->data_.y-y;
	distance2 = sqrt(difX*difX+difY*difY);

	if(distance<distance2){
		return candidate;
	}else{
		return r;
	}
}

Node* bournehwStarbucks::checkOther(double x, double y, Node* r, bool xLevel, bool goLeft){
	double difX, difY, dist1, dist2;
	Node* candidate;

	if(goLeft){
		candidate = search(x, y, r->left_, xLevel);
	}else{
		candidate = search(x, y, r->right_, xLevel);
	}

	if(candidate==NULL)
		return r;

	difX = candidate->data_.x-x;
	difY = candidate->data_.y-y;
	dist1 = sqrt(difX*difX + difY*difY);

	difX = r->data_.x-x; 
	difY = r->data_.y-y;
	dist2 = sqrt(difX*difX + difY*difY);

	if(dist1<dist2){
		return candidate;
	}else{
		return r;
	}
}

void bournehwStarbucks::shuffle(Entry* arr, int n){
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