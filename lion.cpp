#include <iostream>
#include <stdio.h>

using namespace std;


class lion :public warrior//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
{
public:
	int loyalty;
	lion(int _color, int _id, int _type) :warrior(_color, _id, _type)
	{
		loyalty = total[_color];
		printf("Its loyalty is %d\n", loyalty);
	}
	virtual bool escape_judge(void)
	{
		return (loyalty <= 0);
	}
	void loyalty_minus(void)
	{
		loyalty -= loyalty_down;
		return;
	}
};
