inherit ROOM;                                                        
                                                                     
void create ()                                                       
{                                                                    
  set ("short", "������");                                   
  set ("long", @LONG                                                 
 
����һƬ������ʹ���Ҫ�ֲ��巽�򣬻��ǳ��ܿ���

·��ʱ��Ͽ��߰ɡ�
                                           
LONG);                                                          
                                                                     
    set("exits", ([ /* sizeof() == 1 */                              
  "north" : __DIR__"hundun4",                                         
  "east" : __DIR__"hundun",                                    
  "west" : __DIR__"hundun",                                       
  "south" : __DIR__"hundun",
                                     
]));                                                                 
                                                                     
  setup();                                                           
}