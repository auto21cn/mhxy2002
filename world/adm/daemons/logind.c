//By tianlin@MHXY 2001.5.1
//BY tianlin@mhxy for 2002.1.9,�޸�1��bug
// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <mudlib.h>     // for GB_AND_BIG5 define.

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
int mad_lock = 0;
int dienpc = 0;            // add by xhm 2000.11.13  �ƽٲ�������������
string *banned_name = ({
	"��", "��", "��", "��", "��", "��", "������", "��Сƽ", "����", "���Ż�",
	"�Լ�", "ĳ��", "ʬ��", "����","����", "����", "���",
	"�����", "ȥ���", "ë��", "��ʦ", "�����̵�","����","��","�Ž���","�Ž�",
       "��","��","����","��","�","��","��",
});

string *default_name=({"����","����", "����", 
	               "����","�׳�","����","����",
		       "���","ư��","�ȳ�","��",
			"ţ", "�ϻ�", "����",
			"��","è��","��","��",
			"����","�ڹ�","��","���",
			"¹","��","Ϭţ"});
string *default_prefix=({"С","��","��","��","��","��","��","��",
	"ֽ","ľͷ","ʯͷ","��"});


void logind_user_log(); // mon 11/5/98
int total_count;
int howmany_user();
private void encoding(string arg, object ob);
private void if_young(string arg, object ob);
private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
int check_legal_superpasswd(object ob,string arg);//by tianlin@mhxy.2001.6.3д��
string dis_attr(int value);
private void confirm_gift(string yn,object ob,object user);
private void judge_freeze(object ob); //����ԭ�� �����ж��˺��Ƿ񱻶���
int howmany_user()
{
	int i,j,reg_cnt;
	string *dir , *ppls, name;
	mixed info;
	seteuid(getuid());
	reg_cnt=0;
	dir=get_dir(DATA_DIR+"login/");
	for(i=0; i<sizeof(dir);i++)	{
		reset_eval_cost();
		ppls=get_dir(DATA_DIR+"login/"+dir[i]+"/");
		reg_cnt+=sizeof(ppls);
	}
	return reg_cnt;
}
void create() 
{
	seteuid(getuid());
	set("channel_id", "���߾���");
        set("id", "logind");
}

// mon 11/7/98
void logind_user_log()
{
    int user=sizeof(users());
    int total;

    remove_call_out("logind_user_log");
    rm("/log/user_count");    log_file("user_count",""+
            ((total=total_count)?total:user)+"\n"+
            user+"\n"+
            UPTIME_CMD->report_str()+"\n"+
            "�λ�����\n");
    call_out("logind_user_log",600);
}

// added by snowcat Mar 11 1998


void logon(object ob)
{

#ifdef GB_AND_BIG5
   switch ( random(6))
    {
   case 0:
   cat(BANNER);
   break;
   case 1:
   cat(BANNER1);
   break;
   case 2:
   cat(BANNER2);
   break;
   case 3:
   cat(BANNER3);
   break;
   case 4:
   cat(BANNER4);
   break;
   case 5:
   cat(BANNER5);
   break;
   }
// by tianlin 2001.5.1,�������е���,�������þ����˶԰�,�Ǻ�.
//By tianlin@mhxy for 2002.1.20,�ٴθ���
    write("            �λ����λ�ӭ�����ã�ʹ�ù�������������룺[1;38mgb[0;37;0m\n");
    write("               ���O�w��z�ӳX��  �� ���X�a���䣺[1;33mbig5[0;37;0m\n\n");
    write("    [[45m[1;33mIf there is no response after ENTER, please try Ctrl-ENTER[2;37;0m]\n");
    write("        [[1;31m��ʾ��[0;37;0m[41m[1;33m�����ENTER����ϵͳû����Ӧ������ Ctrl-ENTER[2;37;0m]\n\n");
    write("             Welcome to MHXY! Select GB or BIG5 ([1;31mgb[0;37;0m/[1;33mbig5[0;37;0m):");
    input_to( (: encoding :), ob );
#else
    encoding("gb",ob);
#endif

}

