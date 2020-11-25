/****************************************************************************
 *      This is part of the libYafaRay package
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "geometry/object_instance.h"
#include "geometry/primitive_instance.h"
#include "geometry/matrix4.h"

BEGIN_YAFARAY

ObjectInstance::ObjectInstance(const Object *base, const Matrix4 &obj_to_world) : base_(base), obj_to_world_(new Matrix4(obj_to_world))
{
	const std::vector<const Primitive *> primitives = base_->getPrimitives();
	primitive_instances_.reserve(base->numPrimitives());
	for(const auto &primitive : primitives)
	{
		PrimitiveInstance *instance_primitive = new PrimitiveInstance(primitive, this);
		primitive_instances_.emplace_back(instance_primitive);
	}
}

ObjectInstance::~ObjectInstance()
{
	for(auto &primitive_instance : primitive_instances_) delete primitive_instance;
	delete obj_to_world_;
}

/*void ObjectInstance::sample(float s_1, float s_2, Point3 &p, Vec3 &n) const
{
	base_->sample(s_1, s_2, p, n);
}*/

END_YAFARAY