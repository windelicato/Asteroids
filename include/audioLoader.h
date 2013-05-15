/**
 * @file 
 * 
 */
#ifndef _audioLoader_h_
#define _audioLoader_h_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>

/**
 *  Static global variables to connect audio source to buffer
 */
static ALuint laserBuffer,        laserSource,
              asteroidBuffer,     asteroidSource,
              shipBuffer,         shipSource,
              highScoreBuffer,    highScoreSource,
              gameOverBuffer,     gameOverSource;

/**
 *  Static global variable catch errors
 */
static ALenum error;

/**
 *  Creates audio buffers and links them to source files
 */
void initAudio();

/**
 *  Plays laser shot sound
 */
void playLaserSound();

/**
 *  Plays asteroid hit sound
 */
void playAsteroidHitSound();

/**
 *  Plays ship damage sound 
 */
void playShipHitSound();

/**
 *  Plays high score music 
 */
void playHighscoreSound();

/**
 *  Plays game over music
 */
void playGameOverSound();

/**
 *  Frees audio buffers
 */
void closeAudio();

#endif
