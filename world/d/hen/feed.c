// by happ@YSZZ

#include <hen.h>
#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", "喂食");
  set ("long", @LONG

        在这你可以用[1;33m feed[m 指令喂养你的小鸡。
 
        [1;33m feed 1 ：[m吃饭          [1;33mfeed 2 ： [m吃零食  
        [1;33m feed 3 ：[m补丸          [1;33mfeed 4 ： [m吃灵芝
        [1;33m feed 5 ：[m人参          [1;33mfeed 6 ： [m吃雪莲

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "west": __DIR__"road1",
]));

        setup();
}

void init()
{
        add_action("do_feed","feed");
}

int do_feed(string arg)
{
        object ob = this_player();

        if( ! present("zhandou ji",ob) )   return 0;
        ob->command_function("cls");


        switch(arg)
        {
                case "1":
                {
                if( ob->query("hen/inventory/food")  < 1 )
                        return notify_fail("你的食物不够了，快去买吧！\n");
                switch(random(3))
                {
                case 1:
                cat(EAT);
                break;
                case 0:
                cat(DRINK);
                break;
                case 2:
                cat(MILK);
                break;
                }
                ob->add("hen/life",50);
                break;
                }

                case "2":
                {
                if( ob->query("hen/inventory/lingshi")  < 1 )
                        return notify_fail("你的零食不够了，快去买吧！\n");

                cat(FOOD);

                ob->add("hen/life",100);

                ob->query("hen/happy") < 95 ?
                ob->add("hen/happy",5+random(3)) :
                ob->set("hen/happy",100);
                ob->add("hen/weight",1);
                break;
                }

                case "3":
                {
                if( ob->query("hen/inventory/dabu")  < 1 )
                return notify_fail("你的大补不够了，快去买吧！\n");

                cat(EATDABU);
                ob->add("hen/life",500);
                break;
                }

                case "4":
                {
                if( ob->query("hen/inventory/lingzhi")  < 1 )
                        return notify_fail("你的灵芝没有了，快去买吧！\n");

                write(HIC"你加了 1000 点的生命力！\n"NOR);

                ob->add("hen/life",1000);
                break;
                }

                case "5":
                { 
                       if( ob->query("hen/inventory/renshen")  < 1 )
                        return notify_fail("你的人参不够了，快去买吧！\n");

                write(HIC"你加了 500 点的法力！\n"NOR);

                ob->query("hen/fali") + 500 > ob->query("max_fali") ?
                ob->set("hen/fali",ob->query("max_fali")) :
                ob->add("hen/fali",1000);

                break;
                }
                
                case "6":
                {
                if( ob->query("hen/inventory/xuelian")  < 1 )
                        return notify_fail("你的雪莲不够了，快去买吧！\n");

                write(HIC"你的法力加到了最大！\n"NOR);
                ob->set("hen/fali",ob->query("hen/max_fali"));
                break;
                }
        }

        ob->command_function("shape");

        return 1;
}
