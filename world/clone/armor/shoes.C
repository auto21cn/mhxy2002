// by mhsj@gslxz 2001/3/12
#include <ansi.h>
#include <armor.h>;

inherit BOOTS;

void create()
{
        set_name(HIW"��Ө��ѩЬ"NOR, ({ "iceshoes","shoes" }) );
       set("value", 160000);
            set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "˫");
 	        set("long", HIW"�����ɾ�Ө�ı����ɵ�Ь��\n"NOR);
                             set("material", "steel");
                set("armor_prop/armor", 6);
                set("armor_prop/dodge", 20);
        }
        setup();
}