private void encoding(string arg, object ob)
{
	object *usr;
	int i, ttl_cnt, wiz_cnt, ppl_cnt, login_cnt, max_online,avg_online;
	int ip_cnt,wiz_cnt2;
	string ip_name, nowtime, ip_number, online_num;
	string ip_from;
 	int ii;
        mixed info;
	int encode;
	

	if(!arg || arg=="") {
	    write("\nSelect ������ GB or �j���X BIG5 ("HIR"gb"NOR"/"HIY"big5"NOR"):");
	    input_to( (: encoding :), ob );
	    return;
	} else if(arg[0..0]=="g" || arg[0..0]=="G")
	    encode=0;
	else if(arg[0..0]=="b" || arg[0..0]=="B")
	    encode=1;
	else {
	    write("\nSelect ������ GB or �j���X BIG5 ("HIR"gb"NOR"/"HIY"big5"NOR"):");
	    input_to( (: encoding :), ob );
	    return;
	}
	
	ob->set_encoding(encode);

	ip_name = query_ip_name(ob);
	ip_number = query_ip_number(ob);



// snowcat dec 10 1997
// try strict ban here...weiqi.

	if ("/adm/daemons/band"->is_strict_banned(query_ip_number(ob)) == 1) {
	   	write(HIR"���ĵ�ַ�ڱ� MUD ֮���������ƻ��ˡ�\n��E-mail��tianlin,��ַtianlin-mhxy@163.com��\n"NOR);
	   	destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, strict_banned\n"));
	   	return;
	}

	
	// try not accept "name" as IP

	if (!ip_name) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, No IP\n"));
		return;
	}

	for(ii=0; ii<sizeof(ip_number); ii++) {
		if( (ip_number[ii] != '.')&&(ip_number[ii]>'9') ){
			destruct(ob);
			log_file( "ALLCONT", sprintf("kicked out, Non_number\n"));
			return;
		}
	}
	
	write(CLR);
	cat(WELCOME);
	UPTIME_CMD->report();

	// children will show both netdead and interactive users.
	usr = children(USER_OB);
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
/*
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( (wizardp(usr[i]) && (string)wizhood(usr[i])!="(elder)")&& !usr[i]->query("env/invisibility") ) wiz_cnt++;
		else ppl_cnt++;
	}
*/
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) )
		{
			login_cnt++;
		}
		else
		{
			wiz_cnt2 = (int)usr[i]->query("env/invisibility");
			if ( ( !intp(wiz_cnt2)
			|| ( intp(wiz_cnt2) && (wiz_cnt2 <= 0) ) )
			&& !usr[i]->is_ghost() )
			{
			     if ( query_ip_name(ob) == query_ip_name(usr[i]) ) ip_cnt++;
                                 if (ip_cnt >= 40){
		  write("�������������������̫���ˣ��������������ܾ�����һ��ʱ�䡣\n");
		  destruct(ob);
		      return;}
				if ( wizardp(usr[i]) )
				{
					wiz_cnt++;
				}
				else
				{
					ppl_cnt++;
				}
			}
		}
	}
        max_online = atoi(read_file(__DIR__"maxonline",1));
	avg_online = atoi(read_file(__DIR__"avguser",1));
	if(ppl_cnt > max_online)
	   {
	   	online_num = sprintf("%d",ppl_cnt);
	   	write_file(__DIR__"maxonline",online_num,1);
	   }
	printf("�λ�����(�ൺվ)����ע�����"HIY"%s"NOR"λ��\n",chinese_number(howmany_user()));
       write("�λ�����(�ൺվ)���֧������:"HBRED WHT+chinese_number(MAX_USERS)+NOR"�ˡ�\n");
	printf("�λ�����(�ൺվ)��"HIY"[2002]"NOR+HIW"��"NOR+HIG"[1]"NOR+HIW"��"NOR+HIC"[15]"NOR+HIW"��[2;37;0m����������������ߣ�"HIR"%s"NOR" �ˣ�ƽ�����ߣ�"HIY"%s"NOR" �ˡ�\n",chinese_number(max_online),chinese_number(avg_online));
	printf("Ŀǰ����"HIR"%s"NOR"λ������Ա��"HIC"%s"NOR"λ��ң��Լ�"HIG"%s"NOR"λʹ�����ڳ������ߡ�\n\n",
		chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) );
//By tianlin@Mhxy for 2001.12.30
       nowtime = BJTIME_D->chinese_time(1, time());
       printf(HIG"����ʱ��:"NOR" %s \n"NOR,nowtime);
