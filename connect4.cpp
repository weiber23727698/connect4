#include <bits/stdc++.h>
#include "connect4.h"
using namespace std;
//討論同學: b09902055、b09902016、b09902073
int table[7][6], high[7], score[7], delta[5] = {0, 0, 4000, 9000, 0}, up = 1e9, down = -1e9;

void add(int column, int color){//1: 自己; 2: 對手
    table[column][high[column]] = color;
    high[column]++;
}

void destroy(int column){
    high[column]--;
    table[column][high[column]] = 0;
}

int scoring(){
    int totall = 0;
    for(int i = 0;i < 7;i++){
        for(int j = 0;j < 6;j++){
            if(i <= 3){//右
                int red = 0, yellow = 0, blank = 0;
                for(int x = 0;x <= 3;x++){
                    if(table[i+x][j] == 1)  red++;
                    else if(table[i+x][j] == 2) yellow++;
                    else    blank++;
                }
                if(blank != 4){
                    if(red+blank == 4){
                        if(red < 4) totall = totall + delta[red];
                        else if(red == 4)   return up;
                    }
                    else if(yellow+blank == 4){
                        if(yellow < 4)    totall = totall - 4*delta[yellow]/3;
                        else if(yellow == 4)   return down;
                    }
                }
            }
            if(j <= 2){//上
                int red = 0, yellow = 0, blank = 0;
                for(int x = 0;x <= 3;x++){
                    if(table[i][j+x] == 1)  red++;
                    else if(table[i][j+x] == 2) yellow++;
                    else    blank++;
                }
                if(blank != 4){
                    if(red+blank == 4){
                        if(red < 4) totall = totall + delta[red];
                        else if(red == 4)   return up;
                    }
                    else if(yellow+blank == 4){
                        if(yellow < 4)    totall = totall - 4*delta[yellow]/3;
                        else if(yellow == 4)   return down;
                    }
                }
            }
            if(i<=3 && j<=2){//右上
                int red = 0, yellow = 0, blank = 0;
                for(int x = 0;x <= 3;x++){
                    if(table[i+x][j+x] == 1)  red++;
                    else if(table[i+x][j+x] == 2) yellow++;
                    else    blank++;
                }
                if(blank != 4){
                    if(red+blank == 4){
                        if(red < 4) totall = totall + delta[red];
                        else if(red == 4)   return up;
                    }
                    else if(yellow+blank == 4){
                        if(yellow < 4)    totall = totall - 4*delta[yellow]/3;
                        else if(yellow == 4)   return down;
                    }
                }
            }
            if(i<=3 && j>=3){//右下
                int red = 0, yellow = 0, blank = 0;
                for(int x = 0;x <= 3;x++){
                    if(table[i+x][j-x] == 1)  red++;
                    else if(table[i+x][j-x] == 2) yellow++;
                    else    blank++;
                }
                if(blank != 4){
                    if(red+blank == 4){
                        if(red < 4) totall = totall + delta[red];
                        else if(red == 4)   return up;
                    }
                    else if(yellow+blank == 4){
                        if(yellow < 4)    totall = totall - 4*delta[yellow]/3;
                        else if(yellow == 4)   return down;
                    }
                }
            }
        }
    }
    return totall;
}

int grading(bool player, int depth){
    int point = scoring();
    if(depth==5 || point==up || point==down)
        return point;
    else{
        if(player){
            int best = INT_MIN, calpoint = INT_MIN;
            for(int i = 0;i < 7;i++){
                if(high[i] < 6){
                    add(i, 1);
                    calpoint = max(best, grading(false, depth+1));
                    best = max(best, calpoint);
                    destroy(i);
                }
            }
            return best;
        }
        else{
            int best = INT_MAX, calpoint = INT_MAX;
            for(int i = 0;i < 7;i++){
                if(high[i] < 6){
                    add(i, 2);
                    calpoint = grading(true, depth+1);
                    best = min(best, calpoint);
                    destroy(i);
                }
            }
            return best;
        }
    }
}

int decide(int yp_move) {
    if (yp_move == -1) {
        memset(table, 0, 42*sizeof(int));
        memset(high, 0, 7*sizeof(int));
        add(3, 1);
        return 3;
    }
    else {
        add(yp_move, 2);
        for(int i = 0;i < 7;i++){
            int maxpoint = INT_MIN, calpoint = INT_MIN;
            if(high[i] < 6){
                add(i, 1);
                calpoint = grading(false, 1);
                destroy(i);
            }
            score[i] = max(maxpoint, calpoint);
        }
        if(score[3] > down)    score[3] += delta[2];
        int choice = 0;
        for(int i = 1;i < 7;i++){
            if(score[choice] < score[i])
                choice = i;
        }
        if(choice==0 && high[0]>=6){
            for(int i = 1;i < 7;i++){
                if(high[i] < 6)
                    choice = i;
            }
        }
        add(choice, 1);
        return choice;
    }
}
