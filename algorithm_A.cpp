#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){
    int point[5][6]={0};
    int color = player.get_color();
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(board.get_cell_color(i,j)==color||board.get_cell_color(i,j)=='w'){
                int remain=board.get_capacity(i,j)-board.get_orbs_num(i,j);
                bool up_enemy=false,down_enemy=false,left_enemy=false,right_enemy=false;
                if(i>1 && board.get_cell_color(i-1,j)!=color && board.get_cell_color(i-1,j)!='w')  up_enemy=true;
                if(i<4 && board.get_cell_color(i+1,j)!=color && board.get_cell_color(i+1,j)!='w')  down_enemy=true;
                if(j>0 && board.get_cell_color(i,j-1)!=color && board.get_cell_color(i,j-1)!='w')  left_enemy=true;
                if(j<5 && board.get_cell_color(i,j+1)!=color && board.get_cell_color(i,j+1)!='w')  right_enemy=true;
                //depends on position
                if(board.get_capacity(i,j)==2)      point[i][j]+=3;
                else if(board.get_capacity(i,j)==3)     point[i][j]+=2;
                else    point[i][j]+=1;
                //depends on neighbors(enemy)
                if(i>0 && up_enemy && board.get_capacity(i-1,j)-board.get_orbs_num(i-1,j)==1){
                    if(remain==1)   point[i][j]+=50;
                    else if(remain==2)  point[i][j]-=1000;
                }
                if(i<4 && down_enemy && board.get_capacity(i+1,j)-board.get_orbs_num(i+1,j)==1){
                    if(remain==1)   point[i][j]+=50;
                    else if(remain==2)  point[i][j]-=1000;
                }
                if(j>0 && left_enemy && board.get_capacity(i,j-1)-board.get_orbs_num(i,j-1)==1){
                    if(remain==1)   point[i][j]+=50;
                    else if(remain==2)  point[i][j]-=1000;
                }
                if(j<5 && right_enemy && board.get_capacity(i,j+1)-board.get_orbs_num(i,j+1)==1){
                    if(remain==1)   point[i][j]+=50;
                    else if(remain==2)  point[i][j]-=1000;
                }
                //depends on neighbors of neighbors(enemy)
                if(i>1 && board.get_cell_color(i-2,j)!=color && board.get_cell_color(i-2,j)!='w' && board.get_capacity(i-2,j)-board.get_orbs_num(i-2,j)==1){
                    if(board.get_cell_color(i-1,j)==color){
                        if(remain==2)   point[i][j]+=20;
                        else if(remain==3) point[i][j]+=10;
                    }
                }
                if(i<3 && board.get_cell_color(i+2,j)!=color && board.get_cell_color(i+2,j)!='w' && board.get_capacity(i+2,j)-board.get_orbs_num(i+2,j)==1){
                    if(board.get_cell_color(i+1,j)==color){
                        if(remain==2)   point[i][j]+=20;
                        else if(remain==3) point[i][j]+=10;
                    }
                }
                if(j>1 && board.get_cell_color(i,j-2)!=color && board.get_cell_color(i,j-2)!='w' && board.get_capacity(i,j-2)-board.get_orbs_num(i,j-2)==1){
                    if(board.get_cell_color(i,j-1)==color){
                        if(remain==2)   point[i][j]+=20;
                        else if(remain==3) point[i][j]+=10;
                    }
                }
                if(j<4 && board.get_cell_color(i,j+2)!=color && board.get_cell_color(i,j+2)!='w' && board.get_capacity(i,j+2)-board.get_orbs_num(i,j+2)==1){
                    if(board.get_cell_color(i-1,j)==color){
                        if(remain==2)   point[i][j]+=20;
                        else if(remain==3) point[i][j]+=10;
                    }
                }
                //compare neighbors remain
                if(board.get_orbs_num(i,j)>=0){
                    if(i>0 && board.get_cell_color(i-1,j)==color && board.get_capacity(i-1,j)-board.get_orbs_num(i-1,j)>remain)
                        point[i][j]+=8;
                    if(i<4 && board.get_cell_color(i+1,j)==color && board.get_capacity(i+1,j)-board.get_orbs_num(i+1,j)>remain)
                        point[i][j]+=8;
                    if(j>0 && board.get_cell_color(i,j-1)==color && board.get_capacity(i,j-1)-board.get_orbs_num(i,j-1)>remain)
                        point[i][j]+=8; 
                    if(j<5 && board.get_cell_color(i,j+1)==color && board.get_capacity(i,j+1)-board.get_orbs_num(i,j+1)>remain)
                        point[i][j]+=8;
                }
                //neighbors(player) can explode
                if(board.get_cell_color(i,j)=='w'){
                    if(i>0 && board.get_cell_color(i-1,j)==color && board.get_capacity(i-1,j)-board.get_orbs_num(i-1,j)==1)
                        point[i][j]+=5;
                    if(i<4 && board.get_cell_color(i+1,j)==color && board.get_capacity(i+1,j)-board.get_orbs_num(i+1,j)==1)
                        point[i][j]+=5;
                    if(j>0 && board.get_cell_color(i,j-1)==color && board.get_capacity(i,j-1)-board.get_orbs_num(i,j-1)==1)
                        point[i][j]+=5;
                    if(j<5 && board.get_cell_color(i,j+1)==color && board.get_capacity(i,j+1)-board.get_orbs_num(i,j+1)==1)
                        point[i][j]+=5;
                }
                //there is no enemy around
                //usual
                if(!up_enemy && !down_enemy && !left_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=1;
                    else if(remain==3)   point[i][j]+=2;
                    else if(remain==2)   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                //edge
                else if(i==0 && !down_enemy && !left_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=2;
                    else if(remain==2)   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                else if(i==4 && !up_enemy && !left_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=2;
                    else if(remain==2)   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                else if(j==0 && !up_enemy && !down_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=2;
                    else if(remain==2)   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                else if(j==5 && !up_enemy && !down_enemy && !left_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=2;
                    else if(remain==2)   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                //corner
                else if(i==0 && j==0 && !down_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                else if(i==0 && j==5 && !down_enemy && !left_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
                else if(i==4 && j==0 && !up_enemy && !right_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                } 
                else if(i==4 && j==5 && !up_enemy && !left_enemy){
                    if(board.get_cell_color(i,j)=='w')   point[i][j]+=3;
                    else if(remain==1)   point[i][j]+=4;
                }
            }
            else    point[i][j]=-1000000;
        }
    }
    
    int max=point[4][5];
    int index_i=4,index_j=5;
    for(int i=4;i>0;i--){
        for(int j=5;j>0;j--){
            if(max<point[i][j]){
                max=point[i][j];
                index_i=i;
                index_j=j;
            }
        }
    }

    index[0] = index_i;
    index[1] = index_j;
}