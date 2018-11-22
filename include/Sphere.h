#pragma once
#include "Shape.h"
#include "Material.h"

class Sphere :public Shape{
private:
	MVec3 center;
	float radius;
	Material *material;
public:
	Sphere(const MVec3& _center, const float& _radius,Material *_material) :center(_center), radius(_radius), material(_material){}

	virtual bool hit(Ray ray, float _min, float _max, HitRecord& rec){
		MVec3 cur = ray.getOrigin() - center;
		float a = MVec3::dot(ray.getDirection(), ray.getDirection());
		float b = 2.0 * MVec3::dot(ray.getDirection(), cur);
		float c = MVec3::dot(cur, cur) - radius * radius;
		float t = b * b - 4 * a * c;
		if(t > 0){
			float temp = (-b - sqrtf(t)) / (2 * a);
			if (temp < _max&&temp > _min){
				rec.set_T(temp);
				rec.set_Point(ray.getPoint(temp));
				rec.set_Normal(normalize(MVec3(rec.get_Point() - center)));
				rec.set_Material(material);
				return true;
			}
			temp = (-b + sqrtf(t)) / (2 * a);
			if (temp < _max&&temp > _min){
				rec.set_T(temp);
				rec.set_Point(ray.getPoint(temp));
				rec.set_Normal(normalize(MVec3(rec.get_Point() - center)));
				rec.set_Material(material);
				return true;
			}
		}
		return false;
	}

	virtual bool bounding(AABB &boundBox){
		boundBox = AABB(center - MVec3(radius, radius, radius), center + MVec3(radius, radius, radius));
		return true;
	}
};