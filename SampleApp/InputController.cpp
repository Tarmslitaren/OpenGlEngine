#include "InputController.h"
#include "Engine.h"
#include "Converters.h"

InputController::InputController()
{
	GLEN::Engine::GetInstance()->GetInput().CaptureMouseAndDisablePointer(); //good for mouselook
}


InputController::~InputController()
{
}

void InputController::PointerEvent(const CU::Vector2f & mousePosition)
{
	//mouse look
	if (m_firstMouse)
	{
		m_lastX = mousePosition.x;
		m_lastY = mousePosition.y;
		m_firstMouse = false;
	}

	float xoffset = mousePosition.x - m_lastX;
	float yoffset = m_lastY - mousePosition.y;
	m_lastX = mousePosition.x;
	m_lastY = mousePosition.y;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	calculateFront();
	GLEN::Engine::GetInstance()->GetCamera().SetOrientation(m_cameraFront);
	//GLEN::Engine::GetInstance()->GetCamera().LookAt(m_cameraFront); //something is fucked. the position of the camera gets wildly inappropriate

		//GLEN::Engine::GetInstance()->GetCamera().Pitch(m_pitch*0.01);
	//GLEN::Engine::GetInstance()->GetCamera().Yaw(m_yaw*0.01);

}

void InputController::ScrollEvent(const CU::Vector2f & scrollOffset)
{
	float fov = GLEN::Engine::GetInstance()->GetCamera().GetFov();
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= scrollOffset.y;
	}
	if (fov <= 1.0f)
	{
		fov = 1.0f;
	}
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}

	GLEN::Engine::GetInstance()->GetCamera().SetFov(fov);
}

void InputController::Update(float deltaTime)
{
	GLEN::Engine& engine = *GLEN::Engine::GetInstance();
	float cameraSpeed = m_cameraSpeed * deltaTime;
	if (engine.GetInput().GetKeyPressed(GLFW_KEY_W))
		m_cameraPos +=m_cameraFront * cameraSpeed;
	if (engine.GetInput().GetKeyPressed(GLFW_KEY_S))
		m_cameraPos -= m_cameraFront * cameraSpeed;
	if (engine.GetInput().GetKeyPressed(GLFW_KEY_A))
		m_cameraPos -= m_cameraFront.Cross(m_cameraUp).GetNormalized() * cameraSpeed;
	if (engine.GetInput().GetKeyPressed(GLFW_KEY_D))
	{
		m_cameraPos += m_cameraFront.Cross(m_cameraUp).GetNormalized() * cameraSpeed;
	}

	engine.GetCamera().SetPosition(m_cameraPos);
	//engine.GetCamera().UpdatePos();

	//auto cameraPos = CU::Vector3f(0, 0, 3);

	//engine.GetCamera().SetPosition(cameraPos);

}

void InputController::calculateFront()
{
	m_cameraFront.x = cos(Convert::DegreeToRadian(m_yaw)) * cos(Convert::DegreeToRadian(m_pitch));
	m_cameraFront.y = sin(Convert::DegreeToRadian(m_pitch));
	m_cameraFront.z = sin(Convert::DegreeToRadian(m_yaw)) * cos(Convert::DegreeToRadian(m_pitch));
	m_cameraFront.Normalize();
}
