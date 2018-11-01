#pragma once
#ifndef ENUMS_HEADER
#define ENUMS_HEADER
#include "CU_Vector.h"
#include <iostream>
namespace GLEN
{
	enum VertexAttributeLocation
	{
		VERTEX_LAYOUT_POSITION = 0,
		VERTEX_LAYOUT_NORMALS = 1,
		VERTEX_LAYOUT_TEXCOORDS = 2,
		VERTEX_LAYOUT_COLOR = 4,
		VERTEX_LAYOUT_INSTANCE_MATRIX = 10
	};
}
#endif