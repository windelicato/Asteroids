/**
 * @file 
 * 
 */
#ifndef _laser_h_
#define _laser_h_

#include "character.h"

/**
 *  Describes a laser in game
 */
class Laser : public Character {

	public:
                /**
                 *  Constructor for laser type character
		 *
                 *  @param x
		 *  	initial x location on screen
                 *  @param y
		 *  	initial y location on screen
                 *  @param rotation
		 *  	angle laser was shot from
                 *  @param radius
		 *  	size of laser displayed on screen
                 *  @param speed
		 *  	speed of dx dy for laser
                 */
		Laser(double x, double y, double rotation, double radius, double speed);
		
		/**
		 *  Draws the laser on screen
		 */
		void Draw();

		/**
		 *  Checks to see if the laser is offscreen and ready for deletion
		 */
		bool onScreen();

		/**
		 *  member data of the laser class
		 */
	 	double rotation;
};

#endif
