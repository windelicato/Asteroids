#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <unistd.h>

// Project Includes
#include "asteroid.h"
#include "character.h"
#include "ship.h"
#include "laser.h"
#include "modelLoader.h"
#include "audioLoader.h"
#include "top_scores.h"
#include "gameText.h"

#define MAX_HEALTH 100
#define LASER_SIZE 1.35
#define LASER_SPEED 1.89
#define SHOOT_COOLDOWN 5
#define ASTEROID_COOLDOWN 20
#define PI 3.141592

using namespace std;

// Globals Variables
vector<Asteroid *> asteroids;
vector<Laser *> lasers;
Asteroid *a;
Ship *s;
GLMmodel * backgroundm;

// Ship movement globals
double ship_rotation, ship_rotation_next;
double ship_direction, ship_direction_next;
double strafe_direction, strafe_direction_next;
double px = 0;
double py = 0;

// HUD Values for player
int score = 0;
int health = MAX_HEALTH;

// Globals for cooldowns
bool shoot_cooldown;
int shoot_cooldown_count;
int asteroid_cooldown_count;

// Flags for keypresses
int vertical_key, horizontal_key, shoot_key;
bool w_key,a_key,s_key,d_key,space_key;

// Flag for animation running
int playing_game = 3;

// Saved lowest top score
int top_score = 0;

GLint window_width = 500;
GLint window_height = 500;

void reshapeWindow( GLint newWidth, GLint newHeight) {
	glViewport(0,0,newWidth, newHeight);
	window_width = newWidth;
	window_height= newHeight;
}


GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) {
			cout<< "Bad File Name" <<endl;			
			return 0;
		}
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); 
    glBindTexture( GL_TEXTURE_2D, texture ); 
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 


    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );


    //to the edge of our shape. 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successful
}

void place_background(){
	glDisable(GL_LIGHTING);
	glColor3f( 0.5, 0.5, 0.5 );
	glPushMatrix();
		glScalef(100,100,0.25);
		glTranslatef(.5,.5,-30);
		glRotatef(90,1,0,0);
		//glScalef(100,100,0.5);
		drawModel(backgroundm);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}


void display(void) {
	// Before we do anything we need to clear the screen, including the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//place_background();
	// Leave the projection matrix alone. In this function we are constructing M_{wc,vc}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	place_background();
	for(int i=0; i<(signed int)asteroids.size(); i++){
		asteroids[i]->Draw();
	}
	for(int i=0; i<(signed int)lasers.size(); i++){
		lasers[i]->Draw();
	}

	s->Draw();

	// Update HUD
	glColor3f(1.0, 0.0, 0.0);
	char health_str[50];
	sprintf(health_str, "HEALTH: %d", health);
	draw_string(5, 5, 166.0/255, 226.0/255, 46.0/255,health_str);

	char score_str[50];
	sprintf(score_str, "SCORE: %d", score);
	draw_string(70, 5, 253.0/255, 151.0/255, 31.0/255,score_str);
	if(playing_game == 1) {
		game_over_splash();
		top_score_splash();
	}
	if(playing_game == 2) {
		high_score_splash();
		top_score_splash();
	}
	if(playing_game == 3) {
		splash();
		top_score_splash();
	}

	// Tell the API that we are done with this frame
	glPopMatrix();
	glutSwapBuffers();
}

