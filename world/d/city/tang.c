//By waiwai@sjmd 2000/10/07
//���������ּ�ɱ����ֵ�ķ�ʽ
//���Ը�����Ҫ����ʵ�ʵĵ���
//����

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HBRED HIY" �� Թ �� "NOR);
        set("long", 

"\n������̴ľ�㰸������ȼ�ż����㣬������̴��������������\n"+
"���õ��ˣ���Ը��������Թһ�ʹ�����������������������\n"+
"Ϊ���������ˣ����������Ķ���ԹԹ,ֻ����������� "+HIR"(kneel) \n\n"NOR
        );

        set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"sanhua",
]));
	set("no_fight",1);
	set("no_magic",1);
	set("no_kill",1);

	setup();
}

void init()
{
	add_action("do_kneel", "kneel");
}

int do_kneel(string arg)
{
	object me;
	int pk,dx,exp,j;
	me = this_player();
	pk = (int) me->query("PKS");
	dx = (int) me->query("daoxing");
	exp = (int) me->query("combat_exp");

/*
	if(pk <= 0)
		return notify_fail(CYN"��ûɱ���˲��ù��......\n"NOR);
	if(dx <= 0)
		return notify_fail(CYN"��ĵ����Ѿ������ټ���......\n"NOR);
	if(exp <= 0)
		return notify_fail(CYN"�����ѧ�Ѿ������ټ���......\n"NOR);
 	me->set("PKS", (int) pk - 1);
 	me->set("daoxing", (int) dx - 30000);
 	me->set("combat_exp", (int) exp - 20000);
*/

      if((int)me->query("balance")<1000000) 
          return notify_fail(HIC"��Ǯׯ���㣡��\n"NOR);

	if(pk <= 0)
		return notify_fail(CYN"��ûɱ���˲��ù��......\n"NOR);

 	me->set("PKS", (int) pk - 1);
	me->add("balance",-1000000);

	message_vision(HIY"$N���ڵأ�����������ǰ���еĳ��.......\n"NOR,this_player());
	return 1;
}