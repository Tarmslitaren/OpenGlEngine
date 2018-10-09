#include "Engine.h"
#include "enums.h"
#include "Input.h"
#include "Scene.h"
#include "Primitive.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "CU_Matrix.h"
#include "CU_Vector.h"
#include "VectorMath.h"
#include "CommonMacros.h"
#include <math.h>

// compute screen coordinates first
void gluPerspective(
	const float &angleOfView,
	const float &imageAspectRatio,
	const float &n, const float &f,
	float &b, float &t, float &l, float &r)
{
	float scale = tan(angleOfView * 0.5 * CU::PI / 180) * n;
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

int main()
{


	GLEN::SetupInfo info;
	
	GLEN::Engine* engine = GLEN::Engine::Create(info); 

	//triangle test
	GLEN::Scene scene;
	
	//GLEN::Primitive primitive;
	// a plane
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	// a cube 
	float vertices2[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};



	CU::Vector3f cubePositions[] = {
	  CU::Vector3f(0.0f,  0.0f,  0.0f),
	  CU::Vector3f(2.0f,  5.0f, -15.0f),
	  CU::Vector3f(-1.5f, -2.2f, -2.5f),
	  CU::Vector3f(-3.8f, -2.0f, -12.3f),
	  CU::Vector3f(2.4f, -0.4f, -3.5f),
	  CU::Vector3f(-1.7f,  3.0f, -7.5f),
	  CU::Vector3f(1.3f, -2.0f, -2.5f),
	  CU::Vector3f(1.5f,  2.0f, -2.5f),
	  CU::Vector3f(1.5f,  0.2f, -1.5f),
	  CU::Vector3f(-1.3f,  1.0f, -1.5f)
	};

	GLEN::VertexLayout layout;
	layout.hasColor = false;
	layout.texCoordOffset = 3;
	layout.stride = 5;

	GLEN::Texture texture;
	texture.LoadTexture("container.jpg");
	GLEN::Texture texture2;
	texture2.LoadTexture("awesomeface.png");

	//todo: make pool of shaders and shader programs and keep in container in engine.
	GLEN::ShaderProgram shaderProgram("shader.vert", "shader.frag");
	


	std::vector<GLEN::Primitive> primitives;
	for (int i = 0; i < 10; i++)
	{
		GLEN::Primitive* primitive = new GLEN::Primitive();
		primitive->SetVerticeData(vertices2, sizeof(vertices2) / sizeof(float), layout);
		primitive->addTexture(texture.getHandle());
		primitive->addTexture(texture2.getHandle());
		primitive->Finalize(GLEN::STATIC_DRAW);
		scene.AddPrimitive(primitive);
		primitive->SetShaderProgram(shaderProgram);
		primitive->setPosition(cubePositions[i]);
	}

	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	//primitive.SetIndexData(indices, sizeof(indices) / sizeof(int));




	//it's math time!!

	CU::Matrix44f model;
	model.SetIdentity();
	CU::Matrix44f view;
	view = CU::Matrix44f::Identity();
	view.Translate(CU::Vector3f(0, 0, -3));// = CU::Matrix44f::Translate({ 0,0,-3 }); //can't go over 1 unless using a projectoin matrix
	
	CU::Matrix44f projection = CU::Matrix44f::Identity();
	float angleOfView = 45; //degrees
	float aspectRatio = info.m_resolution.width/info.m_resolution.height;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float b, t, l, r; //result
	gluPerspective(angleOfView, aspectRatio, nearPlane, farPlane, b, t, l, r);
	glFrustum(b, t, l, r, nearPlane, farPlane, projection);

	while (engine->Update()) {
		//main loop
		if (engine->GetInput().GetKeyPressed(GLEN::KEY_ESC)) {
			break;
		}
		
		//compared to opengl the x axis is reversed. this is fine, as now positive rotation over x axis is clockwize and not flipped.
		//also the order of matrix multiplication is reversed, now read from left to right instead of right to left...

		model = CU::Matrix44f::RotateX(glfwGetTime() * 50 * 0.5);
		model *= CU::Matrix44f::RotateY(glfwGetTime() * 50 );
		shaderProgram.setMatrix("transform", model * view * projection);
		shaderProgram.setMatrix("model", model);
		shaderProgram.setMatrix("view", view);
		shaderProgram.setMatrix("projection", projection);

		shaderProgram.setFloat("hOffset", glfwGetTime());

		engine->RenderScene();
		scene.Render(view, projection);
		
	}

	engine->Destroy();

	return 0;
}