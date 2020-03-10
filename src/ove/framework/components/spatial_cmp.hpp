#pragma once

#include <ove/math/vec.hpp>
#include <ove/math/quat.hpp>
#include <ove/math/mat.hpp>
#include <ove/math/euler.hpp>

namespace ove
{
	namespace framework
	{
		struct spatial_cmp_t
		{
			math::vec3f position;
			math::eulerf angles;
			math::quatf rotation;
			math::vec3f scale;
			math::mat4f matrix;
			math::mat4f inv_matrix;
		};
	}
}