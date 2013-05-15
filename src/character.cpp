#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include "character.h"

using namespace std;


Character::Character() {

}

Character::~Character() {

}

bool Character::Collision(Character *c) {
	double x_diff = (x - c->x);
	double y_diff = (y - c->y);
	if(this == c)
		return false;
	double distance = sqrt(pow(x_diff, 2.0) + pow(y_diff, 2.0));
	if ( distance <= (radius + c->radius)){
		this->health -= c->radius;
		c->health -= this->radius;
		return true;
	} return false;
}

void Character::Draw() {
}

void Character::Move() {
	double tempX = (x+dx);
	double tempY= (y+dy);
	if(tempX<0){
		x = tempX + 100;
	}else{
		x = fmod(tempX,100.0);
	}
	if(tempY<0){
		y = tempY + 100;
	}else{
		y = fmod(tempY,100.0);
	}	
	if(tempX>99 || tempY>99 || tempX<0 ||tempY<0)
		this->wrapAround = true;

//	cout << x << " " << y <<endl;
}
