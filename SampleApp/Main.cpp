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
//#include "CommonMacros.h"
#include <math.h>
#include "InputController.h"
#include "ModelInstance.h"
#include "ModelContainer.h"


int main()
{


	GLEN::SetupInfo info;

	GLEN::Engine::Create(info);
	GLEN::Engine& engine = *GLEN::Engine::GetInstance();
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

	// a cube with texcords
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

	//cube with normals
	float vertices3[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	layout.hasTexCoords = false;
	//layout.texCoordOffset = 3;
	//layout.stride = 6;

	GLEN::Texture texture = *engine.GetTextureContainer().GetTexture("container.jpg");
	GLEN::Texture texture2 = *engine.GetTextureContainer().GetTexture("awesomeface.png");;

	GLEN::ShaderProgram lightShader = *engine.GetShaderContainer().CreateShaderProgram("lightShader", "lightingShader.vert", "lightingShader.frag");


	engine.GetModelContainer().CreatePrimitive("cube", vertices3, sizeof(vertices3) / sizeof(float), layout, { (int)texture.getHandle() , (int)texture2.getHandle() });

	std::vector<GLEN::Primitive> primitives;
	for (int i = 0; i < 1; i++)
	{
		GLEN::ModelInstance* instance = new GLEN::ModelInstance("cube", "lightShader");
		instance->SetPosition(cubePositions[i]);
		scene.AddModel(instance);
		
	}


	GLEN::ShaderProgram lampShader = *engine.GetShaderContainer().CreateShaderProgram("lampShader", "lampShader.vert", "lampShader.frag");
	GLEN::ModelInstance* lampCube = new GLEN::ModelInstance("cube", "lampShader");
	GLEN::Light* light = new GLEN::Light(lampCube);
	auto lightPos = CU::Vector3f(1.2f, 1.0f, 2.0f);
	lampCube->SetPosition(lightPos);
	lampCube->SetPosition(lightPos);
	lampCube->SetScale(0.2f);

	scene.AddLight(light);

	engine.GetCamera().SetProjection(45, info.m_resolution.width / info.m_resolution.height);

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	

	InputController inputController;

	//main loop
	while (engine.Update(deltaTime)) {
		
		if (engine.GetInput().GetKeyPressed(GLEN::KEY_ESC)) {
			break;
		}

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		inputController.Update(deltaTime);

		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		lightPos = CU::Vector3f(camX, 0, camZ);
		lampCube->SetPosition(lightPos);


		//auto cameraTarget = CU::Vector3f(camX, 0.f, camZ);

		auto view = engine.GetCamera().getView();
		auto pos = view.GetPosition();
		view.Translate(pos);
	

		//view = engine.GetCamera().LookAt(cameraTarget);
		
		//compared to opengl the x axis is reversed. this is fine, as now positive rotation over x axis is clockwize and not flipped.
		//also the order of matrix multiplication is reversed, now read from left to right instead of right to left...

		engine.RenderScene();

		auto projection = engine.GetCamera().getProjection();

		light->SetPosition(lightPos);

		CU::Vector3f lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		CU::Vector3f diffuseColor = lightColor * 0.5f; // decrease the influence
		CU::Vector3f ambientColor = diffuseColor * 0.2f; // low influence

		light->SetAmbient(ambientColor);
		light->SetDiffuse(diffuseColor);

		scene.Render(); //send in the camera here, or let the scene own the camera?
		
	}

	engine.Destroy();

	return 0;
}