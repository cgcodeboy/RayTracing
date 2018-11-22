#pragma once
#include <iostream>
#include <math.h>
#include <random>

class MVec3{
private:
	float x;
	float y;
	float z;

public:
	MVec3() = default;

	MVec3(float _x, float _y, float _z) :x(_x), y(_y), z(_z){}

	MVec3(const MVec3 &vec3){ this->x = vec3.getX(), this->y = vec3.getY(), this->z = vec3.getZ(); }

	MVec3& operator = (const MVec3 &vec3){ this->x = vec3.getX(), this->y = vec3.getY(), this->z = vec3.getZ(); return *this; }

	inline float operator[](int i) const{
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else{
			std::cout << "index i is error!" << std::endl;
			return 0;
		}
	};

	inline MVec3 operator+(){
		return *this;
	}

	inline MVec3 operator-() const{
		return MVec3(-x, -y, -z);
	}

	inline static float dot(const MVec3 &v1, const MVec3 &v2){
		return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
	}

	inline static MVec3 cross(const MVec3 &v1, const MVec3 &v2){
		return MVec3(v1.getY()*v2.getZ() - v1.getZ()*v2.getY(),\
					-v1.getX()*v2.getZ() - v1.getZ()*v2.getX(),\
					v1.getX()*v2.getY() - v1.getY()*v2.getX());
	}

	inline float lengthSquare() const{
		return  x * x + y * y + z * z;
	}

	inline float length() const{
		return sqrtf(lengthSquare());
	}
	inline float getY() const{
		return y;
	}
	inline float getX() const{ 
		return x;
	}
	inline float getZ() const{
		return z;
	}

	inline bool valid(){
		if (x == 0 && y == 0 && z == 0){
			return false;
		}
		return true;
	}

	inline bool operator == (const MVec3& v){
		if (x == v.getX() && y == v.getY() && z == v.getZ())
			return true;
		return false;
	}
};

inline MVec3 operator+(const MVec3 &v1, const MVec3 &v2){
	return MVec3(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

inline MVec3 operator-(const MVec3 &v1, const MVec3 &v2){
	return MVec3(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

inline MVec3 operator*(const float &t, const MVec3& v){
	return MVec3(t * v.getX(), t *v.getY(), t *v.getZ());
}

inline MVec3 operator*(const MVec3& v,const float &t){
	return MVec3(t * v.getX(), t *v.getY(), t *v.getZ());
}

inline MVec3 operator*(const MVec3 &v1, const MVec3 &v2){
	return MVec3(v1.getX()*v2.getX(), v1.getY()*v2.getY(), v1.getZ()*v2.getZ());
}

inline MVec3 operator /(const MVec3& v, const float &t){
	return MVec3(v.getX()/t, v.getY()/t, v.getZ()/t);
}

inline MVec3 operator /(const MVec3& v1, const MVec3& v2){
	return MVec3(v1.getX() / v2.getX(), v1.getY() / v2.getY(), v1.getZ() / v2.getZ());
}

inline MVec3 normalize(const MVec3& v){
	return v / v.length();
}

MVec3 reflect(const MVec3& in, const MVec3& normal){
	return in - normal * MVec3::dot(in, normal) * 2;
}

bool refract(const MVec3& in, const MVec3& normal, float in_over_out, MVec3& refracted){
	MVec3 inNormal = normalize(in);
	float costheta = MVec3::dot(inNormal, normal);
	float discriminant = 1.0 - in_over_out*in_over_out*(1 - costheta*costheta);
	if (discriminant > 0){
		refracted = in_over_out*(inNormal - normal * costheta) - normal*sqrt(discriminant);
		return true;
	}
	else{
		return false;
	}
}

MVec3 getRandUnitVec(){
	MVec3 p;
	do{
		p = MVec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) * 2 - MVec3(1, 1, 1);
	} while (p.length() >= 1);
	return p;
}

MVec3 getRandDiskVec(){
	MVec3 p;
	do{
		p = MVec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0) * 2 - MVec3(1, 1, 0);
	} while (p.length() >= 1);
	return p;
}

float schlick(float cosine, float in_over_out){
	float r0 = (1 - in_over_out) / (1 + in_over_out);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow(1 - cosine, 5);
}