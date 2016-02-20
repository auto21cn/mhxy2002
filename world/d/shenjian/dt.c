// LLY@FYSY
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "大厅");
        set("long", @LONG
一进大厅，便可看到大厅的两根顶柱上挂着两块长木对联，上书：
[37m
		   剑	     一
		   气	     剑
		   纵	     光
		   横	     寒
		   三	     十
		   万	     九
		   里	     洲
[0m
对联的中间偏后的地方便是主人的座位，大厅两边排列着几十个罗汉椅，
是来访宾客的座位，大厅中红毯铺地，四处皆是古玩，名画，花香四溢，
只是与众不同的地方便是横梁上似乎少了一块匾似的。
LONG
        );
                set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"ty",
  "south" : __DIR__"qhuayuan",
  "east" : __DIR__"rpt",
  "west" : __DIR__"lpt",
]));
  set("outdoors", __DIR__);
              set("coor/x",-1310);

	set("coor/y",260);

	set("coor/z",10);
	setup();
}
