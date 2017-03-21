#ifndef StarMap_cpp
#define StarMap_cpp
#include<cstdio>
#include<time.h>
#include<stdlib.h>
#include"StarMap.h"
#include<conio.h>
#include<graphics.h>
#include<iostream>
using namespace std;
int px = 160;
int py = 320;
int size = 48;
IMAGE stars[5];
IMAGE starsHeart[5];
star::star(){color = 0; exist = 1; select = 0;}
star::star(int c, int e){color = c; exist = e; select = 0;}
int star::getColor(){ return color;}
int star::isExist(){ return exist;}
int star::isSelect(){ return select;}
void star::setColor(int c){ color = c;}
void star::setExist(int e){exist = e;}
void star::setSelect(int s){select = s;}

long int map::grade = 0;
map::map(){
	loadimage(&stars[0],"..\\Picture\\blue.jpg");
	loadimage(&stars[1],"..\\Picture\\red.jpg");
	loadimage(&stars[2],"..\\Picture\\green.jpg");
	loadimage(&stars[3],"..\\Picture\\purple.jpg");
	loadimage(&stars[4],"..\\Picture\\orange.jpg");
	loadimage(&starsHeart[0],"..\\Picture\\blue_heart.jpg",48,48,false);
	loadimage(&starsHeart[1],"..\\Picture\\red_heart.jpg",48,48,false);
	loadimage(&starsHeart[2],"..\\Picture\\green_heart.jpg",48,48,false);
	loadimage(&starsHeart[3],"..\\Picture\\purple_heart.jpg",48,48,false);
	loadimage(&starsHeart[4],"..\\Picture\\orange_heart.jpg",48,48,false);
	time(NULL);
	while(1){
		creatmap();
		if(isExtermable()) break;
	}	
}

void map::creatmap(){
	srand((int)time(NULL));
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j)
			block[i][j].setColor(rand()%5);
	}
}

int map::dfs(int y, int x){
	int ans = 1;
	block[x][y].setSelect(1);
	if(x-1 >=0 && block[x-1][y].getColor() == block[x][y].getColor() && block[x-1][y].isExist() && !block[x-1][y].isSelect()){ans += dfs(y,x-1); }
	if(x+1 <10 && block[x+1][y].getColor() == block[x][y].getColor() && block[x+1][y].isExist() && !block[x+1][y].isSelect()){ans += dfs(y,x+1); }
	if(y-1 >=0 && block[x][y-1].getColor() == block[x][y].getColor() && block[x][y-1].isExist() && !block[x][y-1].isSelect()){ans += dfs(y-1,x); }
	if(y+1 <10 && block[x][y+1].getColor() == block[x][y].getColor() && block[x][y+1].isExist() && !block[x][y+1].isSelect()){ans += dfs(y+1,x); }
	return ans;
}

void map::printMap(){
	
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			if(block[i][j].isExist()){
				if(block[i][j].isSelect()){
					putimage(size*j+px,size*i+py,&starsHeart[block[i][j].getColor()]);
				}
				else if(!block[i][j].isSelect()){
					putimage(size*j+px,size*i+py,&stars[block[i][j].getColor()]);
				}
			}
		}
	}
}
bool map::isOperateable(int y, int x){
	if(block[x][y].isExist()){
		if((x-1>=0 && block[x][y].getColor()==block[x-1][y].getColor())||(x+1<10 && block[x][y].getColor()==block[x+1][y].getColor())||(y+1<10 && block[x][y].getColor()==block[x][y+1].getColor())||(y-1>=0 && block[x][y].getColor()==block[x][y-1].getColor())){
			return true;
		}
	}
	return false;
}

bool map::isSelected(int y, int x){
	if(block[x][y].isExist() && block[x][y].isSelect()) return true;
	return false;
}

void map::extermBlock(){
	int sum = 0;
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			if(block[i][j].isSelect()){
				block[i][j].setExist(0);
				sum++;
			}
		}
	}
	grade+=sum;
}

void map::orderBlock(){
	//int pd, pu;
	for(int j = 0; j<10; ++j){
		int posd = 9;
		while(posd>0){
			if(block[posd][j].isExist() == 0){
				break;
			}
			posd--;
		}
		int posu = 1;
		while(posd-posu>=0){
			if(block[posd-posu][j].isExist() == 1){
				break;
			}
			posu++;
		}
		int gn = posd-posu+1;
		for(int k = 0; k<gn; ++k){
			block[posd-k][j].setColor(block[posd-k-posu][j].getColor());
			block[posd-k][j].setExist(1);
			block[posd-k][j].setSelect(0);
			block[posd-k-posu][j].setExist(0);
			block[posd-k-posu][j].setExist(0);
		}
	}

	for(int jj = 1; jj<10; ++jj){
		int temp = jj;
		if(block[9][jj].isExist()){
			while(block[9][temp-1].isExist()==0){
				temp--;
			}
			for(int i = 0; i<10; ++i){
				block[i][temp].setColor(block[i][jj].getColor());
				block[i][temp].setExist(block[i][jj].isExist());
				block[i][temp].setSelect(0);
				//block[i][jj].setExist(0);
			}
		}
	}
}

bool map::isExtermable(){
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			if(block[i][j].isExist()){
				if(i-1>=0 && block[i-1][j].getColor() == block[i][j].getColor()) return true;
				if(i+1<10 && block[i+1][j].getColor() == block[i][j].getColor()) return true;
				if(j+1<10 && block[i][j+1].getColor() == block[i][j].getColor()) return true;
				if(j-1>=0 && block[i][j-1].getColor() == block[i][j].getColor()) return true;
			}
		}
	}
	return false;
}

void map::cancleSelect(){
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			block[i][j].setSelect(0);
		}
	}
}

long int map::getGrade(){ return grade;}
#endif