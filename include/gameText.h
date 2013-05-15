/**
 * @file 
 * 
 */

#ifndef _game_text_h_
#define _game_text_h_
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


/**
 *  Clears screen and prints ascii logos to console
 *
 *  @param i selection to print... options are:
 *  	1) Asteroids logo
 *  	2) Game over logo
 *  	3) High score logo
 */
void print_logo(int i);

/**
 *  Prints high score logo to GL window
 */
void high_score_splash(void);

/**
 *  Prints top scores to GL window
 */
void top_score_splash(void);

/**
 *  Prints game over logo to GL window
 */
void game_over_splash(void);

/**
 *  Prints asteroids logo to GL window
 */
void splash(void);

/**
 *  Draws a string of text to OPEN gl window
 *
 *  @param x
 *  	X position on screen
 *  @param y
 *  	Y position on screen
 *  @param r
 *  	Red color
 *  @param g
 *  	Green color
 *  @param b
 *  	Blue color
 *  @param string
 *  	Sting to print
 */
void draw_string(int x, int y, float r, float g, float b, char *string);

#endif