void LightingInit(){
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	float intensity = 0.0;
	GLfloat lightPos[] = {0,0,10,1};
	float amb_color[] = {0.4,0.4,0.4,1};
	float spec_color[] = {intensity,intensity,intensity,1};
	float dif_color[] = {intensity,intensity,intensity,1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec_color);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void init(void) {
	// We want a smooth interpolation of color between vertices
	glShadeModel(GL_SMOOTH);

	// Enable the z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);

	// Set the background color to clear to white
	//glClearColor(17.0/255.0, 17.0/255.0, 17.0/255.0, 0.0f);
        glClearColor(1,1,1, 0.0f);

	// Initilize the Projection matrix; in this program we never change it
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	LightingInit();
	glOrtho(0.0, 100.0, 0.0, 100.0, -10.0, 10.0);

	// Initilize the ModelView matrix; in this program we never change it
	// 3D viewing based on assigned eye location, lookat point, and up vector
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	backgroundm = getBackgroundModel();
	srand(time(NULL));

	for (int i = 0; i < 5; i++) {
		a = new Asteroid(rand()%100,rand()%100,rand()%100/100.0,rand()%100/100.0,4);
		asteroids.push_back(a);
	}

	s = new Ship(50, 50, 5);

	ship_rotation = 0.0;
	ship_rotation_next = 0.0;
	ship_direction = 0.0; 
	ship_direction_next = 0.0;
        strafe_direction = 0.0;
        strafe_direction_next = 0.0;

	top_score = get_lowest_top_score();
}


void keyboardUp(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			shoot_key = false;
			break;
		case 'w':
			w_key = false;
			break;
		case 's':
			s_key = false;
			break;
		case 'd':
			d_key = false;
			break;
		case 'a':
			a_key = false;
			break;
		default:
			break;
	}


	// Force the screen to be redrawn with new parameters.
	// If this wasn't called, you might have to wait for the user
	// to cover and then uncover the window.
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		case ' ':
			shoot_key = true;
			break;
		case 'w':
			w_key = true;
			break;
		case 's':
			s_key = true;
			break;
		case 'd':
			d_key = true;
			break;
		case 'a':
			a_key = true;
			break;
		default:
			break;
	}


	// Force the screen to be redrawn with new parameters.
	// If this wasn't called, you might have to wait for the user
	// to cover and then uncover the window.
	glutPostRedisplay();
}


void mouseMoveClicker(int x, int y){
	px = x/(window_width/100.0);
	py = (window_height-y)/(window_height/100.0);

	glutPostRedisplay();
}

void mouseClicker(int button, int state, int x, int y){
		
		switch(button){
			case GLUT_LEFT_BUTTON:
				if(state == GLUT_UP)
					shoot_key=false;
				else
					shoot_key=true;
				break;

			case GLUT_RIGHT_BUTTON:
				if(state == GLUT_UP)
					w_key=false;
				else
					w_key=true;
				break;
			default:
				break;
		}	

	px = x/(window_width/100.0);
	py = (window_height-y)/(window_height/100.0);
	glutPostRedisplay();

}

void mouse(int x, int y){
	
	// Mouse rotation function
	px = x/(window_width/100.0);
	py = (window_height-y)/(window_height/100.0);



	glutPostRedisplay();
}


