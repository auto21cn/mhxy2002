//By tianlin@mhxy for 2002.1.14
//�Դ�������̳��ժ��,��д.

#include <ansi.h>

string give_gift();

private mixed *story = ({
        ""HIR"��"HIC"��"NOR+CYN"��"HIY"��"HIW"֮"HIG"�������"NOR,
        "",
        "ׯ�ϵ���ͥ�����֡�",
        "",
        ""HIC"������"NOR+WHT"����գ�������������㱾��Ӧ��������Ҫ����Ⱥ�ڱ�С����",
        "˭֪���㾹Ȼ�ͺ����ͷ��ţħ������̰���ܻߴ�����˽��",
        "�����������İ����Žᣬ��֪��֪���Ѿ�������������",
        "",
        ""HIW"����գ�"NOR+WHT"������,��׷����3���,��Ϊ�׾����Ǹ����˳�����,�Ÿ���ץ��,��Ҫ��Ϊ��������",
        "",
        ""HIG"��ɮ��"NOR+WHT"��գ�����ô�����������������˵���ء�����",
        "",
        ""HIC"������"NOR+WHT"�����أ��㲻Ҫ���죬Ϊ������ල��������ӣ�����������ί��ǣ�",
        "˭֪���㾹Ȼ����ͬ�����ۣ������������ң�",
        "",
        ""HIG"��ɮ��"NOR+WHT"���������֪��������ǵ�ί��ǣ�Ȩ��һ������һ��СС�ļ�ί����������Σ�",
        "���Ի���ʵ��һ���,��һ�����������ֶ���Ϊ�أ�",
        "����˵��̰�۸��ܣ��Ҿ��������Ѿ�εȻ�ɷ磬������һ����֮������Ťת��",
        "��˵�����ɣ��ϴβ���������һ�׼�ͥӰԺ��������",
        "",
        ""HIC"������"NOR+WHT"ס�ڣ�",
        "",
        "��գ���һ�û�¾ͳ�ƪ���ۣ�ߴߴ���ᣬ�������������¶�˵������",
        "������ʿ���㶼���˼Ҷ���������ô��˵���أ��������ģ������ȡ�",
        "",
        "���˵�����ߣ�����ʿ��������ס�������͵����Ρ�",
        "",
        "��������",
        "",
        "��ʪ�谵���η���������ڲݶ�������㲡� ",
        "",
        "���䣺����գ������ң�",
        "",
        "��գ�WHO��",
        "",
        "���䣺�а׾����ġ�",
        "",        
        "�ѵ������ķ��֣�����˳�����Ӽ�����ȥ�����������������ô�������ޣ��������ˡ�",
        "",
        "��գ�������",
        "",
        "�׾�������գ�",
        "",
        "��գ���������ô�ã�ֻ���������ң������Ҹж�����",
        "",
        "�׾�������������������",
        "",
        "��գ���֪��ʲô�ǵ�����������",
        "",
        "�׾��������������㡣����",
        "",
        "��գ����������� ���ǣ�ONLY YOU �ܰ���ȥ���裬ONLY YOU ��������������",
        "ONLY YOU��ס�ң�����̰�ۺ��ܻߣ��������˾���ONLY YOU ��",
        "",
        "�׾�����������ʵ����������",
        "",
        "��գ�ON````ONLY YOU������������������ȥ��ƴȫ��Ϊ���㣬����Ҳֵ�á���������",
        "",
        "�׾��������ON �ˣ�������������",
        "",
        "��գ�ON``````ON",
        "",
        "�׾�������Ǯ��������������¡�",
        "",
        "�׾�����ON���ͷ��������Ϊ�����������㰡�������ڲ�������������磬",
        "��ѧ�˼ҳ���裬�ѵ���׼�����������Ӱ���",
        "",
        "��գ��������",
        "",
        "�׾�����ʡʡ���㣬���Ǻú�׼����ô����һ���ɣ������ӣ�",
        "",
        "��գ��������ˡ�"HIM"��˵�걼���η���"NOR"",
        "",
        "�׾����������һ�û��˵���أ������������ϴθ��ҵĴ��ۣ����뼸�Ű���",
        "",
        "�����Ȼͣ����,��ȫ����ˮ,����Ϊ���ǰ��ҵ�,���ڲ�������������Ǯ,С�ؾ��ǲ��ɿ���.",
        "",
        "��������",
        "",
        "�������ݶ��ҹĻ��Ȼ���٣��ڰ����η���Ʈ��һ������ĸ�������"HIC"�����򡷣�"NOR"",
        "",
        "��������"MAG"����Ϊ�һ�����,������û��,��ֻ�ǿ������ϵ�����,������Ȼ������Ŀ,��ȴ�ſ�ʼ"NOR,
        ""MAG"��һ������,���Ұ��Լ������,̰���������ֵ�,һ���־�����·��������"NOR,
        "",
        "��������"CYN"����Ϊ����ʹ��,������û��,���ҿ��������С��,��Ȼ�����ͬİ·,��γ�����"NOR,
        ""CYN"һ������,���Ұ��������,С����Σ�յ���Ϸ,���ûǮ�Ͳ����Ҹ���������"NOR,
        "",
        "��������"HIC"����"NOR+YEL"һ����;�ʹ˽���,һ����ͷ�ۿ�Ҫ���,�ҵ�һ�����Ǵ���,ɱͷ�Ǹ��ܵ�ʹ��,"NOR,
        ""YEL"ֻԸ���±����ܿ����,����ΪǮȥ������������"NOR,
        "",
        "���̵��������ڵ���,��ձ��������á�",
        "",
        ""HIY"������"NOR+WHT"����գ��㻹��ʲô��Ҫ˵��",
        "",
        "��գ�������һ�����޵�Ů�Ӱ�������ǰ,��û�а���ס�Լ�,����������С��,������Σ��",
        "����Ī���ڴ�,�Ӵ��Ҿͱ����ڲ�,̰���ܻ߼����ڡ����������Ը���һ�����������Ļ���,",
        "��һ����˵���Ҳ�Ҫ�����Ҫ���������ּӸ����ޣ���ϣ���ǣ�"BLINK+HBRED+HIW"һ���꣡"NOR,
        "",
        ""HIY"������"NOR+WHT"�ã��������������������ú����˰ɡ����������������ϻ�Ѻ��",
        "",
        "�������ë�ʣ��ǳ��������ϵ�����ֽ�ϻ���һ��Ȧ���������Ѿ��ǳ�Ŭ���������Բ���",
        "Բ�������е��ź�������ת��һ�롰���ӲŻ���Բ���أ�������Ȼ�����������Լ��Ĳ�Բ�к��ִ���",
        "��ķ��",
        "",
        ""HIM"���̵ģ�������֮������Ǽ�ֵ���ǵ�����Ʒ��ֵ�ö�ö�Ǯ�ɣ���ճճյ��롣"NOR,
        ""HIR"������Ѫ��Ц........"NOR,
          (: give_gift :),

});

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

string give_gift()
{
        STORY_D->give_gift("/clone/gift/qianbao", 1,
                           HIM "\nͻȻ����зɳ�����Ǯ�������������ǰ.\n\n" NOR);//�ҵ����ݴʲ�����.(snicker)
        return HIM "��˵"HIC"�׾���"HIM"��"HIY"Ǯ��"HIM"�����˼��ˣ�\n" NOR;

}