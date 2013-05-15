/**
 * @file 
 * 
 */
#ifndef _ship_h_
#define _ship_h_

#include "character.h"
#include "modelLoader.h"

/**
 *  Describes the ship in game
 */
class Ship : public Character {

	public:
		/**
		 *  Constructor for ship class
                 *
                 *  @param x initial x position of ship
                 *  @param y initial y position of ship
                 *  @param r radius of ship for collisions
                 */
		Ship(double x, double y, double r);

		/*
		 * Draws ship onto screen with ship model at initial position
		 */
		void Draw();

		/*
		 *  Moves ship based on thrust and strafe directions at an angle r
		 *
		 *  @param d thrust ammount to move ship by
		 *  @param s strafe ammount to move ship by
		 *  @param r angle to to move ship by
		 */
		void Move(double d, double s, double r);

		/*
		 * Draws ship onto screen with ship model at initial position
		 */
		void Move();
		
                /**
                 *  Member data of the asteroid class
                 */
		double rotation;

                /**
                 *  Member data of the asteroid class
                 */
		double direction;

                /**
                 *  Member data of the asteroid class
                 */
		double rot_prev;

                /**
                 *  Member data of the asteroid class
                 */
		double tilt_angle;

                /**
                 *  Member data of the asteroid class
                 */
		GLMmodel* shipModel;

};

#endif
