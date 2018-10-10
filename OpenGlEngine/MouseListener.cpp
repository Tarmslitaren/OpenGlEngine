#include "MouseListener.h"
#include "Engine.h"
#include "Input.h"


MouseListener::MouseListener()
{
	GLEN::Engine::GetInstance()->GetInput().AddListener(this);
}


MouseListener::~MouseListener()
{
}
