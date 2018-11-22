#include <CImg.h>
#include <MVec.h>
#include <Ray.h>
#include <HitRecord.h>
#include <ShapeList.h>
#include <Sphere.h>
#include <Camera.h>
#include <time.h>
#include <lambertian.h>
#include <Metal.h>
#include <Dielectric.h>
#include <AABB.h>
#include <BVHNode.h>

using namespace cimg_library;

MVec3 getColor(Ray _r,Shape* _list,int depth){
	HitRecord rec;
	if (_list->hit(_r,0.001,FLT_MAX,rec)){
		Ray scattered;
		MVec3 attenuation;
		Material *m = rec.get_Material();
		if (depth < 15 && m->scatter(_r, rec, attenuation, scattered)){
			return attenuation * getColor(scattered, _list, depth + 1);
		}
		else{
			return MVec3(0, 0, 0);
		}
	}
	else{
		MVec3 unitDir = normalize(_r.getDirection());
		float t = 0.5 * (unitDir.getY() + 1.0);
		return MVec3(1, 1, 1) * (1 - t) + MVec3(0.5, 0.7, 0.9) * t;
	}
}

int main(){
	int width = 500, height = 400;
	CImg<unsigned char> img(width, height, 1, 3);

	Shape** m_geometry = new Shape*[9];
	m_geometry[0] = new Sphere(MVec3(0, -1000, 0), 1000, new Lambertian(MVec3(0.6, 0.4, 0.4)));
	m_geometry[1] = new Sphere(MVec3(2, 0.5, -1.4), 0.5, new Metal(MVec3(0.7, 0.8, 0.4), 0.4));
	m_geometry[2] = new Sphere(MVec3(1.3, 0.3, 1), 0.3, new Metal(MVec3(0.3, 0.5, 0.5), 0.4));
	m_geometry[3] = new Sphere(MVec3(0.2, 0.5, 1.5), 0.5, new Dielectric(1.5));
	m_geometry[4] = new Sphere(MVec3(-0.5, 0.6, -0.8), 0.6, new Metal(MVec3(0.3, 0.9, 0.7), 0.4));
	m_geometry[5] = new Sphere(MVec3(-2.1, 0.4, -2.2), 0.4, new Lambertian(MVec3(0.3, 0.9, 0.4)));
	m_geometry[6] = new Sphere(MVec3(-1.8, 0.5, -0.3), 0.5, new Dielectric(1.5));
	m_geometry[7] = new Sphere(MVec3(0.7, 0.6, 0.4), 0.6, new Metal(MVec3(0.5, 0.2, 0.8), 0.7));
	m_geometry[8] = new Sphere(MVec3(-1.1, 0.3, -2), 0.3, new Dielectric(1.5));

	/*ShapeList geometry;
	geometry.addSphere(new Sphere(MVec3(0, -1000, 0), 1000, new Lambertian(MVec3(0.6, 0.4, 0.4))));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, 1), 0.5, new Metal(MVec3(0.7, 0.8, 0.4), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, -1), 0.5, new Metal(MVec3(0.3, 0.5, 0.5), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, 2), 0.5, new Metal(MVec3(0.6, 0.5, 0.2), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, -2), 0.5, new Metal(MVec3(0.3, 0.9, 0.7), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, -3), 0.5, new Metal(MVec3(0.5, 0.4, 0.7), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, 3), 0.5, new Metal(MVec3(0.8, 0.2, 0.7), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, -4), 0.5, new Metal(MVec3(0.3, 0.7, 0.1), 0.4)));
	geometry.addSphere(new Sphere(MVec3(0, 0.5, 4), 0.5, new Metal(MVec3(0.6, 0.5, 0.9), 0.4)));*/

	Shape *world = new BVH_node(m_geometry, 9);

	MVec3 eye(3,1.5,0);
	MVec3 center(0, 0, 0);
	MVec3 up(0, 1, 0);

	Camera cam(eye,center,up);

	srand(time(0));

	int sample = 30;
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			MVec3 color(0, 0, 0);
			for (int k = 0; k < sample; k++){
				float u = (i + (rand() % 1000) / (float)1000) / width;
				float v = (j + rand() % 1000 / (float)1000) / height;
				Ray r = cam.getRay(u, v);
				color = color + getColor(r, world,0);			
			}
			color = color / sample;
			img(i, height - 1 - j, 0, 0) = color.getX() * 255;
			img(i, height - 1 - j, 0, 1) = color.getY() * 255;
			img(i, height - 1 - j, 0, 2) = color.getZ() * 255;
		}
	}
	img.display("Ray Tracing");

	return 0;
}

