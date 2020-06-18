#pragma once
#include "spacecraft-hostile.hpp"

namespace gsi
{
	std::vector<gsi::CHostileSpacecraft> generateWave(int wave, CHostileSpacecraft spacecraftTemplate, int screenWidth)
	{
		std::vector<gsi::CHostileSpacecraft> result;
		for (int i = 0; i < wave / (i + 1); i++)
		{
			float posY = i * (spacecraftTemplate.getGlobalBounds().height + 75.f) * -1;
			for (int j = 0; j < screenWidth / (spacecraftTemplate.getLocalBounds().width + spacecraftTemplate.getSwitchDistance() * 2); j++)
			{
				float posX = (j * 75 + j * (int)std::ceil(spacecraftTemplate.getGlobalBounds().width)) + spacecraftTemplate.getSwitchDistance();
				spacecraftTemplate.setPosition(posX, posY);
				result.push_back(spacecraftTemplate);
			}
		}
		return result;
	}

	bool isColliding(const gsi::IObject &a, const gsi::IObject &b) // true if 2 objects intersect
	{
		return a.getGlobalBounds().intersects(b.getGlobalBounds());
	}

	template<class T> 
	int isColliding(const IObject &obj, std::vector<T> &vec)
	{
		int result = 0;
		for(int i = vec.size() - 1; i >= 0; i--)
			if (isColliding(obj, vec[i]))
			{
				vec.erase(vec.begin() + i);
				result++;
			}
		return result;
	}

	bool timer(float dTime, float waitTime)
	{
		static float totalTimePassed = 0.f;
		totalTimePassed += dTime;
		if (totalTimePassed >= waitTime)
		{
			totalTimePassed = 0.f;
			return true;
		}
		return false;
	}
}