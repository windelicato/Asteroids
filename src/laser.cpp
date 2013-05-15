#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "laser.h"
#include "character.h"
#include <cmath>

using namespace std;

#define PI 3.141592
Laser::Laser(double x, double y, double rotation, double radius, double speed){
	this->x = x;	
	this->y = y;	
	this->dx = cos((PI/180)*(rotation+90)) * speed;
	this->dy = sin((PI/180)*(rotation+90)) * speed;
	this->health = radius;
	this->rotation = rotation;
	this->radius = radius;
	this->wrapAround = false;	
}

bool Laser::onScreen(){
	if(wrapAround)
		return true;
	return false;
} 

void Laser::Draw() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(x, y, 0);	
	glRotatef(rotation,0,0,1);
	glScalef(radius,radius,radius);
	glBegin(GL_POLYGON);
		glColor3f(236/255.0, 15.0/255.0, 124.0/255.0);
		glVertex3f(-.25, .5, 0);
		glVertex3f( .25 , .5, 0);
		glVertex3f(.25, -.5, 0);
		glVertex3f(-.25, -.5, 0);
	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
