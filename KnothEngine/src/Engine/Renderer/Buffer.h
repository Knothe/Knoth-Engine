#pragma once
#include "Engine/Core.h"

namespace Knoth {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		}

		KNOTH_ASSERT(false, "Unknown Shader Data Type Size");
		return 0;
	}

	struct KNOTH_API BufferElement {
		std::string Name;
		ShaderDataType Type;
		bool Normalized;
		uint32_t Size;
		uint32_t Offset;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0) {}

		uint32_t GetComponentCount() const {
			switch (Type) {
				case ShaderDataType::Float:  return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3:   return 3 * 3;
				case ShaderDataType::Mat4:   return 4 * 4;
				case ShaderDataType::Int:    return 1;
				case ShaderDataType::Int2:   return 2;
				case ShaderDataType::Int3:   return 3;
				case ShaderDataType::Int4:   return 4;
				case ShaderDataType::Bool:   return 1;
			}
			KNOTH_ASSERT(false, "Unknown Shader Data Type Size");
			return 0;
		}
	};

	class KNOTH_API BufferLayout {
	public:
		BufferLayout(){}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: _Elements(elements) {
			CalculateOffsetsAndStride();
		}

		inline const uint32_t GetStride() const { return _Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return _Elements; }
	
		std::vector<BufferElement>::iterator begin() { return _Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return _Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _Elements.end(); }

	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			_Stride = 0;
			for (auto& element : _Elements) {
				element.Offset = offset;
				offset += element.Size;
				_Stride += element.Size;
			}
		}

		std::vector<BufferElement> _Elements;
		uint32_t _Stride = 0;
	};

	class KNOTH_API VertexBuffer {
	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float * vertices, uint32_t size);
	};

	class KNOTH_API IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}