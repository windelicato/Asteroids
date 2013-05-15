#include "audioLoader.h"

void initAudio(){

	alutInit(0,NULL);
	alGetError();

	//Create Buffers
	laserBuffer = alutCreateBufferFromFile("audio/laser.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	asteroidBuffer = alutCreateBufferFromFile("audio/Coin.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	shipBuffer = alutCreateBufferFromFile("audio/Block.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - ship buffer from file: %s\n",alutGetErrorString(error));
	highScoreBuffer = alutCreateBufferFromFile("audio/smb_world_clear.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - ship buffer from file: %s\n",alutGetErrorString(error));
	gameOverBuffer = alutCreateBufferFromFile("audio/smb_mariodie.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - ship buffer from file: %s\n",alutGetErrorString(error));

	//Generate Sources
	alGenSources(1, &laserSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alGenSources(1, &asteroidSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alGenSources(1, &shipSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alGenSources(1, &highScoreSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alGenSources(1, &gameOverSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	//Link sources to buffers
	alSourcei(laserSource, AL_BUFFER, laserBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alSourcei(asteroidSource, AL_BUFFER, asteroidBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alSourcei(shipSource, AL_BUFFER, shipBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alSourcei(highScoreSource, AL_BUFFER, highScoreBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
	alSourcei(gameOverSource, AL_BUFFER, gameOverBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

}

void playLaserSound(){

	alSourcePlay(laserSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play laser: %s\n",alutGetErrorString(error));
}

void playAsteroidHitSound(){

	alSourcePlay(asteroidSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play asteroid: %s\n",alutGetErrorString(error));
}

void playShipHitSound(){

	alSourcePlay(shipSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play ship: %s\n",alutGetErrorString(error));
}

void playHighscoreSound(){

	alSourcePlay(highScoreSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play ship: %s\n",alutGetErrorString(error));
}

void playGameOverSound(){

	alSourcePlay(gameOverSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play ship: %s\n",alutGetErrorString(error));
}

void closeAudio(){

	alutSleep(1);
	alutExit();

}
