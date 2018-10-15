#pragma once
#include <vector>
#include "CU_Vector.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Material.h"
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

	//todo: need to generalise this
	struct VertexLayout {
		VertexLayout() {};

		int locationAtrribute = 0; //set in shader
		int colorAtribute = 1; //set in shader
		int texCoordAttribute = 2; //set in shader
		int normalsAttribute = 1;
		int stride = 6;
		int texCoordOffset = 6;
		int colorOffset = 3;
		int vertexOffset = 0;
		int normalOffset = 3;
		bool hasColor = false;
		bool hasTexCoords = true;
		bool hasNormals = true;
	};



	class Primitive
	{
	public:
		Primitive();
		~Primitive();
		void Render(CU::Matrix44f view, CU::Matrix44f projection);
		void AddVertice(const CU::Vector3f& vertice);//remove
		void SetVerticeData(float data[], int size);
		void SetVerticeData(float data[], int size, const VertexLayout& vertexLayout);
		void SetIndexData(unsigned int data[], int size);
		void AddTriangleIndexes(const CU::Vector3i indexes);//remove?
		int Finalize(DrawFrequency frequency, std::string id );
		void SetPolygonMode(PolygonMode mode) { m_polygonMode = mode; }

		std::string GetId() { return m_id; }
		int GetHandle() { return m_vertexArrayObjectHandle;  } //reuse this as id (could maybe be hash of id string instead but meh.)
		void SetMaterial(const Material& material) { m_material = material; }
	private:
		std::string m_id;

		std::vector<float> m_vertices;
		std::vector<int> m_indexes;
		unsigned int m_vertexBufferObjectHandle;
		unsigned int m_vertexArrayObjectHandle;
		unsigned int m_elementBufferObject;
		ShaderProgram m_shaderProgram;
		unsigned int m_polygonMode;
		VertexLayout m_vertexLayout;
		Material m_material;
	};
}

