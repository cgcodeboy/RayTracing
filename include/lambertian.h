#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian :public Material{
public:
	Lambertian(const MVec3& _albedo) :albedo(_albedo){}
	virtual bool scatter(const Ray& r, const HitRecord& rec, MVec3& attenuation, Ray& scattered){
		MVec3 target = rec.get_Point() + rec.get_Normal() + getRandUnitVec();
		scattered = Ray(rec.get_Point(), target - rec.get_Point());
		attenuation = albedo;
		return true;
	}

private:
	MVec3 albedo;
};

#endif