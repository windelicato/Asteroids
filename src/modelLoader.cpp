#include "modelLoader.h"

/**
 * We will get warnings, but we need to only load the models once then reuse them
 */
void initModels(){
	ship = loadModel("models/ship/GhoulOBJ.obj");
	asteroid = loadModel("models/asteroid/asteroid.obj");
	background = loadModel("models/background/background.obj");

}
GLMmodel* getShipModel(){
	return ship;
}

GLMmodel* getAsteroidModel(){
	return asteroid;
}

GLMmodel *getBackgroundModel(){
	return background;
}
GLMmodel* loadModel( std::string filename){
	const char * c = filename.c_str();
	GLMmodel* model = NULL;
	model = glmReadOBJ((char*)c);
	glmUnitize(model);
	if(model == NULL)
		std::cout << "MODEL IS NULL"<<std::endl;
	return model;
}

void drawModel(GLMmodel* model){ 
	GLuint mode = GLM_SMOOTH|GLM_MATERIAL|GLM_TEXTURE;
	if (model) glmDraw(model, mode);
	else
		std::cout << "MODEL IS NULL IN DRAW"<<std::endl;
	

}

