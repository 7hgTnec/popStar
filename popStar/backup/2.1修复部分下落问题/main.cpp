#include"StarMap.h"
#include"Mouse.h"
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<iostream>
#include<windows.h>
using namespace std;

//*******ģ����߳�***********
bool threadLock[10] = {false};//�߳���
//���������10���߳�
//�������10���̲߳���ִ��
//0Ϊ��ͼ�����߳�
//1Ϊ��������
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
		//if(m.isExtermable()==false){//�ж���Ϸ�Ƿ����
			//if(m.getGrade()<armPoint){
				//do something
			//	break;
		//	}
		//}

		if(MouseHit()){//�����궯��,���ݵ�����򿪷��߳�
			mp.getMousePos();
			if(mp.getLB()){//������������
				if(mp.getRx()>=px && mp.getRx()<=px+(size*10) && mp.getRy()<=py+(size*10) && mp.getRy()>=py){//����������λ����ͼ���򣬿�����ͼ�����߳�
					threadLock[0] = true;
				} 
			}
		}

		//********�߳���**********
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