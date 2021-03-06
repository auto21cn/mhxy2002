//By tianlin@mhxy for 2002.1.2

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include <obstacle.h>

void create()
{
         set_name("姬邑考", ({ "ji yankao", "yankao", "ji", "kao", "master" }));
             set("title", MAG "中天北极紫微大帝"NOR);   
	set("long", @LONG
一位饱经沧桑经历过许多风风雨雨在江湖中 铤而走险的女前辈。
LONG);
         set("gender", "女性");
         set("age", 20);
	set("attitude", "heroism");
	set("per", 9);
	set("max_kee", 2850);
	set("max_gin", 2800);
	set("max_sen", 2850);
	set("force", 15400);
	set("max_force", 8000);
	set("force_factor", 50);
	set("max_mana", 5000);
	set("mana", 11300);
	set("mana_factor", 20);
	set("combat_exp", 2330000);
	set("daoxing", 7450000);
       set_skill("literate", 180);
       set_skill("unarmed", 285);
       set_skill("dodge", 285);
       set_skill("force", 285);
       set_skill("parry", 285);
       set_skill("sword", 285);
       set_skill("spells", 285);
       set_skill("whip", 285);
       set_skill("pansi-dafa", 285);
       set_skill("lanhua-shou", 285);
       set_skill("jiuyin-xinjing", 285);
       set_skill("chixin-jian", 285);
       set_skill("qin", 285);
       set_skill("yueying-wubu", 285);
       set_skill("yinsuo-jinling", 285);
       map_skill("spells", "pansi-dafa");
       map_skill("unarmed", "lanhua-shou");
       map_skill("force", "jiuyin-xinjing");
       map_skill("sword", "chixin-jian");
       map_skill("parry", "yinsuo-jinling");
       map_skill("dodge", "yueying-wubu");
       map_skill("whip", "yinsuo-jinling");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
                (: cast_spell, "wuzhishan" :),
                (: cast_spell, "ziqi" :)
	}) );
        create_family("盘丝洞 ", 1, "祖师");
	setup();
	// carry_object("/u/tianlin/zjmaster/putuo/jiasha")->wear();
	// carry_object("/u/tianlin/zjmaster/putuo/staff")->wield();
}
void init ()
{
  add_action("do_back", "back");
}
void attempt_apprentice(object ob)
{
	int size = sizeof(obstacles);
  	string *names = keys(obstacles);
  	int i;

         if (((int)ob->query_skill("pansi-dafa", 1) < 200 )) {
                command("say " + RANK_D->query_respect(ob) + "不在我派法术上苦修，恐怕难成正果。\n");
                return;
        }
  	for (i = 0; i < size; i++)
      	if (ob->query("obstacle/"+names[i])!="done" && !wizardp(ob))
      	{
 	   command("shake");
    	   command("say 这位" + RANK_D->query_respect(ob) + "尚未历尽西行难关，恐怕难以领悟高深武学。\n");
	   return;
      	}
        command("pat " + ob->query("id") );
        command("jump " + ob->query("id") );
         command("say 好！这才是我的好弟子。只要多加努力，定可早成正果。\n");

        command("recruit " + ob->query("id") );
        message("channel:rumor",HIM+"【"HIW"谣言"HIM"】某人："BLINK+HIY+ob->query("name")+NOR+HIM"西天取经感化众生得到"NOR+MAG"姬邑考"HIM"的亲自指点！\n"NOR,users() );
        return; 
}
int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	      ob->set("class", "xian");
             ob->set("title",MAG"盘丝洞"YEL"散花阵"CYN"传人"NOR);
}
int do_back(string arg)
{
  object who = this_player();
  object me = this_object();
  string here = (string)environment(me);
  string there = who->query_temp("33tian/from");

  message_vision("$N请求$n送$N回返。\n",who,me);
  there = "/d/city/kezhan";

  message_vision("$N的手掌轻轻托起$n向远方伸去……\n",me,who);
  who->move(there);
  message_vision(HIM"……云中伸出一只巨大的佛手轻轻一翻，只见$N从里面跳出来。\n"NOR,who);
  
  return 1;
}

�
