#ifndef __POINT_H__
#define __POINT_H__

// Imports ->
#include<windows.h>
// <- Imports

// Macros ans enums->

// <- Macros and enums

class Point {
private:
	int x;
	int y;
public:
	Point(int x = 0, int y = 0);
	void gotoxy();
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
};
#endif //Point.h