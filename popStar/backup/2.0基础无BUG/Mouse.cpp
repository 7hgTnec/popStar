#include<graphics.h>
#include"Mouse.h"
MOUSEMSG m;
extern int px, py, size;
mPos::mPos(){ x = y = 0; lb = false;}
mPos::mPos(int nx, int ny, bool l){x = nx; y = ny; lb = l;}
mPos::mPos(const mPos& p){this->x = p.x; this->y = p.y; this->lb = p.lb;}
void mPos::getMousePos(){
	m = GetMouseMsg();
	x = (int)(m.x-px)/size;
	y = (int)(m.y-py)/size;
	lb = m.mkLButton;
}
bool mPos::getLB(){ return lb;}
int mPos::getX(){return x;}
int mPos::getY(){return y;}
