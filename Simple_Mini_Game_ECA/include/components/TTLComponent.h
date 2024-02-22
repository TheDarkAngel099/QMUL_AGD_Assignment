#include "Components.h"
class TTLComponent : public Component
{
private:
	int ttl;

public:
	TTLComponent(int timeToLive) : ttl(timeToLive) {}

	void decreaseTTL() { --ttl; }

	int getTTL()
	{
		return ttl;
	}

	ComponentID getID() const override{ return ComponentID::TTL; }
};