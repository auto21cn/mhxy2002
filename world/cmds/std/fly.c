//by tianlin@mhxy for 2001.9.30
//从新改写,请不要抄!

#include <ansi.h>

int main(object me, string arg)
{
	string loc;
        int mana_cost;
	object ridee, map;
	string ridemsg;

        seteuid(getuid());

        if( me->is_fighting() )
                return notify_fail("你正在战斗，飞不开。\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
                return notify_fail("你正忙着呢，没工夫腾云驾雾。\n");
	if( !wizardp(me) && !environment(me)->query("outdoors") )
		return notify_fail("周围没有一片云，没办法腾云驾雾。\n");
	if( me->is_ghost() )
		return notify_fail("[34m做了鬼了，就老实点吧！[2;37;0m\n");
        if( !arg )
                return notify_fail("你要飞到哪里去？\n");
	if( me->query_temp("no_move") )
	    return notify_fail("你被定住了，哪里飞得起来！\n");

	if( RANK_D->grade_dx( RANK_D->describe_dx( (int)me->query("daoxing") ) ) 
		< RANK_D->grade_dx(BLU "初领妙道" NOR) )
	{
		message_vision(HIY
"$N奋力望上一跳，似乎想飞起来。结果离地不到三尺就一个倒栽葱摔了下来。\n"
NOR, me);
		return notify_fail("你现在还初领妙道都谈不上，哪里飞得起来。\n");
	}

	if( RANK_D->grade_fali( RANK_D->describe_fali( (int)me->query("max_mana") ) ) 
		< RANK_D->grade_fali(HIB "腾云驾雾" NOR) )
	{
		message_vision(HIY
"$N奋力望上一跳，似乎想飞起来。结果离地不到三尺就一个倒栽葱摔了下来。\n"
NOR, me);
		return notify_fail("看来以你的法力修为还不能腾云驾雾。\n");
	}

	if( (int)me->query("mana") < 200 )
	{
		message_vision(HIY
"$N奋力望上一跳，似乎想飞起来。结果离地不到三尺就一个倒栽葱摔了下来。\n"
NOR, me);
		return notify_fail("你目前法力不够充盈。\n");
	}


        if( (int)me->query("sen") * 100 / (int)me->query("max_sen") < 50 )
                return
notify_fail("你现在头脑不太清醒，当心掉下来摔死。\n");

        if( (int)me->query("kee") * 100 / (int)me->query("max_kee") < 50 )
                return
notify_fail("你想飞起来，可是体力似乎有点不支。\n");

        mana_cost=-(100-(int)me->query_skill("spells"))/4-40;
        if(mana_cost > 0) mana_cost=0;

          if( (string)me->query("family/family_name") == "陷空山无底洞") {
                  message_vision(HIB"只见平地里忽然刮起一阵阴风，将$N紧紧裹住，\n"+
  "顷刻间$N随风而去，消失得无影无踪。 \n\n"NOR, me);
}
           if( (string)me->query("family/family_name") == "将军府") {
      message_vision(HIY"$N用手轻轻一指，只见天上降下一朵五彩祥云，\n"+
"$N纵身跃上，乘祥云飘摇而去......\n\n"NOR, me);
}
        if( (string)me->query("family/family_name") == "阎罗地府") {
                message_vision(CYN"$N往黑暗处一指，只见所指之处仿佛出现一扇门，\n"+
"$N大步走入，门也随之消失。 \n\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "方寸山三星洞") {
                message_vision(HIG"$N捻个口诀，口中念动真言，大叫一声：“筋斗云！”，\n"+
"只见天上降下一朵七色云彩，$N纵身跃上，飞驰而去......\n\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "月宫") {
                message_vision(HIM"$N妩媚一笑，欣然起舞，随着一阵花香，已消失在月光中。\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "武圣门") {
                message_vision(HIY"$N双臂交叉，默念几句咒语，一道光柱从天而降，$N已消失在光柱中。\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "五庄观") {
                message_vision(HIB"$N大袖一摆，只见风起云涌，人已借风云之势在空中大步迈去。\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "大雪山") {
                message_vision(HIW"$N随手一挥，只见一团雪雾裹住真身，旋转而去。 \n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "南海普陀山") {
                message_vision(HIY"$N口中念着佛号，脚下升起祥云，缓缓离地飞去。  \n"NOR, me);
              }
        if( (string)me->query("title/title_name") =="普通百姓") {
                message_vision(BLU"$N仰天大叫:“六丁六甲,诸天神邸送我一程”.一阵阴风吹过,$N消失的无影无踪....\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="灵界") {
                message_vision(MAG"$N随手掏出根白羽,轻轻挥手间,白云已走远,带走了一片回忆，留下了无边的寂寞..\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="魔教") {
                message_vision(RED"“天魔无形，地魔无影，人魔无踪”，几句咒语念完，$N化为一道"NOR+HIR"火光"NOR+RED"冲出人间..\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="天空界") {
                message_vision(HIB"$N信手掷出自己的守护兽，跃上守护兽的后背，窜霄而去！\n"NOR, me);
        }
        if( (string)me->query("family/family_name") == "东海龙宫") {
                message_vision(HIC"$N摇身一变，现出原形，正是一条神龙，随即穿云而去。 \n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "火云洞") {
              message_vision(RED"$N口捻个口诀，口中念动真言,突然“轰”地冒起一团红雾,$N随即隐入红雾中。\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "乱石山碧波潭") {
              message_vision(CYN"$N摇身一变，现出原形，正是一条神龙，随即穿云而去。 \n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "天蓬帅府") {
              message_vision(WHT"$N口中大喊一声: 猪无能. . .接着你踏起一团"HIR"七"HIM"彩"HIC"祥"HIY"云"NOR WHT"飞向天际。 \n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "武当派") {
              message_vision(HBRED+HIW"$N口中念了几句口诀,来了一招"NOR+HBBLU HIY"“太极十三式”"NOR+HBRED+HIW",缓缓的离去..... \n"NOR, me);//By tianlin@mhxy for 2001.9.30制作
              }
        if( (string)me->query("family/family_name") == "神剑山庄") {
              message_vision(WHT"$N口中念了几句口诀,只见天上飞来无数的剑雨把你给卷了进去.\n"NOR, me);//By tianlin@mhxy for 2001.12.14制作
              }
        if( (string)me->query("family/family_name") == "少林寺") {
              message_vision(WHT"$N口中大喊一声: 猪无能. . .接着你踏起一团"HIR"七"HIM"彩"HIC"祥"HIY"云"NOR WHT"飞向天际。 \n"NOR, me);
              }
         if( (string)me->query("family/family_name") == "蜀山派") {
             message_vision(HIC"$N口捻个口诀，扔出一把宝剑，$N飞驰而上，一招「御剑飞行」向远方飞去。。。。\n"NOR, me);
              }
        if( (string)me->query("family/family_name") == "盘丝洞") {
             message_vision(MAG"$N皓腕轻抖，但见一道彩虹落了下来,$N纤腰轻摆飘然而上,霞光一闪,彩虹消失的无影无踪。\n"NOR, me);
              }
        if((string)me->guery("family/family_name") == "江湖浪子"){
             message_vision(HBYEL+HIB" $N身型一变，口中大喊一声 飞仙 ，$N跟随着自己的这股气道，在茫茫人海消失的不留痕迹。\n"NOR, me); 
              }

        me->add("mana", mana_cost);

        if(arg=="stone") loc="/d/dntg/hgs/entrance";
        else if(arg=="kaifeng") loc="/d/kaifeng/tieta";
        else if(arg=="moon") loc="/d/moon/ontop2";
        else if(arg=="lingtai") loc="/d/lingtai/gate";
        else if(arg=="putuo") loc="/d/nanhai/gate";
        else if(arg=="changan") loc="/d/city/center";
        else if(arg=="sky") loc="/d/dntg/sky/nantian";
	 else if(arg=="wuzhuang") loc="/d/qujing/wuzhuang/gate";
	 else if(arg=="meishan") loc="/d/meishan/erlangwai";
        else if(arg=="wudang") loc="/d/wudang/xuanyuegate";
        else if(arg=="lingjie") loc="/d/lingjie/rukou";
//        else if(arg=="shenjian") loc="/d/shenjian/wuc";
        else if(arg=="shaolin") loc="/d/southern/shaolin/simen";//by tianlin@mhxy for 2001.9.27修改
        else if(arg=="wudangshan") loc="/d/wudang1/guangchang";//by tianlin@mhxy for 2001.9.25加入wudang派
        else if(arg=="33tian") loc="/d/33tian/33tian";//by tianlin 2001.7.1
      else if(arg=="shushan") loc="/d/shushan/shanmen";
              else if(arg=="penglai") {
		if(!(map=present("eastsea map", me)) && !wizardp(me)) {
			write("你在天上转了半天也不知该往那边飞。。。\n");
			message_vision("\n$N失望地从云上跳了下来！\n", me);
			return 1;
			}
		if( !wizardp(me)&&(string)map->query("unit")!="张" ){
			write("你在天上转了半天也不知该往那边飞。。。\n");
                        message_vision("\n$N失望地从云上跳了下来！\n", me);
                        return 1;
                        }
//		write("你驾着祥云向东边海中飞去。。。\n\n");
		loc="/d/penglai/penglai";
	}
//by tianlin 2001.7.17加以修改xueshan的fly xueshan不用map
	else if(arg=="xueshan") {
		if(!(map=present("xueshan map", me)) &&(string)me->query("family/family_name")!="大雪山"&& !wizardp(me)){
			write("你在天上转了半天也不知该往那边飞。。。\n");
			message_vision("\n$N失望地从云上跳了下来！\n", me);
			return 1;
			}
		if( !wizardp(me)&&(string)me->query("family/family_name")!="大雪山"&&(string)map->query("unit")!="张" ){
                        write("你在天上转了半天也不知该往那边飞。。。\n");
                        message_vision("\n$N失望地从云上跳了下来！\n", me);
                        return 1;
                        }
		loc="/d/xueshan/binggu";
	}
//By tianlin@mhxy for 2002.1.10,制作只有shenjian的弟子可以fly shenjian
	else if(arg=="shenjian") {
		if((string)me->query("family/family_name")!="神剑山庄"&& !wizardp(me)){
			write(HIC"你在天空中想了又想，可是忘了去神剑山庄的路了!\n"NOR);
			message_vision(HIY"\n$N从云上跳了下了,非常失望！\n"NOR, me);
			return 1;
			}
		if( !wizardp(me)&&(string)me->query("family/family_name")!="神剑山庄"){
                        write("你在天上转了半天也不知该往那边飞。。。\n");
                        message_vision("\n$N失望地从云上跳了下来！\n", me);
                        return 1;
                        }
		loc="/d/shenjian/wuc";
	}
	else if(arg=="wusheng"){
		loc = "/d/wusheng/room1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}
	else if(arg=="baoxiang"){
		loc = "/d/qujing/baoxiang/bei1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}else if(arg=="pingding"){
		loc = "/d/qujing/pingding/ping1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}else if(arg=="yalong"){
		loc = "/d/qujing/pingding/yalong1.c";
		loc[strlen(loc)-3] = '1'+random(3);
	}else if(arg=="wuji"){
		loc = "/d/qujing/wuji/square.c";
		//loc[strlen(loc)-3] = '1'+random(9);
	}else if(arg=="chechi"){
		loc = "/d/qujing/chechi/jieshi1.c";
		loc[strlen(loc)-3] = '1'+random(9);
	}else if(arg=="tongtian"){
		loc = "/d/qujing/tongtian/hedong1.c";
		loc[strlen(loc)-3] = '1'+random(6);
	}else if(arg=="jindou"){
		loc = "/d/qujing/jindou/jindou1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}else if(arg=="nuerguo"){
		loc = "/d/qujing/nuerguo/towna1.c";
		/*
		if (me->query("obstacle/nuerguo")!="done" && !wizardp(me)){
			write("\n一阵风把你东倒西歪地吹了回来！\n");
			write("看样子飞不过去。\n");
			return 1;
			}
		*/
		loc[strlen(loc)-4] = 'a'+random(3);
		loc[strlen(loc)-3] = '1'+random(3);
	}else if(arg=="dudi"){
		loc = "/d/qujing/dudi/dudi1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}else if(arg=="huangfeng"){
                loc = "/d/qujing/huangfeng/huangfeng1.c";
		loc[strlen(loc)-3] = '1'+random(7);
        }else if(arg=="baigudong"){
                loc = "/d/qujing/baigudong/sroad1.c";
                loc[strlen(loc)-3] = '1'+random(6);
       }else if(arg=="shuangcha"){
		loc = "/d/qujing/shuangcha/shanlu1.c";
		loc[strlen(loc)-3] = '1'+random(5); 
       }else if(arg=="liusha"){
         	loc = "/d/qujing/liusha/river.c";
       }else if(arg=="heifeng"){
		loc = "/d/qujing/heifeng/road1.c";
		loc[strlen(loc)-3] = '1'+random(4);
       }else if(arg=="yingjian"){
		loc = "/d/qujing/yingjian/xiaolu1.c";
		loc[strlen(loc)-3] = '1'+random(4); 
        }else if(arg=="firemount"){
         	loc = "/d/qujing/firemount/cuiyun1.c";
		loc[strlen(loc)-3] = '1'+random(5);
	}else if(arg=="jilei"){
		loc = "/d/qujing/jilei/jilei1.c";
		loc[strlen(loc)-3] = '1'+random(3);
	}else if(arg=="jisaiguo"){
		loc = "/d/qujing/jisaiguo/east1.c";
		loc[strlen(loc)-3] = '1'+random(4);
	}else if(arg=="jingjiling"){
		loc = "/d/qujing/jingjiling/jingji1.c";
	}else if(arg=="xiaoxitian"){
		loc = "/d/qujing/xiaoxitian/simen.c";
        }else if(arg=="zhuzi"){
         	loc = "/d/qujing/zhuzi/zhuzi1.c";
		loc[strlen(loc)-3] = '1'+random(5);
        }else if(arg=="qilin"){
         	loc = "/d/qujing/qilin/yutai.c";
        }else if(arg=="pansi"){
         	loc = "/d/qujing/pansi/ling1.c";
		loc[strlen(loc)-3] = '1'+random(6);
        }else if(arg=="biqiu"){
         	loc = "/d/qujing/biqiu/jie1.c";
		loc[strlen(loc)-3] = '1'+random(9);
        }else if(arg=="qinghua"){
         	loc = "/d/qujing/biqiu/zhuang.c";
	}else if(arg=="wudidong"){
		loc = "/d/qujing/wudidong/firemount-wudidong3.c";
		loc[strlen(loc)-3] = '1'+random(3);
        }else if(arg=="qinfa"){
         	loc = "/d/qujing/qinfa/jiedao1.c";
		loc[strlen(loc)-3] = '1'+random(8);
        }else if(arg=="yinwu"){
         	loc = "/d/qujing/yinwu/huangye1.c";
        }else if(arg=="fengxian"){
         	loc = "/d/qujing/fengxian/jiedao1.c";
		loc[strlen(loc)-3] = '1'+random(9);
        }else if(arg=="yuhua"){
         	loc = "/d/qujing/yuhua/xiaojie1.c";
		loc[strlen(loc)-3] = '1'+random(9);
        }else if(arg=="baotou"){
         	loc = "/d/qujing/baotou/shanlu1.c";
		loc[strlen(loc)-3] = '1'+random(9);
        }else if(arg=="zhujie"){
         	loc = "/d/qujing/zhujie/shanlu11.c";
		loc[strlen(loc)-3] = '1'+random(8);
        }else if(arg=="jinping"){
         	loc = "/d/qujing/jinping/xiaojie1.c";
		loc[strlen(loc)-3] = '1'+random(7);
        }else if(arg=="qinglong"){
         	loc = "/d/qujing/qinglong/shanjian.c";
        }else if(arg=="tianzhu"){
         	loc = "/d/qujing/tianzhu/jiedao11.c";
		loc[strlen(loc)-3] = '1'+random(8);
        }else if(arg=="maoying"){
         	loc = "/d/qujing/maoying/shanpo1.c";
		loc[strlen(loc)-3] = '1'+random(9);
        }else if(arg=="lingshan"){
         	loc = "/d/qujing/lingshan/dalu1.c";
		loc[strlen(loc)-3] = '1'+random(3);
        }else{
                write("\n\n到了！你按下云头跳了下来。\n");
                write("咦？．．．怎么还在原来的地方？\n");
                return 1;
        }

	if (! loc)
		return 1;
		
	// mon /10/18/98
	if(MISC_D->random_capture(me,0,1)) return 1;

	if (ridee = me->ride()) {
	  ridemsg = ridee->query("ride/msg")+"着"+ridee->name();
	  ridee->move(loc);
	}  
	else  
	  ridemsg = "";
	                                            	
	me->move(loc);
       write("\n\n到了！你按下云头跳了下来。\n");

          if( (string)me->query("family/family_name") == "陷空山无底洞") {
message_vision(HIB"\n忽然间刮起一阵阴风，风尽处，$N走了出来。 \n"
  NOR, me);
}
           if( (string)me->query("family/family_name") == "将军府") {
   message_vision(HIY"\n只见空中飘落一朵五彩祥云，$N拨开云端走了出来。 \n"
  NOR, me);
}
        if( (string)me->query("family/family_name")=="阎罗地府") {
                message_vision(CYN"\n阴影中吹起一阵冷风，伴随着冷森森的笑声，$N"+ridemsg+"如魑魅般从黑暗中出现。 \n"
NOR, me);

        }
            if( (string)me->query("family/family_name")=="方寸山三星洞") {
                message_vision(HIG"\n只听见天上传来一声：“俺来也！”，人随声到，$N"+ridemsg+"从筋斗云中冉冉落下。\n"
NOR, me);
            }
            if( (string)me->query("family/family_name")=="月宫") {
                message_vision(HIM"\n只见一道月光洒在你面前，柔柔的，冷冷的，$N"+ridemsg+"从中飘然而至。 \n"
NOR, me);
        }
            if( (string)me->query("family/family_name")=="五庄观") {
                message_vision(HIB"\n一阵清风吹来，$N"+ridemsg+"从空中降落。 \n"
NOR, me);
        }
            if( (string)me->query("family/family_name")=="大雪山") {
                message_vision(HIW"\n霎时间，大雪纷飞，$N"+ridemsg+"亦如晶莹剔透的雪花随风飘下。 \n"
 NOR, me);
        }
            if( (string)me->query("family/family_name")=="南海普陀山") {

                message_vision(HIY"\n一声洪亮的“南无阿弥陀佛”，$N"+ridemsg+"从佛光中，祥云里走出。 \n"
NOR, me);
        }
        if( (string)me->query("title/title_name") =="普通百姓") {
                message_vision(BLU"阴风过处,$N现了出来.......\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="灵界") {
                message_vision(MAG"微风阵阵,$N"+ridemsg+"手持一把混元霹雳珍珠伞迈步走了出来，带着一丝惆怅与孤寂..........\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="魔教") {
                message_vision(RED"一道"+HIR"火光"NOR+RED"$N"+ridemsg+"凭空出现，细看竟然化成一个人形...\n"NOR, me);
        }
        if( (string)me->query("family/family_name") =="天空界") {
                message_vision(HIB"一阵呼啸声过后，$N"+ridemsg+"从天空界的守护神兽背上纵身跳下..... \n"NOR, me);
        }
            if( (string)me->query("family/family_name")=="东海龙宫") {
                message_vision(HIC"\n半空中仿佛冲出一条水柱，$N"+ridemsg+"从水柱上稳稳跳落地下。  \n"
NOR, me);
        }
            if( (string)me->query("family/family_name")=="火云洞") {
                message_vision(RED"\n一团红色的烟雾涌了过来,$N"+ridemsg+"突然从里面蹦了出来. \n"
NOR, me);
        }
        if( (string)me->query("family/family_name") == "乱石山碧波潭") {
              message_vision(CYN"\n半空中仿佛冲出一条水柱，$N"+ridemsg+"从水柱上稳稳跳落地下。  \n"
NOR, me);
              }
        if( (string)me->query("family/family_name") == "天蓬帅府") {
              message_vision(WHT"\n云彩出现在天际，$N"+ridemsg+"一个纵身跳了下来。  \n"
NOR, me);
              }
        if( (string)me->query("family/family_name") == "武当派") {
              message_vision(HBRED HIW"\n突然天气大变，$N"+ridemsg+"慢慢走了过来。  \n"
NOR, me);
              }
        if( (string)me->query("family/family_name") == "神剑山庄") {
              message_vision(WHT"\n突然天空中出现无数剑雨，$N"+ridemsg+"从剑雨中走了过来。  \n"
NOR, me);
              }
        if( (string)me->query("family/family_name") == "少林寺") {
              message_vision(WHT"\n云彩出现在天际，$N"+ridemsg+"一个纵身跳了下来。  \n"
NOR, me);
              }
            if( (string)me->query("family/family_name")=="蜀山派") {
                message_vision(HIC"\n一道蓝光闪过,$N"+ridemsg+"从剑上跳了下来。 \n"
NOR, me);
        }        
            if( (string)me->query("family/family_name") == "盘丝洞") {
                message_vision(MAG"\n但见一道彩虹从天空划过，$N"+ridemsg+"随彩虹飘然而至。 \n"
NOR, me);
        }
            if( (string)me->query("family/family_name") == "武圣门") {
                message_vision(HIY"\n只听空中一声清啸，$N"+ridemsg+"随一朵祥云飘然而至。 \n"
NOR, me);
        }
            if( (string)me->query("family/family_name") == "江湖浪子"){
                message_vision(HBYEL+HIB"\n天空中盘旋着九条金龙，$N"+ridemsg+"从云雾中一冲而出。\n"NOR, me);
        }
                 return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : fly|fei [目的地]

当你的道行和法力高强时，你可以腾云驾雾。

目前你可以飞到的地方：
[33mchangan[2;37;0m         ->[37m长安城                 [33mkaifeng[2;37;0m        ->[37m开封城
[33mstone[2;37;0m           ->[37m花果山仙石             [33msky[2;37;0m            ->[37m南天门
[33mmoon[2;37;0m      	->[37m昆仑山月宫             [33mpenglai[2;37;0m        ->[37m蓬莱仙岛
[33mlingtai[2;37;0m         ->[37m灵台方寸山    	 [33mputuo[2;37;0m     	->[37m南海普陀山
[33mxueshan[2;37;0m	        ->[37m大雪山寒冰谷           [33mmeishan[2;37;0m        ->[37m梅山灌江口
[33mwuzhuang[2;37;0m        ->[37m万寿山五庄观           [33mshushan[2;37;0m        ->[1;32m万剑之尊蜀山[2;37;0m
[33mwusheng[2;37;0m	        ->[37m武圣门                 [33m33tian[2;37;0m           ->[37m兜率宫
[33mlingjie[2;37;0m	        ->[37m灵界                 


[33mbaoxiang[2;37;0m	->[37m宝象国		 [33mpingding[2;37;0m  	->[37m平顶山
[33myalong[2;37;0m    	->[37m压龙山 		 [33mwuji[2;37;0m           ->[37m乌鸡国
[33mchechi[2;37;0m		->[37m车迟国 		 [33mtongtian[2;37;0m	->[37m通天河
[33mjindou[2;37;0m  	->[37m金兜山 		 [33mnuerguo[2;37;0m	->[37m女儿国
[33mdudi[2;37;0m   		->[37m毒敌山 		 [33mfiremount[2;37;0m	->[37m火焰山
[33mjilei[2;37;0m    	->[37m积雷山 		 [33mjisaiguo[2;37;0m	->[37m祭赛国
[33mjingjiling[2;37;0m	->[37m荆棘岭		 [33mxiaoxitian[2;37;0m	->[37m小西天
[33mzhuzi[2;37;0m		->[37m朱紫国		 [33mqilin[2;37;0m		->[37m麒麟山
[33mpansi[2;37;0m		->[37m盘丝岭		 [33mbiqiu[2;37;0m		->[37m比丘国 
[33mqinghua[2;37;0m		->[37m清华庄		 [33mwudidong[2;37;0m       ->[37m无底洞
[33mqinfa[2;37;0m           ->[37m钦法国		 [33mfengxian[2;37;0m	->[37m凤仙郡 
[33myinwu[2;37;0m    	->[37m隐雾山		 [33myuhua[2;37;0m   	->[37m玉华县 
[33mbaotou[2;37;0m  	->[37m豹头山		 [33mzhujie[2;37;0m  	->[37m竹节山
[33mjinping[2;37;0m 	->[37m金平府		 [33mqinglong[2;37;0m	->[37m青龙山 
[33mtianzhu[2;37;0m 	->[37m天竺国		 [33mmaoying[2;37;0m 	->[37m毛颖山 
[33mlingshan[2;37;0m	->[37m灵山                   [33mbaigudong[2;37;0m      ->[1;31m白骨洞[2;37;0m   
[33mhuangfeng[2;37;0m       ->[1;31m黄风洞[2;37;0m                 [33mshuangcha[2;37;0m      ->[1;31m双叉岭[2;37;0m
[33myingjian[2;37;0m        ->[1;31m鹰愁涧[2;37;0m                 [33mheifeng[2;37;0m        ->[1;31m黑风山[2;37;0m
[33mliusha[2;37;0m          ->[1;31m流沙河[2;37;0m                 




HELP
        );
        return 1;
}

