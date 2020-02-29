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


class city
{
public:
	int city_id;
	int flag_color;
	int health_collect;
	int last_win;
	int now_win;
	warrior * soldier[2];
	city(){}
	~city()
	{
		if (soldier[0])
		{
			delete soldier[0];
		}
		if (soldier[1])
		{
			delete soldier[1];
		}
	}
	//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
	void health_add(void)
	{
		health_collect += 10;
		return;
	}
	int get_winner_color(void)
	{
		return now_win;
	}
	void creat_city(int _city_id)
	{
		city_id = _city_id;
		health_collect = 0;
		soldier[0] = NULL;
		soldier[1] = NULL;
		flag_color = -1;
		last_win = -1;
		now_win = -1;
		return;
	}
	void health_take(void)
	{
		int first_attack = -1;
		if (soldier[0] != NULL && soldier[1] == NULL)
		{
			first_attack = 0;
		}
		if (soldier[1] != NULL && soldier[0] == NULL)
		{
			first_attack = 1;
		}
		if (first_attack != -1)
		{
			printf("%03d:30 %s %s %d earned %d elements for his headquarter\n",
				present_hour, color_name[first_attack], warrior_name[soldier[first_attack]->type],
				soldier[first_attack]->id, health_collect);
			total[first_attack] += health_collect;
			//
			//cout << "**********从health_collect到total: health_collect = " << health_collect << "武士" << warrior_name[soldier[first_attack]->type] << " 在城市" << city_id << " " << color_name[first_attack] << " total= " << total[first_attack] << endl;
			//
			health_collect = 0;
		}
	}
	int add_sword_attack(int _color)
	{
		int return_attack = 0;
		if (soldier[_color]->mysword)
		{
			return_attack += soldier[_color]->mysword->get_force();
			soldier[_color]->mysword->use();
			if (soldier[_color]->mysword->sword_abandon_judge())
			{
				delete soldier[_color]->mysword;
				soldier[_color]->mysword = NULL;
			}
		}
		return return_attack;
	}
	void tie(int _first_attack)
	{
		soldier[0]->loyalty_minus();
		soldier[1]->loyalty_minus();
		soldier[_first_attack]->morale_minus();
		soldier[_first_attack]->cheer(city_id);
		last_win = -1;
		return;
	}
	void win(int _color, int is_first_attack, int _transfer_health)
	{
		if (soldier[_color]->type == 4)
		{
			if (soldier[_color]->mysword == NULL && soldier[1 - _color]->mysword)
			{
				soldier[_color]->mysword = new sword(soldier[1 - _color]->mysword->get_force());
				delete soldier[1 - _color]->mysword;
				soldier[1 - _color]->mysword = NULL;
			}
			if (soldier[_color]->myarrow == NULL && soldier[1 - _color]->myarrow)
			{
				soldier[_color]->myarrow = new arrow(soldier[1 - _color]->myarrow->get_time_left(), soldier[1 - _color]->myarrow->get_force());
				delete soldier[1 - _color]->mysword;
				soldier[1 - _color]->mysword = NULL;
			}
			if (!soldier[_color]->bomb_judge() && soldier[1 - _color]->bomb_judge())
			{
				soldier[_color]->bomb = true;
				soldier[1 - _color]->bomb = false;
			}
		}
		
		
		delete soldier[1 - _color];
		soldier[1 - _color] = NULL;
		
		if (is_first_attack == 1)
		{
			soldier[_color]->morale_plus();
			soldier[_color]->cheer(city_id);
		}
		soldier[_color]->health += _transfer_health;
		printf("%03d:40 %s %s %d earned %d elements for his headquarter\n",
			present_hour, color_name[_color], warrior_name[soldier[_color]->type],
			soldier[_color]->id, health_collect);
		//下面暂时寄存准备回收到大本营的生命元
		health_return[_color] += health_collect;
		//
		//cout << "**********从health_collect到health_return:health_collect = " << health_collect  << " " << color_name[_color] << "武士" << warrior_name[soldier[_color]->type] << " " << soldier[_color]->id << " 在城市" << city_id << endl;
		//
		health_collect = 0;
		now_win = _color;
		if (flag_color != _color && last_win == _color)
		{
			flag_color = _color;
			printf("%03d:40 %s flag raised in city %d\n", present_hour, color_name[_color], city_id);
		}
		last_win = _color;
		return;
	}
	void fight(void)
	{
		int first_attack;
		int sword_attack = 0;
		int transfer_health = 0;
		now_win = -1;////
		if (soldier[0] == NULL && soldier[1] == NULL)
		{
			return;
		}
		if (soldier[1] == NULL && soldier[0] != NULL)
		{
			if (soldier[0]->health <= 0)
			{
				delete soldier[0];
				soldier[0] = NULL;
			}
			return;
		}
		if (soldier[0] == NULL && soldier[1] != NULL)
		{
			if (soldier[1]->health <= 0)
			{
				delete soldier[1];
				soldier[1] = NULL;
			}
			return;
		}
		if (soldier[0] != NULL && soldier[1] != NULL)
		{
			if (soldier[0]->health <= 0 && soldier[1]->health <= 0)
			{
				delete soldier[0];
				soldier[0] = NULL;
				delete soldier[1];
				soldier[1] = NULL;
				return;
			}
		}
		if (flag_color == 0 ||flag_color == -1 && city_id % 2 == 1)
		{
			first_attack = 0;
		}
		else
		{
			first_attack = 1;
		}
		if (soldier[first_attack]->health <= 0)
		{
			win(1 - first_attack, 0, 0);
			return;
		}
		if (soldier[1 - first_attack]->health <= 0)
		{
			win(first_attack, 1, 0);
			return;
		}
		printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
			present_hour, color_name[first_attack], warrior_name[soldier[first_attack]->type],
			soldier[first_attack]->id, color_name[1 - first_attack], warrior_name[soldier[1 - first_attack]->type],
			soldier[1 - first_attack]->id, city_id, soldier[first_attack]->health, soldier[first_attack]->attack);
		//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		if (soldier[1 - first_attack]->type == 3)
		{
			//暂存下可能战死的后攻击lion的生命元数量
			transfer_health += soldier[1 - first_attack]->health;
		}
		else transfer_health = 0;
		//主动进攻事件开始
		sword_attack = add_sword_attack(first_attack);
		soldier[1 - first_attack]->health -= (sword_attack + soldier[first_attack]->attack);
		if (soldier[1 - first_attack]->health <= 0)
		{
			printf("%03d:40 %s %s %d was killed in city %d\n",
				present_hour, color_name[soldier[1 - first_attack]->color],
				warrior_name[soldier[1 - first_attack]->type], soldier[1 - first_attack]->id, city_id);
			win(first_attack, 1, transfer_health);
			return;
		}
		//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		if (soldier[1 - first_attack]->type != 1)
		{
			printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
				present_hour, color_name[soldier[1 - first_attack]->color],
				warrior_name[soldier[1 - first_attack]->type], soldier[1 - first_attack]->id,
				color_name[first_attack], warrior_name[soldier[first_attack]->type], soldier[first_attack]->id,
				city_id);
			if (soldier[first_attack]->type == 3)
			{
				transfer_health = 0;
				//暂存下可能战死的先攻击lion的生命元数量
				transfer_health += soldier[first_attack]->health;
			}
			else transfer_health = 0;
			//反击事件开始
			sword_attack = add_sword_attack(1 - first_attack);
			soldier[first_attack]->health -= (sword_attack + int((soldier[1 - first_attack]->attack) / 2));
			if (soldier[first_attack]->health <= 0)
			{
				printf("%03d:40 %s %s %d was killed in city %d\n",
					present_hour, color_name[soldier[first_attack]->color],
					warrior_name[soldier[first_attack]->type], soldier[first_attack]->id, city_id);
				win(1 - first_attack, 0, transfer_health);
				return;
			}
		}
		tie(first_attack);
		return;
	}
	void go_next_city(city * from_city, int _color)
	{
		soldier[_color] = from_city->soldier[_color];
		//抵达下一个城市时判断雪人
		if (soldier[_color] != NULL)
		{
			if (soldier[_color]->type == 2)
			{
				if (_color == 0 && city_id % 2 == 0 || _color == 1 && (city_number + 1 - city_id) % 2 == 0)
				{
					soldier[_color]->health -= 9;
					if (soldier[_color]->health <= 0)
					{
						soldier[_color]->health = 1;
					}
					soldier[_color]->attack += 20;
				}
			}
		}
		return;
	}
	void lion_escape(int _color)
	{
		if (soldier[_color])
		{
			if (soldier[_color]->type == 3 && soldier[_color]->escape_judge())
			{
				printf("%03d:05 %s lion %d ran away\n", present_hour, color_name[_color], soldier[_color]->id);
				delete soldier[_color];
				soldier[_color] = NULL;
			}
		}
		return;
	}
	void print_reach(void)
	{
		if (soldier[0] != NULL)
		{
			printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
				present_hour, color_name[0], warrior_name[soldier[0]->type], soldier[0]->id, city_id,
				soldier[0]->health, soldier[0]->attack);
		}
		if (soldier[1] != NULL)
		{
			printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
				present_hour, color_name[1], warrior_name[soldier[1]->type], soldier[1]->id, city_id,
				soldier[1]->health, soldier[1]->attack);
		}
		return;
	}
	void print_weapon(int _color)
	{
		bool _bo = false;
		if (soldier[_color] == NULL)
		{
			return;
		}
		printf("%03d:55 %s %s %d has ", present_hour, color_name[_color], warrior_name[soldier[_color]->type],
			soldier[_color]->id);
		if (soldier[_color]->myarrow)
		{
			printf("arrow(%d)", soldier[_color]->myarrow->get_time_left());
			_bo = true;
		}
		if (soldier[_color]->bomb_judge())
		{
			if (_bo)
			{
				printf(",");
			}
			printf("bomb");
			_bo = true;
		}
		if (soldier[_color]->mysword)
		{
			if (_bo)
			{
				printf(",");
			}
			printf("sword(%d)", soldier[_color]->mysword->get_force());
			_bo = true;
		}
		if (!_bo)
		{
			printf("no weapon");
		}
		printf("\n");
		return;
	}
	bool reach_head(int _color)
	{
		if (!last_color[_color] || soldier[_color] == NULL)////
		{
			return false;
		}
		
		printf("%03d:10 %s %s %d reached %s headquarter with %d elements and force %d\n",
			present_hour, color_name[_color], warrior_name[soldier[_color]->type], soldier[_color]->id,
			color_name[1 - _color], soldier[_color]->health, soldier[_color]->attack);
			
		if (number_in_head[1 - _color] == 1)
		{
			return true;
		}
		number_in_head[1 - _color] = 1;
		return false;
	}
	void use_arrow(city * next_city, int _color)
	{
		if (soldier[_color] == NULL || next_city->soldier[1 - _color] == NULL)
		{
			return;
		}
		if (soldier[_color]->myarrow)
		{
			printf("%03d:35 %s %s %d shot", present_hour, color_name[_color], warrior_name[soldier[_color]->type],
				soldier[_color]->id);
			next_city->soldier[1 - _color]->health -= soldier[_color]->myarrow->get_force();
			soldier[_color]->myarrow->use();
			if (soldier[_color]->myarrow->arrow_abandon_judge())
			{
				delete soldier[_color]->myarrow;
				soldier[_color]->myarrow = NULL;
			}
			if (next_city->soldier[1 - _color]->health <= 0)
			{
				next_city->soldier[1 - _color]->health = 0;
				printf(" and killed %s %s %d",
					color_name[1 - _color], warrior_name[next_city->soldier[1 - _color]->type],
					next_city->soldier[1 - _color]->id);
				/*
				delete next_city->soldier[1 - _color];
				next_city->soldier[1 - _color] = NULL;
				*/
			}
			printf("\n");
		}
		return;
	}
	void use_bomb(void)
	{
		if (soldier[0] == NULL || soldier[0]->health <= 0 || soldier[1] == NULL || soldier[1]->health <= 0)
		{
			return;
		}
		int first_attack;
		if (flag_color == 0 || flag_color == -1 && city_id % 2 == 1)
		{
			first_attack = 0;
		}
		else if (flag_color == 1 || flag_color == -1 && city_id % 2 == 0)
		{
			first_attack = 1;
		}
		int first_attack_power;
		int second_attack_power;
		if (soldier[first_attack]->mysword)
		{
			first_attack_power = soldier[first_attack]->attack + soldier[first_attack]->mysword->get_force();
		}
		else
		{
			first_attack_power = soldier[first_attack]->attack;
		}
		if (soldier[1 - first_attack]->mysword)
		{
			second_attack_power = int(soldier[1 - first_attack]->attack / 2) + soldier[1 - first_attack]->mysword->get_force();
		}
		else
		{
			second_attack_power = int(soldier[1 - first_attack]->attack / 2);
		}
		if (first_attack_power >= soldier[1 - first_attack]->health)
		{
			if (soldier[1 - first_attack]->bomb_judge())
			{
				printf("%03d:38 %s %s %d used a bomb and killed %s %s %d\n", present_hour,
					color_name[1 - first_attack], warrior_name[soldier[1 - first_attack]->type],
					soldier[1 - first_attack]->id, color_name[first_attack], warrior_name[soldier[first_attack]->type],
					soldier[first_attack]->id);
				delete soldier[first_attack];
				soldier[first_attack] = NULL;
				delete soldier[1 - first_attack];
				soldier[1 - first_attack] = NULL;
				return;
			}
			else return;
		}
		//dragon-0，ninja-1，iceman-2，lion-3，wolf-4
		if (soldier[1 - first_attack]->type != 1)
		{
			if (second_attack_power >= soldier[first_attack]->health)
			{
				if (soldier[first_attack]->bomb_judge())
				{
					printf("%03d:38 %s %s %d used a bomb and killed %s %s %d\n", present_hour,
						color_name[first_attack], warrior_name[soldier[first_attack]->type],
						soldier[first_attack]->id, color_name[1 - first_attack], warrior_name[soldier[1 - first_attack]->type],
						soldier[1 - first_attack]->id);
					delete soldier[first_attack];
					soldier[first_attack] = NULL;
					delete soldier[1 - first_attack];
					soldier[1 - first_attack] = NULL;
					return;
				}
				return;
			}
			return;
		}
		return;
	}
}mycity[22];
