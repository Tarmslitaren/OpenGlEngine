#include "Engine.h"
#include "enums.h"
#include "Input.h"
#include "Scene.h"
#include "Model.h"
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
#include "Material.h"


int main()
{


	GLEN::SetupInfo info;

	GLEN::Engine::Create(info);
	GLEN::Engine& engine = *GLEN::Engine::GetInstance();
	//triangle test
	GLEN::Scene scene;

	// a plane
	float planeVerts[] = {
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

	//cube with normals and texture coords
	float cubeVerts[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
	layout.hasTexCoords = true;
	layout.hasNormals = true;
	layout.normalOffset = 3;
	layout.texCoordOffset = 6;
	layout.texCoordAttribute = 2;
	layout.stride = 8;

	GLEN::ShaderProgram lightShader = *engine.GetShaderContainer().CreateShaderProgram("lightShader", "lightingShader.vert", "lightingShader.frag");
	//GLEN::ShaderProgram lightShader = *engine.GetShaderContainer().CreateShaderProgram("lightShader", "depthTest.vert", "depthTest.frag");


	GLEN::Material material;
	material.AddDiffuseTexture("container2.png", 0);
	material.AddSpecularTexture("container2_specular.png", 1);
	material.SetShininess(32.f);
	material.SetShader(lightShader.GetHandle());
	material.InitShaderVariables();

	int meshId = engine.GetMeshContainer().CreateMesh("cube", cubeVerts, sizeof(cubeVerts) / sizeof(float), layout, material);
	GLEN::Mesh* mesh = engine.GetMeshContainer().GetMesh(meshId);
	engine.GetModelContainer().CreateModel("cube", mesh);
	std::vector<GLEN::Model> primitives;
	for (int i = 0; i < 10; i++)
	{

		float angle = 20.0f * i;	

		GLEN::ModelInstance* instance = new GLEN::ModelInstance("cube", "lightShader");
		instance->SetPosition(cubePositions[i]);
		CU::Matrix33f ori;
		ori.SetIdentity();
		ori.SetRotationX(angle);
		ori.SetRotationY(0.3*angle);
		ori.SetRotationZ(0.5*angle);
		instance->SetOrientation(ori);
		scene.AddModel(instance);
		//instance->SetOutline(0.2f);

		
	}

	//loaded model
	engine.GetModelContainer().CreateModel("nanosuit/nanosuit.obj", material);
	GLEN::ModelInstance* instance = new GLEN::ModelInstance("nanosuit", "lightShader");
	instance->SetScale(0.1f);
	scene.AddModel(instance);
	instance->SetOutline(0.2f);

	//grass
	std::vector<CU::Vector3f> vegetationPos;
	vegetationPos.push_back({ -1.5f, 0.0f, -0.48f });
	vegetationPos.push_back({ 1.5f, 0.0f, 0.51f });
	vegetationPos.push_back({ 0.0f, 0.0f, 0.7f });
	vegetationPos.push_back({ -0.3f, 0.0f, -2.3f });
	vegetationPos.push_back({ 0.5f, 0.0f, -0.6f });
	GLEN::Material grassMaterial;
	grassMaterial.AddDiffuseTexture("grass.png", 0);
	grassMaterial.SetShader(lightShader.GetHandle());
	grassMaterial.InitShaderVariables();
	GLEN::VertexLayout planeLayout;
	planeLayout.hasTexCoords = true;
	planeLayout.hasNormals = false;
	planeLayout.texCoordOffset = 6;
	planeLayout.texCoordAttribute = 2;
	planeLayout.stride = 8;
	int gmeshId = engine.GetMeshContainer().CreateMesh("grass", planeVerts, sizeof(planeVerts) / sizeof(float), planeLayout, grassMaterial, indices, sizeof(indices) / sizeof(int));
	GLEN::Mesh* grassMesh = engine.GetMeshContainer().GetMesh(gmeshId);
	engine.GetModelContainer().CreateModel("grass", grassMesh);
	for (int i = 0; i < vegetationPos.size(); i++)
	{
		GLEN::ModelInstance* instance = new GLEN::ModelInstance("grass", "lightShader");
		instance->SetPosition(vegetationPos[i]);
		scene.AddModel(instance, true);
	}

	//init lights
	GLEN::ShaderProgram lampShader = *engine.GetShaderContainer().CreateShaderProgram("lampShader", "lampShader.vert", "lampShader.frag");

	//dir light
	GLEN::Light* light = new GLEN::Light(GLEN::DIRECTIONAL_LIGHT);
	light->SetDirection({ -0.2f, -1.0f, -0.3f });
	// light properties
	light->SetAmbient({ 0.1,0.1,0.1 });
	light->SetDiffuse({ 0.8f, 0.8f, 0.8f });
	light->SetSpecular({ 1.0f, 1.0f, 1.0f });
	scene.AddLight(light);

	//point lights
	CU::Vector3f pointLightPositions[] = {
	CU::Vector3f(0.7f,  0.2f,  2.0f),
	CU::Vector3f(2.3f, -3.3f, -4.0f),
	CU::Vector3f(-4.0f,  2.0f, -12.0f),
	CU::Vector3f(0.0f,  0.0f, -3.0f)
	};
	int nrPointLights = 2;
	for (int i = 0; i < nrPointLights; i++) {
		GLEN::ModelInstance* lampCube = new GLEN::ModelInstance("cube", "lampShader");
		GLEN::Light* light = new GLEN::Light(GLEN::POINT_LIGHT, lampCube, i);
		auto lightPos = pointLightPositions[i];//CU::Vector3f(1.2f, 1.0f, 2.0f);
		light->SetPosition(lightPos);

		lampCube->SetScale(0.2f);

		// light properties
		// we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
		// each environment and lighting type requires some tweaking to get the best out of your environment.
		light->SetAmbient({ 0.1,0.1,0.1 });
		light->SetDiffuse({ 0.8f, 0.8f, 0.8f });
		light->SetSpecular({ 1.0f, 1.0f, 1.0f });
		light->SetAttenuation(0.09f, 0.032f, 1);

		scene.AddLight(light);
	}
	lightShader.setInt("nrPointLights", nrPointLights); //todo: not here


	//flashlight:
	GLEN::Light* flashlight = new GLEN::Light(GLEN::SPOT_LIGHT);
	flashlight->SetDirection({ -0.2f, -1.0f, -0.3f });
	// light properties
	flashlight->SetAmbient({ 0.1,0.1,0.1 });
	flashlight->SetDiffuse({ 0.8f, 0.8f, 0.8f });
	flashlight->SetSpecular({ 1.0f, 1.0f, 1.0f });
	flashlight->SetSpotlightRadius(12.5f, 17.5f);
	scene.AddLight(flashlight);


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

		//move the light
		//float radius = 5.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//lightPos = CU::Vector3f(camX, 0, camZ);
		//light->SetPosition(lightPos);
		//light->SetDirection(CU::Vector3f(0, 0, 0) - lightPos);

		//move light with cammera (flashlight)
		flashlight->SetPosition(engine.GetCamera().GetPosition());
		flashlight->SetDirection(inputController.GetFront());

		
		//compared to opengl the x axis is reversed. this is fine, as now positive rotation over x axis is clockwize and not flipped.
		//also the order of matrix multiplication is reversed, now read from left to right instead of right to left...

		engine.RenderScene();


		//change light color
		//CU::Vector3f lightColor;
		//lightColor.x = sin(glfwGetTime() * 2.0f);
		//lightColor.y = sin(glfwGetTime() * 0.7f);
		//lightColor.z = sin(glfwGetTime() * 1.3f);
		//CU::Vector3f diffuseColor = lightColor * 0.5f; // decrease the influence
		//CU::Vector3f ambientColor = diffuseColor * 0.2f; // low influence
		//light->SetAmbient(ambientColor);
		//light->SetDiffuse(diffuseColor);

		scene.Render();
		
	}

	engine.Destroy();

	return 0;
}