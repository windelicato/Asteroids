/**
 * @file 
 * 
 */

#ifndef _asteroid_h_
#define _asteroid_h_

#include <vector>
#include <ctime>
#include <cmath>

#include "character.h"
#include "modelLoader.h"

using namespace std;

/**
 *  Describes an asteroid character in the asteroid game.
 */
class Asteroid : public Character {

	public:
                /**
                 *
                 *  @param x
                 *  @param y
                 *  @param dx
                 *  @param dy
                 *  @param r
                 */
		Asteroid(double x, double y, double dx, double dy, double r );
	        /**
                 *
                 */
                ~Asteroid();
		
                /**
		 *  @param target 
		 *  @param index 
		 */
                void spawnChildren(vector<Asteroid *> * target, int index);
		
                /**
                 *  Draws the Asteroid
                 */
                void Draw();

                /**
                 *  Stores the GLMmodel of the asteroid  
                 */
		GLMmodel * asteroidModel;
                
                /**
                 *  Member data of the asteroid class
                 */
		double x_rot;
                
                /**
                 *  Member data of the asteroid class
                 */
                double y_rot;
               
                /**
                 *  Member data of the asteroid class
                 */
                double z_rot;
                
                /**
                 *  Member data of the asteroid class
                 */
                double speed_rot;
                
                /**
                 *  Member data of the asteroid class
                 */
                double pos_rot;

};

#endif
