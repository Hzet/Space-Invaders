#pragma once 
#include "game-object.hpp"

namespace gsi
{
#define CLASS_EQUALITY(l, r) CObjectFactory::ClassEquality(l, #r);
#define MAKE_PRODUCT(T) CObjectFactory::MakeProduct<T>()
#define REGISTER_PRODUCT(T) { T *ptr = new T(); if(static_cast<IGameObject*>(ptr) != NULL) CObjectFactory::RegisterProduct(ptr); delete ptr; ptr = NULL; }

	class CObjectFactory
	{
	public:
		static bool ClassEquality(IGameObject const *const l, const char *r)
		{
			return typeid(*l).name() == r;
		}

		template<typename T>
		static IGameObject* MakeProduct()
		{
			auto found = Types.find(typeid(T).name());
			if (found == Types.end())
				return NULL;
			return found->second->clone();
		}

		static void RegisterProduct(IGameObject*);

		static std::map<const char*, IGameObject*> Types;
	private:
	};
}