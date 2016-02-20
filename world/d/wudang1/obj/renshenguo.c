// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
	add_action("do_eat", "eat");
	remove_call_out("destguo");
	call_out("destguo", 10);
}
void destguo()
{
	message_vision("$N��������ˮ����һ��͸��õ��ˡ�\n",this_object());
	destruct(this_object());
}

void create()
{
	set_name(HIR"�˲ι�"NOR, ({"guo", "renshen guo"}));
	set("unit", "��");
	set("long", "����һֻ�˲ι�, �Ѿ�����, ����������ܲ�����С����\n");
	setup();
}

int do_eat(string arg)
{
	object me=this_player();
	if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");
	if(arg=="guo")
	{
		me->add("max_force",10);
		me->set("force",me->query("max_force"));
		me->set("eff_kee",me->query("max_kee"));
		me->set("kee",me->query("eff_kee"));
                message_vision("$N����һö�˲ι���ֻ���þ���������Ѫ��ӯ����������ԴԴ�������������ٸе������ɿ�!\n",me);

		destruct(this_object());
	}
	return 1;
}