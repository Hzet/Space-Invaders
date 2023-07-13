#include "game-object.hpp"

namespace gsi
{
	std::map<const char*, sf::Texture> IGameObject::Textures = std::map<const char*, sf::Texture>();

	void IGameObject::saveTexture(const char *filename, sf::Texture texture)
	{
		auto found = Textures.find(filename);
		if (found == Textures.end())
			Textures.emplace(filename, texture);
	}

	const sf::Texture& IGameObject::loadTexture(const char *filename)
	{
		auto found = Textures.find(filename);
		if (found != Textures.end())
			return found->second;
		throw std::out_of_range("map key not found");
	}

}