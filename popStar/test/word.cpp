#include<graphics.h>
#include<conio.h>
#include<cstdio>

int main()
{
	initgraph(400,400);

	IMAGE t;
	loadimage(&t,"..\\Picture\\background,jpg",400,400,false);
	putimage(0,0,&t);
	getchar();
	return 0;
}