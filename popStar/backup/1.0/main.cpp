#include"StarMap.h"
#include"StarMap.cpp"

main()
{
	initgraph(800,800);
	map m;
	m.printMap();
	getchar();
	closegraph();
	return 0;
}
