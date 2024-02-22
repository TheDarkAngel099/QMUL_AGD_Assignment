class Fire;
class HealthComponent;
class VelocityComponent;
class InputComponent;
class PlayerStateLogic;
class Subject;

class Player : public Entity
{
public:
	const float playerSpeed = 100.0f;
	const int startingHealth = 60;
	const int maxHealth = 100;

	Player();
	~Player();
	virtual void initSpriteSheet(const std::string& spriteSheetFile) override;
	void draw(Window* window) override;

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	bool collidesWith(Entity& other) override;

	std::shared_ptr<PlayerStateLogic> getPlayerStateComponent() override { return stateComponent; }
	std::shared_ptr<HealthComponent> getHealthComponent() { return healthComponent; }
	std::shared_ptr<VelocityComponent> getVelocityComponent() override { return velocityComponent; }
	std::shared_ptr<ColliderComponent> getColliderComponent() override { return colliderComponent; }
	std::shared_ptr<InputComponent> getInputComponent() override { return inputComponent; }

	Subject& getSubjectPotion() { return subjectPotion; }
	Subject& getSubjectShout() { return subjectShout; }

	void handlePotionCollision(std::shared_ptr<Entity> other, Game&game);
	void handleLogCollision(std::shared_ptr<Entity> other, Game& game);

private:
	std::shared_ptr<Fire> createFire(Player& entity) const;

	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<InputComponent> inputComponent;
	std::shared_ptr<VelocityComponent> velocityComponent;
	std::shared_ptr<ColliderComponent> colliderComponent;
	std::shared_ptr<PlayerStateLogic> stateComponent;

	Subject subjectPotion;
	Subject subjectShout;
};

