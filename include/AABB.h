#ifndef AABB_H
#define AABB_H

#include <MVec.h>
#include <Ray.h>

inline float M_min(float a, float b){ return a < b ? a : b; }
inline float M_max(float a, float b){ return a > b ? a : b; }

class AABB{
public:
	AABB(){}
	AABB(const MVec3& min, const MVec3& max) :_min(min), _max(max){}
	MVec3 min(){return _min;}
	MVec3 max(){return _max;}
	bool hit(const Ray& r, float min, float max) const{
		for (int i = 0; i < 3; i++){
			float invD = 1.0f / r.getDirection()[i];
			float t0 = (_min[i] - r.getOrigin()[i]) * invD;
			float t1 = (_max[i] - r.getOrigin()[i]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			min = t0 > min ? t0 : min;
			max = t1 < max ? t1 : max;
			if (max <= min)
				return false;
		}
		return true;
	}
private:
	MVec3 _min;
	MVec3 _max;
};

AABB surroundBox(AABB box_0, AABB box_1){
	MVec3 _small(fmin(box_0.min().getX(), box_1.min().getX()), \
		fmin(box_0.min().getY(), box_1.min().getY()), \
		fmin(box_0.min().getZ(), box_1.min().getZ()));
	MVec3 _big(fmax(box_0.max().getX(), box_1.max().getX()), \
		fmax(box_0.max().getY(), box_1.max().getY()), \
		fmax(box_0.max().getZ(), box_1.max().getZ()));
	return AABB(_small, _big);
}

#endif