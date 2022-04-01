#ifndef MONSTER_H
#define MONSTER_H
#include "Object.h"

class Player;
class Monster :
	public Object
{
public:
	Monster() {};
	Monster(const Object* player);

	void update(std::vector<Object*> objects) override;
	
	int attack() const override;
	void defend(int damage) override;
	void print(std::ostream& o) const override;
private:
	int AC{ 0 };

};

#endif // !MONSTER_H