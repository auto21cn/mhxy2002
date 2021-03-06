// By tianlin 2001.5.1
// hunpofeiyang.c 魂魄飞扬
 
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
 
inherit SSERVER;
 
int perform(object me)
{
	string msg;
	object weapon, target;
	
	me->clean_up_enemy();
	target = me->select_opponent();

	if( !me->is_fighting() )
	    	return notify_fail("「魂魄飞扬」只能在战斗中使用。\n");

	if( (int)me->query("force") < 500 )
		return notify_fail("你的内力还不够高！\n");

	if( (int)me->query_skill("unarmed") < 150 )
		return notify_fail("你的拳法还不到家，无法使用魂魄飞扬！\n");

	if( (int)me->query_skill("huagu-mianzhang", 1) < 60)
		return notify_fail("你化骨绵掌的修为不够，不能使用魂魄飞扬! \n");
	 
	msg = HIY "$N大喝一声，使出化骨绵掌的绝技[5m[1;37m「魂魄飞扬」[2;37;0m[1;33m，双拳势如雷霆，向$n击去。\n"NOR;
             message_vision(msg, me, target);
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
	
	me->start_busy(2);
	return 1;
}
