#include "HittableList.h"

HittableList::HittableList() {}

HittableList::HittableList(shared_ptr<Hittable> object)
{
	add(object);
}

void HittableList::clear()
{
	objectList.clear();
}

void HittableList::add(shared_ptr<Hittable> object)
{
	objectList.push_back(object);
}

bool HittableList::hit(Ray r, Interval ray_t, RaycastHit& rec) const
{
    RaycastHit temp_rec;
    bool is_hit = false;
    float closest_so_far = ray_t.max;

    for (const auto& object : objectList) 
    {
        if (object->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) 
        {
            is_hit = true;
            closest_so_far = temp_rec.m_t;
            rec = temp_rec;
        }
    }

    return is_hit;
}
