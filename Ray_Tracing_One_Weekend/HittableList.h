#pragma once
#include <vector>
#include <memory>

#include "Hittable.h"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
	std::vector<shared_ptr<Hittable>> objectList;

	HittableList();
	HittableList(shared_ptr<Hittable> object);

	void clear();
	void add(shared_ptr<Hittable> object);

	bool hit(Ray r, Interval ray_t, RaycastHit& rec) const override;
};

