//created by vikee
//2000.10

inherit ROOM;
 
void create()
{
   set("short", "����¯���޹�");
   set("long",@LONG

�����¯���Ĵ���������֮���������У�ֻ�е����������ѵ���
LONG
        );
 
   set("exits", ([
       "east" : __DIR__"bgl5",
        "north" : __DIR__"bgl7",
                "west" : __DIR__"bgl1",
                "south" : __DIR__"bgl3",
   ]));
    set("valid_startroom", 1);
   set("objects",([
      "/d/dntg/sky/npc/huobing" : 1,      
   ]));



        setup();
}

