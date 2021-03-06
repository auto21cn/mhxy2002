//by tianlin@mhxy 2001.8.20,在我看电视连续剧里的<鱼美人>里的张天师 ,有一个法宝叫元牝珠,我突发灵感.......

#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

int do_wear(string arg);
int do_remove(string arg);
object offensive_target(object me);

void create()
{
        set_name(HIY "元"HIC"牝"HIW"珠" NOR, ({"yuan pinzhu", "zhu"}) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("material", "crystal");
                set("value",10000);
                set("rumor_msg",1);
                set("no_steal",1);
                set("no_drop", "如此宝贵的武器再世难求啊。\n");
                set("no_give", "这种稀世之宝怎么能轻易送人呢?\n");
                set("no_sell", "卖?这种稀世之宝谁买得起啊!\n");
                set("long",HIC"这是张天师所创,总总留传了七七四十九代,此珠吸取了日月精华。\n"NOR);
                set("bb",1);
                set("replace_file", "/d/obj/flower/rose");
                set("armor_prop/armor", 1);
        }
        setup();
}

int init()
{
        add_action("do_wear","wear");
        add_action("do_remove", "remove");
        return 1;
}

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
        int sz;
        object *enemy;

        enemy = me->query_enemy();
        if( !enemy || !arrayp(enemy) ) return 0;

        sz = sizeof(enemy);
        if( sz > 4 ) sz = 4;

        if( sz > 0 ) return enemy[random(sz)];
        else return 0;
}

int do_wear (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if (arg != "all" && arg != "zhu" &&  arg != "yuan pinzhu" )
    return notify_fail("你要佩带什么？\n");
  msg = "$N戴上一颗"+name+"，不禁精神一振。\n"; 
  zhu->set("wear_msg",msg);
remove_call_out("yuanpinzhuconditions");
call_out("yuanpinzhuconditions",1,me,zhu);
  return 0;
}

int do_remove (string arg)
{
  object me = this_player();
  object zhu = this_object();
  string name = zhu->query("name");
  string msg;

if (arg != "all" && arg != "zhu" && arg != "yuan pinzhu")
    return notify_fail("你要摘掉什么？\n");

  msg = "$N将"+name+"轻轻地摘下来……\n"; 
  zhu->set("unequip_msg",msg);
  remove_call_out("yuanpinzhuconditions");
  return 0;
}

void yuanpinzhuconditions(object who,object ob)
{
     object target;
     int ap,dp,damage;
     string msg;
string type;
type = ob->query("armor_type");
if( who->query_temp("armor/" + type) && ob->query("equipped")!="worn")
return;
        target = offensive_target(who);
     if( who->is_fighting() &&target) //by xlwang
     {
  if( ! target ) return ;      
 if( ! present( target,environment(who)) ) return ;    
        msg = HIY
"\n元牝珠轰的一声，发出了耀眼的光芒，其中有 
"HIB"蓝色"NOR"                                     "NOR+HIM"★"NOR"
     "HIR"红色"NOR"                           "NOR+HIC"☆"NOR"    
          "HIY"黄色"NOR"                 "NOR+WHT"★"NOR" 
               "HIW"白色"NOR"      "NOR+RED"☆"NOR"
                    "NOR+MAG"紫色"NOR"
             "NOR+YEL"☆"NOR"          "HIG"绿色"NOR"
      "NOR+CYN"★"NOR"                       "HIC"青色"NOR"
"HIB"☆"NOR"                                   "HIR+BLK"灰色"NOR"
"HIY"这些光芒瞬间化成一股很强的"HIC"灵气"HIY",就再那一瞬间
这股"HIC"灵气"HIY"冲向了$n"HIY"，在$n"HIY"的周围爆炸！\n"NOR;

        ap = 2000000;
        dp = target->query("combat_exp");
        if( random(ap + dp) > dp )
           {
                damage = random(300) + 500;
                damage -= (int)target->query("max_mana") / 10 + random((int)target->query("eff_sen") / 5);                                              
                damage -= random((int)target->query("mana_factor"));
//here we can see if 2 players are at same status, the attacker has higher chance.
                if( damage > 0 ) 
                {
                msg +=  HIC "\n$n"HIC"被$N"HIC"这股灵气炸开差点要了，$n"HIC"的老命。\n" NOR;
//finally damage also depends on enabled spells level.
                target->receive_damage("sen", damage);
                target->receive_wound("sen", damage/2);
                target->start_busy(1); 
                }
            else 
//here, cast failed and the target's mana_factor will be added to the previous 
//damage to hurt yourself:(...note damage<0.
                msg += HIR "\n谁知$n"HIR"身形一转躲了过去。\n" NOR;
           } 
        else
               msg += "\n谁知$n对$N这强大的灵气一点反映也没有，可能是吓坏了。\n";
                           target->start_busy(1);       
        message_vision(msg, who, target);
    }
call_out("yuanpinzhuconditions",7,who,ob);
}
 
