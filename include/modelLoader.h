/**
 * @file 
 * 
 */
#ifndef _modelLoader_h_
#define _modelLoader_h_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <glm.h>
#include <cstring>
#include <iostream>


/**
 *  Wrapper for glmReadOBJ file
 *  Opens obj file and returns reference to model
 *
 *  @param filename filename of obj file
 */
GLMmodel* loadModel( std::string filename);

/**
 *  Wrapper for glmDraw function
 *  Draws the model reference to the screen
 *
 *  @param model reference to model loaded in memory
 */
void drawModel(GLMmodel* model);

/**
 *  Calls load model for the all models in the scene. Ship, asteroid, background
 */
void initModels();

/**
 *  Returns reference to static ship model 
 */
GLMmodel* getShipModel();

/**
 *  Returns reference to static asteroid model 
 */
GLMmodel* getAsteroidModel();

/**
 *  Returns reference to static background model 
 */
GLMmodel* getBackgroundModel();

/**
 *  Holds a reference to the ship model so we don't have to keep loading it
 */
static GLMmodel* ship;

/**
 *  Holds a reference to the asteroid model so we don't have to keep loading it
 */
static GLMmodel* asteroid;

/**
 *  Holds a reference to the background model so we don't have to keep loading it
 */
static GLMmodel* background;
#endif
