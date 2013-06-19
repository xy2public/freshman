
// dhwl.c
//write by yeahsi
//yeahsi@21cn.com

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

void perform_effect(object me, object target);
void check(object me, object target, int dodge_amount);
void remove_effect(object me);
void match_force(object me,object target);
void perform_effect2(object me, object target);

int perform(object me, object target)
{
        int skill,skill_fork,fengbo_skill,skill_dodge,dodge_amount,ini_dodge_apply,ini_damage_apply;
        
        skill = me->query_skill("dragonforce",1);
        skill_dodge = me->query_skill("dodge",1);
        skill_fork= me->query_skill("fork",1);
        fengbo_skill= me->query_skill("fengbo-cha",1);
	dodge_amount = (skill+skill_dodge)/20;              
        
        if (!me->query_temp("dhwl"))
             ini_dodge_apply = me->query_temp("apply/dodge");
                  
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ������������\n");

        if(!me->is_fighting())
               return notify_fail("����������ֻ����ս����ʹ�ã�\n");
                
        if( time()-(int)me->query_temp("dhwl_end") < 6 )
                return notify_fail("�����ö�Ͳ����ˣ�\n");
        
        if (me->query_temp("dhwl")) return notify_fail("���Ѿ��������ˡ�\n");
        if( skill < 100 )  return notify_fail("��������ķ���Ϊ������\n");
        if( skill_fork < 100 )  return notify_fail("��Ļ����淨δ�����졣\n");
        if( fengbo_skill < 160 )  return notify_fail("��ķ粨ʮ����δ�����졣\n");
               
        if( (int)me->query("force") < skill )     
		return notify_fail("�������������\n");
 
        me->add("force", -skill);
        me->set_temp("dhwl_target",target);
        tell_object(me, MAG"�㲻����ɫ�������ķ�������һת������һ�������ӽ���ӿȪѨ��������\n"NOR);
        me->set_temp("no_move",1);  
        me->set_temp("dhwl", 1);
        me->set_temp("before_dhwl_dodge",ini_dodge_apply);
        call_out("check", 1, me,target,dodge_amount);
        return 1;
}


void check(object me, object target, int dodge_amount)
{   	
	object weapon;
		
	 if(!me) return;
	 
    if(!target) return;
	 if (me->query_skill_mapped("force") != "dragonforce"
	         || !objectp(weapon=me->query_temp("weapon")) 
	         || (weapon->query("apply/skill_type") != "fork" 
	             && weapon->query("skill_type") != "fork" ) 
	         ||  me->query_skill_mapped("fork") != "fengbo-cha" )     
	     remove_effect(me);
	 	 	    
         else if(!present(target->query("id"), environment(me)) || !me->is_fighting(target) || !me->is_fighting())
	           remove_effect(me);
	 
	 else if(!me->query_temp("dhwl"))
	       remove_effect(me);
	           
	else {me->add_temp("dhwl",1);
	      if (me->query_temp("dhwl")==10)
	            tell_object(me, MAG"������һ���죬��������ǿ�Ե�������ͻȻ���Լ����һ��������Ϊ����Ϊ��ֻ��ͷ����\n\n"NOR);     
	      else if (me->query_temp("dhwl")==9)
	            tell_object(me, MAG"��ͻ��������ת�����޷�ͻ�ƣ�������Ŀ��˼��Ȼ�����ڱ���˫Ŀ��һ˲����ʶ���۲��Ӷ����ڸεĵ�����\n\n"NOR);
	      else if (me->query_temp("dhwl")==8)
	            tell_object(me, MAG"����ƽ�����������������಻�����룻�����Ŷ�����������������������������һ�㡣\n\n"NOR);
	      else if (me->query_temp("dhwl")==7)
	            tell_object(me, MAG"����ס��Ϣ����ת�����ڷμ䡣���������Ƴ�����Ȼ�ﵽ�˱ǲ�������ڷεľ��硣\n\n"NOR);
	      else if (me->query_temp("dhwl")==6)
	            tell_object(me, MAG"�����������ķ����ԣ��಻���������ġ���æ����������������������һƬ���顣\n\n"NOR);
	      else if (me->query_temp("dhwl")==5)
	            tell_object(me, MAG"�㽫���뵤��֮������ȫ��������žž���죬��ת����ֱ���ζ����̲�ס������Х��\n\n"NOR);
	      else if (me->query_temp("dhwl")==4)
	            tell_object(me, MAG"��Ĭ�������ķ�����֫����������Ƣ������δ����ȴֻ���������ڵ������������\n\n"NOR);
	      else if (me->query_temp("dhwl")==3)
	            tell_object(me, MAG"���������񣬰ѽŵ���������ϥ������������������ת�������ޱȡ�\n\n"NOR);
	      else if (me->query_temp("dhwl")==2)
	            tell_object(me, MAG"\n�����������ķ���ת˲��ͻȻ��������������죬���ϸ��ֳ�����������\n\n"NOR);
	      	                                          
	     // me->add_temp("apply/dodge",random(dodge_amount));
	      
	      call_out("check", 1, me,target,dodge_amount);
	     }
             
}


void remove_effect(object me)
{
        if(!me) return;
        remove_call_out("check");
        remove_call_out("remove_effect");
        me->set_temp("apply/dodge",me->query_temp("before_dhwl_dodge"));
        me->delete_temp("before_dhwl_dodge");
        me->delete_temp("dhwl_target");
        if (!me->query_temp("dhwl_match_force"))
               me->delete_temp("no_move");
        if (me->query_temp("dhwl"))
             tell_object(me, GRN"��ֻ������һ�ɣ��᲻���ˡ�\n"NOR);
        me->delete_temp("dhwl");
}

