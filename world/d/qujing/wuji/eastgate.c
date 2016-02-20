//by tianlin 2001.8.5

inherit ROOM;

void create ()
{
  set ("short", "东门");
  set ("long", @LONG

这是乌鸡国的东门城楼，青石筑成两层楼台坚固异常，巍峨
宽阔的拱行城门上方镂着[1;31m「乌鸡国」[2;37;0m三个红漆大字。 
LONG);

  set("exits", ([ /* sizeof() == 2 */
    "east" : __DIR__"street2",
    "west" : __DIR__"estreet",
  ]));
  set("outdoors", __DIR__"");

  setup();
}

int valid_leave (object who, string dir)
{
  if (dir != "west" && !interactive(who))
    return 0;
  return ::valid_leave(who, dir);
}
