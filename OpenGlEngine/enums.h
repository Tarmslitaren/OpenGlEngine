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
		VERTEX_LAYOUT_NORMALS = 10,
		VERTEX_LAYOUT_TEXCOORDS = 2,
		VERTEX_LAYOUT_COLOR = 3
	};
}
#endif