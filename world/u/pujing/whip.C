//By tianlin@mhxy for 2002.1.2.
#include <ansi.h>
#include <weapon.h>

inherit WHIP;

void create()
{
        set_name(HIR "Ѫ�������" NOR, ({"xueyu bian","whip","bian"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",HIG"�˱����޷�����֮����\n"NOR);
                set("unit", "��");
                set("value", 200000);
		  set("no_sell",1);
		  set("no_get",1);
		  set("no_give",1);
		  set("no_drop",1);
                set("rumor_msg",1);
                set("is_monitored", 1);
                set("wield_msg", HIW"$N��$n"HIW"������⿪����Χ���˶��ж�ʱ�����������š�\n"NOR);
                set("unwield_msg", HIW"$N��$n"HIW"�̻����ϣ�һ���ָֻ���������\n"NOR);
        }
        init_whip(100+random(100));
        setup();
}
