#pragma once
#include "CU_Vector.h"
class MouseListener
{
public:
	MouseListener();
	virtual ~MouseListener();
	virtual void PointerEvent(const CU::Vector2f& mousePosition) = 0;
	virtual void ScrollEvent(const CU::Vector2f& scrollOffset) = 0;
};

