// by happ@YSZZ
inherit ROOM;

void create ()
{
  set ("short", "商业街");
  set ("long", @LONG

        这里非常热闹，有教堂，酒吧，教堂，你在这可以赚到很多的
    钱，只要你肯干活，赚钱是没有问题的拉，北面是一家[1;34m墓地[m，南面
    是[1;34m家教服务中心[m。

LONG);

  set("exits", ([ /* sizeof() == 4 */
         "east": __DIR__"syroad5",
         "west": __DIR__"meirong",
          "north": __DIR__"mudi",
         "south": __DIR__"jj",
]));

        setup();
}
