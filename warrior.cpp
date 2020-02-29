#include <iostream>
#include <stdio.h>

using namespace std;



class warrior
{
public:
	int type;
	int attack;
	int id;
	int color;
	int health;
	sword * mysword;
	arrow * myarrow;
	bool bomb;
	bool bomb_judge(void)
	{
		return bomb;
	}
	void get_award(void)
	{
		health += 8;
		return;
	}
	//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
	virtual void cheer(int x) {}
	virtual void morale_plus(void) {}
	virtual void morale_minus(void) {}
	virtual bool escape_judge(void)
	{
		return false;
	}
	virtual void loyalty_minus(void) {}
	warrior(int _color, int _id, int _type)
	{
		printf("%03d:00 %s %s %d born\n", present_hour, color_name[_color], warrior_name[_type], _id);
		color = _color;
		id = _id;
		type = _type;
		health = warrior_health[type];
		total[color] -= warrior_health[type];
		//
		//cout << "**********total 生成武士" << color_name[color] << " " << warrior_name[type] << " " << id << " total= " << total[color] << endl;
		//
		attack = warrior_attack[type];
		mysword = NULL;
		myarrow = NULL;
		bomb = false;
		if (type == 0)//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		{
			if (id % 3 == 0)
			{
				if (int(attack * 0.2) != 0)
				{
					mysword = new sword(int(attack * 0.2));
				}
			}
			else if (id % 3 == 1)
			{
				bomb = true;
			}
			else if (id % 3 == 2)
			{
				myarrow = new arrow(3, arrow_attack);
			}
		}
		else if (type == 2)//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		{
			if (id % 3 == 0)
			{
				if (int(attack * 0.2) != 0)
				{
					mysword = new sword(int(attack * 0.2));
				}
			}
			else if (id % 3 == 1)
			{
				bomb = true;
			}
			else if (id % 3 == 2)
			{
				myarrow = new arrow(3, arrow_attack);
			}
		}
		else if (type == 1)//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		{
			if (id % 3 == 0)
			{
				if (int(attack * 0.2) != 0)
				{
					mysword = new sword(int(attack * 0.2));
				}
				bomb = true;
			}
			else if (id % 3 == 1)
			{
				bomb = true;
				myarrow = new arrow(3, arrow_attack);
			}
			else if (id % 3 == 2)
			{
				myarrow = new arrow(3, arrow_attack);
				if (int(attack * 0.2) != 0)
				{
					mysword = new sword(int(attack * 0.2));
				}
			}
		}
	}
	~warrior()
	{
		if (mysword)
		{
			delete mysword;
		}
		if (myarrow)
		{
			delete myarrow;
		}
	}

};
