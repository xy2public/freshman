// Room: /d/qujing/wudidong/book_cave1
// created 9-14-97 pickle
/************************************************************/

inherit ROOM;
#include <ansi.h>

// some global variables.
#include <ansi.h>

string book="/d/obj/book/kugu-";

/************************************************************/

void create ()
{
  object dao, shu;

  set ("short", "��Ѩ");
  set ("long", @LONG

����Ķ�ѨͻȻ�������ࡣ�ıڲ��ż�֧ţ�����򣬷�������������
�Ĺ⡣��Ѩ������ĺܣ����˱��߿�ǽ��һ�ž޴��ʯ���⣬ʲô��
û�С�ӭ��ǽ���ƺ�����һ����(zi)��
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "southup" : __DIR__"book-cave1",
]));
  set("item_desc", ([
	"��": RED"������ˣ�����������Ե���������ţ���ǧ����У��������ǣ�"NOR"\n�����ƺ���һ��С�֡�(warning)\n",
	"zi": RED"������ˣ�����������Ե���������ţ���ǧ����У��������ǣ�"NOR"\n�����ƺ���һ��С�֡�(warning)\n",
	"warning": RED"�����Ź治�࣬����̰���������Ϊ֮��\n"NOR,
	]) );
  setup();
  if( "/d/obj/weapon/blade/kugudao"->in_mud() == 0 )   {
	 dao= new("/d/obj/weapon/blade/kugudao");
	 dao->move(this_object());
  }
  if((book+"1")->in_mud() == 0)
  {
	shu=new(book+"1");
	shu->move(this_object());
  }
  if((book+"2")->in_mud() == 0)
  {
	shu=new(book+"2");
	shu->move(this_object());
  }
  if((book+"3")->in_mud() == 0)
  {
	shu=new(book+"3");
	shu->move(this_object());
  }
}

/************************************************************/
int valid_leave(object me, string dir)
{
    object *inv;
    int i, treasure_count;

    inv=all_inventory(me);
    i=sizeof(inv);
    while (i--)
    {
	if (inv[i]->query("name_recognized") == "�ݹǵ�����")
	    treasure_count+=1;
        if (inv[i]->query("name_recognized") == "�ݹǵ�")
	    treasure_count+=1;
	continue;
    }
    if (treasure_count > 1)
	return notify_fail("��̫̰���ˣ�\n");
    return ::valid_leave(me, dir);
}