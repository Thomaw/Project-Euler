#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RULES 32
#define MAX_PRESSURE 16
#define SEQ_LENGTH 16

typedef unsigned char uchar;

typedef struct {
    uchar i, seq[MAX_RULES][SEQ_LENGTH], correct[MAX_RULES];
} rule_set;

void rule_push(rule_set *r, const char *seq, const uchar correct) {
    /* Add a rule to the rule_set */
    int i;
    r->correct[r->i] = correct;
    for(i=0; i<SEQ_LENGTH; ++i) r->seq[r->i][i] = (seq[i] - '0');
    if((++r->i) == MAX_RULES) r->i = 0;
}

uchar rule_score(rule_set *r, const uchar max, const uchar *seq) {
    /* Calculate a score from the rule_set, stop if max is exceeded */
    int i, j;
    uchar wrong = 0, match;
    for(j=0; j<r->i; ++j) {
        match = 0;
        for(i=0; i<SEQ_LENGTH; ++i) {
            if(r->seq[j][i] == seq[i]) ++match;
        }
        wrong += abs(r->correct[j] - match);
        if(wrong > max) return wrong;
    }
    return wrong;
}

int main(int argc, char *argv[]) {
    int n=0, i=0;
    rule_set rules;
    uchar seq[SEQ_LENGTH], score=255, old_score=255, new_score;
    uchar pressure=0, old;

    srand(time(0));

    rules.i = 0;
    rule_push(&rules, "5616185650518293", 2);
    rule_push(&rules, "3847439647293047", 1);
    rule_push(&rules, "5855462940810587", 3);
    rule_push(&rules, "9742855507068353", 3);
    rule_push(&rules, "4296849643607543", 3);
    rule_push(&rules, "3174248439465858", 1);
    rule_push(&rules, "4513559094146117", 2);
    rule_push(&rules, "7890971548908067", 3);
    rule_push(&rules, "8157356344118483", 1);
    rule_push(&rules, "2615250744386899", 2);
    rule_push(&rules, "8690095851526254", 3);
    rule_push(&rules, "6375711915077050", 1);
    rule_push(&rules, "6913859173121360", 1);
    rule_push(&rules, "6442889055042768", 2);
    rule_push(&rules, "2321386104303845", 0);
    rule_push(&rules, "2326509471271448", 2);
    rule_push(&rules, "5251583379644322", 2);
    rule_push(&rules, "1748270476758276", 3);
    rule_push(&rules, "4895722652190306", 1);
    rule_push(&rules, "3041631117224635", 3);
    rule_push(&rules, "1841236454324589", 3);
    rule_push(&rules, "2659862637316867", 2);

    /* Randomly initialize sequence */
    for(i=0; i<SEQ_LENGTH; ++i) seq[i] = 0;

    while(score != 0) {

        for(i=0; i<SEQ_LENGTH; ++i) {
            /* "walk" to the lowest local point */
            old = seq[i];
            seq[i] = rand() % 10;
            new_score = rule_score(&rules, score, seq);
            if(new_score <= score) score = new_score;
            else seq[i] = old;
        }

        if(score == old_score) {
            /* "jump" randomly if stuck in local "ditch" too long */
            if((++pressure) == MAX_PRESSURE) {
                pressure = 0;
                seq[rand() % SEQ_LENGTH] = rand() % 10;
                score = rule_score(&rules, 255, seq);
            }
        } else {
            /* Score has changed (not stuck), release pressure */
            pressure = 0;
        }

        if(((++n) == 100000) || (score == 0)) {
           /* Print best (lowest) score */
           for(i=0; i<SEQ_LENGTH; ++i) printf("%i", seq[i]);
           printf(" %i\n", score);
           n = 0;
        }

        old_score = score;
    }
}