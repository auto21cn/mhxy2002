// CMDS USR news.c
// Created by kittt@DJX2000
// Last Modified by kittt@DJX 6/2/2000
// XKX 中玩家了解更新消息一般是用 Help Whatsnew
// 因此巫师在更新后需要编写/doc/help/文件，很不方便。
// 采用了这个新闻系统，发布更新消息只需像POST一样简单
// 也更有条理。玩家阅读起来也比较方便。
//By waiwai@2000/11/17 修正优化时间问题.加入色彩支持.
//Last modified by waiwai@2001/07/08 修正负数显示.
#include <ansi.h>;
#include <mudlib.h>
#include <command.h>
inherit BULLETIN_BOARD;

// create part和普通的BOARD差不多
void create()
{
set_name(HIY"梦幻西游新闻发布中心"NOR, ({ "newsboard"}) );
set("location", "/d/wiz/newsroom"); // 这里用了一个ROOM来放置BOARD，简单，你做 
set("board_id", "news_b");              // 成一个指令来输入新闻也可以。
setup();
set("capacity", 1000);//最大新闻存档数.自动减档数后面设定为 1/100
}

// 这个部份是用来在login时调用的。NEWS_D->check_news(user);
int check_news(object me)
{
int num,i,last_time_read;
mapping *notes, last_read_time;
string myid,msg="";

notes = query("notes");
last_read_time = me->query("board_last_read");
myid = query("board_id");

if( !pointerp(notes) || !sizeof(notes) ) return 1;

if(me->query("lastReadNews") < sizeof(notes))
i=sizeof(notes)-me->query("LastReadNews");
                write(HIG"\n从您上次阅读到现在"NOR+((i==0)? ""HIG"没有任何":""HIG"共有"+HIY+i+NOR+HIG"条")+HIG"新闻发布。(目前总共有 "HIR+sizeof(notes)+NOR+HIG" 条新闻)\n\n"NOR);
if(i>6) { 
write(HIY"\n━━━━━━━━━━━━━━━━━ "HIR"梦幻西游最新消息"HIY
" ━━━━━━━━━━━━━━━━\n\n"NOR); 
write(WHT"\t\t你可以用 "HIR"Help news "NOR WHT"来查看梦幻西游新闻系统的使用方法。\n\n"NOR); 
write(HIY"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n"NOR);
write(HBBLU HIY" 欢迎光临"+INTERMUD_NAME+"                           本站地址：qd.qdmud.com 6666\n\n"NOR);
} else
// if(userp(me)){
if( i <=6 && i>=1 ) {// 小于等于6条新闻才显示标题，不然会FLOOD
msg = HIY"\n━━━━━━━━━━━━━━━━━ "HIR"梦幻西游最新消息"HIY
" ━━━━━━━━━━━━━━━━   \n"NOR;

if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
num = 1;
else
for(num = 1; num<=sizeof(notes); num++)
if( notes[num-1]["time"] > last_read_time[myid] ) break;

if (mapp(last_read_time)) last_time_read = last_read_time[myid];
for(i=sizeof(notes)-1 ; i>num-2 ; i--) {
msg += sprintf("[%4d]"NOR,i+1);
msg += sprintf("     %-=35s %18s (%s)\n",
notes[i]["title"], notes[i]["author"],
                                 BJTIME_CMD->chinese_time(7, ctime(notes[i]["time"])));
}

msg += HIY"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  \n"NOR;
msg+=HBBLU HIY" 欢迎光临"+INTERMUD_NAME+"                           本站地址：qd.qdmud.com 6666 \n"NOR;
msg+=WHT"你可以用 "HIR"Help news "NOR WHT"来查看梦幻西游新闻系统的使用方法。\n\n"NOR;
me->start_more(msg);
}

// }
}

