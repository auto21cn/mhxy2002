// zhting.c

inherit ROOM;

void create ()
{
  set ("short", "��˾");
  set ("long", @LONG

����������ܵظ�֮�У�ż��������������������˾��ǣ��Щ����
��������������ȥ����Χ��һ������¥�󹬵������Ҳ�൱�ĸ�
���ûʣ���ֵ��Ƕ���һ�ȶ��Ž𶤵ĺ�ľ�ź�һ�������ż���
LONG);

  set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"walk1",
  "east" : __DIR__"room4",
  "west" : __DIR__"room3",
  "north" : __DIR__"walk3",
]));
  set("hell", 1);

  setup();
}