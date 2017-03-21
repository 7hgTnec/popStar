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
	map(int g);
	void creatmap();
	int dfs(int y, int x);//��ͨ����������,
	void printMap();//������ǵ�ͼ
	bool isOperateable(int y, int x);//�жϵ�����Ƿ�����������ṩ�Ӿ���ʾ
	bool isSelected(int y, int x);
	void extermBlock();//���ѡ�е����ӿ�
	void orderBlock();//������������ӿ��������
	bool isExtermable();//�жϵ�ͼ�Ƿ������ͨ��
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