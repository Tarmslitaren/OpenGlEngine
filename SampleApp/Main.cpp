#pragma once
#include "Engine.h"
#include "Input.h"
#include "Scene.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "CU_Matrix.h"
#include "CU_Vector.h"
#include "VectorMath.h"
#include <math.h>
#include "InputController.h"
#include "ModelInstance.h"
#include "ModelContainer.h"
#include "Material.h"
#include "PostProcess.h"
#include "SkyBox.h"
#include "ErrorHandler.h"
#include "Mesh.h"
#include "ShaderInput.h"
#include "SceneContainer.h"

int main()
{


	GLEN::SetupInfo info;

	GLEN::Engine::Create(info);
	GLEN::Engine& engine = *GLEN::Engine::GetInstance();
	GLEN::Scene& scene = engine.GetSceneContainer().AddScene();

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

	//skybox
	std::vector< std::pair <std::string, GLEN::CubeMapOrientation> > cubemapImages = {
		{"skybox/right.jpg", GLEN::CUBE_MAP_POSITIVE_X},
		{"skybox/left.jpg", GLEN::CUBE_MAP_NEGATIVE_X},
		{"skybox/bottom.jpg", GLEN::CUBE_MAP_POSITIVE_Y},
		{"skybox/top.jpg", GLEN::CUBE_MAP_NEAGATIVE_Y},
		{"skybox/front.jpg", GLEN::CUBE_MAP_POSITIVE_Z},
		{"skybox/back.jpg", GLEN::CUBE_MAP_NEAGATIVE_Z},
	};
	GLEN::SkyBox* skyBox = new GLEN::SkyBox("skybox", cubemapImages);
	scene.SetSkyBox(skyBox);


	GLEN::Material material("lightShader");
	material.AddDiffuseTexture("container2.png", 0);
	material.AddSpecularTexture("container2_specular.png", 1);
	material.SetCubeMapTexture("skybox");
	material.InitShaderVariables();

	GLEN::Mesh* mesh = engine.GetMeshContainer().GetMesh(engine.GetMeshContainer().CreateBox("cube", {1,1,1},material));
	engine.GetModelContainer().CreateModel("cube", mesh);

	std::vector<GLEN::ModelInstance*> cubes;
	for (int i = 0; i < 10; i++)
	{

		float angle = 20.0f * i;	

		GLEN::ModelInstance* instance = new GLEN::ModelInstance("cube");
		instance->SetPosition(cubePositions[i]);
		CU::Matrix33f ori;
		ori.SetIdentity();
		ori.SetRotationX(angle);
		ori.SetRotationY(0.3*angle);
		ori.SetRotationZ(0.5*angle);
		instance->SetOrientation(ori);
		scene.AddModel(instance);
		cubes.push_back(instance);
		//instance->SetOutline(0.2f);

		
	}

	//new reflection cube
	GLEN::Material materialr("reflectShader");
	materialr.SetCubeMapTexture("skybox");
	materialr.InitShaderVariables();

	GLEN::Mesh* meshr = engine.GetMeshContainer().GetMesh(engine.GetMeshContainer().CreateBox("cuber", { 2,2,1 }, materialr));
	engine.GetModelContainer().CreateModel("cuber", meshr);
	GLEN::ModelInstance* instancer = new GLEN::ModelInstance("cuber");
	//scene.AddModel(instancer);


	//loaded model
	GLEN::Material material2("lightShader");
	material2.InitShaderVariables();
	engine.GetModelContainer().CreateModel("nanosuit/nanosuit.obj", material2);
	GLEN::ModelInstance* instance = new GLEN::ModelInstance("nanosuit");
	instance->SetScale(0.1f);
	//instance->SetRendeMode(GLEN::RENDERMODE_LINE_LOOP);
	scene.AddModel(instance);
	//instance->SetOutline(0.2f);

	//grass
	std::vector<CU::Vector3f> vegetationPos;
	vegetationPos.push_back({ -1.5f, 0.0f, -0.48f });
	vegetationPos.push_back({ 1.5f, 0.0f, 0.51f });
	vegetationPos.push_back({ 0.0f, 0.0f, 0.7f });
	vegetationPos.push_back({ -0.3f, 0.0f, -2.3f });
	vegetationPos.push_back({ 0.5f, 0.0f, -0.6f });
	GLEN::Material grassMaterial("lightShader");
	grassMaterial.AddDiffuseTexture("blending_transparent_window.png", 0, true);
	grassMaterial.InitShaderVariables();
	
	int gmeshId = engine.GetMeshContainer().CreateQuad("grass", { 1,1,0 }, grassMaterial);
	GLEN::Mesh* grassMesh = engine.GetMeshContainer().GetMesh(gmeshId);
	engine.GetModelContainer().CreateModel("grass", grassMesh);
	for (int i = 0; i < vegetationPos.size(); i++)
	{
		GLEN::ModelInstance* instance = new GLEN::ModelInstance("grass");
		instance->SetPosition(vegetationPos[i]);
		scene.AddModel(instance, true);
	}

	//geometry shader test
	GLEN::VertexContent content;
	content.positions = {
	-0.5f,  0.5f, 0, // top-left
	 0.5f,  0.5f, 0, // top-right
	 0.5f, -0.5f, 0, // bottom-right
	-0.5f, -0.5f, 0  // bottom-left
	};

	content.colors = {
	1.0f, 0.0f, 0.0f, // top-left
	0.0f, 1.0f, 0.0f, // top-right
	0.0f, 0.0f, 1.0f, // bottom-right
	1.0f, 1.0f, 0.0f  // bottom-left
	};

	engine.GetShaderContainer().CreateShaderProgram("simpleGeom", "simple.vert", "singleColor.frag", "houses.geom");
	GLEN::Material geomMaterial("simpleGeom");
	geomMaterial.InitShaderVariables();
	int geomMeshId = engine.GetMeshContainer().CreateMesh("points", content, geomMaterial);
	GLEN::Mesh* geomMesh = engine.GetMeshContainer().GetMesh(geomMeshId);
	engine.GetModelContainer().CreateModel("points", geomMesh);
	//geomMesh->SetPolygonMode(GLEN::PolygonMode::POLYGONMODE_POINT);
	GLEN::ModelInstance* pointsinstance = new GLEN::ModelInstance("points");
	pointsinstance->SetRendeMode(GLEN::RENDERMODE_POINTS);
	//scene.AddModel(pointsinstance);


	//init lights:

	//dir light
	GLEN::Light* light = new GLEN::Light(GLEN::DIRECTIONAL_LIGHT);
	light->SetDirection({ -0.2f, -1.0f, -0.3f });
	// light properties
	light->SetAmbient({ 0.1,0.1,0.1 });
	light->SetDiffuse({ 0.8f, 0.8f, 0.8f });
	light->SetSpecular({ 1.0f, 1.0f, 1.0f });
	scene.AddLight(light);

	//point lights
	GLEN::Material lampMat("lampShader");
	lampMat.InitShaderVariables();
	GLEN::Mesh* meshlamp = engine.GetMeshContainer().GetMesh(engine.GetMeshContainer().CreateBox("lampCube", { 0.2,0.2,0.2 }, lampMat));
	engine.GetModelContainer().CreateModel("lampCube", meshlamp);


	CU::Vector3f pointLightPositions[] = {
	CU::Vector3f(0.7f,  0.2f,  2.0f),
	CU::Vector3f(2.3f, -3.3f, -4.0f),
	CU::Vector3f(-4.0f,  2.0f, -12.0f),
	CU::Vector3f(0.0f,  0.0f, -3.0f)
	};
	int nrPointLights = 2;
	for (int i = 0; i < nrPointLights; i++) {
		GLEN::ModelInstance* lampCube = new GLEN::ModelInstance("lampCube");
		GLEN::Light* light = new GLEN::Light(GLEN::POINT_LIGHT, lampCube, i);
		auto lightPos = pointLightPositions[i];//CU::Vector3f(1.2f, 1.0f, 2.0f);
		light->SetPosition(lightPos);


		// light properties
		// we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
		// each environment and lighting type requires some tweaking to get the best out of your environment.
		light->SetAmbient({ 0.1,0.1,0.1 });
		light->SetDiffuse({ 0.8f, 0.8f, 0.8f });
		light->SetSpecular({ 1.0f, 1.0f, 1.0f });
		light->SetAttenuation(0.09f, 0.032f, 1);

		//scene.AddLight(light);
	}


	//flashlight:
	GLEN::Light* flashlight = new GLEN::Light(GLEN::SPOT_LIGHT);
	flashlight->SetDirection({ -0.2f, -1.0f, -0.3f });
	// light properties
	flashlight->SetAmbient({ 0.1,0.1,0.1 });
	flashlight->SetDiffuse({ 0.8f, 0.8f, 0.8f });
	flashlight->SetSpecular({ 1.0f, 1.0f, 1.0f });
	flashlight->SetSpotlightRadius(12.5f, 17.5f);
	scene.AddLight(flashlight);

	/////////////////////////////////// second scene ////////////////////


	GLEN::Scene& scene2 = engine.GetSceneContainer().AddScene();
	engine.GetSceneContainer().SetCurrentScene(scene2);
	
	engine.GetSceneContainer().SetCurrentScene(scene2);
	scene2.AddLight(flashlight);
	scene2.AddLight(light);

	scene2.SetSkyBox(skyBox);

	//scene2.AddModel(instance);

	//loaded space models
	GLEN::Material material3("noLightShaderInstanced");
	material3.InitShaderVariables();
	engine.GetModelContainer().CreateModel("planet/planet.obj", material2);
	GLEN::ModelInstance* planet = new GLEN::ModelInstance("planet");
	//instance->SetScale(0.1f);
	scene2.AddModel(planet);

	engine.GetModelContainer().CreateModel("rock/rock.obj", material3);

	int amount = 10000;
	srand(glfwGetTime()); // initialize random seed	
	float radius = 150.0;
	float offset = 25.f;
	for (int i = 0; i < amount; i++)
	{
		GLEN::ModelInstance* rock = new GLEN::ModelInstance("rock");
		//rock->SetStatic(true);
		scene2.AddModel(rock, true);


		//placement generation
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = (rand() % 20) / 100.0f + 0.05;

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = (rand() % 360);

		CU::Matrix33f ori = CU::Matrix33f::Identity();
		ori.SetRotationX(rotAngle * 0.4);
		ori.SetRotationY(rotAngle * 0.6);
		ori.SetRotationZ(rotAngle * 0.8);
		CU::Vector3f pos{ x, y, z };
		rock->SetOrientation(ori);
		rock->SetPosition(pos);
		rock->SetScale(scale);
	}


	engine.GetCamera().SetProjection(45, info.m_resolution.width / info.m_resolution.height, 0.1, 1000);
	engine.GetCamera().UpdateShaders();

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	bool renderNormals = false;

	InputController inputController;

	int index = 0;
	std::vector < std::string > ppEffects = {
		"pp_grayscale",
		"pp_edges",
		"pp_invert",
		"pp_sharpen",
		"pp_blur",
		"pp_simple"

	};

	//main loop
	int sceneIndex = 0;
	while (engine.Update(deltaTime)) {

		if (engine.GetInput().GetKeyPressed(GLEN::KEY_ESC)) {
			break;
		}

		if (engine.GetInput().GetKeyPressed(GLFW_KEY_V))
		{
			index++;
			if (index >= ppEffects.size()) {
				index = 0;
			}
			scene.GetPostProcess().SetShader(ppEffects[index]);
		}
		if (engine.GetInput().GetKeyPressed(GLFW_KEY_B))
		{
			index--;
			if (index < 0) {
				index = ppEffects.size() - 1;
			}
			scene.GetPostProcess().SetShader(ppEffects[index]);
		}

		if (engine.GetInput().GetKeyPressed(GLFW_KEY_R))
		{
			renderNormals = !renderNormals;
			scene.RenderNormals(renderNormals);
		}

		if (engine.GetInput().GetKeyPressed(GLFW_KEY_Y))
		{
			if (sceneIndex == 0)
			{
				sceneIndex = 1;
			}
			else {
				sceneIndex = 0;
			}
			engine.GetSceneContainer().SetCurrentScene(sceneIndex);
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
		ErrorHandler::CheckError("mainloop 1");

		//move the cube:
		float radius = 5.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		auto pos = CU::Vector3f(camX, 0, camZ);
		cubes[0]->SetPosition(pos);
		for (auto cube : cubes)
		{
			auto pos = cube->GetPosition();
		}
	
	}

	engine.Destroy();

	return 0;
}