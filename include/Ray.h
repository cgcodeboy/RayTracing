#pragma once

#include "MVec.h"

class Ray{
private:
	MVec3 origin;
	MVec3 direction;
	MVec3 normal;
public:
	Ray(MVec3 _origin, MVec3 _direction) :origin(_origin), direction(_direction){
		this->normal = normalize(direction);
	};

	Ray(){}

	inline MVec3 getPoint(float t){
		return origin + direction * t;
	}

	inline MVec3 getNormal() const{
		return normal;
	}

	inline MVec3 getOrigin() const{
		return origin;
	}

	inline MVec3 getDirection() const{
		return direction;
	}
};