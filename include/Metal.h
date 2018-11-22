#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal :public Material{
public:
	Metal(const MVec3& _albedo,const float _fuzz) :albedo(_albedo),fuzz(_fuzz){}
	virtual bool scatter(const Ray& r, const HitRecord& rec, MVec3& attenuation, Ray& scattered){
		MVec3 reflected = reflect(normalize(r.getDirection()), rec.get_Normal());
		scattered = Ray(rec.get_Point(), reflected + fuzz*getRandUnitVec());
		attenuation = albedo;
		return MVec3::dot(scattered.getDirection(),rec.get_Normal())>0;
	}

private:
	MVec3 albedo;
	float fuzz;
};

#endif