#include <iostream>
#include <stdio.h>

using namespace std;


class arrow
{
public:
	int time_left;
	int force;
	arrow(int _time_left, int _force) :time_left(_time_left), force(_force) {}
	void use(void)
	{
		time_left--;
		return;
	}
	bool arrow_abandon_judge(void)
	{
		return (time_left <= 0);
	}
	int get_force(void)
	{
		return force;
	}
	int get_time_left(void)
	{
		return time_left;
	}
};
