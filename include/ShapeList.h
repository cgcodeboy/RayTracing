#include "Shape.h"
#include "Sphere.h"
#include <list>
#include <iostream>

using namespace std;

class ShapeList :public Shape{
private:
	list<Shape*>* m_shapeList;
public:
	ShapeList(){
		this->m_shapeList = new list<Shape*>;
	}

	~ShapeList(){
		m_shapeList->clear();
	}

	void addSphere(Sphere* _sphere){
		this->m_shapeList->push_back(_sphere);
	}

	virtual bool hit(Ray r, float _min, float _max, HitRecord& rec){
		HitRecord tempRec;
		bool hitSomething = false;
		float closest = _max;
		for (list<Shape*>::iterator it = m_shapeList->begin(); it != m_shapeList->end();it++){
			if ((*it)->hit(r, _min, closest, tempRec)){
				hitSomething = true;
				closest = tempRec.get_T();
				rec = tempRec;
			}
		}
		return hitSomething;
	}

	virtual bool bounding(AABB& boundBox){
		if (m_shapeList->size() < 1)
			return false;
		AABB temp_box;
		bool boolValue = m_shapeList->front()->bounding(temp_box);
		if (!boolValue)
			return false;
		else
			boundBox = temp_box;
		for (list<Shape*>::iterator it = m_shapeList->begin(); it != m_shapeList->end(); it++){
			if ((*it)->bounding(temp_box))
				boundBox = surroundBox(boundBox, temp_box);
			else
				return false;
		}
		return true;
	}
};