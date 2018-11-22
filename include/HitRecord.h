#pragma once

#include "CImg.h"

class Material;

class HitRecord{
private:
	float t;
	MVec3 point;
	MVec3 normal;
	Material* material;
public:
	float get_T(){
		return t;
	}
	void set_T(float _t){
		this -> t = _t;
	}

	MVec3 get_Point() const{
		return point;
	}
	void set_Point(const MVec3& _point){
		this->point = _point;
	}
	
	MVec3 get_Normal() const{
		return normal;
	}
	void set_Normal(const MVec3& _normal){
		this->normal = _normal;
	}

	Material* get_Material(){
		return material;
	}

	void set_Material(Material* _material){
		material = _material;
	}
};