void animate(int key) {
	  
	if(playing_game == 0) {
		ship_rotation_next = (180/PI)*atan2((py-s->y),(px-s->x))-90;

		if(shoot_key) {
			if(!shoot_cooldown) {
				lasers.push_back(new Laser(s->x, s->y, s->rotation,LASER_SIZE, LASER_SPEED));
				shoot_cooldown = true;
				playLaserSound();
			} 
		}
		if(w_key) {
			ship_direction_next = fmod((ship_direction+1),2);
		}
		if(s_key) {
			ship_direction_next = fmod((ship_direction-1),2);
		}
		if(a_key) {
			strafe_direction_next = fmod((strafe_direction-1),2);
		}
		if(d_key) {
			strafe_direction_next = fmod((strafe_direction+1),2);
		}

		for(int i=0; i<(signed int)asteroids.size(); i++){
			asteroids[i]->Move();
			for(int j=0; j<(signed int)asteroids.size(); j++){
				if(asteroids[i]->Collision(asteroids[j]) && i!=j){
					if(i<j) {
						asteroids[j]->spawnChildren(&asteroids, j);
						asteroids[i]->spawnChildren(&asteroids, i);
					} else {
						asteroids[i]->spawnChildren(&asteroids, i);
						asteroids[j]->spawnChildren(&asteroids, j);
					}
					break;
				}
			}
			if(asteroids[i]->Collision(s)){
				health-=10*(int)asteroids[i]->radius;
				asteroids.erase(asteroids.begin()+i);
				playShipHitSound();
			}

		}

		// Check for laser collisions
		for(int i=0; i<(signed int)lasers.size(); i++){
			lasers[i]->Move();
			if(lasers[i]->onScreen())
				lasers.erase(lasers.begin()+i);

			for(int j=0; j<(signed int)asteroids.size(); j++){
				if(lasers[i]->Collision(asteroids[j])){
					lasers.erase(lasers.begin()+i);
					asteroids[j]->spawnChildren(&asteroids, j);
					score+=100;
					playAsteroidHitSound();
					//cout << score << endl;
					break;
				}
			}
		}

		// Update ship position
		
		#ifndef GODMODE
		if(health <= 0) {
			if(score > top_score){
				playing_game = 2;
			} else {
				playing_game = 1;
			}
			splash();
		}
		#endif

		ship_direction = ship_direction_next;
		strafe_direction = strafe_direction_next;
		ship_rotation = ship_rotation_next;

		s->Move(ship_direction, strafe_direction, ship_rotation);
		ship_direction_next = 0;
		strafe_direction_next=0;	
		if(shoot_cooldown) {
			if(shoot_cooldown_count < SHOOT_COOLDOWN){
				shoot_cooldown_count++;
			} else {
				shoot_cooldown = false;
				shoot_cooldown_count = 0;
			}
		}	

		// Generate more asteroids based on score
		double cooldown_factor = (ASTEROID_COOLDOWN)-0.05*pow((score+1)/1000,4)/50;
		if(cooldown_factor < 4) {
			cooldown_factor = 4;
		}
		if(asteroid_cooldown_count <cooldown_factor ) {
			asteroid_cooldown_count++;
		} else {
			fflush(stdout);
			if(rand()%2 == 0){
				if(rand()%2 == 0) {
					a = new Asteroid(0,rand()%100,rand()%100/100.0,rand()%100/100.0,4);
				} else {
					a = new Asteroid(100,rand()%100,-rand()%100/100.0,-rand()%100/100.0,4);
				}
			} else {
				if(rand()%2 == 0) {
					a = new Asteroid(rand()%100,0,rand()%100/100.0,rand()%100/100.0,4);
				} else {
					a = new Asteroid(rand()%100,100,-rand()%100/100.0,-rand()%100/100.0,4);
				}
			}
			asteroids.push_back(a);
			asteroid_cooldown_count=0;
		}
		
		glutPostRedisplay();
		glutTimerFunc(1000/30, animate, 0);

	} else if (playing_game == 1 || playing_game == 2 ){	// Game over
		print_logo(2);
		topScore(score);

		health = MAX_HEALTH;
		score = 0;
		asteroids.clear();
		lasers.clear();
		playing_game = 0;
		init();
		glutPostRedisplay();
		glutTimerFunc(1000/30, animate, 0);

	} else if (playing_game == 3) {
		sleep(3);
		playing_game = 0;
		glutPostRedisplay();
		glutTimerFunc(1000/30, animate, 0);
	}

}


int main(int argc, char** argv) {

	print_logo(1);

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Asteroid GAMEEEE!!!");

	//Initializing models + audio
	initModels();
        initAudio();
	// Call our init function
	init();

	// Register our callbacks with GLUT
	// Note that these are actually pointers to the functions declared above.
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(mouseClicker);
	glutMotionFunc(mouseMoveClicker);
	glutReshapeFunc(reshapeWindow);
	glutTimerFunc(1000/30, animate, 0);

	// Call GLUT's main loop, which never ends
	glutMainLoop();

	// Our program will never reach here
	return 0;
}
