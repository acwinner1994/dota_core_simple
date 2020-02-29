#include <iostream>
#include <stdio.h>

using namespace std;
int number_color[2] = {};//各魔军已生成武士数量，0为红，1为蓝
int present_hour = 0;
int present_minute = 0;
int total[2] = {};
int warrior_health[5] = {};//依次为dragon-0，ninja-1，iceman-2，lion-3，wolf-4初始生命值
int warrior_attack[5] = {};//依次为dragon-0，ninja-1，iceman-2，lion-3，wolf-4初始攻击力
char warrior_name[5][10] = { "dragon","ninja","iceman","lion","wolf" };
char weapon_name[3][10] = { "sword","bomb","arrow" };
char color_name[2][10] = { "red","blue" };
int order[2][5] = { { 2,3,4,1,0 },{ 3,0,1,2,4 } };//两军生成武士顺序
int _total;
int city_number;
int arrow_attack;
int loyalty_down;
int total_minute;
int health_return[2] = {};
int number_in_head[2] = {};
bool last_color[2];
int order_now[2] = {};
bool end_of_warcraft = false;

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
