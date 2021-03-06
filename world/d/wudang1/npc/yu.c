//By tianlin@mhxy for 2001.9.27
//部分优化

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_mieyao(object me);
string ask_cancel();

void create()
{
	set_name("俞莲舟", ({ "yu lianzhou", "yu" }));
	set("nickname", HIW"武当"NOR+HIR"二侠"NOR);
	set("long", 
		"他就是张三丰的二弟子俞莲舟。\n"
		"他今年五十岁，身材魁梧，气度凝重。\n"
		"虽在武当七侠中排名第二，功夫却是最精。\n");
	set("gender", "男性");
	set("age", 50);
	set("attitude", "peaceful");
	set("class", "wudang");
	set("shen_type", 1);
	set("str", 28);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	
	set("max_kee", 3500);
	set("max_sen", 3800);
	set("force", 5000);
	set("max_force", 5000);
	set("mana", 5000);
	set("max_mana", 5000);
       set("force_factor", 140);
       set("mana_factor", 140);
	set("combat_exp", 1800000);
	set("daoxing", 1800000);

	set_skill("force", 210);
	set_skill("wudang-force", 200);
	set_skill("dodge", 200);
	set_skill("tiyunzong", 230);
	set_skill("unarmed", 180);
	set_skill("taiji-quan", 240);
	set_skill("parry", 200);
	set_skill("sword", 200);
	set_skill("spells", 200);
	set_skill("taiji-jian", 210);
	set_skill("liangyi-jian", 180);
	set_skill("wudang-xianfa", 200);
	set_skill("literate", 150);

	map_skill("force", "wudang-force");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	set("chat_chance_combat", 90);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );
        set("inquiry", ([
      "kill": (: ask_mieyao :),
      "cancel": (: ask_cancel :),
      "放弃": (: ask_cancel :),
]) );

	create_family("武当派", 2, "弟子");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang1/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if ( ((int)ob->query("combat_exp") < 100000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
        if ((int)ob->query_skill("wudang-force", 1) < 140) {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在太极神功上多下点功夫？");
                return;
        }
	command("say 好吧，既然" + RANK_D->query_respect(ob) + "也是" +
		"我辈中人，今天就收下你吧。");
	command("recruit " + ob->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
                ob->set("title", "[1;33m武当派[1;37m第[1;36m三[1;37m代弟子[2;37;0m");
}
string ask_mieyao(object me)
{
    me=this_player();
    if((string)me->query("family/family_name")=="武当派") {
    tell_room(environment(me),"俞莲舟举起手中的长剑，顿时大吼一声。\n");
    write(HIY+"/d/obj/mieyao"->query_yao(me)+NOR);
    return (HIG"即我门人,当除妖魔为己任.\n"NOR);
    }
    return ("贫道不知。");
}

string ask_cancel()
{
    object me=this_player();
    
    if("/d/obj/mieyao"->delete_mieyao(me))
      me->add("faith",-5);
    return ("没用的东西！");
}
