#include"StarMap.h"
#include"Mouse.h"
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<iostream>
#include<windows.h>
using namespace std;

//*******模拟多线程***********
bool threadLock[10] = {false};//线程锁
//最多允许并行10个线程
//最多运行10个线程并发执行
//0为星图操作线程
//1为分数操作
//****************************

extern mapx, mapy;
extern px, py, size;
extern IMAGE stars[5];
extern IMAGE starsHeart[5];
extern int hg;

int armPoint = 1000;
int finish = 0;
mPos mp;
map m;

void starMapFunc()
{
	if(m.isSelected(mp.getX(),mp.getY())){
		m.extermBlock();
		m.orderBlock();
		m.cancleSelect();
	}
	else{
		m.cancleSelect();
		if(m.isOperateable(mp.getX(),mp.getY())){
			m.dfs(mp.getX(),mp.getY());
		}
	}
}

void changeGrade(){
	RECT r = {0, 0, 100, 50};
	char s[10];
	while(hg<=m.getGrade()){
		sprintf(s,"%d",hg);
		drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		hg++;
	}	
}

main()
{
	initgraph(mapx,mapy);
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
	m.printMap();
	while(1){
		//if(m.isExtermable()==false){//判断游戏是否结束
			//if(m.getGrade()<armPoint){
				//do something
			//	break;
		//	}
		//}

		if(MouseHit()){//检测鼠标动作,根据点击区域开放线程
			mp.getMousePos();
			if(mp.getLB()){//如果鼠标左键点击
				if(mp.getRx()>=px && mp.getRx()<=px+(size*10) && mp.getRy()<=py+(size*10) && mp.getRy()>=py){//如果点击区域位于星图区域，开放星图操作线程
					threadLock[0] = true;
				} 
			}
		}

		//********线程区**********
		if(threadLock[0]){
			starMapFunc();
			cleardevice();
			m.printMap();
			threadLock[0] = false;
		}

		if(threadLock[1]){
			
		}
	}
	getchar();
	closegraph();
	return 0;
}

/*
starMapFunc();
cleardevice();
m.printMap();
*/