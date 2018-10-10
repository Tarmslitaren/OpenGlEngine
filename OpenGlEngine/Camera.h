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
		const CU::Matrix44f& LookAt(const CU::Vector3f& target); //sets view matrix and dir, right, up
		void LookForward();
		CU::Matrix44f& getView(){return m_view;}
		CU::Matrix44f& getProjection() { return m_projection; }
		void SetProjection(float fov, float aspectRatio, float near = 0.1f, float far = 100.f);
		void SetProjection(ProjectionValues projectionValues);
		float GetFov();
		void SetFov(float fov);

		void Pitch(float angle);
		void Yaw(float angle);
		void Roll(float angle);
	private:
		CU::Vector3f m_position;
		CU::Matrix44f m_view;
		CU::Matrix44f m_projection;

		//these could be temporary if lookat sets position
		CU::Vector3f m_backDirection;
		CU::Vector3f m_rightDirection;
		CU::Vector3f m_upDirection;
		ProjectionValues m_projectionValues;
	};
}

