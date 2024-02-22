class Fire : public Entity
{
public:
	const int startTimeToLive = 150;

	Fire();
	~Fire();

	int getTTL() const 
	{
		return ttl->getTTL();
	}

	std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocity; }
	virtual std::shared_ptr<TTLComponent> getTTLComponent() override { return ttl; }

private:
	std::shared_ptr<TTLComponent> ttl;
	std::shared_ptr<VelocityComponent> velocity;
	bool inUse = false;

};

