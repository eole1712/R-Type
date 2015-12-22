


Rectangle::Rectangle(int x, int y, int width, int height) : mX(x), mY(y), mHeight(height), mWidth(width) {}

Rectangle::~Rectangle() {}

int Rectangle::getX() const {
	return mX;
}

int Rectangle::getY() const {
	return mY;
}

int Rectangle::getWidth() const {
	return mWidth;
}

int Rectangle::getHeight() const {
	return mHeight;
}