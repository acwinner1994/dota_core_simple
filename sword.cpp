#include <iostream>
#include <stdio.h>

using namespace std;


class sword
{
public:
	int force;
	sword(int _force) :force(_force) {}
	void use(void)
	{
		force = int(double(force) * 0.8);
		return;
	}
	bool sword_abandon_judge(void)
	{
		return (force == 0);
	}
	int get_force(void)
	{
		return force;
	}
};