//BY tianlin@mhxy for 2001.12.27
	      	ip_from="/adm/daemons/ipd"->seek_ip_address(query_ip_number(ob));
	printf("���� IP ��ַ��"HIY"%s"NOR",�˵�ַĿǰ����"HIC" %d "NOR"���������,������: "HIG"%s"NOR" \n",query_ip_number(ob),ip_cnt, ip_from);
     if(file_size("/log/static/shutdown")>0 ) write("�λ�����("HIR"����ԭ��"NOR")��" + read_file("/log/static/shutdown"));//by tianlin 2001.7.5.����shutdown����
	// mon 11/7/98
	//check whether user_log still running.
	info = filter_array(call_out_info(), (: $1[1]=="logind_user_log" :));
	if(!sizeof(info)) logind_user_log();


      /* move this check to after user input id.
	 
// mon 4/19/98
// reduce number of pending login users.
#ifdef MAX_USERS
	if(sizeof(usr)>(MAX_USERS+10)) {
	    write("�Բ���"+MUD_NAME+"������Ѿ�̫���ˣ�������������\n");
	    destruct(ob);
	    return;
	}
#endif


*/
	if (ob) ob->set_temp("id_count",0);
	//mon 10/15/97 to prevent flooding illegal ID after login.

#ifndef GB_AND_BIG5
#endif
        
	//we do not welcome young kid playing mud. weiqi...971220.
	write("����ѧ������Ҫ������ѧϰ������Ϸ����ӭ��Сѧ�����档\n");
	write("���Ƿ�����Сѧѧ���������С��("HIR"yes"NOR"/"HIY"no"NOR")");
	input_to( (: if_young :), ob );
}

