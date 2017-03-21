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

#define size 40 //С�����Сsize*size
#define xnumber 10
#define ynumber 15

#define ok 1
#define error 0

struct Small{
	int cunzai;					//1�� 0��
	int yanse;					//1�� 2�� 3�� 4�� 5��
}ismall[ynumber][xnumber];


//���εģ�
int down[10]={15,15,15,15,15,15,15,15,15,15};
int left[15]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int sumNum;



int sum=0;//����
int grade=1;//����
char fenshu[9];
char jibie[3];
char q[5],w[5],e[5],r[5],t[5];


int begin()
{
	setlinecolor(WHITE);//���ÿ����ɫ
	rectangle(leftline,upline,xnumber*size+leftline,ynumber*size+upline);//����
	settextcolor(LIGHTCYAN);
	outtextxy(leftline+xnumber*size+70,upline,"����˵��");//upline���������ÿ��һ��+20����ʾ
	outtextxy(leftline+xnumber*size+20,upline+20,"������������ܶ����");
	outtextxy(leftline+xnumber*size+20,upline+40,"ͨ�ķ��飬��ͨ��Խ���");
	outtextxy(leftline+xnumber*size+20,upline+60,"��Խ�ߡ�");
	outtextxy(leftline+xnumber*size+20,upline+80,"������");
	sprintf(fenshu, "%d", sum);
	outtextxy(leftline+xnumber*size+70,upline+80, fenshu);
	sprintf(jibie,"%d",grade);
	outtextxy(leftline+xnumber*size+20,upline+100,"����");
	outtextxy(leftline+xnumber*size+70,upline+100,jibie);
	outtextxy(leftline+xnumber*size+20,upline+120,"����Ŀ�������");
	sprintf(q,"%d",diyi);
	sprintf(w,"%d",dier);
	sprintf(e,"%d",disan);
	sprintf(r,"%d",disi);
	sprintf(t,"%d",diwu);
	outtextxy(leftline+xnumber*size+60,upline+140,"��һ�أ�");
	outtextxy(leftline+xnumber*size+60,upline+160,"�ڶ��أ�");
	outtextxy(leftline+xnumber*size+60,upline+180,"�����أ�");
	outtextxy(leftline+xnumber*size+60,upline+200,"���Ĺأ�");
	outtextxy(leftline+xnumber*size+60,upline+220,"����أ�");
	outtextxy(leftline+xnumber*size+120,upline+140,q);
	outtextxy(leftline+xnumber*size+120,upline+160,w);
	outtextxy(leftline+xnumber*size+120,upline+180,e);
	outtextxy(leftline+xnumber*size+120,upline+200,r);
	outtextxy(leftline+xnumber*size+120,upline+220,t);
	return ok;
}


void pushsmall(int x,int y,int a)	//���С���飨����X,����Y,��ɫ��
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

int panduan(){//�ж��Ƿ�����ͨ��û����ͨ����0���з���1��1��ʾ������Ϸ��
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

int fdfs(int yy, int xx){//����������x ��y�� ���󷵻�-1
	int flag =0;
	if(ismall[xx][yy].cunzai == 0) return 0;
	if(xx<0 || xx>14 || yy<0 || yy>9) return 0;

	/*****************************************************************************************************************/
	if(sumNum == 0 ){///����ǵ�һ���飬����Ҫ�ж���Χ�Ƿ�����ͬ��ɫ��û�еĻ�������
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

//��꺯��
void shubiao ()
{


	int key = 1;
	while (key)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//�ж��������λ���Ƿ�����Ϸ���ڣ���������������
			if(m.x < leftline || m.x > leftline + 400) continue;
			else if (m.y < upline || m.y > upline + 600) continue;
			//���ǣ�������ת��Ϊ��ά���������
			else
			{
				int X = (m.x - leftline) / 40;
				int Y = (m.y - upline) / 40;
				//����DFS �õ��������ǵ�����
				int sumstar = dfs(X, Y); //�������������������
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
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2,"��ϲ��ͨ����");
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+20,"��ķ����ǣ�");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+20,fenshu);
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+40,"��ĵȼ��ǣ�");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+40,jibie);
	}
	if(r!=6)
	{
		for(i=0;i<15;i++)
			for(j=0;j<10;j++)
			{
				pushsmall(j+1, i+1, ismall[i][j].yanse);
			}
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2,"���ź���û����ͨ��С�����ˡ���Ϸ����");
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+20,"��ķ����ǣ�");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+20,fenshu);
		outtextxy(leftline+xnumber*size/2,upline+ynumber*size/2+40,"��ĵȼ��ǣ�");
		outtextxy(leftline+xnumber*size/2+100,upline+ynumber*size/2+40,jibie);
	}
	getchar();
	return 0;
}
