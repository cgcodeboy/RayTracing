#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric :public Material{
public:
	Dielectric(float _shellIndex) :shellIndex(_shellIndex){}
	virtual bool scatter(const Ray& r, const HitRecord& rec, MVec3& attenuation, Ray& scattered){
		MVec3 outNormal;
		MVec3 reflected = reflect(r.getDirection(), rec.get_Normal());
		float in_over_out;
		attenuation = MVec3(1.0, 1.0, 1.0);
		MVec3 refracted;
		float reflect_prob;
		float cosine;
		if (MVec3::dot(r.getDirection(), rec.get_Normal()) > 0){
			outNormal = -rec.get_Normal();
			in_over_out = shellIndex;
			cosine = in_over_out*MVec3::dot(r.getDirection(), rec.get_Normal()) / r.getDirection().length();
		}
		else{
			outNormal = rec.get_Normal();
			in_over_out = 1/shellIndex;
			cosine = -MVec3::dot(r.getDirection(), rec.get_Normal()) / r.getDirection().length();
		}
		if (refract(r.getDirection(), outNormal, in_over_out, refracted)){
			reflect_prob = schlick(cosine, in_over_out);
		}
		else{
			scattered = Ray(rec.get_Point(), reflected);
			reflect_prob = 1.0;
		}
		if ((float)rand() / RAND_MAX < reflect_prob){
			scattered = Ray(rec.get_Point(), reflected);
		}
		else{
			scattered = Ray(rec.get_Point(), refracted);
		}
		return true;
	}

private:
	float shellIndex;
};

#endif