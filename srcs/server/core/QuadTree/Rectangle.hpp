
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

class Rectangle {
public:
	Rectangle(int x, int y, int width, int height);
	~Rectangle();
public:
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
private:
	Rectangle();
private:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
}

#endif /* !RECTANGLE_H_ */