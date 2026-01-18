#pragma once
class Character
{
private:
	double maxHealth;
	double tempHealth;
	double strength;
	double mana;

public:
	/**
	* Deals damage to a character
	*
	* @param character The character that this character is attacking.
	*/
	virtual void attack(Character& character);


	/**
	Heals the user, using up a source of mana.
	* 
	*/
	virtual void heal();


	/**
	* Deals damage to itself. Used for regulating on hit functions;
	* 
	* @param damage The amount of damage that is done. 
	*/
	virtual void damageDealt(double damage);

	/**
	* @return the strength of the character in a double format
	*/
	double getStrength();

	/**
	* sets the stregnth of the Character
	* 
	* @param dmg the amount the stregnth is being set to.
	*/
	void setStrength(double dmg);


	/**
	* @return current health in the form of a decimal
	*/
	double getTempHealth();
	

	/**
	* sets the current health of the character
	* 
	* @param hitPoints amount of hit points the character will be set to
	*/
	void setTempHealth(double hitPoints);


	/**
	* @return max health in the form of a decimal
	*/
	double getMaxHealth();


	/**
	* sets the max health of the character
	*
	* @param hitPoints amount of hit points the character will be set to
	*/
	void setMaxHealth(double hitPoints);


	/**
	* @return mana in the form of a decimal
	*/
	double getMana();


	/**
	* sets the mana of the character
	*
	* @param mana amount of mana the character will be set to
	*/
	void setMana(double mana);

	Character(double health, double strength, double mana) :
		maxHealth{ health },
		tempHealth{ health },
		strength{ strength },
		mana{ mana } { }
};

