

// by happ@YSZZ 

#include <ansi.h>
#include <hen.h>

inherit NPC;
static int last_age_set;

void create()
{
        set_name("星空战斗鸡", ({ "zhandou ji","ji" }) );
        set("race", "野兽");
        set("long","一只星空战斗鸡，如果要为它起名字，就用setname吧。\n");
        set("deathstamp",1);            
        set("value",100000);
        set("no_drop",1);
        set("no_give",1);
        set("no_sell",1);
        set("no_steal",1);
        set("max_kee",300);
        set("weight",0);
        set("max_sen",300);
        set("limbs", ({ "头部", "身体", "前心", "後背", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("obedience",60);
        setup();
}

void init()
{
        if( interactive(environment()) && !query("owner") )
        set("owner",environment()->query("id"));
        add_action("do_shape","shape");
        add_action("do_setname","setname");
        add_action("do_kiss","kiss_hen");
        add_action("do_diuqi","diuqi");
}
int do_diuqi()
{
        object me = this_player();
        cat(DEATH2);
        tell_object(me,"爸爸不要我了！\n");
        me->delete("hen");
        call_out("des",1);
        return 1;
}

int do_setname (string arg)
{

  object me = this_player();
  this_object()->set("name",arg);
  tell_object(me,"你的小鸡的名字就是"+arg+"了!\n");
  return 1;
}

void init_data(object owner)
{
    
        owner->set("hen/owner",owner->query("id"));
        owner->set("hen/age",0);                  
        owner->set("hen/max_life",50);
        owner->set("hen/tired",0);
        owner->set("hen/life",owner->query("hen/max_life"));
        owner->set("hen/ill",0);           // 病气
        owner->set("hen/dirty",0);         // 脏脏
        owner->set("hen/weight",30);       //30*age 正负 (30*age)/3
        owner->set("hen/max_dirty",100);
        owner->set("hen/fali",0);
        owner->set("hen/max_fali",0);
        owner->set("hen/affection",1000);    // 亲子关系 
        owner->set("hen/money",5000);      // 金钱
        owner->set("hen/mold",0);          // 气质
        owner->set("hen/might",0);         // 智力
        owner->set("hen/love",0);          // 爱心
        owner->set("hen/art",0);           // 艺术
        owner->set("hen/ethics",0);        // 道德
        owner->set("hen/homework",0);      // 家事
        owner->set("hen/decorum",0);       // 礼仪
        owner->set("hen/reflect",0);       // 应对
        owner->set("hen/cook",0);          // 厨师
        owner->set("hen/happy",50);        // 快乐
        owner->set("hen/satisfy",50);      // 满意度
        owner->set("hen/relation",0);      // 人际关系
        owner->set("hen/charm",0);         // 魅力
        owner->set("hen/brave",0);         // 勇敢
        owner->set("hen/belief",0);        // 信仰
        owner->set("hen/impurity",0);      // 罪孽
        owner->set("hen/feel",0);          // 感受
        owner->set("hen/evaluation", ([
                        "combat"        :0,
                        "society"       :0,
                        "magic"         :0,
                        "homework"      :0,
                        ]));

        owner->set("hen/inventory", ([
                         "food"         :20,
                         "lingshi"      :5,
                         "dabu"         :1,
                         "lingzhi"      :1,
                         "renshen"      :1,
                         "xuelian"      :1,
                        ]));

        owner->set("hen/attack",10);
        owner->set("hen/defence",10);
        owner->set("hen/speed",10);
        owner->set("hen/anticmagic",0);
        owner->set("hen/combat_ski",0);
        owner->set("hen/magic_ski",0);
}


string condition()
{
        object owner=find_player(query("owner"));

        if( owner->query("hen/age") == 0 )
                return "诞生";
        
        if( owner->query("hen/age") <=3 && owner->query("hen/age") > 0 )
                return "小小鸡";

        if( owner->query("hen/age") <=15 && owner->query("hen/age") > 3 ) 
                return "儿童";

        if( owner->query("hen/age") <=30 && owner->query("hen/age") > 15 )       
                return "青年";

        if( owner->query("hen/age") <=50 && owner->query("hen/age") > 30 )
                return "中年";

        if( owner->query("hen/age") <=80 && owner->query("hen/age") > 50 )            
                return "老年";

        if( owner->qurey("hen/age") > 80 )
                return "老掉牙";
}
 
                          
string dirty()
{
        object owner=find_player(query("owner"));
 
       if ( owner->query("hen/dirty") > 2*owner->query("hen/max_dirty") )
                return "[31m快臭死了![m";

        if ( owner->query("hen/dirty") >owner->query("hen/max_dirty") )
                return "[32m有点臭了[m";

                return "[1;37m我是干净的小鸡![m";
}
string tired()
{
        object owner=find_player(query("owner"));

        if( owner->query("hen/tired") > 90 )
                return "[35m快累死了[m";
        if( owner->query("hen/tired") > 60 )
                return "[32m有点小累[m";
                return "";
}

string happy()
{
        object owner=find_player(query("owner"));

        if( owner->query("hen/happy") > 90 )
                return "[32m特别快乐[m";

        if( owner->query("hen/happy") > 60 )
                return "[34m心情不错[m";

        if( owner->query("hen/happy") > 30 )
                return "[33m不太高兴[m";

                return "[36m很不高兴[m";
}
string eat()
{
        object owner=find_player(query("owner"));

        if ( owner->query("hen/max_life")/3 > owner->query("hen/life") )
                return "[33m快饿死了[m";

        if ( owner->query("hen/max_life")/2 > owner->query("hen/life") )
                return "[32m肚子空空[m";

                return "[36m肚子饱饱[m";
 }

string statisfy()
{

        object owner=find_player(query("owner"));

        if( owner->query("hen/satisfy") > 90 )
                return "[32m心满意足[m";

        if( owner->query("hen/satisfy") > 30 )
                return "[33m不太满意[m";

                return "[35m很不满意[m";
}

string ill()
{
        object owner=find_player(query("owner"));

        if( owner->query("hen/ill") > 90 )
                return "[31m病危[m";

        if( owner->query("hen/ill") > 60 )
                return "[32m病重[m";

        if( owner->query("hen/ill") > 30 )
                return "[33m生病了[m";
                return "";
}
int do_shape(string arg)
{ 
        object me;

       if( ! query("owner") )
                return notify_fail("你没有星空战斗鸡啊，去养一只吧！\n");    
        me = find_player(query("owner"));

printf(HIG+BCYN"星空战斗鸡      [33m%10s      主人: %10s                              \n[m",name(),this_object()->query("owner"));
printf(HIG+"[状态]:      %6s      [年龄]:       %3d      [金钱]:  %6d    [亲情]: %4d\n",condition(),query("age"),me->query("hen/money"),me->query("hen/affection"));
printf(HIY+"[生命]: %5d/%5d      [法力]: %5d/%5d    [体重]: %4d       [疲劳]: %3d\n",me->query("hen/life"),me->query("hen/max_life"),me->query("hen/fali"),me->query("hen/max_fali"),me->query("hen/weight"),me->query("hen/tired"));
printf(HIR+"[脏脏]:   %3d            [病气]:    %2d          [快乐]:  %3d       [满意]:  %3d\n"NOR,me->query("hen/dirty"),me->query("hen/ill"),me->query("hen/happy"),me->query("hen/satisfy"));
printf("%-16s   %-8s   %-8s      %-8s       %-6s\n",dirty(),eat(),happy(),statisfy(),ill()); 
printf("/-----------------------------------------------------------------------------\\");
printf("\n");

        if( me->query("hen/affection") < 0 )
        {
        cat(DEATH3);
        message_vision("$N大哭：$n不要我了。：（\n",this_object(),me);
        me->delete("hen");
        call_out("des",3);
        return 1;
        }

        if( me->query("hen/dirty") > 90 )
        {
        cat(DEATH1);
        message_vision("$N要死了，$n不给我洗澡。：（\n",this_object(),me);
        me->delete("hen");
        call_out("des",3);

        return 1;
        }

        if( me->query("hen/life") < 0 )
        {
        cat(DEATH1);
        message_vision("$N要死了，$n不给我吃饭。：（\n",this_object(),me);
        me->delete("hen");
        call_out("des",3);
        return 1;
        }

        if( me->query("hen/tired") > 90 )
        {
        cat(DEATH2);
        message_vision("$N要死了，$n不让我休息。：（\n",this_object(),me);
        me->delete("hen");
        call_out("des",3);
        return 1;
        }


        if( me->query("hen/ill") > 90 )
        {
        cat(DEATH1);
        message_vision("$N要死了，$n不给我治病。：（\n",this_object(),me);
        me->delete("hen");
        call_out("des",3);
        return 1;
        }

  return 1;
}

int do_kiss()
{
        object ob = this_player();
        ob->add("hen/dirty",5);

       ob->query("hen/happy") > 95 ?
        ob->set("hen/happy",100):
        ob->add("hen/happy",5+random(2));

        ob->query("hen/satisfy") > 95 ?
        ob->set("hen/satisfy",100):
        ob->add("hen/satisfy",5+random(2));
        ob->add("hen/affection",1);
        ob->command_function("cls");
        ob->command_function("shape");
        cat(KISS);
        write("来嘛! 啵一个.....\n");
        return 1;
}

void update_age()
{

        if( !last_age_set ) last_age_set = time();
        add("mud_age", time() - last_age_set);
        last_age_set = time();
        set("age", (int)query("mud_age") / 172800);
}

int heal_up()
{
        object ob;

        if( ! query("owner") )
        {
        call_out("des",3);
        return 1;
        }
/*
        ob = find_player(query("owner"));
        
        if( ! interactive(ob) )
        {
        call_out("des",3);
        return 1;
        }
        update_age();

        if( ob->query("hen/affection") < 0 )
        {
        message_vision("$N大哭：$n不要我了。：（\n",this_object(),ob);
        ob->delete("hen");
        call_out("des",3);
        return 1;
        }

        if( ob->query("hen/dirty") > 90 )
        {
        message_vision("$N要死了，$n不给我洗澡。：（\n",this_object(),ob);
        ob->delete("hen");
        call_out("des",3);
        return 1;
        }

        if( ob->query("hen/life") < 0 )
        {
        message_vision("$N要死了，$n不给我吃饭。：（\n",this_object(),ob);
        ob->delete("hen");
        call_out("des",3);
        return 1;
        }

        if( ob->query("hen/tired") > 90 )
        {
        message_vision("$N要死了，$n不让我休息。：（\n",this_object(),ob);
        ob->delete("hen");
        call_out("des",3);
        return 1;
        }


        if( ob->query("hen/ill") > 90 )
        {       
        message_vision("$N要死了，$n不给我治病。：（\n",this_object(),ob);
        ob->delete("hen");
        call_out("des",3);
        return 1;
        }

*/        set_heart_beat(1);
        return ::heal_up();
}

void des()
{
        destruct(this_object());
}
