inherit NPC;
 
void do_drink();
 
void create()
{
        seteuid(getuid());
        set_name("李不缺", ({"libu que", "que"}));
        set("long", "有了李不缺,什么都不愁。\n");
        set("gender","男性");
	set("title", "兵器贩子");
	set("class", "scholar");
        set("age",37);
        set("con",30);
        set("per",30);
        set("str",25);
        set("int",35);
        set("combat_exp",600000);
        set("attitude","heroism");
        set("chat_chance",20);
        set("chat_msg", ({
        "李不缺低声说道：我的倚天剑威力无比。\n",
        "李不缺低吟道：我虽然钱不多,但是更新一次我就有一百两黄金也不错。\n",
        "李不缺高兴的唱起歌来：一 二 三 四 五 上山打老虎。\n",
        "李不缺长吟道：穷呀,没钱呀,谁能给我点钱!\n",
	(: random_move :)
        }));

        set("chat_chance", 90);

        set_skill("dodge", 90);
        set_skill("force", 90);
        set_skill("parry", 90);
        set_skill("unarmed", 90);
        set_skill("sword", 90);
        set_skill("literate", 120);
	set("max_force", 2000);
	set("force", 2000);
	set("force_factor", 1000);
        set("max_kee", 2000);
        set("max_gin", 4000);
        set("max_sen", 2000);

        setup();
        carry_object("/d/obj/armor/jinsijia")->wear();
        carry_object("/d/obj/weapon/sword/yitian")->wield();
	carry_object("d/obj/cloth/monkcloth")->wear();
	carry_object("d/obj/cloth/shoupipifeng")->wear();
	carry_object("d/lingtai/obj/shoe")->wear();
	carry_object("d/qujing/tianzhu/obj/tiekui")->wear();
        add_money("gold", 100);
}
 
void do_drink()
{
    object *list, ob;
    int i, can_drink;
    if ((int)this_object()->query("water") >= 380) return;
    list = all_inventory(this_object());
    i = sizeof(list);
    can_drink = 0;
    while (i--) {
        if ((string)list[i]->query("liquid/type") == "alcohol") {
            ob = list[i];
            can_drink = 1;
        }
    }
    if (can_drink) {
        command("drink "+(string)ob->query("id"));
        if ((int)ob->query("liquid/remaining") == 0)
            command("drop "+(string)ob->query("id"));
    }
    else {
        command("sigh");
        command("say 穷呀...穷呀! ");
    }
    return;
}

int accept_object(object who, object ob)
{	object m;
	m=new("/d/obj/book/jianpu.c");
    if ((string)ob->query("liquid/type")=="alcohol")
    {
        if ((int)ob->query("liquid/remaining") == 0)
        {
            command("shake");
            command("say 空的我不要．．．");
            return notify_fail("好象李不缺不是收破烂的，不要空瓶子。\n");
        }
        else
                if ( (string)ob->name()=="牛皮酒袋" )
                {
                        command ("frown");
                        command ("say 这酒还是您留着自己喝吧。");
                        return
notify_fail("好象李不缺看不起你给他的酒。\n");
                }
                else
                {
                        command("smile");
                        command("say 多谢!");
			if ((int)who->query_temp("mark/李不缺") < 1){
			who->set_temp("mark/李不缺", 1 ); 
			}
                        if(present("jian pu", this_object())) {
			return 0;
			}
                        who->add_temp("mark/李不缺", 1 );
                        call_out("destroy", 1, ob);
                if ((int)who->query_temp("mark/李不缺") >= 5+random(5))
                        {
command ( "whisper " + who->query("id") + 
" 我看您也是位练功习武的人，也算咱们有缘，这本剑谱就送给你拿去研读吧。\n");
				m->move(who);
                                who->set_temp("mark/李不缺", 0 );
				return 1;
                        }
                        return 1;
                }
        }
    }

void destroy(object ob)
{
        destruct(ob);
        return;
}