private void if_young(string arg, object ob)
{
        int id_count;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id.
        id_count++;
        ob->set_temp("id_count",id_count);
        if(id_count>3) {
          destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
          return;
        }

        if(arg=="\n" || arg=="") {
	    write("���Ƿ�����Сѧѧ���������С��([1;31myes[2;37;0m/[1;33mno[2;37;0m)");
	    input_to( (: if_young :), ob );
	    return;
	}

	if( arg[0..0] == "y" || arg[0..0] == "Y" )
	{
		write("\n[5m[1;36m�ã��Ͻ�ȥѧϰ������������[2;37;0m\n");
		destruct(ob);
		return;
	}

	if( arg[0..0] != "n" && arg[0..0] != "N" ) {
	    write("���Ƿ�����Сѧѧ���������С��([1;31myes[2;37;0m/[1;33mno[2;37;0m)");
	    input_to( (: if_young :), ob );
	    return;
	}

	cat(XYJ_SITES);
	write("\n����Ӣ�����֣������������� [1;31mnew[0;37;0m ע�ᣩ");
	input_to( (: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	object ppl, *usr = children(USER_OB);
        int id_count;

//edw 6/2/98
        int NowLogin, MaxLimit, login_site, i;
	string my_ip, new_ip;
//end edw

        if(!ob) return;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id. 
        id_count++;
        ob->set_temp("id_count",id_count);
	if(id_count>6) {
	  destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
	  return;
        }

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("����Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}

	ppl = find_body(arg);

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
	&& sizeof(users()) >= MAX_USERS ) {
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		// i.e., ppl exist. (has nothing to do with whether it interactive) -- mon 3/15/99
		//if( !ppl || !interactive(ppl) ) 
		if( !ppl ) {
		  write("�Բ���"+MUD_NAME+"������Ѿ�̫���ˣ�������������\n");
		  destruct(ob);
		  return;
		} 
	}
#endif

	if( wiz_level(arg) < wiz_lock_level ) {
		write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL
                         + " ���ϵ��˲������ߡ�\n�Բ���Ŀǰ�ڲ������뵽���������߽���.��ʱ��ȫ���ָ������������ߵȵȵ�����,������help sorry\n");
		destruct(ob);
		return;
	}
	
//edw@zju.mirror.xyj 6/2/98 (limit multi-login)
// MAX_LOGIN and LOGIN_SITE should be defined in login.h
#ifdef MAX_LOGIN
	
      if(!ppl) { // only check this for new login.
	         // allow existing players to reconnect.
      my_ip=query_ip_number(ob);

      MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
      if(!MaxLimit) MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
      login_site=LOGIN_SITE;
#else
	  login_site=0;
#endif
      if(my_ip && login_site==0) // ignore the last field of the IP
	  my_ip=my_ip[0..strsrch(my_ip, ".", -1)];

      NowLogin=0;

      for(i=0;i<sizeof(usr);i++) 
        if(ob!=usr[i]) {
	    new_ip=query_ip_number(usr[i]);
	    
	    // for net_dead players.
	    if(!new_ip && !interactive(usr[i]))
		new_ip=usr[i]->query_temp("netdead_ip");

	    if(new_ip && login_site==0)
		new_ip=new_ip[0..strsrch(new_ip, ".", -1)];

            if(my_ip==new_ip) {
               NowLogin++;
	    }
			
	}

      if(NowLogin>=MaxLimit) {
	      write(sprintf("�Բ��𣬴����IP��ַ����ͬʱ��¼%sλ���\n",
		      chinese_number(MaxLimit+1)));
              destruct(ob);
              return;
       } 
      }
#endif

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	if( arg=="guest" ) {
		// If guest, let them create the character.
//		confirm_id("Yes", ob);
//		return;
} else if (arg=="new") { // new player login
                write(HIG"[4;53m��ӭ���������!\n"NOR);
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id",ob);
		return;
	} else if( file_size(ob->query_save_file() 
		    + __SAVE_EXTENSION__) >= 0 ) {
		if( ob->restore() ) {
                        write(BRED+HIC"������Ӧ����"NOR":"NOR"");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("�������ﴢ�浵����һЩ���⣬������ guest ����֪ͨ��ʦ������\n");
		destruct(ob);
		return;
	} 
	
        write("û�������ң�����\n");
	write("����Ӣ�����֣������������� [1;31mnew[2;37;0m ע�ᣩ");
	input_to("get_id", ob);
	return;
}
private void judge_freeze(object ob)
{
        int freeze_time;        
      freeze_time=ob->query("freeze_time");
        if( time() < freeze_time ) {            
write ("�Բ�������˺��Ѿ�������,����"+(freeze_time+3600-time())/3600 +"Сʱ����ʹ�á� \n");
             destruct(ob);
             return;
        }       
}                      
private void get_new_id(string arg, object ob)
{
        object ppl;
	int id_count;

        if(!ob) return;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id. 
        id_count++;
        ob->set_temp("id_count",id_count);
	if(id_count>6) {
	  destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
	  return;
        }

        if(!arg) {
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id", ob);
		return;
        }

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id", ob);
		return;
	}

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	ppl = find_body(arg);
	if(ppl || arg=="guest" || arg=="new") {
	    write("��������Ѿ���������ʹ���ˣ�����");
            write("\n�������Լ�ȡһ��Ӣ�����֣�");
	    input_to("get_new_id",ob);
	    return;
	}

	if( file_size(ob->query_save_file() 
		    + __SAVE_EXTENSION__) >= 0 ) {
	    write("��������Ѿ���������ʹ���ˣ�����");
            write("\n�������Լ�ȡһ��Ӣ�����֣�");
	    input_to("get_new_id",ob);
	    return;
	} 

	confirm_id("Yes", ob);
	return;
}

private void get_passwd(string pass, object ob)
{
	string my_pass,id;
	object user;

	write("\n");
	my_pass = ob->query("password");
	if( crypt(pass, my_pass) != my_pass ||
	 !SECURITY_D->match_wiz_site(ob, query_ip_number(ob)) ) {
//By tianlin@mhxy for 2002.1.21
		write("\t\t\t\t[5m[1;31mGAME OVER ![2;37;0m\n");
		log_file("ATTEMPT_LOGIN",sprintf("������� %s ���Դ� %s����ʧ�ܡ�\n",
		ob->query("id"), query_ip_name(ob)));
		if((id=ob->query("id")) && member_array(id,
			SECURITY_D->get_wizlist())!=-1)
		  log_file("wizlogin",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		else
		  log_file("login",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		destruct(ob);
		return;
	}

	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
	    
	    // netdead is delayed being set
	    // after disconnected, so should use interactive.
	    // mon 7/5/98
		if( !interactive(user) ) {
			reconnect(ob, user);
			return;
		}
		write(RED"��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��"WHT"(y/n)"NOR);
		input_to("confirm_relogin", ob, user);
		return;
	}

   if( objectp(user = make_body(ob)) ) {
		if( user->restore() ) {
			log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),
				user->query("id"), query_ip_number(ob), ctime(time()) ) );
                      if(time()-(int)user->query("kickout_time") < 600)
			{
			write("������Υ�������߳���Ϸ����Ϊ�ͷ���ʮ���Ӻ������ߡ�\n");
			destruct(user);
			destruct(ob);
			return;
		}
		
           if(!wizardp(user)&& time()-(int)user->query("quit_time") < 40)
			{
                        write("���˳����������Ϊ�˽���ϵͳ���ɣ����ǵ�һС��������ɣ�\n");
			destruct(user);
			destruct(ob);
			return;
			}
			enter_world(ob, user);
			return;
		} else {
			destruct(user);
		}
	}
	
	if(ob) destruct(ob);
	return;

   write("�������´���������\n");
   confirm_id("y", ob);
}


