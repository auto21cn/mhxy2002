// by happ@YSZZ
inherit ROOM;

void create ()
{
  set ("short", "大学路");
  set ("long", @LONG

        这里全是学习的地方，有学文，也有学武的，不过这都不是
    义务教育，全部要收费的哦，南面是学习[1;35m格斗[m的，北面是学习[1;35m剑术[m的。

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "east": __DIR__"xxroad4",
         "west": __DIR__"xxroad2",
          "north": __DIR__"jianshu",
         "south": __DIR__"gedou",
]));

        setup();
}
