#pragma once
#ifndef INPUTCONTROLLER_HEADER
#define INPUTCONTROLLER_HEADER
#include "Camera.h"
#include "Input.h"
#include "Engine.h"
//#include "MouseListener.h"
class InputController: public MouseListener 
{
public:
	InputController();
	~InputController();
	void PointerEvent(const CU::Vector2f& mousePosition);
	void ScrollEvent(const CU::Vector2f& scrollOffset);
	void Update(float deltaTime);
	CU::Vector3f GetFront() { return m_cameraFront; }
private:
	void calculateFront();
	float m_lastX = 400, m_lastY = 300;
	float m_yaw = -90.f, m_pitch = 0;
	bool m_firstMouse = true; //to prevent initial hitch
	float m_cameraSpeed = 2.5f;
	CU::Vector3f m_cameraPos = { 0, 0, 3 };
	CU::Vector3f m_cameraFront = { 0, 0, -1 };
	CU::Vector3f m_cameraUp = { 0, 1, 0 };

};
#endif

