#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define ROWS 6
#define COLS 7
void set_zero(int matrix[ROWS][COLS]){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            matrix[i][j] = 0;
        }
    }
}
void win_cord_setzero(int coord[4][2]){
    for(int i = 0; i<4; i++){
        for(int j=0; j<2; j++){
            coord[i][j] = 0;
        }
    }
}
void print_win_cord(int coord[4][2]){
    for(int i = 0; i<4; i++){
        printf("coord: %d, %d\n", coord[i][0], coord[i][1]);
    }
}
bool in_win_coord(int a, int b, int coords[4][2]){
    for(int i = 0; i<4; i++){
        if((a == coords[i][0]) && (b == coords[i][1]) && (coords[1][0] | coords[1][1] > 0)){
            return 1;
        }
    }
    return 0;
}
void clean_input(){
    int c; while ((c = getchar()) != '\n' && c != EOF) {};
}
bool begin_new(){
    while(1){
        char choice;
        clean_input();
        printf("\nDo you wish to start again? [y/n]");
        choice = getchar();
        printf("%c", choice);
        if(choice == 'y'){
            return 0;
        }
        else if(choice == 'n'){
            return 1;
        }
    }
}
//print the matrix but modded, if the value is 1, print " X", if 2 print " O", if other(0) print "  "
void print_matrix(int matrix[ROWS][COLS], int latest, int win_coords[4][2]){
    printf("\e[1J");
    if(latest > 0){
	for(int i=0; i<7; i++){
	    if(i == latest-1){
	        printf(" %c", 33);
	    }
            else{
	        printf("  ");
	    }
	}
    }
    printf("\n");
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if(in_win_coord(i, j, win_coords)){
                if(matrix[i][j]==1){
                    printf("\e[4m|\e[0m");
                    printf("\e[4;5;31m%c\e[0m", 35);
                }
                else if(matrix[i][j]==2){
                    printf("\e[4m|\e[0m");
                    printf("\e[4;5;37m%c\e[0m", 35);
                }
                else{
                    printf("\e[4m| \e[0m");
                }
            }
            else{
                if(matrix[i][j]==1){
                    printf("\e[4m|\e[0m");
                    printf("\e[4;31m%c\e[0m", 35);
                }
                else if(matrix[i][j]==2){
                    printf("\e[4m|\e[0m");
                    printf("\e[4;37m%c\e[0m", 35);
                }
                else{
                    printf("\e[4m| \e[0m");
                }
            }
        }
        printf("\e[4m|\e[0m");
        printf("\n");
    }
    printf(" 1 2 3 4 5 6 7\n");
}
void print_debug(int matrix[ROWS][COLS]){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int winner_rows(int matrix[ROWS][COLS], int win_coord[4][2]){
    int p1=0;
    int p2=0;
    //check all rows, count up p1 or p2 when either 1 or 2 is detected at the position in the array.
    //if the previously checked position doesn't have the same value as the presently checked position, set p1 & p2 to zero.
    for(int i=0; i<6; i++){
        p1=0;
        p2=0;
        for(int j=0; j<7; j++){
            if(matrix[i][j]!=matrix[i][j-1]){
                p1=0;
                p2=0;
            }
            if(matrix[i][j]==1){
                p1++;
                win_coord[p1-1][0] = i;
                win_coord[p1-1][1] = j;
            }
            else if(matrix[i][j]==2){
                p2++;
                win_coord[p2-1][0] = i;
                win_coord[p2-1][1] = j;
            }
            if(p1==4||p2==4){
                return 1;
            }
        }
    }
    return 0;
}
    //check all columns, count up p1 or p2 when either 1 or 2 is detected at the position in the array.
    //if the previously checked position doesn't have the same value as the presently checked position, set p1 & p2 to zero.
int winner_columns(int matrix[ROWS][COLS], int win_coord[4][2]){
    int p1=0;
    int p2=0;
    for(int i=0; i<7; i++){
        p1=0;
        p2=0;
        for(int j=0; j<6; j++){
            if(matrix[j][i]!=matrix[j-1][i]){
                p1=0;
                p2=0;
            }
            if(matrix[j][i]==1){
                p1++;
                win_coord[p1-1][0] = j;
                win_coord[p1-1][1] = i;
            }
            else if(matrix[j][i]==2){
                p2++;
                win_coord[p2-1][0] = j;
                win_coord[p2-1][1] = i;
            }
            if(p1==4||p2==4){
                return 1;
            }
        }
    }
    return 0;
}
    //check all diagonals sloping right that can contain 4 or more values
    //count up p1 or p2 when either 1 or 2 is detected at the position in the array.
    //if the previously checked position doesn't have the same value as the presently checked position, set p1 & p2 to zero.
int winner_diagR(int matrix[ROWS][COLS], int win_coord[4][2]){
    int p1=0;
    int p2=0;
    for(int j=1; j<3; j++){
        p1=0;
        p2=0;
        for(int i=5; i>0; i--){
            if((i-j)<0){
                break;
            }
            if(matrix[i][i-j]!=matrix[i+1][i-j+1]){
            p1=0;
            p2=0;
            }
            if(matrix[i][i-j]==1){
                p1++;
                win_coord[p1-1][0] = i;
                win_coord[p1-1][1] = i-j;
            }
            else if(matrix[i][i-j]==2){
                p2++;
                win_coord[p2-1][0] = i;
                win_coord[p2-1][1] = i-j;
            }
            if(p1==4){
                return 1;
            }
            else if(p2==4){
                return 2;
            }
        }
    }
    for(int j=0; j<4; j++){
        p1=0;
        p2=0;
        for(int i=0; i<6; i++){
            if((i+j)>6){
                break;
            }
            if(matrix[i][i+j]!=matrix[i-1][i+j-1]){
            p1=0;
            p2=0;
            }
            if(matrix[i][i+j]==1){
                p1++;
                win_coord[p1-1][0] = i;
                win_coord[p1-1][1] = i+j;
            }
            else if(matrix[i][i+j]==2){
                p2++;
                win_coord[p2-1][0] = i;
                win_coord[p2-1][1] = i+j;
            }
            if(p1==4){
                return 1;
            }
            else if(p2==4){
                return 2;
            }
        }
    }
    return 0;
}
    //check all diagonals sloping left that can contain 4 or more values.
    //if the previously checked position doesn't have the same value as the presently checked position, set p1 & p2 to zero.
    //count up p1 or p2 when either 1 or 2 is detected at the position in the array.
int winner_diagL(int matrix[ROWS][COLS], int win_coord[4][2]){
    int p1=0;
    int p2=0;
    for(int j=0; j<2; j++){
        p1=0;
        p2=0;
        int count=4;
        for(int i=0; i<5; i++){
            if((count-j)<0){
                break;
            }
            if(matrix[i][count-j]!=matrix[i-1][count-j+1]){
            p1=0;
            p2=0;
            }
            if(matrix[i][count-j]==1){
                p1++;
                win_coord[p1-1][0] = i;
                win_coord[p1-1][1] = count-j;
            }
            else if(matrix[i][count-j]==2){
                p2++;
                win_coord[p2-1][0] = i;
                win_coord[p2-1][1] = count-j;
            }
            if(p1==4){
                return 1;
            }
            else if(p2==4){
                return 2;
            }
            count--;
        }
    }
    for(int j=0; j<4; j++){
        p1=0;
        p2=0;
        int count=0;
        for(int i=5; i>=0; i--){

            if((count+j)>6){
                break;
            }
            if(matrix[i][count+j]!=matrix[i+1][count+j-1]){
            p1=0;
            p2=0;
            }
            if(matrix[i][count+j]==1){
                p1++;
                win_coord[p1-1][0] = i;
                win_coord[p1-1][1] = count+j;
            }
            else if(matrix[i][count+j]==2){
                p2++;
                win_coord[p2-1][0] = i;
                win_coord[p2-1][1] = count+j;
            }
            if(p1==4){
                return 1;
            }
            else if(p2==4){
                return 2;
            }
            count++;
        }
    }
    return 0;
}
//let the player choose what column they want to drop thier marken in, then check from the highest row (lowest when printed)
//if the position is valued 0 or other, if the position is set to other than 0
//the check the same column but one lower row (higher when printed). Set the next available position to 1 or 2.
int place_marker(int matrix[ROWS][COLS], int choice, int player){

    for(int i=5; i>=0; i--){
        if(matrix[i][choice-1]!=0){
            if(i==0){
                return 1;
            }
            continue;
        }
        matrix[i][choice-1]=player;
        break;
    }
    return 0;
}

int main()
{
    int matrix[6][7];
    int win_coord[4][2];
    int player;
    int choice = 1;
    int stats[]={0,0,0};
    set_zero(matrix);
    while(true){
        for(int i=0; i<42; i++){
            print_matrix(matrix, choice, win_coord);
            if(i%2==0){
                player = 1;
            }
            else{
                player = 2;
            }
            printf("Player %d, place you marker.\n", player);
            printf("Input a number 1-7: ");
            while(1){
                if((scanf("%d", &choice)!=1)||(choice<1||choice>7)){
                    printf("\e[1A");
                    clean_input();
                    if(choice == 0){
                        printf("\nGood Bye!\n");
                        return 0;
                    }
                    printf("\r\e[2K\rInput must be an integer between 1-7: ");
                    continue;
                }
                if(place_marker(matrix, choice, player)){
                    printf("\e[1A");
                    printf("\r\e[2K\rThat column is full, pick another: ");
                    continue;
                }
                break;
            }

            if(winner_rows(matrix, win_coord)||winner_columns(matrix, win_coord)||winner_diagR(matrix, win_coord)||winner_diagL(matrix, win_coord)){
                stats[player-1]+=1;
                print_matrix(matrix, choice, win_coord);
                printf("Player %d wins!\n\n", player);
                for(int i=0; i<3; i++){
                    if(i==2){
                        printf("Tied: %d\n\n", stats[i]);
                    }
                    else {
                        printf("Player %d: %d\n", i+1, stats[i]);
                    }

                }
                if(begin_new()){
                    return 0;
                }
                set_zero(matrix);
                win_cord_setzero(win_coord);
                choice = 0;
                i=-1;
                continue;
            }
            else{
                win_cord_setzero(win_coord);
            }
        }
        print_matrix(matrix, choice, win_coord);
        printf("tied\n");
        stats[2]+=1;
        for(int i=0; i<3; i++){
            if(i==2){
                printf("Tied: %d\n\n", stats[i]);
            }
            else {
                printf("Player %d: %d\n", i+1, stats[i]);
            }
        }
        if(begin_new()){
            return 0;
        }
        set_zero(matrix);
        choice = 0;
        continue;
    }

  return 0;
}
