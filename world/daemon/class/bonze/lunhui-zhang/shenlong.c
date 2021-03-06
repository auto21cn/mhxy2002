// xian.c  云龙三现
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("[1;33m神龙三现只能对战斗中的对手使用。[1;0m\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("你使用的武器不对。\n");
                
        if( (int)me->query_skill("lunhui-zhang", 1) < 120 )
                return notify_fail("你的轮回杖法不够娴熟，不会使用「神龙三现」。\n");
                                
        if( (int)me->query_skill("lotusforce", 1) < 120 )
                return notify_fail("你的莲花心法不够高，不能用来反震伤敌。\n");
                        
        if( (int)me->query("force", 1) < 1500 )
                return notify_fail("你现在内力太弱，不能使用「神龙三现」。\n");
                        
        msg = MAG "只见$N微微一笑，猛吸一口气,欲使出聚气驭杖绝技攻击$n。\n"NOR;

        if( !target->is_killing(me) ) target->kill_ob(me);

        if (random(me->query_skill("force")*2.2)> target->query_skill("force"))
        {
                target->start_busy(random(1));
                
                damage = (int)me->query_skill("lotusforce", 1)/2;
                damage = damage +  (int)me->query_skill("lotusmove", 1)/2;
                damage = damage +  (int)me->query_skill("lunhui-zhang", 1)/2;
                
                target->receive_damage("kee", damage);
                target->receive_wound("kee", damage*2/3);
                msg += HIY"$N手中禅杖幻作一条金龙,腾空而起,倏的罩向$n,\n$n只觉一股大力铺天盖地般压来,登时眼前一花，两耳轰鸣,哇的喷出一口鲜血！！\n"NOR;
                me->start_busy(2);
        } else 
        {
                msg += CYN"可是$p猛地向前一跃,跳出了$P的攻击范围。\n"NOR;
                me->start_busy(3);
        }
        message_vision(msg, me, target);
        me->add("force",-200);
        return 1;
}
