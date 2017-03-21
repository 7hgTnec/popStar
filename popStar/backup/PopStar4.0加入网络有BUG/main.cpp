#include"StarMap.h"
#include"Mouse.h"
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<iostream>
#include<windows.h>
#include<winsock2.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;
#define TS 8000000000
#define DESIP "172.16.0.151"
#define DEPPORT 59782

//*******模拟多线程***********
bool threadLock[10] = {false};//线程锁
//最多允许并行10个线程
//最多运行10个线程并发执行
//0为星图操作线程
//1为分数操作
//2为获取网络排名
long int start[10] = {false};
bool reset[10] = {true};
//****************************

extern mapx, mapy;
extern px, py, size;
extern IMAGE stars[5];
extern IMAGE starsHeart[5];
extern leftPoint[10];


RECT gradePos = {mapx/2-50, 0, mapx/2+50, 50};
RECT rankPos[10]={
	{0,50,100,110},
	{0,110,100,170},
	{0,170,100,230},
	{0,230,100,290},
	{0,290,100,350},
	{0,350,100,410},
	{0,410,100,470},
	{0,470,100,530},
	{0,530,100,590},
	{0,590,100,650}
};
char grades[10];
extern int hg;
int ms = CLK_TCK/1000; 
int armPoint = 1000;
int finish = 0;
char rankName[10][255];
char rankNum[10][255];
mPos mp;
map m;
SOCKET sclient;

//////////////SOCKET////////////////////////
bool socketConnect()
{
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA data;
	if(WSAStartup(sockVersion,&data) != 0){
		return false;
	}
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET){
		return false;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(9999);//端口号
	serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.153.237");//服务器IP地址
	if(connect(sclient,(sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR){
		closesocket(sclient);
		return false;
	}
	return true;
}
////////////////////////////////////////////

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

void getRank(){
	if(reset[2]) {start[2] = clock()%TS; reset[2] = false;}
	if(mdelay(2000,2)){
		reset[2] = true;
		threadLock[2] = true;
	}
}

void showRank(){
	int i;
	char sendData[255] = "getRank";
	if(socketConnect()){
		//strcpy(sendData,"getRank");
		//sendData[strlen(sendData)] = '\0';
		send(sclient,sendData, strlen(sendData),0);
		//strcpy(sendData,"孙伟涛");
		sendData[strlen(sendData)] = '\0';
		send(sclient,sendData, strlen(sendData),0);
		sprintf(sendData,"%d",m.getGrade());
		sendData[strlen(sendData)] = '\0';
		send(sclient,sendData, strlen(sendData),0);
		char temp[255];
		i = 0;
		while(recv(sclient,temp,255,0) && strcmp(temp,"finish")!=0){
			strcpy(rankName[i],temp);
			recv(sclient,temp,255,0);
			strcpy(rankNum[i],temp);
			i++;
		}
		closesocket(sclient);
		for(int j = 0; j<i; ++j){
			RECT pos = {0,50+(j*60),100,70+(j*60)};
			drawtext("NO.1",&pos,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT np = {0,70+(j*60),100,90+(j*60)};
			drawtext(rankName[i],&np,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT gp = {0,90+(j*60),100,110+(j*60)};
			drawtext(rankNum[i],&gp,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
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
		getRank();
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
			if(m.isExtermable() == false){
				if(m.getGrade()<armPoint){
					//do somethings 
				}
			}
			if(hg>m.getGrade()) threadLock[1] = 0;
		}
		if(threadLock[2]){
			showRank();
			threadLock[2] = false;
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