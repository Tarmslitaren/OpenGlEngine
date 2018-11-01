#pragma once
#include <vector>
#include "CU_Vector.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Material.h"
namespace GLEN
{

	/*	GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
		GL_DYNAMIC_DRAW : the data is likely to change a lot.
		GL_STREAM_DRAW : the data will change every time it is drawn.
	*/
	enum DrawFrequency
	{
		STATIC_DRAW = GL_STATIC_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		STREAM_DRAW = GL_STREAM_DRAW
	};
	enum PolygonMode
	{
		POLYGONMODE_FILL = GL_FILL,
		POLYGONMODE_LINE = GL_LINE,
		POLYGONMODE_POINT = GL_POINT
	};

	enum RenderMode
	{
		RENDERMODE_POINTS = GL_POINTS,
		RENDERMODE_LINES = GL_LINES,
		RENDERMODE_LINE_LOOP = GL_LINE_LOOP,
		RENDERMODE_LINE_STRIP = GL_LINE_STRIP,
		RENDERMODE_TRIANGLES = GL_TRIANGLES,
		RENDERMODE_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		RENDERMODE_TRIANGLE_FAN = GL_TRIANGLE_FAN,
	};

	struct VertexLayout
	{
		int stride = 6;
		int texCoordOffset = 6;
		int colorOffset = 3;
		int vertexOffset = 0;
		int normalOffset = 3;
		bool hasColor = false;
		bool hasTexCoords = true;
		bool hasNormals = true;
	};

	struct VertexContent
	{
		std::vector<int> indexes;
		std::vector<float> positions;
		std::vector<float> texCoords;
		std::vector<float> normals;
		std::vector<float> colors;

		//use this only for interleaved data
		std::vector<float> interleavedVertices;
		VertexLayout vertexLayout;
	};


	class Mesh
	{
	public:
		Mesh(std::string id, const Material& material, const VertexContent& data, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Mesh(const Material& material);
		~Mesh();

		void Render(const CU::Matrix44f& model, RenderMode rendermode = RENDERMODE_TRIANGLES); //todo: noooope not here: keep this in the instances
		void Render(const CU::Matrix44f& model, std::string overrideShader, RenderMode rendermode = RENDERMODE_TRIANGLES);
		void RenderInstanced(const std::vector<CU::Matrix44f>& models, RenderMode rendermode = RENDERMODE_TRIANGLES);
		void Render(RenderMode rendermode = RENDERMODE_TRIANGLES);
		

		void SetPolygonMode(PolygonMode mode) { m_polygonMode = mode; }

		std::string GetId() { return m_id; } //not guaranteed to be unique!
		int GetHandle() { return m_vertexArrayObjectHandle; } //reuse this as id (could maybe be hash of id string instead but meh.)
		Material& GetMaterial() { return m_material; }
	private:
		void SetVerticeData(float data[], int size);
		void SetVerticeData(float data[], int size, const VertexLayout& vertexLayout);
		void SetIndexData(unsigned int data[], int size);
		int Finalize(DrawFrequency frequency, std::string id); //todo: raii

		void RenderInternal(RenderMode rendermode);
		void InitInterleaved();
		void InitNonInterleaved();
		std::string m_id;

		//std::vector<float> m_vertices;
		//std::vector<int> m_indexes;
		unsigned int m_vertexBufferObjectHandle;
		unsigned int m_vertexArrayObjectHandle;
		unsigned int m_elementBufferObject;
		unsigned int m_polygonMode;
		Material m_material;
		VertexContent m_vertexData;
		DrawFrequency m_frequency;
	};
}

