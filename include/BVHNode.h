#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <shape.h>

int Xcompare(const void* a, const void* b);
int Ycompare(const void* a, const void* b);
int Zcompare(const void* a, const void* b);

class BVH_node :public Shape{
public:
	BVH_node(){}
	BVH_node(Shape **shape, int n){
		cout << "construct a node!" << endl;
		int axis = int(3 * (float)rand() / RAND_MAX);
		if (axis == 0)
			qsort(shape, n, sizeof(Shape*), Xcompare);
		else if (axis == 1)
			qsort(shape, n, sizeof(Shape*), Ycompare);
		else
			qsort(shape, n, sizeof(Shape*), Zcompare);
		if (n == 1)
			_left = _right = shape[0];
		else if (n == 2){
			_left = shape[0];
			_right = shape[1];
		}
		else{
			_left = new BVH_node(shape, n / 2);
			_right = new BVH_node(shape + n / 2, n - n / 2);
		}
		AABB box_left, box_right;
		if (!_left->bounding(box_left) || !_right->bounding(box_right))
			cout << "no bounding box in bvh node constructor" << endl;
		_box = surroundBox(box_left, box_right);
	}
	virtual bool hit(Ray ray, float _min, float _max, HitRecord& rec){
		if (_box.hit(ray, _min, _max)){
			HitRecord rec_left, rec_right;
			bool hit_left = _left->hit(ray, _min, _max, rec_left);
			bool hit_right = _right->hit(ray, _min, _max, rec_right);
			if (hit_left&&hit_right){
				if (rec_left.get_T() < rec_right.get_T())
					rec = rec_left;
				else
					rec = rec_right;
				return true;
			}
			else if (hit_left){
				rec = rec_left;
				return true;
			}
			else if (hit_right){
				rec = rec_right;
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	virtual bool bounding(AABB &boundBox){
		boundBox = _box;
		return true;
	}

private:
	Shape* _left;
	Shape* _right;
	AABB _box;
};

int Xcompare(const void* a, const void* b){
	AABB box_left, box_right;
	Shape* shapeA = *(Shape**)a;
	Shape* shapeB = *(Shape**)b;
	if (!shapeA->bounding(box_left) || !shapeB->bounding(box_right))
		cout << "no bounding box in bvh node constructor" << endl;
	if (box_left.min().getX() - box_right.min().getX() < 0.0)
		return -1;
	else
		return 1;
}

int Ycompare(const void* a, const void* b){
	AABB box_left, box_right;
	Shape* shapeA = *(Shape**)a;
	Shape* shapeB = *(Shape**)b;
	if (!shapeA->bounding(box_left) || !shapeB->bounding(box_right))
		cout << "no bounding box in bvh node constructor" << endl;
	if (box_left.min().getY() - box_right.min().getY() < 0.0)
		return -1;
	else
		return 1;
}

int Zcompare(const void* a, const void* b){
	AABB box_left, box_right;
	Shape* shapeA = *(Shape**)a;
	Shape* shapeB = *(Shape**)b;
	if (!shapeA->bounding(box_left) || !shapeB->bounding(box_right))
		cout << "no bounding box in bvh node constructor" << endl;
	if (box_left.min().getZ() - box_right.min().getZ() < 0.0)
		return -1;
	else
		return 1;
}

#endif