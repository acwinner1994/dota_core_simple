#include <iostream>
#include <stdio.h>

using namespace std;

class dragon :public warrior//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
{
public:
	double morale;
	dragon(int _color, int _id, int _type) :warrior(_color, _id, _type)
	{
		morale = double(total[_color]) / double(warrior_health[0]);
		printf("Its morale is %.2lf\n", morale);
	}
	void cheer(int city_number)
	{
		if (morale > 0.8)
		{
			printf("%03d:40 %s %s %d yelled in city %d\n", present_hour, color_name[color],
				warrior_name[type], id, city_number);
		}
		return;
	}
	void morale_plus(void)
	{
		morale += 0.2;
		return;
	}
	void morale_minus(void)
	{
		morale -= 0.2;
		return;
	}
};
