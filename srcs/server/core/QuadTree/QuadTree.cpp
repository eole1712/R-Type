
#include "QuadTree.hpp"

QuadTree::QuadTree(Rectangle bounds) : mLevel(0), mBounds(bounds) {}

Quadtree::Quadtree(Rectangle bounds, int level) : mLevel(level), mBounds(bounds)  {}

QuadTree::~QuadTree() {
	mObjects.clear();
	for (Quadtree* quadTree : mSubTrees) {
		if (quadTree) {
			delete quadTree();
			quadTree = NULL;
		}
	}
}

void	QuadTree::split() {
	if (mSubTrees.size() != 0)
		std::cerr << "Error Already splitted" << std::endl;
	//top-left
	Rectangle newBounds(bounds.getX(), bounds.getY(), bounds.getWidth() / 2, bounds.getHeight() / 2);
	mSubTrees.push_back(new Quadtree(newBounds, mLevel + 1));
	//top-right
	newBounds = Rectangle(bounds.getX() + bounds.getWidth() / 2, bounds.getY(), bounds.getWidth() / 2, bounds.getHeight() / 2);
	mSubTrees.push_back(new Quadtree(newBounds, mLevel + 1));
	//bottom-right
	newBounds = Rectangle(bounds.getX() + bounds.getWidth() / 2, bounds.getY() + bounds.getHeight() / 2, bounds.getWidth() / 2, bounds.getHeight() / 2);
	mSubTrees.push_back(new Quadtree(newBounds, mLevel + 1));
	//bottom-left
	newBounds = Rectangle(bounds.getX(), bounds.getY() + bounds.getHeight() / 2, bounds.getWidth() / 2, bounds.getHeight() / 2);
	mSubTrees.push_back(new Quadtree(newBounds, mLevel + 1));
}

int QuadTree::getSubTreeIndex(Rectangle& bounds) {
	bool fitsTop = bounds.getY() + bounds.getHeight() <= mBounds.getY() + mBounds.getHeight() / 2;
	bool fitsBot = bounds.getY() > mBounds.getY() + mBounds.getHeight() / 2;
	bool fitsLeft = bounds.getX() + bounds.getWidth() <= mBounds.getX() + mBounds.getWidth() / 2;;
	bool fitsRight = bounds.getX() > mBounds.getX() + mBounds.getWidth() / 2;
	
	if (fitsTop && fitsLeft) return 0;
	if (fitsTop && fitsRight) return 1;
	if (fitsBot && fitsRight) return 2;
	if (fitsBot && fitsLeft) return 3;
	return -1;
}

void QuadTree::insert(Rectangle& bounds) {
	if (mSubTrees.size() > 0) {
		if ((int index = getSubTreeIndex(Rectangle bounds)) != -1) {
			mSubTrees[index]->insert(bounds);
			return;
		}
	}
	mObjects.push_back(bounds);
	if (mObjects.size() > kMaxObjects && mSubTrees.size() == 0) {
		split();
		int i = 0;
		while (i < mObjects.size()) {
			if ((int index = getSubTreeIndex(mObject[i])) != -1) {
				mSubTrees[index]->insert(mObjects[i]);
				mObjects.erase(mObjects.begin() + i);
			}
			else {
				i++;
			}
		}
	}
}

void Quadtree::getItems()
