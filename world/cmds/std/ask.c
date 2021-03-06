//By tianlin@Mhxy for 2001.12.16

#include <ansi.h>
string query_inquiry(object ob);
inherit F_CLEAN_UP;

string *msg_dunno = ({
	"$n摇摇头，说道：没听说过。\n",
	"$n疑惑地看着$N，摇了摇头。\n",
	"$n睁大眼睛望着$N，显然不知道$P在说什么。\n",
	"$n耸了耸肩，很抱歉地说：无可奉告。\n",
	"$n说道：嗯．．．这我可不清楚，你最好问问别人吧。\n",
	"$n想了一会儿，说道：对不起，你问的事我实在没有印象。\n",
	"$n冷冷地说道：我什么都不知道，你也不要再问了，就算我知道我也不会告诉你的。\n",
	"$n罗嗦地说道：你有事问我吗，你有事就问吧，你不问我我怎么知道你要问我什么呢。\n",
	"$n罗嗦地说道：你知不知道什么是铛铛铛铛铛铛？\n",
	"$n说道：你是个聪明人，我可以用聪明的方法跟人说话。外面的人就不行！\n"
});

int main(object me, string arg)
{
	string dest, topic, msg;
	object ob;
	mapping inquiry;

	seteuid(getuid());

	if( !arg || sscanf(arg, "%s about %s", dest, topic)!=2 )
		return notify_fail("你要问谁什么事？\n");

	if( !objectp(ob = present(dest, environment(me))) )
		return notify_fail("这里没有这个人。\n");

	if( !ob->is_character() ) {
		message_vision( YEL "$N对着$n自言自语．．．\n" NOR, me, ob);
		return 1;
	}

	if( !ob->query("can_speak") ) {
		message_vision("$N向$n打听有关『"+HIG"" + topic 
			+ ""+NOR"』的消息，但是$p显然听不懂人话。\n", me, ob);
		return 1;
	}

	if( !INQUIRY_D->parse_inquiry(me, ob, topic) )
		message_vision("$N向$n打听有关『"+HIG"" + topic + ""+NOR"』的消息。\n", me, ob);

		if(topic=="all")
			{
			message_vision( WHT "$N"NOR+WHT"对你悄声说道:"+query_inquiry(ob)+"!\n" NOR, ob);
			return 1;
		}
		if(topic=="news")
			{
			string str;
			str=read_file("/log/NEWS");
			message_vision( CYN "$N对你点了点头说到,最近听有人说过"+str+"" NOR, ob);
			return 1;
		}	
		if(topic=="here")
			{
			message_vision( CYN "$N对你悄声说道:这里就是"HIW+environment(me)->query("short")+NOR CYN",你没听说过吗？\n" NOR, ob);
			return 1;
		}
		if(topic=="name")
			{
			message_vision( CYN "$N说道：我的名字就是$N," + RANK_D->query_respect(me)+ "有什么事?\n" NOR, ob);
			return 1;
		}
	if( userp(ob) ) return 1;
	if( !living(ob) ) {
		message_vision("[1;37m但是很显然的，$n现在的状况没有办法给$N任何答覆。[2;37;0m\n",
			me, ob);
		return 1;
	}

	// by snowcat jan 23 1998
	  if ( msg = QUEST->quest_ask (me, ob, topic) ) {
		if( stringp(msg) ) {
			message_vision( WHT "$N说道：" + msg + "\n" NOR, ob);
			return 1;
		}
	}

	if( msg = ob->query("inquiry/" + topic) ) {
		if( stringp(msg) ) {
			message_vision( WHT "$N说道：" + msg + "\n" NOR, ob);
			return 1;
		}
	} else
		message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);
	return 1;
       } 
//从npc身上读取inquiry
string query_inquiry(object ob)
{
	int i=0;
	mapping inq;
	string str="", *indexs;
	
	if(mapp(inq=ob->query("inquiry")))
		{
		indexs=keys(inq);
		for(i=0;i<sizeof(indexs);i++)
			{
				str=indexs[i]+" "+str;
				}
		str="有关于 "NOR+HIR+str+NOR WHT"的事情,我很高兴告诉你!";
		return str;
		}
	return "实在是对不起,我什么也不知道呀!";
	}
int help(object me)
{
   write( @HELP
指令格式: ask <someone> about <something>

这个指令在解谜时很重要, 通常必须藉由此一指令才能
获得进一步的资讯。
预设的询问主题:
	here
	name
	news
	all
HELP
   );
   return 1;
}

