#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include "ship.h"
#include "character.h"

#define PI 3.141592

#define MAX_SPEED  2.0
#define RESISTANCE 0.008
#define ACCELERATION 0.2

using namespace std;

Ship::Ship(double x, double y, double r){
	this->x = x;	
	this->y = y;	
	this->radius = r;	
	this->rotation = 0;
	this->rot_prev = 0;	
	this->tilt_angle = 0;
	this->direction = 0;
        this->dx = 0;
        this->dy = 0;
	glPushMatrix();
	//this->shipModel = loadModel("models/asteroid/asteroid.obj");
	
	//this->shipModel = loadModel("models/ship/GhoulOBJ.obj");
	this->shipModel = getShipModel();
	//cout << "Glm untize result" << glmUnitize(this->shipModel) <<endl;
	glPopMatrix();
}

void Ship::Move() {
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

void Ship::Move(double thrust_dir, double strafe_dir, double r){
        double thrust_x = thrust_dir * ACCELERATION * cos((PI/180)*(r+90));
        double thrust_y = thrust_dir * ACCELERATION * sin((PI/180)*(r+90));
        
        //double strafe_x = 0;
        //double strafe_y = 0;
        //not sure why the code below doesn't work as expected - some type of max strafe speed problem
        double strafe_x = strafe_dir * ACCELERATION * cos((PI/180)*(r));
        double strafe_y = strafe_dir * ACCELERATION * sin((PI/180)*(r));
        
        if(this->dx > 0 || this->dx < 0){ //check x dir
                this->dx = this->dx + (thrust_x + strafe_x) - (RESISTANCE) * this->dx;
        }else{
                this->dx = thrust_x + strafe_x;
        } 
        if(this->dy > 0 || this->dy < 0){ //check y dir
                this->dy = this->dy + (thrust_y + strafe_y) - (RESISTANCE) * this->dy;
        }else{
                this->dy = thrust_y + strafe_y;
        }
        
        if(abs(this->dx) > MAX_SPEED){  //enforce speed limit
                //determines sign of movement direction and multiplies by max speed
                this->dx = ((this->dx > 0) - (this->dx<0)) * MAX_SPEED;
        }
        if(abs(this->dy) > MAX_SPEED){
                this->dy = ((this->dy > 0) - (this->dy<0)) * MAX_SPEED;
        }
	tilt_angle = fmod(r-rot_prev,30) *3;
	//cout<< "Delta Rot: " <<tilt_angle<< endl;
	rot_prev = r;


	glDisable(GL_LIGHT1);
	float intensity_ship = 1.0;
	float amb_color_ship[] = {240/255.0,240/255.0,0,1};
	float spec_color_ship[] = {intensity_ship,intensity_ship,intensity_ship,1};
	float dif_color_ship[] = {intensity_ship,intensity_ship,intensity_ship,1};
	GLfloat lightPos_ship[] = {this->x,this->y,-5,1};
	GLfloat lightDir_ship[] = {cos((PI/180)*(r+90)),sin((PI/180)*(r+90)),0.5};

	glLightfv(GL_LIGHT1, GL_AMBIENT, amb_color_ship);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_color_ship);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec_color_ship);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos_ship);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir_ship);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);	// Spotlight cutoff angle
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,8.0);   	// set focusing strength

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001);
	glEnable(GL_LIGHT1);

        this->Move();

        rotation = r;
	direction = thrust_dir;
}

void Ship::Draw() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
          glColor3f(1, 1.0, 1);
          glTranslatef(x, y, 0);
          glRotatef(rotation+90, 0, 0, 1);
          glScalef(radius,radius,radius);
          glRotatef(tilt_angle, 1,0,0);
          drawModel(shipModel);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
