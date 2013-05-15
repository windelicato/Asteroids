/**
 * @file 
 * 
 */

#ifndef _top_scores_h_
#define _top_scores_h_
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
#include<unistd.h>

/**
 *  Returns lowest score in top scores that player must pass
 *  	in order to be included on the top scoreboard
 */
int get_lowest_top_score(void);

/**
 *  Copies top scores into player and score buffer for use outside of this file
 *
 *  @param p pointer to malloc'ed array of destination player names
 *  @param s pointer to array of destination scores
 */
void score_buffer(char** p, int* s);

/**
 *  Loads the scores from /data/scores.txt into static buffers
 */
int loadScores(void);

/**
 *  Adds top score to top score database. Prompts user for name
 *
 *  @param score new score to be loaded
 */
void topScore(int score);

/**
 *  Saves n scores into database. Used internally in this file
 *
 *  @param n number of scores to be loaded into database
 */
void saveScores(int n);

#endif
