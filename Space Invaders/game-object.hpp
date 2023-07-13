#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

namespace gsi
{
	class IGameObject
		: public sf::Sprite
	{
	public:
		static void saveTexture(const char*, sf::Texture);
		static const sf::Texture& loadTexture(const char*);

		using sf::Sprite::Sprite;

		virtual ~IGameObject() = default;


		virtual IGameObject* clone() const = 0;
		virtual int getType() const = 0;
		virtual const char* getTypeName() const
		{
			return typeid(*this).name();
		}
	private:
		static std::map<const char*, sf::Texture> Textures;
	};
}