#include "Camera.h"
#include "CommonMacros.h"
using namespace GLEN;

GLEN::Camera::Camera()
{
	m_rightDirection = { 1, 0, 0 };
	m_upDirection = { 0, 1, 0 };
	m_backDirection = { 0, 0, 1 };
	m_position = { 0,0,3 };
	LookAt({ 0, 0, 0 });
}

GLEN::Camera::~Camera()
{
}

const CU::Matrix44f& GLEN::Camera::LookAt(const CU::Vector3f & target)
{
	auto target2 = m_position + target;
	m_backDirection = CU::Vector3f(m_position - target2).GetNormalized();
	auto upDirection = CU::Vector3f(0.0f, 1.0f, 0.0f); //world up
	m_rightDirection = upDirection.Cross(m_backDirection).GetNormalized();
	m_upDirection = m_backDirection.Cross(m_rightDirection);

	m_view.Set(m_rightDirection.x, m_rightDirection.y, m_rightDirection.z, 0, //right
		m_upDirection.x, m_upDirection.y, m_upDirection.z, 0, //up
		m_backDirection.x, m_backDirection.y, m_backDirection.z, 0, //direction
		0, 0, 0, 1);


	//m_view.Translate({ -m_position.x, -m_position.y, -m_position.z });
	CU::Matrix44f pos;
	pos.SetIdentity();
	CU::Vector3f invertPos = { -m_position.x, -m_position.y, -m_position.z }; //why invert?
	pos.Translate(invertPos);
	//m_view = m_view * pos; //check the mult order here prolly wrong

	//m_view.Translate({ -m_position.x, -m_position.y, -m_position.z });
	return m_view;

	//return UpdatePos();
}

void GLEN::Camera::LookForward()
{
	LookAt(m_position + CU::Vector3f(0, 0, -1));
}

void GLEN::Camera::SetPosition(const CU::Vector3f& position)
{
	m_position = position;
	m_view.Translate({ -m_position.x, -m_position.y, -m_position.z });
}

// compute screen coordinates first
void gluPerspective(
	const float &angleOfView,
	const float &imageAspectRatio,
	const float &n, const float &f,
	float &b, float &t, float &l, float &r)
{
	float scale = tan(angleOfView * 0.5f * CU::PI / 180) * n;
	r = imageAspectRatio * scale;
	l = -r;
	t = scale;
	b = -t;
}

// set the OpenGL perspective projection matrix
void glFrustum(
	const float &b, const float &t, const float &l, const float &r,
	const float &n, const float &f,
	CU::Matrix44f &M)
{
	// set OpenGL perspective projection matrix

	M.myMatrix[0][0] = 2 * n / (r - l);
	M.myMatrix[0][1] = 0;
	M.myMatrix[0][2] = 0;
	M.myMatrix[0][3] = 0;

	M.myMatrix[1][0] = 0;
	M.myMatrix[1][1] = 2 * n / (t - b);
	M.myMatrix[1][2] = 0;
	M.myMatrix[1][3] = 0;

	M.myMatrix[2][0] = (r + l) / (r - l);
	M.myMatrix[2][1] = (t + b) / (t - b);
	M.myMatrix[2][2] = -(f + n) / (f - n);
	M.myMatrix[2][3] = -1;

	M.myMatrix[3][0] = 0;
	M.myMatrix[3][1] = 0;
	M.myMatrix[3][2] = -2 * f * n / (f - n);
	M.myMatrix[3][3] = 0;


	/*M.myMatrix[0][0] = 2 * n / (r - l);
	M.myMatrix[1][0] = 0;
	M.myMatrix[2][0] = 0;
	M.myMatrix[3][0] = 0;

	M.myMatrix[0][1] = 0;
	M.myMatrix[1][1] = 2 * n / (t - b);
	M.myMatrix[2][1] = 0;
	M.myMatrix[3][1] = 0;

	M.myMatrix[0][2] = (r + l) / (r - l);
	M.myMatrix[1][2] = (t + b) / (t - b);
	M.myMatrix[2][2] = -(f + n) / (f - n);
	M.myMatrix[3][2] = -1;

	M.myMatrix[0][3] = 0;
	M.myMatrix[1][3] = 0;
	M.myMatrix[2][3] = -2 * f * n / (f - n);
	M.myMatrix[3][3] = 0;*/
}

void GLEN::Camera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_projectionValues.fov = fov;
	m_projectionValues.aspectRatio = aspectRatio;
	m_projectionValues.nearp = nearPlane;
	m_projectionValues.farp = farPlane;
	m_projection = CU::Matrix44f::Identity();
	float b, t, l, r; //result
	gluPerspective(fov, aspectRatio, nearPlane, farPlane, b, t, l, r);
	glFrustum(b, t, l, r, nearPlane, farPlane, m_projection);
}

void GLEN::Camera::SetProjection(ProjectionValues pv)
{
	SetProjection(pv.fov, pv.aspectRatio, pv.nearp, pv.farp);
}

float GLEN::Camera::GetFov()
{
	return m_projectionValues.fov;
}
void GLEN::Camera::SetFov(float fov)
{
	m_projectionValues.fov = fov;
	SetProjection(m_projectionValues);
}

void GLEN::Camera::Pitch(float angle)
{
	m_view *= CU::Matrix44f::RotateX(angle);
}

void GLEN::Camera::Yaw(float angle)
{
	m_view *= CU::Matrix44f::RotateY(angle);
}

void GLEN::Camera::Roll(float angle)
{
	m_view *= CU::Matrix44f::RotateZ(angle);
}
