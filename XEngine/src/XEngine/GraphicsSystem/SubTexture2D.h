#pragma once
#include "Texture.h"
#include <glm/glm.hpp>
namespace XEngine
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		const Ref<Texture2D> GetTexture() const
			{ return subTexture; }
		const glm::vec2* GetTexCoords() const
			{ return subTextureCoords; }
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2 coords, const glm::vec2& cellSize, const glm::vec2 spriteSize = { 1, 1 });
	private:
		Ref<Texture2D> subTexture;
		glm::vec2 subTextureCoords[4];
	};
}