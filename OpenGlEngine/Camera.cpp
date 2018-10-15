#include "Camera.h"
#include "CommonMacros.h"
#include "VectorMath.h"
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

//the view matrix is somehow wrong
CU::Matrix44f GLEN::Camera::LookAt(const CU::Vector3f & target)
{
	
	auto target2 = m_position + target;
	m_backDirection = CU::Vector3f(m_position - target2).GetNormalized(); //zaxis
	auto upDirection = CU::Vector3f(0.0f, 1.0f, 0.0f); //world up
	m_rightDirection = upDirection.Cross(m_backDirection).GetNormalized(); //xaxis
	m_upDirection = m_backDirection.Cross(m_rightDirection); //yaxis

	CU::Matrix44f view;
	view.Set(m_rightDirection.x, m_rightDirection.y, m_rightDirection.z, 0, //right
		m_upDirection.x, m_upDirection.y, m_upDirection.z, 0, //up
		m_backDirection.x, m_backDirection.y, m_backDirection.z, 0, //direction
		0, 0, 0, 1);


	//m_view.Translate({ -m_position.x, -m_position.y, -m_position.z });
	CU::Matrix44f pos;
	pos.SetIdentity();
	CU::Vector3f invertPos = { -m_position.x, -m_position.y, -m_position.z }; //why invert? because the view matrix is the camera model matrix inversed.
	pos.Translate(invertPos);
	
	view = pos * view; //the mult order should here be reversed as  the matrix is inverted
	//view.SetPosition(invertPos);

	//view.Translate({ -m_position.x, -m_position.y, -m_position.z });
	return view;

	//return UpdatePos();
	/*
	    vec3 zaxis = normal(eye - target);    // The "forward" vector.
    vec3 xaxis = normal(cross(up, zaxis));// The "right" vector.
    vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.
 
    // Create a 4x4 orientation matrix from the right, up, and forward vectors
    // This is transposed which is equivalent to performing an inverse 
    // if the matrix is orthonormalized (in this case, it is).
    mat4 orientation = {
       vec4( xaxis.x, yaxis.x, zaxis.x, 0 ),
       vec4( xaxis.y, yaxis.y, zaxis.y, 0 ),
       vec4( xaxis.z, yaxis.z, zaxis.z, 0 ),
       vec4(   0,       0,       0,     1 )
    };
     
    // Create a 4x4 translation matrix.
    // The eye position is negated which is equivalent
    // to the inverse of the translation matrix. 
    // T(v)^-1 == T(-v)
    mat4 translation = {
        vec4(   1,      0,      0,   0 ),
        vec4(   0,      1,      0,   0 ), 
        vec4(   0,      0,      1,   0 ),
        vec4(-eye.x, -eye.y, -eye.z, 1 )
    };
 
    // Combine the orientation and translation to compute 
    // the final view matrix. Note that the order of 
    // multiplication is reversed because the matrices
    // are already inverted.
    return ( orientation * translation );*/

	/*
	    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation; // Identity matrix by default
    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation;
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z; 

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)*/
}


void GLEN::Camera::SetOrientation(const CU::Matrix33f & orientation)
{
		m_orientation = orientation;
}

void GLEN::Camera::SetOrientation(const CU::Vector3f& lookAt)
{
	m_orientation = CU::GenerateMatrix(lookAt);
}

void GLEN::Camera::SetPosition(const CU::Vector3f& position)
{
	m_position = position;
	m_orientation.Translate({ m_position.x, m_position.y, m_position.z });
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
}

CU::Vector3f GLEN::Camera::GetLookAtDirection()
{
	CU::Vector3f lookat;
	lookat.Set(0.0f, 0.0f, 1.0f);
	lookat = lookat * m_orientation.GetMatrix33().Transpose();
	return lookat;
}

CU::Matrix44f GLEN::Camera::GetView()
{
	return LookAt(GetLookAtDirection());
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
	//not coorect
	//m_view *= CU::Matrix44f::RotateX(angle);
	m_orientation.SetRotationX(angle);
}

void GLEN::Camera::Yaw(float angle)
{
	//not coorect
	//m_view *= CU::Matrix44f::RotateY(angle);
	m_orientation.SetRotationY(angle);
}

void GLEN::Camera::Roll(float angle)
{
	//not coorect
	//m_view *= CU::Matrix44f::RotateZ(angle);
	m_orientation.SetRotationZ(angle);
}
