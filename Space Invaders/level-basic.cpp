#include "level-basic.hpp"

namespace gsi
{
	IBasicLevel::~IBasicLevel()
	{
		for (auto &v : levelObjects_)
		{
			delete v;
			v = NULL;
		}
	}

	void IBasicLevel::scaleLevel(float x, float y)
	{
		for (auto &v : levelObjects_)
			v->scale({ x, y });
	}

	void IBasicLevel::setPlayerSpacecraft(const CSpacecraft &spacecraft)
	{
		spacecraft_ = spacecraft;
	}

	const CSpacecraft& IBasicLevel::getPlayerSpacecraft() const
	{
		return spacecraft_;
	}

	void IBasicLevel::drawElements(sf::RenderWindow &window) const
	{
		window.draw(spacecraft_);
		for (const auto &v : levelObjects_)
			window.draw(*v);
	}
}