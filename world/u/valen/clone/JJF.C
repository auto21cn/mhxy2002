// jjf.c ������

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "������" NOR, ({ "wan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "һ�������ҩ�裬��˵��������skills��\n");
                set("value", 0);
		set("unit", "��");
	}
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object me;

        if (! id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

        me = this_player();
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
       
                tell_object(me, HIG "���skills�Ѿ������ˣ�"
                            "����jifa�����skills��Ȼ��������ʦҪdan��ף�����п��֣�\n" NOR);
                                     me->set_skill("bawang-qiang",120);
                            me->set_skill("changquan",120);
                            me->set_skill("dodge",120);
                            me->set_skill("force",120);
                            me->set_skill("lengquan-force",120);
                            me->set_skill("literate",120);
                            me->set_skill("mace",120);
                            me->set_skill("parry",120);
                            me->set_skill("spear",120);
                            me->set_skill("unarmed",120);                            
                            me->set_skill("wusi-mace",120); 
                             me->set_skill("yanxing-steps",120);
                            me->set_skill("sanban-axe", 120);
                            me->set_skill("axe",120);
                            me->set_skill("baguazhou",120);
                            me->set_skill("spells",120);
           
       destruct(this_object());
	return 1;
}
