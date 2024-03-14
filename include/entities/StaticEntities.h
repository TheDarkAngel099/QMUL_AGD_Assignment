class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION), colliderComponent{ std::make_shared<ColliderComponent>() } { addComponent(colliderComponent); }
	~Potion() {}

	void init(const std::string& textureFile, float scale) override
	{
		Entity::init(textureFile, scale);
		auto size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y)};
		colliderComponent->init(*this, size);
	}

	virtual void draw(Window* window) override
	{
		Entity::draw(window);
	}

	int getHealth() const { return potionHealth; }

	std::shared_ptr <ColliderComponent> getColliderComponent() override { return colliderComponent; }

protected:
	const int potionHealth = 10;
	std::shared_ptr <ColliderComponent> colliderComponent;

};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG), colliderComponent{ std::make_shared<ColliderComponent>() } { addComponent(colliderComponent); }
	~Log() {}

	void init(const std::string& textureFile, float scale) override
	{
		Entity::init(textureFile, scale);
		auto size{ Vector2f(gc->getTextureSize().x * gc->getSpriteScale().x, gc->getTextureSize().y * gc->getSpriteScale().y) };
		colliderComponent->init(*this,size);
	}

	virtual void draw(Window* window) override 
	{
		Entity::draw(window);
	}

	int getWood() const { return woodAdded; }

	std::shared_ptr <ColliderComponent> getColliderComponent() override { return colliderComponent; }

protected:
	const int woodAdded = 15;
	std::shared_ptr <ColliderComponent> colliderComponent;

};