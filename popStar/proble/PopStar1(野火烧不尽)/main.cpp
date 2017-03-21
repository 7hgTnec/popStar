#include"StarMap.h"
#include"Mouse.h"
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#include<iostream>
using namespace std;
int armPoint = 1000;
main()
{
	int finish = 0;
	mPos mp;
	initgraph(800,800);
	map m;
	m.printMap();
	while(!finish){
		if(m.isExtermable()==false){
			if(m.getGrade()<armPoint){
				
				break;
			}
		}
		if(MouseHit()){
			mp.getMousePos();
			if(mp.getLB()){
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
			cleardevice();
			m.printMap();
			}	
		}
	}
	//getchar();
	closegraph();
	return 0;
}
