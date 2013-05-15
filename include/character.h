/**
 * @file 
 * 
 */
#ifndef _character_h_
#define _character_h_

/**
 *  Describes a generic game character
 */
class Character {
		
	public:
		Character();
		~Character();

		/**
		 *  Generic draw function, will be overloaded by all child classes
		 */
		virtual void Draw();

		/**
		 *  Generic move method
		 *  	Moves character based on current x,y by dx,dy
		 *  	Accounts for screen wraparound
		 */
		void Move();

		/**
		 *  Generic collision method
		 *  	Returns whether collision with another character
		 *
		 *  	@param c character to test for collision with
		 */
		bool Collision(Character *c);

		/**
		 *  Are we wrapping around?
		 */
		bool wrapAround;

		/**
		 *  Member data of the character class
		 */
		double radius; 	//Radius of character

		/**
		 *  Member data of the character class
		 */
		double x, y; 	//Position

		/**
		 *  Member data of the character class
		 */
		double dx, dy; 	//Direction

		/**
		 *  Member data of the character class
		 */
		double health;
};

#endif
