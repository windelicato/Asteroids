#include "gameText.h"
#include "top_scores.h"

using namespace std;

const char* top_score_title = "TOP SCORES:";

void top_score_splash(void){
	char* text[6];
	char* text_s[6];
	char* p[6];
	int s[6];
	score_buffer(p, s);
	int temp_int;
	char* temp_char;
	
	// Bubble Sort
	for( int i = 0; i <6; i++){
		for (int j = 0; j <6; j++){
			if(s[j] < s[i]){
				//swap
				temp_int = s[i];
				s[i] = s[j];
				s[j] = temp_int;

				
				temp_char = p[i];
				p[i] = p[j];
				p[j] = temp_char;
			}
		}
	}

	int i;
	for(i=0; i< 6; i++) {
		text[i] = (char*)malloc(100);
		text_s[i] = (char*)malloc(100);
		sprintf(text[i], "%d  %s", i+1 ,p[i], s[i]);
		sprintf(text_s[i], "%d", s[i]);
	}
	draw_string(30, 55, 166/255.0, 226/255.0, 46/255.0, (char*)top_score_title);
	for (i = 0; i < 5; i++) {
		draw_string(30, 50-3*i, 253/255.0, 151/255.0, 31/255.0, (char*)text[i]);
		draw_string(50, 50-3*i, 253/255.0, 151/255.0, 31/255.0, (char*)text_s[i]);
	}
}

void print_logo(int i) {
	system("clear");
	
	switch(i) {
		case 1:
			cout << "   _____            __                      .__    .___      " << endl;
			cout << "  /  _  \\   _______/  |_  ___________  ____ |__| __| _/______" << endl;
			cout << " /  /_\\  \\ /  ___/\\   __\\/ __ \\_  __ \\/  _ \\|  |/ __ |/  ___/" << endl;
			cout << "/    |    \\\\___ \\  |  | \\  ___/|  | \\(  <_> )  / /_/ |\\___ \\ " << endl;
			cout << "\\____|__  /____  > |__|  \\___  >__|   \\____/|__\\____ /____  >" << endl;
			cout << "        \\/     \\/            \\/                     \\/    \\/ " << endl;
			break;
		case 2:
			cout << "   _________    _____   ____     _______  __ ___________ " << endl;
			cout << "  / ___\\__  \\  /     \\_/ __ \\   /  _ \\  \\/ // __ \\_  __ \\" << endl;
			cout << " / /_/  > __ \\|  Y Y  \\  ___/  (  <_> )   /\\  ___/|  | \\/" << endl;
			cout << " \\___  (____  /__|_|  /\\___  >  \\____/ \\_/  \\___  >__|   " << endl;
			cout << "/_____/     \\/      \\/     \\/                   \\/      " << endl;
			break;
		case 3:
			cout << ".__    .__       .__                                       ._." << endl;
			cout << "|  |__ |__| ____ |  |__     ______ ____  ___________   ____| |" << endl;
			cout << "|  |  \\|  |/ ___\\|  |  \\   /  ___// ___\\/  _ \\_  __ \\_/ __ \\ |" << endl;
			cout << "|   Y  \\  / /_/  >   Y  \\  \\___ \\\\  \\__(  <_> )  | \\/\\  ___/\\|" << endl;
			cout << "|___|  /__\\___  /|___|  / /____  >\\___  >____/|__|    \\___  >_" << endl;
			cout << "     \\/  /_____/      \\/       \\/     \\/                  \\/\\/" << endl;
			break;
	}
}

void high_score_splash(void){
	const char* text[6];
	text[0] = ".__    .__       .__                                       ._.";
	text[1] = "|  |__ |__| ____ |  |__     ______ ____  ___________   ____| |";
	text[2] = "|  |  \\|  |/ ___\\|  |  \\   /  ___// ___\\/  _ \\_  __ \\_/ __ \\ |";
	text[3] = "|   Y  \\  / /_/  >   Y  \\  \\___ \\\\  \\__(  <_> )  | \\/\\  ___/\\|";
	text[4] = "|___|  /__\\___  /|___|  / /____  >\\___  >____/|__|    \\___  >_";
	text[5] = "     \\/  /_____/      \\/       \\/     \\/                  \\/\\/";

	int i;
	for (i = 0; i < 6; i++) {
		draw_string(1, 80-2*i, 0.0, 1.0, 0.0, (char*)text[i]);
	}
}

void game_over_splash(void){
	const char* text[6];
	text[0] = "   _________    _____   ____     _______  __ ___________ ";
	text[1] = "  / ___\\__  \\  /     \\_/ __ \\   /  _ \\  \\/ // __ \\_  __ \\";
	text[2] = " / /_/  > __ \\|  Y Y  \\  ___/  (  <_> )   /\\  ___/|  | \\/";
	text[3] = " \\___  (____  /__|_|  /\\___  >  \\____/ \\_/  \\___  >__|   ";
	text[4] = "/_____/     \\/      \\/     \\/                   \\/      ";

	int i;
	for (i = 0; i < 5; i++) {
		draw_string(5, 80-2*i, 158/255.0, 111/255.0, 254/255.0, (char*)text[i]);
	}
}

void splash(void){

	const char* text[6];
	text[0] = "   _____            __                      .__    .___      ";
	text[1] = "  /  _  \\   _______/  |_  ___________  ____ |__| __| _/______";
	text[2] =  " /  /_\\  \\ /  ___/\\   __\\/ __ \\_  __ \\/  _ \\|  |/ __ |/  ___/";
	text[3] =  "/    |    \\\\___ \\  |  | \\  ___/|  | \\(  <_> )  / /_/ |\\___ \\ ";
	text[4] =  "\\____|__  /____  > |__|  \\___  >__|   \\____/|__\\____ /____  >";
	text[5] =  "        \\/     \\/            \\/                     \\/    \\/ ";

	int i;
	for (i = 0; i < 6; i++) {
		draw_string(2, 80-2*i, 22/255.0, 146/255.0, 208/255.0, (char*)text[i]);
	}
}

void draw_string(int x, int y, float r, float g, float b, char *string)
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f( r, g, b );
	glRasterPos3f(x, y, 10);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}
