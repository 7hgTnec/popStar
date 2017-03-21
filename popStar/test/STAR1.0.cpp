#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<graphics.h>

#define upline 25
#define downline 25
#define leftline 80
#define rightline 200

#define diyi 2000
#define dier 5000
#define disan 8000
#define disi 12000
#define diwu 16000

#define size 40 //小方块大小size*size
#define xnumber 10
#define ynumber 15

#define ok 1
#define error 0

struct Small{
	int cunzai;					//1有 0无
	int yanse;					//1红 2黄 3绿 4蓝 5紫
}ismall[ynumber][xnumber];


//涛涛的：
int down[10]={15,15,15,15,15,15,15,15,15,15};
int left[15]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int sumNum;



int sum=0;//分数
int grade=1;//级别
char fenshu[9];
char jibie[3];
char q[5],w[5],e[5],r[5],t[5];


int begin()
{
	setlinecolor(WHITE);//设置框的颜色
	rectangle(leftline,upline,xnumber*size+leftline,ynumber*size+upline);//画框
	settextcolor(LIGHTCYAN);
	outtextxy(leftline+xnumber*size+70,upline,"操作说明");//upline后面的数字每加一行+20来显示
	outtextxy(leftline+xnumber*size+20,upline+20,"用鼠标点击尽可能多的连");
	outtextxy(leftline+xnumber*size+20,upline+40,"通的方块，连通的越多分");
	outtextxy(leftline+xnumber*size+20,upline+60,"数越高。");
	outtextxy(leftline+xnumber*size+20,upline+80,"分数：");
	sprintf(fenshu, "%d", sum);
	outtextxy(leftline+xnumber*size+70,upline+80, fenshu);
	sprintf(jibie,"%d",grade);
	outtextxy(leftline+xnumber*size+20,upline+100,"级别：");
	outtextxy(leftline+xnumber*size+70,upline+100,jibie);
	outtextxy(leftline+xnumber*size+20,upline+120,"过关目标分数：");
	sprintf(q,"%d",diyi);
	sprintf(w,"%d",dier);
	sprintf(e,"%d",disan);
	sprintf(r,"%d",disi);
	sprintf(t,"%d",diwu);
	outtextxy(leftline+xnumber*size+60,upline+140,"第一关：");
	outtextxy(leftline+xnumber*size+60,upline+160,"第二关：");
	outtextxy(leftline+xnumber*size+60,upline+180,"第三关：");
	outtextxy(leftline+xnumber*size+60,upline+200,"第四关：");
	outtextxy(leftline+xnumber*size+60,upline+220,"第五关：");
	outtextxy(leftline+xnumber*size+120,upline+140,q);
	outtextxy(leftline+xnumber*size+120,upline+160,w);
	outtextxy(leftline+xnumber*size+120,upline+180,e);
	outtextxy(leftline+xnumber*size+120,upline+200,r);
	outtextxy(leftline+xnumber*size+120,upline+220,t);
	return ok;
}


void pushsmall(int x,int y,int a)	//输出小方块（坐标X,坐标Y,颜色）
{
	//if(x>11||y>16)
	//	printf(" error");
	if(ismall[y-1][x-1].cunzai==0)
		return ;
	setlinecolor(WHITE);
	switch(a)
	{
	case 1:
		setfillcolor(RED);break;
	case 2:
		setfillcolor(YELLOW);break;
	case 3:
		setfillcolor(GREEN);break;
	case 4:
		setfillcolor(BLUE);break;
	case 5:
		setfillcolor(MAGENTA);break;
	default:
		return ;
	}
	bar(leftline+(x-1)*size,upline+(y-1)*size,leftline+(x)*size,upline+(y)*size);
	rectangle(leftline+(x-1)*size,upline+(y-1)*size,leftline+(x)*size,upline+(y)*size);
}




//**********************************************************************************************************

int panduan(){//判断是否有联通的没有联通返回0，有返回1（1表示继续游戏）
    int flag = 0;
    for(int x=0; x<15; ++x){
        for(int y = 0; y<10; ++y){
			if(!ismall[x][y].cunzai) continue;
            if(x+1<15 && ismall[x+1][y].yanse == ismall[x][y].yanse && ismall[x+1][y].cunzai ) {flag = 1; break;}
            if(y+1<10 && ismall[x][y+1].yanse == ismall[x][y].yanse && ismall[x][y+1].cunzai ) {flag = 1; break;}
            if(x-1>-1 && ismall[x-1][y].yanse == ismall[x][y].yanse && ismall[x-1][y].cunzai ) {flag = 1; break;}
            if(y-1>-1 && ismall[x][y-1].yanse == ismall[x][y].yanse && ismall[x][y-1].cunzai ) {flag = 1; break;}
        }
    }

    return flag;
}


int jisuanfenshu(int sumstar)
{
	return (5 * (sumstar * sumstar));
}




int fdfs(int xx, int yy);

