#pragma once
#include <vector>
#include "CU_Vector.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
namespace GLEN
{


	/*GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
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

	struct VertexLayout {
		VertexLayout() {};

		int locationAtrribute = 0; //set in shader
		int colorAtribute = 1; //set in shader
		int texCoordAttribute = 2; //set in shader
		int stride = 8;
		int texCoordOffset = 6;
		int colorOffset = 3;
		int vertexOffset = 0;
		bool hasColor = true;
		bool hasTexCoords = true;
	};



	class Primitive
	{
	public:
		Primitive();
		~Primitive();
		void Render(CU::Matrix44f view, CU::Matrix44f projection);
		void AddVertice(const CU::Vector3f& vertice);
		void SetVerticeData(float data[], int size);
		void SetVerticeData(float data[], int size, const VertexLayout& vertexLayout);
		void SetIndexData(unsigned int data[], int size);
		void AddTriangleIndexes(const CU::Vector3i indexes);
		void Finalize(DrawFrequency frequency);
		void SetShaderProgram(const ShaderProgram& program); //todo: put shaders in a pool, and set only id of shader to run for each primitive, and make it optional, if we don't need special shaders.
		void setPolygonMode(PolygonMode mode) { m_polygonMode = mode; }
		void addTexture(int aTextureHandle) { m_textureHandles.push_back(aTextureHandle); }

		//todo: create base class for this:
		void setPosition(CU::Vector3f aPosition) { m_position = aPosition; }
		CU::Vector3f m_position;
	private:
		

		std::vector<float> m_vertices;
		std::vector<int> m_indexes;
		unsigned int m_vertexBufferObjectHandle;
		unsigned int m_vertexArrayObjectHandle;
		unsigned int m_elementBufferObject;
		ShaderProgram m_shaderProgram;
		unsigned int m_polygonMode;
		VertexLayout m_vertexLayout;
		std::vector<unsigned int> m_textureHandles;
	};
}

