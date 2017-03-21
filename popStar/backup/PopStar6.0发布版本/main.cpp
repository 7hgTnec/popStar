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

IMAGE pass;
IMAGE background;
extern int mapx, mapy;
extern int px, py, size;
extern IMAGE stars[5];
extern IMAGE starsHeart[5];
extern int leftPoint[10];
extern IMAGE levelPic[21];



RECT gradePos = {mapx/2-50, 0, mapx/2+50, 50};
char grades[10];
char player[20];
extern int hg;
int ms = CLK_TCK/1000; 
int armPoint[22] = {0,1000,3000,6000,8000,10000,13000,15000,17000,20000,22000,25000,27000,30000,32000,35000,37000,40000,42000,45000,50000};
int level = 1;
int showNum = 0;
char rankName[10][255];
char rankNum[10][255];
char playerName[20];
bool mconnect = false;
bool isPass = false;
bool gamef = true;
mPos mp;
map m;
SOCKET sclient;

//////////////SOCKET////////////////////////
bool socketConnect()
{
	outtextxy(20,20,"========                                                        17%");
	Sleep(210);
	WORD sockVersion = MAKEWORD(2,2);
	outtextxy(20,20,"============                                                    26%");
	Sleep(130);
	WSADATA data;
	outtextxy(20,20,"=================                                               32%");
	Sleep(200);
	if(WSAStartup(sockVersion,&data) != 0){
		return false;
	}
	outtextxy(20,20,"===========================                                     50%");
	Sleep(150);
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET){
		return false;
	}
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	outtextxy(20,20,"==================================                              62%");
	Sleep(800);
	serAddr.sin_port = htons(9999);//端口号
	serAddr.sin_addr.S_un.S_addr = inet_addr("115.28.27.145");//服务器IP地址
	outtextxy(20,20,"============================================                    75%");
	Sleep(600);
	if(connect(sclient,(sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR){
		closesocket(sclient);
		return false;
	}
	outtextxy(20,20,"=======================================================  100%");
	Sleep(200);
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
	//if(mdelay(10,1)){
		//sprintf(grades,"关卡:%d		目标分数:%d  当前分数:%d",level,armPoint[level],hg);
		sprintf(grades,"%d",hg);
		drawtext(grades, &gradePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		reset[1]  = true;
		hg++;
	//}
}

void getRank(){
	if(reset[2]) {start[2] = clock()%TS; reset[2] = false;}
	if(mdelay(2000,2)){
		reset[2] = true;
		threadLock[2] = true;
	}
}

void showRank(){
	if(mconnect){
		char sendData[255];
		int len;
		sprintf(sendData,"getRank.%s.%d",playerName,m.getGrade());
		send(sclient,sendData, strlen(sendData),0);
		char temp[255];
		showNum = 0;
		len = recv(sclient,temp,255,0);
		temp[len] = 0;
		if(strcmp(temp,"next") == 0)
		while(1){
			send(sclient,"next", 4,0);
			len = recv(sclient,temp,255,0);
			temp[len] = 0;
			if(strcmp(temp,"finish")==0){break;}
			strcpy(rankName[showNum],temp);
			//printf("rankName %s %d\n", temp, i);
			send(sclient,"next", 4,0);
			len = recv(sclient,temp,255,0);
			temp[len] = 0;
			strcpy(rankNum[showNum],temp);
			//printf("rankNum %s %d\n", temp, i);
			showNum++;
		}
		putimage(0,0,&background);
		m.printMap();
		drawtext(grades, &gradePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		for(int j = 0; j<showNum; ++j){
			RECT pos = {0,50+(j*60),100,70+(j*60)};
			char numb[10];
			if(j<9)
				sprintf(numb,"===NO.%d===",j+1);
			else sprintf(numb,"===NO.%d==",j+1);
			drawtext(numb,&pos,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT np = {0,70+(j*60),100,90+(j*60)};
			//printf("rankName %s\n", rankName[j]);
			drawtext(rankName[j],&np,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT gp = {0,90+(j*60),100,110+(j*60)};
			drawtext(rankNum[j],&gp,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void gradeClearProof(){
	//putimage(0,0,&background);
	//m.printMap();
	drawtext(grades, &gradePos, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	for(int j = 0; j<showNum; ++j){
		RECT pos = {0,50+(j*60),100,70+(j*60)};
		char numb[10];
		if(j<9)
			sprintf(numb,"===NO.%d===",j+1);
		else sprintf(numb,"===NO.%d==",j+1);
		drawtext(numb,&pos,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		RECT np = {0,70+(j*60),100,90+(j*60)};
		//printf("rankName %s\n", rankName[j]);
		drawtext(rankName[j],&np,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		RECT gp = {0,90+(j*60),100,110+(j*60)};
		drawtext(rankNum[j],&gp,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

void gameWin(){
	initgraph(550,40);
	outtextxy(227,0,"连接网络中...");
	outtextxy(20,20,"==                                                               2%");
	mconnect = socketConnect();
	closegraph();
	if(mconnect == true){
		InputBox(playerName,20,"请输入用户名:(英文)");
	}
	else{
		HWND hWnd = GetHWnd();
		MessageBox(hWnd,"网络连接失败，即将进入单机游戏","Connect Error", MB_OKCANCEL ); 
	}
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
	loadimage(&starsHeart[4],"..\\Picture\\orange_heart.jpg",40,40,false);
	char path[20];
	for(int p = 1; p<21; ++p){
		sprintf(path,"..\\Picture\\level%d.jpg",p);
		loadimage(&levelPic[p],path);
		//loadimage(&levelPic[1],"..\\Picture\\level1.jpg");
	}
	putimage(0,0,&levelPic[1]);
	Sleep(2000);
	loadimage(&background,"..\\Picture\\background.jpg");
	//putimage(0,0,&levelPic[1]);
	//getchar();
	putimage(0,0,&background);
	m.printMap();
	while(gamef){
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
			Sleep(10);
			if(threadLock[1]){
		//	cout<<"Lock1"<<endl;
			changeGrade();
			if(hg>m.getGrade()) threadLock[1] = 0;
		}
		if(threadLock[2]){
			showRank();
			threadLock[2] = false;
		}
			continue;//m.cancelSelect();
		}

//********线程区**********
		if(threadLock[0]){
			starMapFunc();
			putimage(0,0,&background);
			m.printMap();
			gradeClearProof();
			threadLock[0] = false;
		}

		if(threadLock[1]){
		//	cout<<"Lock1"<<endl;
			changeGrade();
			if(m.isExtermable() == false){
				if(m.getGrade()>=armPoint[level]){
					level++;
					m.creatmap();
					putimage(0,0,&levelPic[level]);
					Sleep(2000);
					putimage(0,0,&background);
					m.printMap();
				}
				else if(mconnect){
					char temp[255];
					sprintf(temp,"finish.%d",m.getGrade());
					send(sclient,temp, strlen(temp),0);
					int len = recv(sclient,temp,255,0);
					temp[len] = 0;
					if(strcmp("next",temp)==0){
						send(sclient,"next",4,0);
						len = recv(sclient,temp,255,0);
						temp[len] = 0;
						char ou[100];
						HWND hWnd = GetHWnd();
						sprintf(ou,"最终排名: %s", temp);
						MessageBox(hWnd,ou,"游戏结束", MB_OKCANCEL ); 
						gamef = false;
					}
				}
				else{
					//do something
				}
			}
			if(hg>m.getGrade()) threadLock[1] = 0;
		}
		if(threadLock[2]){
			showRank();
			threadLock[2] = false;
		}
		//Sleep(10);
	}
	closegraph();
	return;
}

int menu(){
	initgraph(400,650);
	IMAGE menu;
	loadimage(&menu,"..\\Picture\\menu.jpg",400,650,false);
	//loadimage(&pass,"..\\Picture\\pass.jpg");
	while(1){
		putimage(0,0,&menu);
		if(MouseHit()){
				mp.getMousePos();
				//printf("%d,%d\n", mp.getRx(), mp.getRy());
				if(mp.getLB() && mp.getRx()>=110 && mp.getRx()<=290){//如果鼠标左键点击
					if(mp.getRy()>=342 && mp.getRy()<=372){
						//cout<<"m1"<<endl;
						//开始新游戏
						closegraph();
						return 1;
					}
					else if(mp.getRy()>=420 && mp.getRy()<=450){
						//继续游戏
						closegraph();
						return 2;
					}
					else if(mp.getRy()>=420 && mp.getRy()<=450){
						//游戏说明
						closegraph();
						return 3;
					}
					else{
						Sleep(10);
						continue;
					}
				}
		}
	}
	//SetWorkingImage(&menu);
	//putimage(0,0,&pass,DSTINVERT);
	return 0;
}

int main()
{
	while(1){
		int op = menu();
		switch (op){
			case 1:{
				gamef = true;
				gameWin();
				 break;
			}
			case 2:{
				break; 
			}
			case 3:{
				break;
			}
			case 0:{
				 continue;
				 break;
			}
			default:
				//cout<<"default"<<endl;
				return 0;
		}
	}
	return 0;
}

/*
starMapFunc();
cleardevice();
m.printMap();
*/