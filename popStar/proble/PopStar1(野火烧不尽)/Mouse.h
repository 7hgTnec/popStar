#ifndef MOUSE_H
#define MOUSE_H
class mPos{
public:
	mPos();
	mPos(int nx, int ny, bool l);
	mPos(const mPos& p);
	void getMousePos();
	int getX();
	int getY();
	bool getLB();
private:
	int x;
	int y;
	bool lb;
};
#endif