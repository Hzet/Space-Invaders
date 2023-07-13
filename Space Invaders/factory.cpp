#include "factory.hpp"

namespace gsi
{
	std::map<const char*, IGameObject*> CObjectFactory::Types = std::map<const char*, IGameObject*>();

	void CObjectFactory::RegisterProduct(IGameObject *obj)
	{
		if (!Types.empty())
		{
			auto found = Types.find(obj->getTypeName());
			if (found != Types.end())
				return;
		}
		Types.emplace(obj->getTypeName(), obj->clone());
	}
}