private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}	

	if( (yn[0]!='y' && yn[0]!='Y') || !user ) {
	    // user may be destructed during the process.
	    // so I put in this check. mon 4/15/98
		write("�ðɣ���ӭ�´�������\n");
		destruct(ob);
		return;
	} else {
		tell_object(user, "���˴ӱ�( " + query_ip_number(ob)
			+ " )����ȡ���������Ƶ����\n");
		log_file( "USAGE", sprintf("%s(%s) ȡ�� %s (%s)\n",
		user->query("name"), user->query("id"),
			query_ip_number(ob), ctime(time()) ) );
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");

//	if( old_link ) {
	// mon 7/5/98
	// need to check user is interactive before exec.
	// user may become non-interactive after the input_to.
	if( old_link && interactive(user)) {
	        // 5/11/98 mon
	        user->set_encoding(ob->query_encoding());

		exec(old_link, user);
	}
	if(old_link)      // mon 9/14/98
		destruct(old_link);

	reconnect(ob, user);	
}

private void confirm_id(string yn, object ob)
{
    /*
	if( yn=="" ) {
		write("ʹ��������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
		input_to("confirm_id", ob);
		return;
	}	

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("�ðɣ���ô��������������Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}
	*/


	write( @TEXT

�������Լ���һ������[1;36m���λ����Ρ�[2;37;0m��������������֡���
�����ֽ����������λ������е�����������󽫲����ٸ��ġ�
�벻ҪȡһЩ���Ż�����������������ŵ����֡�

TEXT
	);
	write("�����������֣�");
	ob->set_temp("get_name",0);
	input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
        arg = CONVERT_D->input(arg,ob);

	if( !check_legal_name(arg) ) {
            ob->add_temp("get_name",1);
	    if(ob->query_temp("get_name")>2) {
	        // the user can't input proper chinese name.
	        // assign one for him/her.    mon 4/19/98

		arg=default_prefix[random(sizeof(default_prefix))]+
		    default_name[random(sizeof(default_name))];

		write("��Ϊ�㲻�������ʵ����������֣�"HIW"ϵͳ"NOR"ָ���������Ϊ��"BLINK+HIC""+
			arg+"\n"NOR);
		write("���ڽ�����Ϸ������ʦ�����޸ġ�\n");

	    } else {
		write("�����������֣�");
		input_to("get_name", ob);
		return;
	    }
	}

	printf("%O\n", ob);
	ob->set("name", arg);
	write("���趨�������룺");
	input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) {
		write("��������Ҫ������ַ���ɣ��������������룺");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write("��������һ���������룬��ȷ����û�Ǵ���");
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("��������������벢��һ�����������趨һ�����룺");
		input_to("new_password", 1, ob);
		return;
	}

	write("���趨�������ݱ�ʶ��");                                                                          
	input_to("get_new_superpasswd", 1, ob);
}
// By tianlin superpasswd for 2001.7.8
int check_legal_superpasswd(object ob,string superpasswd)
{
        int i;
        int bigletter=0;
        int smlletter=0;
        int number=0;
        string id;
        i = strlen(superpasswd);
        if( strlen(superpasswd) <= 5)   {
                write(WHT"�Բ���������ݱ�ʶ��������"BLINK HIY"��"WHT"���ַ���\n"NOR);
                return 0;
        }
        while(i--) {
                if( superpasswd[i]<='Z' && superpasswd[i] >='A' ) bigletter++;
                if( superpasswd[i]<='z' && superpasswd[i] >='a' ) smlletter++;
        }
        if( bigletter == 0 || smlletter == 0 || bigletter+smlletter == strlen(superpasswd)){
        write(WHT"�������ݱ�ʶ�������"HIY"��д" NOR HIR"��" + HIY"СдӢ����ĸ" NOR HIR"��" + WHT"����"HIY"������ţ����֣���㣩"NOR WHT"��\n"NOR);
                return 0;
        }
        return 1;
}
private void get_new_superpasswd(string superpasswd, object ob)
{
        if( !check_legal_superpasswd(ob,superpasswd)) {
                write("���趨�������ݱ�ʶ"HIM"[ "HIC"SuperPassWord"HIM" ]"NOR"��");
                input_to("get_new_superpasswd", 1, ob);
                return;
        }
	ob->set("superpasswd", crypt(superpasswd,0) );
        write("\n��������һ���µ����ݱ�ʶ��");
        input_to("confirm_new_superpasswd", 1, ob, crypt(superpasswd,0));
}
private void confirm_new_superpasswd(string superpasswd, object ob, string new_superpasswd)
{
	string old_superpasswd;
	write("\n");
	old_superpasswd = ob->query("superpasswd");
        if( crypt(superpasswd, old_superpasswd)!=old_superpasswd ) {
                write("��������������ݱ�ʶ����һ�����������趨һ�Σ�\n");
		input_to("get_new_superpasswd", 1, ob);
                return;
        }
          write(BLINK+RED"ע��!"NOR+ CYN" ����ȷ�������ĵ����ʼ���ַ�Ա㵱������뱻��ʱ����ָ�\n\n"NOR+"���ĵ����ʼ���ַ��");
//	write("���ĵ����ʼ���ַ��");
	input_to("get_email",  ob);
}
private void get_email(string email, object ob)
{

	ob->set("email", email);
        write("\n���ĸ�����ҳ��");
	input_to("get_webpage",  ob);
	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.

}
private void get_webpage(string webpage, object ob)
{
	

	ob->set("webpage", webpage);
        write("\n����(ICQ/OICQ)��");
	input_to("get_icq",  ob);
}
private void get_icq(string icq, object ob)
{
	object user;

	ob->set("icq", icq);
        ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) ) {
	    if(ob) destruct(ob);
	    return;
	}

	write("\n��Ҫ��������[1;32m(m)[2;37;0m�Ľ�ɫ��Ů��[1;35m(f)[2;37;0m�Ľ�ɫ��");
	input_to("get_gender", ob, user);
}
private void get_gender(string gender, object ob, object user)
{
	if( gender=="" ) {
		write("��Ҫ��������[1;32m(m)[2;37;0m�Ľ�ɫ��Ů��[1;35m(f)[2;37;0m�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "����");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "Ů��" );
	else {
		write("�Բ�����ֻ��ѡ������[1;32m(m)[2;37;0m��Ů��[1;35m(f)[2;37;0m�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}
	
        confirm_gift("n",ob,user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

        if(!ob->query("body")) {
	  return 0;
        }
	user = new(ob->query("body"));
	if(!user) {
		write("���ڿ������������޸��������ĳ�ʽ���޷����и��ơ�\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

private void confirm_gift(string yn, object ob, object user)
{
        int n, a, b;

	if(!ob || !user) {
            if(user) {
	      destruct(user);
	      return;
	    }
            if(ob) destruct(ob);
	    return;
        }

                if (find_player(query("id")))
                {
                        write(HIR"�Բ������������Ѿ�����ע��������ע�ᡣ\n"NOR);
                        destruct(ob);
                        destruct(user);
                }

        user->set("kar", 20 );
	user->set("str", 20 );
	user->set("cps", 20 );
	user->set("int", 25 );
	user->set("cor", 20 );
	user->set("con", 20 );
	user->set("spi", 25 );
	user->set("per", 20 );

	// mon 3/21/99 allow players to choose gift after login.
	user->set("no_gift",1);

	    CHAR_D->setup_char(user); //setup user weight. mon 11/7/97
	    user->set("title", "��ͨ����");
	    user->set("birthday", time() );
	    user->set("potential", 99);
	    user->set("food", user->max_food_capacity());
	    user->set("water", user->max_water_capacity());
	    user->set("channels", ({ "chat","rumor","sldh" ,"bill"}) );
	    log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
	    query_ip_number(ob), ctime(time()) ) );
//By tianlin@mhxy for 2001.12.28
    message("channel:chat",WHT"��"HIY"��սʥ��"NOR+WHT"��"HIC"�����(Sun wukong)��"NOR+CYN"��˵����һλ����"YEL""+user->query("name")+CYN"("YEL+user->query("id")+CYN")��"HIR+RANK_D->query_respect(user)+NOR+CYN"̤��������ȡ��֮·��\n"NOR,users());
	    ob->set("last_from",query_ip_number(ob));
	    ob->set("last_on",time());

	    return enter_world(ob, user);
           }

string dis_attr(int value)
{       int gift=20;
        if( value > gift ) return sprintf( HIY "%3d" NOR, value );
        else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
        else return sprintf("%3d", value);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mbx;
	string startroom="";
       string *f_ids;
	string ip_from;
       string *ok_ip;
       int num,i;
       mapping friends;

       reset_eval_cost();
       user->set_temp("temp_time",time());//by tianlin@mhxy for 2001.8.20 ��wizlist��Գ�,������ʱ��ʱ�亯��
       user->set_temp("combat_exp",user->query("combat_exp"));//����������һ����ʱ�ļ�
	user->set_temp("potential",user->query("potential"));
	user->set_temp("daoxing",user->query("daoxing"));
	user->set_temp("max_mana",user->query("max_mana"));
	user->set_temp("max_force",user->query("max_force"));

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	write("ĿǰȨ�ޣ�[1;33m" + wizhood(user) + "[0;37;0m\n");
	user->setup();

	// In case of new player, we save them here right aftre setup 
	// compeleted.
	user->save();
	ob->save();

        if( !silent ) {
	     if(file_size(MOTD)>0)
             user->start_more(read_file(MOTD));
		
	     // mon 3/21/99 
	     // new user login.
                if( wizardp(user) )
                        startroom="/d/wiz/wizroom";
             if(user->query("no_gift")) {
	       user->move("/d/wiz/init",1);
	     } else {
		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( strlen(startroom = user->query("startroom"))<2 )
			startroom = START_ROOM;

                if(!wizardp(user) && startroom[0..2]=="/u/") {
		  startroom = START_ROOM;
                  user->set("startroom",startroom);
                }
                //added by mon 10/27/97

		// the following 7 lines are aded by snowcat dec 10 1997
		if (("/adm/daemons/band"
		    ->create_char_banned(query_ip_number(user)) == 1 ||
	    	    "/adm/daemons/band"->is_banned(query_ip_number(user))
		    == 1) && !wizardp(user)) {
			user->move("/d/wiz/guest");
			log_file( "ALLCONT", sprintf("from banned site\n"));
		}
		else if( !catch(load_object(startroom)) )
			user->move(startroom);
		else {
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		if( !silent ) { 
	//	message_vision(HIW"$N���߽����������,��ʼ���Լ���"HIR"�� "HIG"ȡ �� ֮ ·"HIR" ��"HIW"��\n" NOR, user);

	    }

		if(!wizardp(user) || !user->query("env/invisibility"))
		tell_room(startroom, user->query("name") + "���߽���������硣\n",
			({user}));
	 if( !wizardp(user) )
    message("channel:chat", HIM"���λ����Ρ�: "HIC"��˵"+HIW+user->name()+HIC "�������λ����Σ���������δ��ɵ�·;\n"NOR,users());
	     }
	        if(file_size("/log/notice")>0){
       write(CYN"     �ԡԡԡԡԡԡԡԡԡԡԡ�"HIR"�λ���������֪ͨ"NOR CYN"�ԡԡԡԡԡԡԡԡԡԡԡԡ�\n");
       write("     "+read_file("/log/notice"));
       write(CYN"     �ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ�\n"NOR);
        }

//����Ƿ�������а�add by jackyboy@cctx 1999/3/8
                TOPTEN_D->topten_checkplayer(user);
                friends=user->query("friendof");
                if(!friends|| !mapp(friends)||  (sizeof(friends) == 0))
                 friends=([]);
                f_ids = keys(friends);
                for(i=0;i<sizeof(f_ids);i++)
                {
                if( ! find_player(f_ids[i]) ) continue;
                tell_object(find_player(f_ids[i]),CYN"�����ˡ�"HIC"�λþ���"NOR+CYN"͵͵�ĸ�����:����ĺ���"HBRED+BLINK+WHT+user->name()+NOR+CYN"�Ѿ���������\n"NOR);
                }
   		mbx=ob->query_temp("mbox_ob");
		if (!mbx) {
		  mbx=new(MAILBOX_OB);
		  mbx->set_owner(ob->query("id"));
                }
		num=mbx->query_new_mail();
		if( num>0 ) {
	          write( GRN + "\nǧ���۸����㣺����"
		    +chinese_number(num)+
		    "���ţ��뵽�ϳǿ�ջ��һ�ˣ�����\n\n" + NOR);
		}
		destruct(mbx);
	      	ip_from="/adm/daemons/ipd"->seek_ip_address(query_ip_number(user));
	        CHANNEL_D->do_channel( this_object(), "sys",
		sprintf(NOR WHT "%s�� " HIG "%s" NOR WHT "���߽���,IP���ԣ�"HIG"%s"NOR,user->name()+"("+capitalize(user->query("id")) + ")", query_ip_number(user), ip_from));  
		}

	UPDATE_D->check_user(user, 0);
       NEWS_D->check_news(user);
      {object caishen;
	if(objectp(caishen=find_object("/d/wiz/npc/caishen"))) {
	  caishen->check_one(user);
        }
      }
        	if ( wizhood(user)=="(admin)")	{
			if( user->query("wiz_check/FILES") != file_size("/log/FILES") ) 
			{
				user->set("wiz_check/FILES", file_size("/log/FILES"));
				write(HIW"����ʦ�зǷ�д�����������鿴 /log/FILES ��\n"NOR);
			}
			if( user->query("wiz_check/CALL_PLAYER") != file_size("/log/static/CALL_PLAYER") ) 
			{
				user->set("wiz_check/CALL_PLAYER", file_size("/log/static/CALL_PLAYER"));
				write(HIR"����ʦ��ʹ�ù�call�������鿴 /log/static/CALL_PLAYER ��\n"NOR);
			}
			if( user->query("wiz_check/debug") != file_size("/log/debug") ) 
			{
				user->set("wiz_check/debug", file_size("/log/debug"));
				write(BLINK+HIB"�����ļ�update���������鿴 /log/debug.log ��\n"NOR);
			}
			if( user->query("wiz_check/PURGE_PLAYER") != file_size("/log/static/PURGE") ) 
			{
				user->set("wiz_check/PURGE_PLAYER", file_size("/log/static/PURGE"));
				write(HIC"����ʹ�ù�PURGE���������鿴 /log/static/PURGE ��\n"NOR);
			}
			if( user->query("wiz_check/promotion_PLAYER") != file_size("/log/static/promotion") ) 
			{
				user->set("wiz_check/promotion_PLAYER", file_size("/log/static/promotion"));
				write(HIM"����ʹ�ù�Ȩ����������鿴 /log/static/promotion ��\n"NOR);
			}
		}
		return;
}

varargs void reconnect(object ob, object user, int silent)
{
        object old_link;
	
	// mon 9/15/98
	old_link=user->query_temp("link_ob");
	if(old_link && old_link!=ob)
	    destruct(old_link);

       user->set_temp("temp_time",time());//by tianlin@mhxy for 2001.8.20 ��wizlist��Գ�
       user->set_temp("link_ob", ob);
       ob->set_temp("body_ob", user);
  
	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	user->reconnect();
	if( !silent && !user->query("env/invisibility")) {
		tell_room(environment(user), user->query("name") + "�������߻ص�������硣[1;32mGood Luck![2;37;0m\n",
		({user}));
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s��%s�������߽��롣", user->query("name")+"(" + capitalize(user->query("id")) + ")", query_ip_name(user)) );
	}
	UPDATE_D->check_user(user, 1); // this is for reconnect.
}

int check_legal_id(string id)
{
	int i;
	string *legalid;

	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 8 ) ) {
		write("�Բ������Ӣ�����ֱ����� 3 �� 8 ��Ӣ����ĸ��\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("�Բ������Ӣ������ֻ����Ӣ����ĸ��\n");
			return 0;
		}
	legalid = explode(read_file(BANNED_ID), "\n");
	for(i=0; i<sizeof(legalid); i++)   {
	   if( id == legalid[i] )   {
		  write("�Բ����������ֻ���������˵����š�\n");
		  return 0;
       }
	}
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);
	
	if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
		write("�Բ�������������ֱ�����һ�����������֡�\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("�Բ�������������ֲ����ÿ����ַ���\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("�Բ��������á����ġ�ȡ���֡�\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("�Բ����������ֻ���������˵����š�\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++) {
          ob=body[i];
	  if( clonep(ob) && getuid(ob) == name 
            && ob->query("max_gin")>0 ) return ob;
	    //check max_gin to avoid damaged user object.
        }

	return 0;
}
int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}

// add by xhm  2000.11.13   ���Ӻƽ��ж����������Ķ�ȡ������
void add_dienpc()
{
	dienpc++;
}
void set_dienpc(int i)
{
	if (i == -1) {
		mad_lock = 1;
		dienpc = 0;
		return;
	}
	dienpc = i;
}
int get_dienpc()
{
	return dienpc;
}

void set_madlock(int i)
{
	if( i == 1 ) mad_lock = 1;
	else mad_lock = 0;
}
int get_madlock()
{
	return mad_lock;
}