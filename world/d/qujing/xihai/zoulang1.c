inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�������������ȣ����������������ɷ���ɷǷ���������
�İ�����һ���������Ϻ��Ϻ�ţ��������ڴ��������֡�
�컨���������ϸ�ƣ��̻��ŵ�����������ƽ�������ķṦ
ΰ���� 
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"dian",
                "west" : __DIR__"zoulang3",
                "north" : __DIR__"zoulang7",
        ]));

        setup();
}
