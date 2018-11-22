#ifndef MATERIAL_H
#define MATERIAL_H

#include "HitRecord.h"
#include "Ray.h"

class Material{
public:
	virtual bool scatter(const Ray& r, const HitRecord& rec, MVec3& attenuation, Ray& scattered) = 0;
};

#endif