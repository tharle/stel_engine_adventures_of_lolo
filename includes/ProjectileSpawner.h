#pragma once
#include "Projectil.h"
#include <map>

typedef std::map<std::string, Projectil*> TProtoMap;
class Spawner
{
public:
	~Spawner() = default;
	void AddPrototype(const std::string& name, Projectil* proto)
	{
		m_Prototypes[name] = proto;
	}

	Projectil* Spawn(const std::string& name)
	{
		if (m_Prototypes.count(name) > 0)
		{
			return m_Prototypes[name]->Clone();
		}
		return nullptr;
	}
private:
	TProtoMap m_Prototypes;
};
