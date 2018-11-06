#pragma once
#include "CU_Vector.h"
#include "CU_Matrix.h"
namespace GLEN
{
	struct ProjectionValues
	{
		float fov;
		float aspectRatio;
		float nearp;
		float farp;
	};
	class Camera
	{
	public:
		Camera();
		~Camera();
		void SetPosition(const CU::Vector3f& position);
		CU::Matrix44f LookAt(const CU::Vector3f& target); //sets view matrix and dir, right, up
		CU::Matrix44f GetOrientation(){return m_orientation;}
		void SetOrientation(const CU::Matrix33f& orientation);
		void SetOrientation(const CU::Vector3f& lookAt);
		CU::Matrix44f GetProjection() { return m_projection; }
		CU::Vector3f GetPosition() { return m_position; }
		CU::Vector3f GetLookAtDirection();
		CU::Matrix44f GetView();
		void SetOrthographicProjection(float left, float right, float top, float bottom, float nearPlane, float farPlane);
		void SetProjection(float fov, float aspectRatio, float near = 0.1f, float far = 100.f);
		void SetProjection(ProjectionValues projectionValues);
		float GetFov();
		void SetFov(float fov);

		void Pitch(float angle);
		void Yaw(float angle);
		void Roll(float angle);

		void UpdateShaders();
	private:
		CU::Vector3f m_position;
		CU::Matrix44f m_orientation;
		CU::Matrix44f m_projection;

		//these could be temporary if lookat sets position
		CU::Vector3f m_backDirection;
		CU::Vector3f m_rightDirection;
		CU::Vector3f m_upDirection;
		ProjectionValues m_projectionValues;
	};
}

