#include "Engine.h"
#include "enums.h"
#include "Input.h"
#include "Scene.h"
#include "Primitive.h"
#include "ShaderProgram.h"
#include "Texture.h"

int main()
{
	GLEN::SetupInfo info;
	
	GLEN::Engine* engine = GLEN::Engine::Create(info); 

	//triangle test
	GLEN::Scene scene;
	
	GLEN::Primitive primitive;

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	float texCoords[] = {
	0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};

	primitive.SetVerticeData(vertices, sizeof(vertices)/sizeof(float));

	GLEN::Texture texture;
	texture.LoadTexture("container.jpg");
	primitive.setTexture(texture.getHandle());

	primitive.Finalize(GLEN::STATIC_DRAW);
	scene.AddPrimitive(&primitive);


	//todo: make pool of shaders and shader programs and keep in container in engine.
	GLEN::ShaderProgram shaderProgram("shader.vert", "shader.frag");
	primitive.SetShaderProgram(shaderProgram);


	while (engine->Update()) {
		//main loop
		if (engine->GetInput().GetKeyPressed(GLEN::KEY_ESC)) {
			break;
		}

		shaderProgram.setFloat("hOffset", glfwGetTime());

		engine->RenderScene();
		scene.Render();
		
	}

	engine->Destroy();

	return 0;
}