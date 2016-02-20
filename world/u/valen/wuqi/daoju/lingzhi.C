
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
  }                                    
  add_action("do_eat", "eat");
}

void create()
{
  set_name(HIR"������֥"NOR, ({"wannian lingzhi","wannian","lingzhi"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "����һ���������֥���ǳ����\n");
    set("value", 2000000);
    set("drug_type", "��Ʒ");
  }
  
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  
  if (!id(arg))
    return notify_fail("��Ҫ��ʲô��\n");
  
  me->set("food", (int)me->max_food_capacity());
  me->add_maximum_mana(20);
  message_vision(HIR "$N����һ��������֥��ֻ���÷����ޱߣ������޵��ˣ� \n" NOR, me);
  
  destruct(this_object());
  return 1;
}