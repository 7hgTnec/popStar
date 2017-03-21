#include<iostream>
#include<conio.h>
#include<cstdio>
#include<graphics.h>
using namespace std;
int main()
{
	IMAGE p;
	loadimage(&p,"..\\Picture\\menu.jpg",400,650,false);
	initgraph(400,650,SHOWCONSOLE);
	putimage(0,0,&p);
	while(1){
		if(MouseHit()){
			MOUSEMSG m = GetMouseMsg();
			cout<<m.x<<" "<<m.y<<endl;
		}
		Sleep(10);
	}
	return 0;
}
