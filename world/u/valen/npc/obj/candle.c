// by night
// fid �޸�

inherit ITEM;
#include <ansi.h> 

void create()
{
        set_name(HIM"��Ը"HIR"����"NOR, ({"wish candle","candle"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
         set("long", "����һ֧���Ƶ����򣬾�˵�Ե���ʱ��ȼ������ʵ��һ��Ը����\n������õ�ȼָ���ȼ����(fire)");
                set("unit", "֧");
                set("value", 10000);
        }
} 

void init()
{
    add_action("do_fire","fire");
}

int do_fire(string arg)
{    object me, ob;
    me=this_player();
    ob=this_object();

    if (arg=="wish candle"||arg=="candle") {
        if (!present("cake", me) ) 
                return notify_fail("��û�е��⣬����Ը������ʲô�ã�\n");
        message_vision(HIR"$N��ȼ��������ذ���������˵����ϡ�\n"NOR, me); 
     me->set("fired",1); 
     destruct(ob);     return 1;
     }    return notify_fail("��Ҫ����ʲô��\n");
}