int dfs(int xx,int yy){
    int temp;
    sumNum = fdfs(xx,yy);

    for( int x=0; x<10; ++x){
        for(int y=14; y>-1; --y){
        int f = 0;
            if(ismall[y][x].cunzai == 0){
                temp = y-1;
                f = 1;
                while(temp>-1){
                    if(ismall[temp][x].cunzai == 1){
                        break;
                    }
                    temp--;
                }
            }
            if(temp>-1 && f == 1){
                ismall[y][x].yanse = ismall[temp][x].yanse;
                ismall[y][x].cunzai = 1;
                ismall[temp][x].cunzai = 0;
			}
        }
    }


   for( x=0; x<9; ++x){
        if(ismall[14][x].cunzai == 0){
			int tempx = x+1;
			while(ismall[14][tempx].cunzai != 1 && tempx <9){
				tempx++;
			}
            for(int y = 14; y>-1; --y){
                ismall[y][x].yanse = ismall[y][tempx].yanse;
                ismall[y][x].cunzai = ismall[y][tempx].cunzai;
                ismall[y][tempx].cunzai = 0;
            }
        }
    }
    return sumNum;
}

int fdfs(int yy, int xx){//消灭函数，先x 后y， 错误返回-1
	int flag =0;
	if(ismall[xx][yy].cunzai == 0) return 0;
	if(xx<0 || xx>14 || yy<0 || yy>9) return 0;

	/*****************************************************************************************************************/
	if(sumNum == 0 ){///如果是第一个块，首先要判断周围是否有相同颜色，没有的话不消除
		if(yy-1 >=0 && ismall[xx][yy-1].cunzai == 1 &&ismall[xx][yy-1].yanse == ismall[xx][yy].yanse) flag = 1;
		if(yy+1 <10 && ismall[xx][yy+1].cunzai==1 && ismall[xx][yy+1].yanse == ismall[xx][yy].yanse) flag = 1;
		if(xx-1 >=0 && ismall[xx-1][yy].cunzai==1 &&ismall[xx-1][yy].yanse == ismall[xx][yy].yanse) flag = 1;
		if(xx+1 <15 && ismall[xx+1][yy].cunzai==1 &&ismall[xx+1][yy].yanse == ismall[xx][yy].yanse) flag = 1;

		if(flag ==0) return 0;
	}

  /**********************************************************************************************************************/


    sumNum ++;
    ismall[xx][yy].cunzai = 0;
    if(ismall[xx][yy-1].yanse == ismall[xx][yy].yanse) fdfs(yy-1,xx);
    if(ismall[xx-1][yy].yanse == ismall[xx][yy].yanse) fdfs(yy,xx-1);
    if(ismall[xx+1][yy].yanse == ismall[xx][yy].yanse) fdfs(yy,xx+1);
    if(ismall[xx][yy+1].yanse == ismall[xx][yy].yanse) fdfs(yy+1,xx);
    return sumNum;
}







//***************************************************************************************************

//鼠标函数
void shubiao ()
{


	int key = 1;
	while (key)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//判断鼠标点击的位置是否在游戏框内，若不是则继续检测
			if(m.x < leftline || m.x > leftline + 400) continue;
			else if (m.y < upline || m.y > upline + 600) continue;
			//若是，将坐标转换为二维数组的坐标
			else
			{
				int X = (m.x - leftline) / 40;
				int Y = (m.y - upline) / 40;
				//传入DFS 得到消灭星星的数量
				int sumstar = dfs(X, Y); //并且星星重新排列完毕
				sum += jisuanfenshu(sumstar);
				key = 0;
			}
		}
	}
}


//****************************************************************************
void chushihua()
{
	int r;
	int i,j;
	srand(time(NULL));
	for(i=0;i<=14;i++)
		for(j=0;j<=9;j++)
	{
		r=rand()%5+1;
		ismall[i][j].cunzai=1;
		ismall[i][j].yanse=r;
    }
}




//*****************************************************************************
int main()
{
	int i,j, r=0;
	int guan[6]={0,diyi,dier,disan,disi,diwu};
	for(;sum>=guan[r];r++)
	{
		chushihua();
		initgraph(leftline+xnumber*size+rightline,upline+ynumber*size+downline);
		while(panduan())
		{
			sumNum = 0;
     		begin();
			for(i=0;i<15;i++)
			for(j=0;j<10;j++)
			{
				pushsmall(j+1, i+1, ismall[i][j].yanse);
			}
			shubiao();
			cleardevice();

		}
	grade++;
	if(r>=6) break;
	}

	if(r==6)
	{
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2,"恭喜你通关了");
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+20,"你的分数是：");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+20,fenshu);
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+40,"你的等级是：");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+40,jibie);
	}
	if(r!=6)
	{
		for(i=0;i<15;i++)
			for(j=0;j<10;j++)
			{
				pushsmall(j+1, i+1, ismall[i][j].yanse);
			}
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2,"很遗憾，没有连通的小方块了。游戏结束");
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+20,"你的分数是：");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+20,fenshu);
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+40,"你的等级是：");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+40,jibie);
	}
	getchar();
	return 0;
}
