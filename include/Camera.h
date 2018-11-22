#ifndef CAMERA_H
#define CAMERA_H

#include <Ray.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Camera{
public:
	Camera(MVec3 eye, MVec3 center, MVec3 up, float fov = 120, float aspect = 1.25){
		float theta = fov * M_PI / 180;
		float half_width = tan(theta / 2);
		float half_height = half_width / aspect;
		origin = eye;
		MVec3 u, v, w;
		w = normalize(eye - center);
		u = normalize(MVec3::cross(up,w));
		v = MVec3::cross(w,u);
		leftLow = origin - half_width * u - half_height * v - w;
		horizontal = 2  * half_width * u;
		vertical = 2 * half_height * v;
	}

	Ray getRay(float s, float t){
		return Ray(origin , leftLow + horizontal* s + vertical * t - origin );
	}
	MVec3 leftLow;
	MVec3 horizontal;
	MVec3 vertical;
	MVec3 origin;
};

#endif