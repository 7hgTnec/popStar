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
extern bool threadLock[10];
extern bool reset[5];
extern bool isPass;


int size = 40;
int mapx = 800;
int mapy = 650;
int hg = 0;
int px = (mapx-(size*10))/2;
int py = mapy-(size*10);


IMAGE stars[5];
IMAGE levelPic[21];
IMAGE starsHeart[5];
extern int level;
extern IMAGE background;
extern IMAGE pass;
int leftPoint[10] = {2000,1980,1920,1820,1680,1500,1280,1020,720,380};


star::star(){color = 0; exist = 1; select = 0;}
star::star(int c, int e){color = c; exist = e; select = 0;}
int star::getColor(){ return color;}
int star::isExist(){ return exist;}
int star::isSelect(){ return select;}
void star::setColor(int c){ color = c;}
void star::setExist(int e){exist = e;}
void star::setSelect(int s){select = s;}



long int map::grade = 0;
int map::leftNum = 0;
map::map(){
	creatmap();
	threadLock[1] = true;
}
map::map(int g){
	creatmap();
	grade = g;
	threadLock[1] = true;
}
void map::creatmap(){
	//putimage(0,0,&levelPic[level]);
	//Sleep(2000);
	srand((int)time(NULL));
	leftNum = 0;
	while(1){
		for(int i = 0; i<10; ++i){
			for(int j = 0; j<10; ++j){
				block[i][j].setColor(rand()%5);
				block[i][j].setExist(1);
				block[i][j].setSelect(0);
			}
		}
		if(isExtermable()) break;
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
			//printf("%d",block[i][j].isExist());
			if(block[i][j].isExist()){
				if(block[i][j].isSelect()){
					putimage(size*j+px,size*i+py,&starsHeart[block[i][j].getColor()]);
				}
				else if(!block[i][j].isSelect()){
					putimage(size*j+px,size*i+py,&stars[block[i][j].getColor()]);
				}
			}
		}
		//printf("\n");
	}
	//printf("\n\n");
}
bool map::isOperateable(int y, int x){
	if(block[x][y].isExist()){
		if((x-1>=0 && block[x-1][y].isExist() && block[x][y].getColor()==block[x-1][y].getColor())||(x+1<10 && block[x+1][y].isExist() &&  block[x][y].getColor()==block[x+1][y].getColor())||(y+1<10 && block[x][y+1].isExist() &&  block[x][y].getColor()==block[x][y+1].getColor())||(y-1>=0 && block[x][y-1].isExist() &&  block[x][y].getColor()==block[x][y-1].getColor())){
			return true;
		}
	}
	return false;
}

bool map::isSelected(int y, int x){
	if(x<0 || y<0 || x>9 || y>9) return false;
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
	hg = grade;
	grade+=sum*sum*5;
	threadLock[1] = true;
	//reset[1] = true;
}

void map::orderBlock(){
	//int pd, pu;
	star pl[10];
	for(int j = 0; j<10; ++j){
		int testp = 0;
		while(testp<10){
			if(block[testp][j].isExist() == 0){
				for(int ci = 0; ci<10; ++ci){
					pl[ci].setColor(block[ci][j].getColor());
					pl[ci].setExist(block[ci][j].isExist());
					pl[ci].setSelect(0);
					block[ci][j].setExist(0);
				}
				int c1, c2;
				c1 = c2 = 9;
				while(c1>=0){
					if(pl[c1].isExist() == 1){
						block[c2][j].setColor(pl[c1].getColor());
						block[c2][j].setExist(1);
						block[c2][j].setSelect(0);
						c2--;
						c1--;
					}
					else c1--;
				}
				break;
			}
			testp++;
		}
	}

	for(int jj = 0; jj<10; ++jj){
		if(block[9][jj].isExist()==0){
			int temp = jj;
			while(temp<10){
				if(block[9][temp].isExist() == 1){
					break;
				}
				temp++;
			}
			int tp = 0;
			while(temp+tp<10){
				for(int ti = 0; ti<10; ++ti){
					block[ti][jj+tp].setColor(block[ti][temp+tp].getColor());
					block[ti][jj+tp].setExist(block[ti][temp+tp].isExist());
					block[ti][jj+tp].setSelect(0);
					block[ti][temp+tp].setSelect(0);
					block[ti][temp+tp].setExist(0);
				}
				tp++;
			}
			break;
		}
	}
}

bool map::isExtermable(){
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			if(block[i][j].isExist()){
				leftNum++;
				if(i-1>=0 && block[i-1][j].isExist() && block[i-1][j].getColor() == block[i][j].getColor()) return true;
				if(i+1<10 && block[i+1][j].isExist() && block[i+1][j].getColor() == block[i][j].getColor()) return true;
				if(j+1<10 && block[i][j+1].isExist() && block[i][j+1].getColor() == block[i][j].getColor()) return true;
				if(j-1>=0 && block[i][j-1].isExist() && block[i][j-1].getColor() == block[i][j].getColor()) return true;
			}
		}
	}
	if(leftNum < 10){
		grade+= leftPoint[leftNum];
		//show something
	}
	return false;
}

void map::cancelSelect(){
	for(int i = 0; i<10; ++i){
		for(int j = 0; j<10; ++j){
			block[i][j].setSelect(0);
		}
	}
}

long int map::getGrade(){ return grade;}
int map::getLeftNum(){ return leftNum;}
#endif


/*
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
		//int gn = posd-posu+1;
		int k = 0;
		while(posd-k-posu>=0 && block[posd-k-posu][j].isExist()){
			block[posd-k][j].setColor(block[posd-k-posu][j].getColor());
			block[posd-k][j].setExist(1);
			block[posd-k][j].setSelect(0);
			block[posd-k-posu][j].setExist(0);
			block[posd-k-posu][j].setSelect(0);
			k++;
		}
*/

/*

*/
