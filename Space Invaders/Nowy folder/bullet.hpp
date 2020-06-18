#pragma once
#include "object.hpp"

namespace gsi
{
	struct CBullet
		: public IObject
	{
		using IObject::IObject;

		virtual ~CBullet() = default;

		virtual int getType() const override;
		virtual void moveOverTime(float) override;
	};
}