int main(object me, string arg)
{
int num,i,last_time_read;
mapping *notes, last_read_time;
string myid,msg;

last_read_time = me->query("board_last_read");
myid = query("board_id");
notes = query("notes");

i=sizeof(notes)-me->query("LastReadNews");

if( !pointerp(notes) || !sizeof(notes) )
return notify_fail("梦幻西游 目前没有任何新闻发布。\n"NOR);

if( !arg ) {
if(i>1 && !i<0 ) write("你可以"HIR" Help news "NOR"来查看梦幻西游新闻系统的使用方法。\n"); 
return notify_fail(
"梦幻西游 目前共有 "HIR+sizeof(notes)+NOR" 条新闻发布"+((i==0)? "。":"，您有 "HIY+
i++ +NOR" 条新闻尚未阅读。")+"\n"); }

if( arg=="all") {// 显示所有新闻
msg = HIB"\n\n ━━━━━━━━━━━━━━━━━ "HIW"梦幻西游新闻全览"HIB
" ━━━━━━━━━━━━━━━━━   \n"NOR;
notes = query("notes");

if (mapp(last_read_time)) last_time_read = last_read_time[myid];
for(i=sizeof(notes)-1 ; i>-1 ; i--) {
msg += sprintf("%s[%4d]" NOR,
notes[i]["time"] > last_time_read ? HIR"(未读)"NOR:WHT"(已读)"NOR, i+1);
msg += sprintf("     %-=30s %18s (%s)\n",
notes[i]["title"], notes[i]["author"],
                                   BJTIME_CMD->chinese_time(7, ctime(notes[i]["time"])));
}
msg += HIB" ━━━━━━━━━━━━━━━━━ "HIW"梦幻西游新闻全览"HIB
" ━━━━━━━━━━━━━━━━━   \n"NOR;
me->start_more(msg);
return 1;
}
else
if ( arg=="new" || arg=="next" ) { // 显示最新新闻
if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
num = 1;
else
for(num = 1; num<=sizeof(notes); num++)
if( notes[num-1]["time"] > last_read_time[myid] ) break;

} else if( !sscanf(arg, "%d", num) )

return notify_fail("你到底要看第几条新闻呀？\n");

if( num < 1 || num > sizeof(notes) )
return notify_fail("你已经看完了最新新闻了。\n");

num--;
me->start_more( sprintf("\n\n%s\n"HIR"新闻主题："HIY"%s\n"HIW"发布巫师：%s\n"HIG"新闻时间：%s\n"NOR

WHT"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"NOR,
BBLU HIG"「"HIC"梦幻西游"HIG"」第"+chinese_number(num + 1)+"条新闻 "NOR, 
COLOR_D->replace_color(notes[num]["title"],1), notes[num]["author"],
             BJTIME_CMD->chinese_time(1, ctime(notes[num]["time"])))
+ COLOR_D->replace_color(notes[num]["msg"],1)+NOR
     WHT"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"HIY"["HIC"梦幻西游"HIY"]\n"NOR, );

if( !mapp(last_read_time) )
me->set("board_last_read", ([ myid: notes[num]["time"] ]) );
else 
if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
last_read_time[myid] = notes[num]["time"];

if(me->query("LastReadNews") < num + 1)
me->set("LastReadNews",num+1);

return 1;
}

void init()
{
add_action("do_post", "post");
add_action("do_discard", "discard");
}

int do_post(string arg)
{
mapping note;
      object me;
      me = this_player();

if(!arg) return notify_fail("新闻要个加题目。\n");

       if(strlen(arg) > 20 ) return notify_fail("标题过长,请控制在10个中文字符以内！\n");

      if (wizardp(me) &&  wiz_level(me) < wiz_level("(admin)") )
          return notify_fail("你没有在这里增加新闻的权利。\n");//By waiwai@2001/07/08

      if(!wizardp(me)) 
          return notify_fail("只有巫师才可以在这里增加新闻。\n");//By waiwai@2001/07/08

note = allocate_mapping(4);
note["title"] = arg;
      note["author"] = this_player()->query("name")+"("+this_player()->query("id")+")";
note["id"] = this_player()->query("id"); 
this_player()->edit( (: done_post, this_player(), note :));
return 1;
}

void done_post(object me, mapping note, string text)
{
mapping *notes;

note["time"] = time();
note["msg"] = text;
notes = query("notes");
if( !pointerp(notes) || !sizeof(notes) )
notes = ({ note });
else
notes += ({ note });

if( sizeof(notes) > query("capacity"))
notes = notes[query("capacity")/100 .. query("capacity")];

set("notes", notes);
save();
restore();
// 使用channel显示提示有了最新新闻.为了能够更广泛的便于玩家知道.channel最好不要设定为chat.
message("channel:rumor", HIB"\n\t══════════════════════════════════════\n"NOR, users());
message("channel:rumor", HIC"\t  〓"HIB"☆"HIC"〓"HIG" ╠╣"BLINK+HBRED+HIW"梦幻西游"NOR+HIG"╠╣"HIM"有最新新闻发布！请用 "HIR"news new"HIM" 了解详细情况 "NOR HIC"〓"HIB"☆"HIC"〓"NOR, users());
message("channel:rumor", HIB"\n\t══════════════════════════════════════\n\n"NOR, users());

tell_object(me, HIY"新闻成功发表完毕。\n"NOR);

return;
}

int help(object me)
{
   write(@HELP

「梦幻西游」新闻系统指令 

指令格式 :
news                    查看共有的和最新发布的新闻。
news all                梦幻西游新闻一览。 
news new                阅读最新的新闻。 
news next               阅读最新的新闻。 
news <新闻编号>         查看此编号新闻的详细内容。 

HELP
   );
   return 1;
}



 