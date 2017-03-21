#include"StarMap.h"
#include"Mouse.h"
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<iostream>
#include<windows.h>
using namespace std;
#define TS 8000000000

//*******模拟多线程***********
bool threadLock[10] = {false};//线程锁
//最多允许并行10个线程
//最多运行10个线程并发执行
//0为星图操作线程
//1为分数操作
long int start[10] = {false};
bool reset[10] = {false};
//****************************

extern mapx, mapy;
extern px, py, size;
extern IMAGE stars[5];
extern IMAGE starsHeart[5];
RECT gradePos = {0, 0, 100, 50};
char grades[10];
extern int hg;
int ms = CLK_TCK/1000; 
int armPoint = 1000;
int finish = 0;
mPos mp;
map m;

void starMapFunc()
{
	if(m.isSelected(mp.getX(),mp.getY())){
		m.extermBlock();
		m.orderBlock();
		m.cancelSelect();
	}
	else{
		m.cancelSelect();
		if(m.isOperateable(mp.getX(),mp.getY())){
			m.dfs(mp.getX(),mp.getY());
		}
	}
}


bool mdelay(int dt, int i){
	if((clock()-start[i])/ms >=dt) return true;
	return false;
}

void changeGrade(){
	if(reset[1]) {start[1] = clock()%TS; reset[1] = false;}
	if(mdelay(10,1)){
		sprintf(grades,"%d",hg);
		drawtext(grades, &gradePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		reset[1]  = true;
		hg++;
	}
}

main()
{
	initgraph(mapx,mapy);
	loadimage(&stars[0],"..\\Picture\\blue.jpg",40,40,false);
	loadimage(&stars[1],"..\\Picture\\red.jpg",40,40,false);
	loadimage(&stars[2],"..\\Picture\\green.jpg",40,40,false);
	loadimage(&stars[3],"..\\Picture\\purple.jpg",40,40,false);
	loadimage(&stars[4],"..\\Picture\\orange.jpg",40,40,false);
	loadimage(&starsHeart[0],"..\\Picture\\blue_heart.jpg",40,40,false);
	loadimage(&starsHeart[1],"..\\Picture\\red_heart.jpg",40,40,false);
	loadimage(&starsHeart[2],"..\\Picture\\green_heart.jpg",40,40,false);
	loadimage(&starsHeart[3],"..\\Picture\\purple_heart.jpg",40,40,false);
	loadimage(&starsHeart[4],"..\\Picture\\orange_heart.jpg",40,40,false);
	m.printMap();
	while(1){
	//	cout<<"main"<<endl;
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
		else{
			//m.cancelSelect();
		}

		//********线程区**********
		if(threadLock[0]){
			starMapFunc();
			clearcliprgn();
			m.printMap();
			drawtext(grades, &gradePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			threadLock[0] = false;
		}

		if(threadLock[1]){
		//	cout<<"Lock1"<<endl;
			changeGrade();
			if(hg>m.getGrade()) threadLock[1] = 0;
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