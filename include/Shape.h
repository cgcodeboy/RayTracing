#pragma once

#include <Ray.h>
#include <HitRecord.h>
#include <AABB.h>
#include <iostream>
using namespace std;

class Shape{
public:
	virtual bool hit(Ray r, float _min, float _max, HitRecord& rec) = 0;
	virtual bool bounding(AABB &boundBox) = 0;
};