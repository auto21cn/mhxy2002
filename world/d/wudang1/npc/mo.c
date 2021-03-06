//[4;53m[1;31mBy tianlin@mhxy for 2001.9.27[2;37;0m
//部分优化

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("莫声谷", ({ "mo shenggu", "mo" }));
        set("nickname", HIW"武当"NOR+HIR"七侠"NOR);
        set("long",
                "他就是张三丰的最小弟子、武当七侠之末的莫声谷。\n"
                "身穿一件干干净净的灰色道袍。\n"
                "他不过二十出头年纪，显得稚气未脱，身材瘦长，眉宇飞扬。。\n");
        set("gender", "男性");
        set("age", 21);
        set("attitude", "peaceful");
        set("class", "wudang");
        set("shen_type", 1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 26);

        set("max_kee", 1800);
        set("max_sen", 800);
        set("force", 1800);
        set("max_force", 1800);
        set("mana", 1800);
        set("max_mana", 1800);
        set("force_factor", 50);
        set("mana_factor", 50);
        set("combat_exp", 200000);
        set("daoxing", 560000);

        set_skill("force", 80);
        set_skill("wudang-force", 90);
        set_skill("spells", 80);
        set_skill("wudang-xianfa", 90);
        set_skill("dodge", 90);
        set_skill("tiyunzong", 90);
        set_skill("unarmed", 80);
        set_skill("taiji-quan", 85);
        set_skill("parry", 90);
        set_skill("sword", 90);
        set_skill("liangyi-jian", 90);

        map_skill("force", "wudang-force");
        map_skill("spells", "wudang-xianfa");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "liangyi-jian");
        map_skill("sword", "liangyi-jian");
	set("chat_chance", 20);
        set("chat_msg", ({
            "莫声谷轻声说道：在石柱面壁可以大有收获的。\n",
            "莫声谷斜了你一眼：不过邪魔外道就不能面壁的了。\n",
            "莫声谷偷偷告诉你：面壁是一定要注明技能的。\n",
            "莫声谷自豪地说道：只有我武当才是天下的正宗。\n",
            "莫声谷对张三丰的钦仰溢于言表：如果想成为绝顶高手，一定要学道德经。\n"
        }));

        create_family("武当派", 2, "弟子");

        setup();
        set("inquiry", ([
           "石柱":     "在石柱面壁可以大有收获的。",
           "面壁":     "面壁是一定要注明技能的。",
           "张三丰":   "我恩师学究天人，尤其是他的道学心法。"]) );
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang1/obj/greyrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if ( ((int)ob->query("combat_exp") < 100000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
        if ((int)ob->query_skill("wudang-force", 1) < 130) {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在太极神功上多下点功夫？");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("recruit " + ob->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
}
