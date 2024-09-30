#include "knothpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Knoth {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case Knoth::ShaderDataType::None:	return GL_FLOAT;
			case Knoth::ShaderDataType::Float:	return GL_FLOAT;
			case Knoth::ShaderDataType::Float2:	return GL_FLOAT;
			case Knoth::ShaderDataType::Float3:	return GL_FLOAT;
			case Knoth::ShaderDataType::Float4:	return GL_FLOAT;
			case Knoth::ShaderDataType::Mat3:	return GL_FLOAT;
			case Knoth::ShaderDataType::Mat4:	return GL_FLOAT;
			case Knoth::ShaderDataType::Int:	return GL_INT;
			case Knoth::ShaderDataType::Int2:	return GL_INT;
			case Knoth::ShaderDataType::Int3:	return GL_INT;
			case Knoth::ShaderDataType::Int4:	return GL_INT;
			case Knoth::ShaderDataType::Bool:	return GL_BOOL;
		}
		KNOTH_ASSERT(false, "Unknown Shader Data Type Size");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray(){
		glCreateVertexArrays(1, &_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray(){
		glDeleteVertexArrays(1, &_RendererID);
	}

	void OpenGLVertexArray::Bind() const{
		glBindVertexArray(_RendererID);
	}

	void OpenGLVertexArray::Unbind() const{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer){
		glBindVertexArray(_RendererID);
		vertexBuffer->Bind();
		KNOTH_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer){
		glBindVertexArray(_RendererID);
		indexBuffer->Bind();
		_IndexBuffer = indexBuffer;
	}
}