// Copyright 2019 the donut authors. See AUTHORS.md

#pragma once

#include <memory>

namespace Donut
{
	namespace GL
	{
		class ShaderProgram;
		class VertexBuffer;
		class IndexBuffer;
		class VertexBinding;
	}

	namespace P3D
	{
		class BillboardQuadGroup;
	}

	class Shader;

	class BillboardBatch
	{
	public:

		BillboardBatch(const P3D::BillboardQuadGroup& billboardQuadGroup);

		void Draw(GL::ShaderProgram& shader, bool opaque);

	private:

		std::shared_ptr<GL::VertexBuffer> _vertexBuffer;
		std::shared_ptr<GL::IndexBuffer> _indexBuffer;
		std::shared_ptr<GL::VertexBuffer> _instanceBuffer;
		std::shared_ptr<GL::VertexBinding> _vertexBinding;

		uint32_t _numQuads;

		std::shared_ptr<Shader> _shader;
		bool _zTest;
		bool _zWrite;
	};
}