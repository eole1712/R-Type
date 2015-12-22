
#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <vector>
#include "Rectangle.hpp"

class QuadTree {

static constexpr int kMaxLevels = 8;
static constexpr int kMaxObjects = 8;

public:
	QuadTree(Rectangle bounds);
	~QuadTree();
private:
	Quadtree(Rectangle bounds, int level);
public:

private:
	void split();
	unsigned int getSubTreeIndex();
private:
	unsigned int mLevel;
	Rectangle mBounds;

	std::vector<QuadTree*> mSubTrees;

	std::vector<> mObjects;
};

#endif /* !QUADTREE_H_ */