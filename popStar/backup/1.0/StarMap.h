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
//��ͼ����:
//����Ĭ�ϵ�ԭ������Ļ�����Ͻǣ�X ������Ϊ����Y ������Ϊ����������λ�����ء�
//�������꣺
//���Ͻ�Ϊ����ԭ�㣬 �±����ͼ�����Ӧ��ϵΪ [y][x]



class map{
public:
	map();
	void creatmap();
	int dfs(int y, int x);//��ͨ����������,
	void printMap();//������ǵ�ͼ
	void isOperateable(int y, int x);//�жϵ�����Ƿ�����������ṩ�Ӿ���ʾ
	void extermBlock();//�������ӿ�
	void orderBlock();//������������ӿ��������
	bool isExtermable();//�жϵ�ͼ�Ƿ������ͨ��
	void cancleSelect();
	long int getGrade();

private:
	star block[10][10];
	static long int grade;
};
#endif