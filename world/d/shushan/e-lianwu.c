//����ɽ�ɡ�mhxy-yushu 2001/2
inherit ROOM;
#include <ansi.h>
void create()
{
	set("short","���䳡");
	set("long", @LONG

����¶�����䳡���ö�����������������ţ������ڳ��У�û����
��ͷ����һ�ۣ����ھ۾�����������Լ��Ĺ���
LONG);
        set("outdoors", 2);
        set("exits", ([
           "west" : __DIR__"yongdao",
	]));
         set("objects", ([ 
             __DIR__"obj/muren" : 4,
             __DIR__"npc/dizi" : 1,
             __DIR__"npc/dizi1" : 1,
       ]));
        setup();
}
