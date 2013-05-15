#include "top_scores.h"
#include "audioLoader.h"
#include "gameText.h"

#define MAX_TOP_SCORES 5

using namespace std;

const char* score_path = "./data/scores.txt";
const char* format = "PLAYER: %s SCORE: %d\n";
int scores[MAX_TOP_SCORES+1];
char* players[MAX_TOP_SCORES+1];

int get_lowest_top_score(void) {
	int n = loadScores();

	if(n != MAX_TOP_SCORES) {
		return 0;
	}

	int min = scores[0];
	for (int i = 1; i < n; i++) {
		if(scores[i] < min){	
			min = scores[i];
		}
	}
	return min;
}

void score_buffer(char** p, int* s){
	int n = loadScores();
	int i;
	for (i = 0; i < n; i++) {
		s[i] = scores[i];	
		p[i] = players[i];	
	}
	for (i = n; i < MAX_TOP_SCORES; i++) {
		s[i] = 0;
		p[i] = NULL;
	}
}


// Loads scores from file into buffer
// Returns the number of top scores signed
int loadScores(void){
	FILE* top_score_fd = fopen(score_path, "r");
	int score;
	char player[100];

	int fields_read;
	int line_number = 0;
	while((fields_read = fscanf(top_score_fd, format, player, &score)) != EOF){
		if( fields_read != 2 ){ 
			printf("Invalid score syntax");
			return -1;
		}
		scores[line_number] = score;
		players[line_number] = (char*)malloc(100);

		memcpy(players[line_number], player, 99);

		line_number++;
	}
	fclose(top_score_fd);

	return line_number;
}

// Writes n scores to file
void saveScores(int n) {
	FILE* top_score_fd = fopen(score_path, "w");
	int i;

	for(i=0; i<n; i++) {
		fprintf(top_score_fd, format, players[i], scores[i]);
	}
	fclose(top_score_fd);
}

void topScore(int score) {
	int n = loadScores();
	if(n < MAX_TOP_SCORES) {
		// Definate top score player
		playHighscoreSound();
		print_logo(3);

		string player;
		cout << "Player: ";
		cin >> player;
		
		scores[n] = score;
		players[n] = (char*)player.c_str();
		saveScores(n+1);
	} else {
		// Check for lowest score
		int i;

		int min_i = 0;
		int min = scores[0];
		for(i=1; i<MAX_TOP_SCORES; i++){
			if(scores[i] < min) {
				min = scores[i];
				min_i = i;
			}
		}
		if (score > min) {
			playHighscoreSound();
			print_logo(3);

			string player;

			cout << "CONGRATULATIONS" << endl;
			cout << "What is your name winner?" << endl;
			cout << ">>> ";
			cin >> player;
			scores[min_i] = score;
			players[min_i] =(char*)player.c_str();
		} else {
			playGameOverSound();
			print_logo(2);
			sleep(3);
		}

		saveScores(n);
	}
}
