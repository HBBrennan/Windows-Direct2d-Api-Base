#pragma once
#include "Minion.h"

class Unit :
	public Minion
{
	bool selected = false;

	//Basic Stats
	float attack;
	float attackTimer;
	float attackSpeed;
	float attackSpeedModifier;
	float armor;
	float maxHealth;
	float currentHealth;
	float movementSpeed;
	float movementSpeedModifier;
	float radius;
	float shields;
	float maxShields;
	float maxEnergy;
	float energy;
	float attackRange;
	float projectileSpeed;
	float splashRadius;
	int supplyCount;
	int cargo;

	bool melee;

	//Movement/Commands
	float stopRadius = 5.0f;

	Unit* target = nullptr;

	bool moving = true;
	float moveX = 1000;
	float moveY = 1000;

public:

	//Armor Types
	static const int ARMOR_NONE = 0;
	static const int ARMOR_LIGHT = 1;
	static const int ARMOR_HEAVY = 2;

	//Unit Types
	static const int TYPE_NONE = 0;
	static const int TYPE_BIOLOGICAL = 1;
	static const int TYPE_MECHANICAL = 2;

	Unit(float x, float y, float attack, float attackSpeed, float armor, float maxHealth, float movementSpeed, float radius, float maxShields, float maxEnergy, float attackRange, float projectileSpeed, float splashRadius, int supplyCount, int cargo, bool melee, wchar_t* fileName) : Minion(x, y, true, fileName)
	{
		this->attack = attack;
		this->attackSpeed = attackSpeed;
		this->armor = armor;
		this->maxHealth = maxHealth;
		this->movementSpeed = movementSpeed;
		this->radius = radius;
		this->maxShields = maxShields;
		this->maxEnergy = maxEnergy;
		this->attackRange = attackRange;
		this->projectileSpeed = projectileSpeed;
		this->supplyCount = supplyCount;
		this->cargo = cargo;
		this->melee = melee;
		this->splashRadius = splashRadius;

		attackSpeedModifier = 1.0f;
		movementSpeedModifier = 1.0f;
		currentHealth = maxHealth;
		shields = maxShields;
		energy = 0;
		posX = x;
		posY = y;
	}

	virtual int getArmorType() = 0;
	virtual int getUnitType() = 0;
	virtual bool isAirUnit() = 0;

	float getAttack() const { return attack; }
	float getAttackSpeed() const { return attackSpeed; }
	float getArmor() const { return armor; }
	float getMaxHealth() const { return maxHealth; }
	float getCurrentHealth() const { return currentHealth; }
	float getMovementSpeed() const { return movementSpeed; }
	float getRadius() const { return radius; }
	float getMaxShields() const { return maxShields; }
	float getShields() const { return shields; }
	float getMaxEnergy() const { return maxEnergy; }
	float getEnergy() const { return energy; }
	float getAttackRange() const { return attackRange; }
	float getProjectileSpeed() const { return projectileSpeed; }
	float getSplashRadius() const { return splashRadius; }

	int getSupplyCount() const { return supplyCount; }
	int getCargo() const { return cargo; }
	
	bool isMelee() const { return melee; }

	bool isSelected() const { return selected; }

	void select() { selected = true; }

	void deselect() { selected = false; }

	//Fix when team system set up
	bool getAlly() { return false; }


	void setMoveLocation(float moveX, float moveY);

	void virtual Update(float deltaTime, KeyboardListener* kbd, MinionList* minions);
	void move(float deltaTime, float distance);

	~Unit();
};
