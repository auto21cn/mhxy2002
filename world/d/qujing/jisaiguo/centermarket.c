#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "����");
  set ("long", @LONG

�������зǳ��ķ�����·�ܵ�¥̨���ʣ������ͷס�ֻ��������
���У���ֳͨ�ƣ������˵��¹�¡�أ������񸻺�����·����һ
�Ҵ��¥��Ʈ���������ζ��
LONG);

  set("objects", ([ /* sizeof() == 1*/ 
  __DIR__"npc/xiaofan" : 1,
]));
  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"westmarket",
  "east" : __DIR__"eastmarket",
  "south" : __DIR__"restaurant",
"north" : __DIR__"jitan1",
  "northup" : __DIR__"yunqi",
]));

  setup();
}
