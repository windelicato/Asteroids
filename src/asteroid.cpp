#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

#include "asteroid.h"
#include "character.h"


#define MINIMUM_SIZE 1
using namespace std;

Asteroid::Asteroid(double x, double y, double dx, double dy, double r ){
	this->x = x;	
	this->y = y;	
	this->dx = dx;	
	this->dy = dy;	
	this->radius = r;
	this->health = r/1.3;	
	//cout<< this->health<<endl;
	//this->asteroidModel = loadModel("models/asteroid/asteroid.obj");
	this->asteroidModel =getAsteroidModel();	
	//srand(time(NULL));
	this->x_rot = rand()%100/100.0 - 0.5;
	this->y_rot = rand()%100/100.0 - 0.5;
	this->z_rot = rand()%100/100.0 - 0.5;
	this->speed_rot = rand()%100/100.0 - 0.5;
	this->pos_rot = 0.0;
	//glmUnitize(this->asteroidModel);
	//cout << "Glm untize asteroid result" << glmUnitize(this->asteroidModel) <<endl;
}

Asteroid::~Asteroid(){
}

void Asteroid::spawnChildren(vector<Asteroid*> * target, int index){
		if(this->health >0){	
			return;
		}
		//srand(time(NULL));
		if(this->radius/2 < MINIMUM_SIZE){
			target->erase(target->begin()+index);
			return;
		}
		double radius = this->radius/2.0;
		double delt_X = fmod(rand(),(radius));
		double delt_Y = fmod(rand(),(radius))+sqrt(radius*radius - delt_X*delt_X);

		Asteroid * a = new Asteroid(this->x+delt_X,this->y+delt_Y,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);
		Asteroid * b = new Asteroid(this->x-delt_X,this->y-delt_Y,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);
		
/*Asteroid * a = new Asteroid(this->x+fmod(rand(),(this->radius*2))-this->radius,this->y+fmod(rand(),(this->radius*2))-this->radius,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);
		Asteroid * b = new Asteroid(this->x+fmod(rand(),(this->radius*2))-this->radius,this->y+fmod(rand(),(this->radius*2))-this->radius,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);*/
	/**
   * Make sure the Asteroids dont automatically kill eachother
   */		
		/*while(a->Collision(b)){
				b = new Asteroid(this->x+fmod(rand(),(this->radius*2))-this->radius,this->y+fmod(rand(),(this->radius*2))-this->radius,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);
				a = new Asteroid(this->x+fmod(rand(),(this->radius*2))-this->radius,this->y+fmod(rand(),(this->radius*2))-this->radius,(rand()%500 -250)/500.0,(rand()%500 -250)/500.0,radius);
			}*/
		target->push_back(a);
		target->push_back(b);
		target->erase(target->begin()+index);
		//glmDelete(this->asteroidModel);
		return;
} 
void Asteroid::Draw() {
	
	glPushMatrix();
	
	glTranslatef(x, y, 0);
	glScalef(radius,radius,radius);
	//glScalef(radius,radius,radius);
	/*glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(-1, -1, 0);
	glEnd();*/
	glRotatef(pos_rot, x_rot,y_rot,z_rot);
	pos_rot += speed_rot*10;
	drawModel(asteroidModel);
	glPopMatrix();
}
