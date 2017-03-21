#ifndef StarMap_h
#define StarMap_h
class star{
public:
	star();
	star(int c, int e);
	int getColor();
	int isExist();
	int isSelect();
	void setColor(int c);
	void setExist(int e);
	void setSelect(int s);
private:
	int color;
	int exist;
	int select;
};
//绘图坐标:
//坐标默认的原点在屏幕的左上角，X 轴向右为正，Y 轴向下为正，度量单位是象素。
//数组坐标：
//坐上角为坐标原点， 下标与绘图坐标对应关系为 [y][x]



class map{
public:
	map();
	map(int g);
	void creatmap();
	int dfs(int y, int x);//联通块搜索函数,
	void printMap();//输出星星地图
	bool isOperateable(int y, int x);//判断点击点是否可消除，并提供视觉提示
	bool isSelected(int y, int x);
	void extermBlock();//清除选中的连接块
	void orderBlock();//对消除后的连接块进行排序
	bool isExtermable();//判断地图是否存在联通块
	void cancelSelect();
	long int getGrade();
	void zeroGrade();
	int getLeftNum();
	int load();
	int save();

private:
	star block[10][10];
	static long int grade;
	static int leftNum;
};
#endif