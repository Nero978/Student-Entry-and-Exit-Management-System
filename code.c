/*
* 文件名：[code.c]
* 作者：Chris Liu <ChrisLiu@bjfu.edu.cn>
* 版权：Copyright (C) 2022 Chris Liu
* 描述：程序基础课程设计，制作校园出入人员信息管理系统。
* 修改人：Chris Liu 
* 最后修改时间：2022-12-09
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//新建全局变量，考虑到数据的复杂性，设置了结构体
struct people{
    char Pjob[100];//身份
    char Pname[100];//姓名
    char Pnum[100];//学工号
    char Cinfo[100];//联系方式
    char Pid[100];//身份证号
    int Pio;//出入
    char Time[100];//时间
};
struct people list[100];
int total=0;//total全局变量，表示系统内录入的信息数

//welcome函数用于打印开始的欢迎屏幕，以及功能选择
int welcome()
{
    printf("*************欢迎使用校园出入管理系统*************\n");
    printf("--------------------------------------------------\n");
    printf("-------------1.录入出入校园人员信息---------------\n");
    printf("-------------2.保存出入校园人员信息---------------\n");
    printf("-------------3.浏览出入校园人员信息---------------\n");
    printf("-------------4.查询出入校园人员信息---------------\n");
    printf("-------------5.增加出入校园人员信息---------------\n");
    printf("-------------6.删除出入校园人员信息---------------\n");
    printf("-------------7.修改出入校园人员信息---------------\n");
    printf("-------------8.统计出入校园人员信息---------------\n");
    printf("-------------9.对出入校园人员信息进行排序---------\n");
    printf("-------------10.退出------------------------------\n");
    printf("--------------------------------------------------\n");
    printf("********************感谢使用！********************\n");
    int code=0;
    do {
        printf("请选择(1~10):");
        scanf("%d",&code);
        if (code>10||code<1) {
            printf("输入有误，请重新输入！\n");
        }
    }while (code>10||code<1);//对于用户输入进行验证
    return code;
}

//isJob函数验证用户输入的人员身份是否正确
int isJob(char exam[])
{
    if (strcmp(exam,"学生")!=0&&
        strcmp(exam,"教职工")!=0&&
        strcmp(exam,"其他")!=0) {
        printf("人员身份校验失败，请从“学生”“教职工”“其他”中选择一个！\n");
        return -1;
    } else {
        return 0;//合法返回0
    }
}

//isTime函数验证用户输入的时间格式是否正确
int isTime(char time[])
{
    char year[5]={'0'},month[3]={'0'},day[3]={'0'};
    int i,j=0;
    for (i=0; i<4; i++) {
        year[j]=time[i];
        j++;
    }
    j=0;
    for (i=5; i<7; i++) {
        month[j]=time[i];
        j++;
    }
    j=0;
    for (i=8; i<10; i++) {
        day[j]=time[i];
        j++;
    }
    if (strlen(time)!=10||
        time[4]!='/'||
        time[7]!='/'||
        strspn(year, "0123456789")!=strlen(year)||
        strspn(month, "0123456789")!=strlen(month)||
        strspn(day, "0123456789")!=strlen(day)) {
        printf("日期校验失败，格式应为“YYYY/MM/DD”！\n");
        return -1;
    } else {
        return 0;//返回0合法
    }
}

//isList函数验证用户输入的整条出入校园数据是否正确
int isList(struct people exam)
{
    //调用isJob判断身份输入合法性
    int res=0;
    if (isJob(exam.Pjob)!=0) {
        res++;
    }
    //验证姓名是否正确
    if (strspn(exam.Pname, "0123456789")!=0) {
        printf("姓名校验失败，其中不应含有数字！\n");
        res++;
    }
    //验证学工号是否正确
    if (strspn(exam.Pnum, "0123456789")!=strlen(exam.Pnum)||
        strlen(exam.Pnum)!=9) {
        printf("学工号校验失败，应为9位纯数字！\n");
        res++;
    }
    //验证手机号是否正确
    if (strspn(exam.Cinfo, "0123456789")!=strlen(exam.Cinfo)||
        strlen(exam.Cinfo)!=11) {
        printf("手机号校验失败，应为11位纯数字！\n");
        res++;
    }
    //验证身份证号是否正确
    if (strspn(exam.Pid, "0123456789X")!=strlen(exam.Pid)||
        strlen(exam.Pid)!=18) {
        printf("身份证号码校验失败，应为18位字符！\n");
        res++;
    }
    //验证出入状态码是否为0/1
    if (exam.Pio!=0&&exam.Pio!=1) {
        printf("出入校园状态码（0/1）校验失败！\n");
        res++;
    }
    //调用isJob判断身份输入合法性
    if (isTime(exam.Time)!=0) {
        res++;
    }
    if (res!=0) {
        printf("该行输入数据非法，请重新输入！\n");
    }
    return res;//返回为0则合法
}

//isExam函数验证用户在查找时输入的整条数据是否合法
int isExam(struct people exam)
{
    int res=0;
    //校验姓名
    if (strspn(exam.Pname, "0123456789")!=0) {
        printf("姓名校验失败,，其中不应含有数字！\n");
        res++;
    }
    //校验身份证号码
    if (strspn(exam.Pid, "0123456789X")!=strlen(exam.Pid)||
        strlen(exam.Pid)!=18) {
        printf("身份证号码校验失败，应为18位字符！\n");
        res++;
    }
    //校验出入状态码
    if (exam.Pio!=0&&exam.Pio!=1) {
        printf("出入校园状态码（0/1）校验失败！\n");
        res++;
    }
    //校验日期格式
    if (isTime(exam.Time)!=0) {
        res++;
    }
    if (res!=0) {
        printf("该行输入数据非法，请重新输入！\n");
    }
    return res;//返回为0则合法
}

//isABC校验用户输入的选项是否为ABC
int isABC(char in)
{
    if (in!='A'&&in!='B'&&in!='C') {
        return -1;
    } else {
        return 0;//返回为0则合法
    }
}

//isABCD校验用户输入的选项是否为ABCD
int isABCD(char in)
{
    if (in!='A'&&in!='B'&&in!='C'&&in!='D') {
        return -1;
    } else {
        return 0;//返回为0则合法
    }
}

//isABCDE校验用户输入的选项是否为ABCDE
int isABCDE(char in)
{
    if (in!='A'&&in!='B'&&in!='C'&&in!='D'&&in!='E') {
        return -1;
    } else {
        return 0;//返回为0则合法
    }
}

//isyn执行操作确认功能，校验输入的同时返回确认参数
int isyn()
{
    printf("是否继续y/n？");
    char yn;
    scanf("%s",&yn);
    if (yn=='y') {
        return 0;//继续
    }
    if (yn=='n') {
        return -1;//终止
    } else {
        printf("输入不合法，请重试！\n");
        return isyn();
    }
}

//write执行文件写入功能
void write()
{
    FILE *fp=fopen("database.txt", "w");
    if (fp==NULL) {
        printf("数据保存失败，请重试！\n");
    } else {
        int j;
        for (j=0; j<total; j++) {
            fprintf(fp, "%s\t", list[j].Pjob);
            fprintf(fp, "%s\t", list[j].Pname);
            fprintf(fp, "%s\t", list[j].Pnum);
            fprintf(fp, "%s\t", list[j].Cinfo);
            fprintf(fp, "%s\t", list[j].Pid);
            fprintf(fp, "%d\t", list[j].Pio);
            fprintf(fp, "%s\n", list[j].Time);
        }
        fclose(fp);
        printf("数据存入文件成功！\n");
    }
}

//read执行文件读取功能
void read()
{
    FILE *fp=fopen("database.txt", "r");
    if (fp==NULL) {
        total=0;
        return;
    } else {
        int j;
        total=0;
        for (j=0; !feof(fp); j++) {
            fscanf(fp, "%s", list[j].Pjob);
            fscanf(fp, "%s", list[j].Pname);
            fscanf(fp, "%s", list[j].Pnum);
            fscanf(fp, "%s", list[j].Cinfo);
            fscanf(fp, "%s", list[j].Pid);
            fscanf(fp, "%d", &list[j].Pio);
            fscanf(fp, "%s", list[j].Time);    
        }
        total=j-1;
        fclose(fp);
        printf("文件读取成功！\n");
    }
}

//put_in执行信息录入功能
int put_in()
{
    //调用read函数，配合if检查是否重复录入的问题
    if (total==0) {
        read();
    }
    if (total!=0) {
        printf("检测到已有录入信息，再次录入会覆盖原有数据！\n");
        printf("要查看已保存的数据，请在返回主菜单后输入“3”。\n");
        printf("如需增加数据，请在返回主菜单后输入“5”。\n");
        if (isyn()!=0) {
            return -1;
        }
    }
    
    //验证输入，保证数组不越界
    int i=0;
    do {
        printf("请输入录入人员个数(1~100):");
        scanf("%d",&i);
        if (i<=0||i>100) {
            printf("输入数据非法，请重试！\n");
        }
    }while (i<=0||i>100);
    total=i;

    printf("请从左至右依次输入人员身份、姓名、学工号、联系方式、身份证号、出入状态、时间。\n");
    printf("每个项目之间用空格隔开，每个人员之间用回车隔开。\n");
    printf("--------------------------------------------------\n");
    printf("人员身份\t姓名\t学工号\t联系方式\t身份证号\t出入状态(0/1)\t时间\n");
    int j;
    for (j=0; j<i; j++) {
        do {
            scanf("%s",list[j].Pjob);
            scanf("%s",list[j].Pname);
            scanf("%s",list[j].Pnum);
            scanf("%s",list[j].Cinfo);
            scanf("%s",list[j].Pid);
            scanf("%d",&list[j].Pio);
            scanf("%s",list[j].Time);
        }while (isList(list[j])!=0);
    }
    printf("录入成功！\n");
    return 0;
}

//save函数执行数据保存到文件功能，并打印结果提示
void save()
{
    if (total==0) {
        printf("没有新的数据可以保存！\n");
        printf("请返回主菜单后输入“1”录入，或输入“3”浏览已保存的数据。\n");
        return;
    } else {
        write();
    }
    return;
}

//view函数打印系统内的所有数据
void view()
{
    //数据为空时提示
    read();
    if (total==0) {
        printf("数据为空，请先录入！\n");
        return;
    }
    int j;
    printf("--------------------------------------------------\n");
    for (j=0; j<total; j++) {
        printf("%s\t", list[j].Pjob);
        printf("%s\t", list[j].Pname);
        printf("%s\t", list[j].Pnum);
        printf("%s\t", list[j].Cinfo);
        printf("%s\t", list[j].Pid);
        printf("%d\t", list[j].Pio);
        printf("%s\n", list[j].Time);
    }
    printf("共有%d条数据，已全部显示。\n",total);
    return;
}

//searchJob执行按人员身份查找功能
void searchJob()
{
    struct people search[100];
    char type[100];
    int result;
    int i=0,j=0;

    do {
        printf("请输入人员类型：");
        scanf("%s",type);
        if (isJob(type)!=0) {
            printf("输入不合法，请重新输入！\n");
        }
    }while (isJob(type)!=0);

    if (strcmp(type, "学生")==0) {
        for (i=0,j=0; i<total; i++) {
            if (strcmp(list[i].Pjob,"学生")==0) {
                search[j]=list[i];
                j++;
            }
        }
        result=j;
    }

    if (strcmp(type, "教职工")==0) {
        for (i=0,j=0; i<total; i++) {
            if (strcmp(list[i].Pjob,"教职工")==0) {
                search[j]=list[i];
                j++;
            }
        }
        result=j;
    }

    if (strcmp(type, "其他")==0) {
        for (i=0,j=0; i<total; i++) {
            if (strcmp(list[i].Pjob,"其他")==0) {
                search[j]=list[i];
                j++;
            }
        }
        result=j;
    }

    printf("--------------------------------------------------\n");
    if (result==0) {
        printf("没有符合条件的查询结果！\n");
    } else {
        for (j=0; j<result; j++) {
            printf("%s\t", search[j].Pjob);
            printf("%s\t", search[j].Pname);
            printf("%s\t", search[j].Pnum);
            printf("%s\t", search[j].Cinfo);
            printf("%s\t", search[j].Pid);
            printf("%d\t", search[j].Pio);
            printf("%s\n", search[j].Time);
        }
        printf("查询到共有%d条数据，已全部显示。\n",result);
    }
    return;
}

//searchName执行按人员姓名查找功能
void searchName()
{
    struct people search[100];
    char name[100];
    int result;
    int i=0,j=0;

    printf("请输入人员姓名：");
    scanf("%s",name);

    for (i=0,j=0; i<total; i++) {
        if (strcmp(list[i].Pname,name)==0) {
            search[j]=list[i];
            j++;
        }
    }
    result=j;

    printf("--------------------------------------------------\n");
    if (result==0) {
        printf("没有符合条件的查询结果！\n");
    } else {
        for (j=0; j<result; j++) {
            printf("%s\t", search[j].Pjob);
            printf("%s\t", search[j].Pname);
            printf("%s\t", search[j].Pnum);
            printf("%s\t", search[j].Cinfo);
            printf("%s\t", search[j].Pid);
            printf("%d\t", search[j].Pio);
            printf("%s\n", search[j].Time);
        }
        printf("查询到共有%d条数据，已全部显示。\n",result);
    }
    return;
}

//searchIO执行出入的状态码查找功能
void searchIO()
{
    struct people search[100];
    int IO;
    int result;
    int i=0,j=0;

    do {
        printf("请输入出入校类型（0/1）：");
        scanf("%d",&IO);
        if (IO!=0&&IO!=1) {
            printf("输入不合法，请重新输入！\n");
        }
    }while (IO!=0&&IO!=1);

    for (i=0,j=0; i<total; i++) {
        if (list[i].Pio==IO) {
            search[j]=list[i];
            j++;
        }
    }
    result=j;

    printf("--------------------------------------------------\n");
    if (result==0) {
        printf("没有符合条件的查询结果！\n");
    } else {
        for (j=0; j<result; j++) {
            printf("%s\t", search[j].Pjob);
            printf("%s\t", search[j].Pname);
            printf("%s\t", search[j].Pnum);
            printf("%s\t", search[j].Cinfo);
            printf("%s\t", search[j].Pid);
            printf("%d\t", search[j].Pio);
            printf("%s\n", search[j].Time);
        }
        printf("查询到共有%d条数据，已全部显示。\n",result);
    }
    return;
}

//search执行查找类型选择功能
void search()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内没有存入数据，暂时无法查询！\n");
        return;
    }

    printf("A.按人员身份查询\n");
    printf("B.按姓名查询\n");
    printf("C.按出入校查询\n");
    printf("D.退出\n");
    char code;
    do {
        printf("请选择（A~D）：");
        scanf("%s",&code);
        if (isABCD(code)!=0) {
            printf("输入不合法，请重新输入！\n");
        }
    }while (isABCD(code)!=0);
    
    switch (code) {
        case 'A':
            searchJob();
            break;
        case 'B':
            searchName();
            break;
        case 'C':
            searchIO();
            break;
        case 'D':
            printf("即将返回主菜单。\n");
            return;
        default:
            printf("出现错误！即将返回主菜单。\n");
            return;
    }
}

//add执行增加数据功能
int add()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内还没有任何数据，请在返回主菜单后输入“1”导入！\n");
        return -1;
    }
    if (total==100) {
        printf("储存记录已满，请删除部分后重试！\n");
        return -1;
    }
    
    int i=0;
    printf("已储存%d条数据，还可以储存%d条。\n",total,100-total);
    do {
        printf("请输入需要增加人员的个数(1~%d):",100-total);
        scanf("%d",&i);
        if (i<=0||i>100-total) {
            printf("输入数据非法，请重试！\n");
        }
    }while (i<=0||i>100-total);
    
    printf("请从左至右依次输入人员身份、姓名、学工号、联系方式、身份证号、出入状态、时间。\n");
    printf("每个项目之间用空格隔开，每个人员之间用回车隔开。\n");
    printf("--------------------------------------------------\n");
    printf("人员身份\t姓名\t学工号\t联系方式\t身份证号\t出入状态(0/1)\t时间\n");
    int j;
    for (j=total; j<total+i; j++) {
        do {
            scanf("%s",list[j].Pjob);
            scanf("%s",list[j].Pname);
            scanf("%s",list[j].Pnum);
            scanf("%s",list[j].Cinfo);
            scanf("%s",list[j].Pid);
            scanf("%d",&list[j].Pio);
            scanf("%s",list[j].Time);
        }while (isList(list[j])!=0);
    }
    total+=i;
    printf("增加成功！\n");
    return 0;
}

//delete执行删除数据功能
int delete()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内还没有任何数据，请在返回主菜单后输入“1”导入！\n");
        return -1;
    }

    struct people exam,search;
    printf("--------------------------------------------------\n");
    printf("请从左至右依次输入姓名、身份证号、出/入校、出/入校时间，并以空格隔开：\n");
    do {
        scanf("%s",exam.Pname);
        scanf("%s",exam.Pid);
        scanf("%d",&exam.Pio);
        scanf("%s",exam.Time);
    }while (isExam(exam)!=0);

    int i=0;
    int result=0;
    int id=0;
    for (i=0; i<total; i++) {
        if (strcmp(list[i].Pname,exam.Pname)==0&&
            strcmp(list[i].Pid,exam.Pid)==0&&
            list[i].Pio==exam.Pio&&
            strcmp(list[i].Time,exam.Time)==0) {
            search=list[i];
            result++;
            id=i;
            break;
        }
    }
    printf("--------------------------------------------------\n");
    if (result==0) {
        printf("没有找到结果！\n");
        return -1;
    } else {
        printf("%s\t", search.Pjob);
        printf("%s\t", search.Pname);
        printf("%s\t", search.Pnum);
        printf("%s\t", search.Cinfo);
        printf("%s\t", search.Pid);
        printf("%d\t", search.Pio);
        printf("%s\n", search.Time);
        printf("即将删除这条数据！");
        if (isyn()==0) {
            struct people temp;
            int j;
            list[total-1]=temp;
            for (j=id; j<total-1; j++) {
                list[id]=list[id+1];
            }
            total--;
            printf("删除成功！\n");
            return 0;
        } else {
            printf("操作取消！\n");
            return -1;
        }
    }
}

//edit执行编辑数据功能
int edit()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内还没有任何数据，请在返回主菜单后输入“1”导入！\n");
        return -1;
    }

    struct people exam,search;
    printf("--------------------------------------------------\n");
    printf("请从左至右依次输入姓名、身份证号、出/入校、出/入校时间，并以空格隔开：\n");
    do {
        scanf("%s",exam.Pname);
        scanf("%s",exam.Pid);
        scanf("%d",&exam.Pio);
        scanf("%s",exam.Time);
    }while (isExam(exam)!=0);

    int i=0;
    int result=0;
    int id=0;
    for (i=0; i<total; i++) {
        if (strcmp(list[i].Pname,exam.Pname)==0&&
            strcmp(list[i].Pid,exam.Pid)==0&&
            list[i].Pio==exam.Pio&&
            strcmp(list[i].Time,exam.Time)==0) {
            search=list[i];
            result++;
            id=i;
            break;
        }
    }
    printf("--------------------------------------------------\n");
    if (result==0) {
        printf("没有找到结果！\n");
        return -1;
    } else {
        printf("%s\t", search.Pjob);
        printf("%s\t", search.Pname);
        printf("%s\t", search.Pnum);
        printf("%s\t", search.Cinfo);
        printf("%s\t", search.Pid);
        printf("%d\t", search.Pio);
        printf("%s\n", search.Time);
        printf("即将修改这条数据！");
        if (isyn()==0) {
            int num;
            int IO;
            char temp[100];
            struct people new;
            new=list[id];
            do {
                printf("需要修改哪项数据(0~6)？");
                scanf("%d",&num);
                if (num>6||num<0) {
                    printf("输入有误，请重新输入！\n");
                }
            }while (num>6||num<0);
            printf("请输入需要修改的数据：");
            switch (num) {
                case 5:
                    scanf("%d",&IO);
                    new.Pio=IO;
                    break;
                default:
                    scanf("%s",temp);
                    switch (num) {
                        case 0:
                            strcpy(new.Pjob, temp);
                            break;
                        case 1:
                            strcpy(new.Pname, temp);
                            break;
                        case 2:
                            strcpy(new.Pnum, temp);
                            break;
                        case 3:
                            strcpy(new.Cinfo, temp);
                            break;
                        case 4:
                            strcpy(new.Pid, temp);
                            break;
                        case 6:
                            strcpy(new.Time, temp);
                            break;
                        default:
                            break;
                    }
                break;
            }
            if (isList(new)==0) {
                list[id]=new;
                printf("修改成功！\n");
                return 0;
            } else {
                printf("输入数据不合法，修改失败！\n");
                return -1;
            }
        } else {
            printf("操作取消！\n");
            return -1;
        }
    }
    return -1;
}

//today执行按某个日期统计功能
void today(int IO)
{
    char date[100];
    printf("请输入需要统计的日期：");
    scanf("%s",date);

    int Student=0,Teacher=0,Other=0;
    struct people result[100];
    int i,j;
    for (i=0,j=0; i<total; i++) {
        if (strcmp(list[i].Pname,date)==0&&list[i].Pio==IO) {
            result[j]=list[i];
            j++;
            if (strcmp(list[i].Pjob,"学生")==0) {
                Student++;
            }
            if (strcmp(list[i].Pjob,"教职工")==0) {
                Teacher++;
            }
            if (strcmp(list[i].Pjob,"其他")==0) {
                Other++;
            } else {
                printf("程序出错，请稍后重试！");
                return;
            }
        }
    }
    int All=j;
    printf("--------------------------------------------------\n");
    if (All==0) {
        printf("当天没有任何信息可以统计！\n");
    } else {
        for (j=0; j<All; j++) {
            printf("%s\t", result[j].Pjob);
            printf("%s\t", result[j].Pname);
            printf("%s\t", result[j].Pnum);
            printf("%s\t", result[j].Cinfo);
            printf("%s\t", result[j].Pid);
            printf("%s\t", result[j].Pid);
            printf("%d\t", result[j].Pio);
            printf("%s\n", result[j].Time);
        }
        if (IO==0) {
            printf("当天共有%d人出校，所有数据已全部显示。\n",All);
        } else {
            printf("当天共有%d人入校，所有数据已全部显示。\n",All);
        }
        printf("其中：学生%d人，教职工%d人，其他%d人。\n",Student,Teacher,Other);
    }
    return;
}

//all执行所有时间段统计功能
void all(int IO)
{
    int Student=0,Teacher=0,Other=0;
    struct people result[100];
    int i,j;
    for (i=0,j=0; i<total; i++) {
        if (list[i].Pio==IO) {
            result[j]=list[i];
            j++;
            if (strcmp(list[i].Pjob,"学生")==0) {
                Student++;
            }
            if (strcmp(list[i].Pjob,"教职工")==0) {
                Teacher++;
            }
            if (strcmp(list[i].Pjob,"其他")==0) {
                Other++;
            }
        }
    }
    int All=j;
    printf("--------------------------------------------------\n");
    if (All==0) {
        printf("所有时段内没有任何信息可以统计！\n");
    } else {
        for (j=0; j<All; j++) {
            printf("%s\t", result[j].Pjob);
            printf("%s\t", result[j].Pname);
            printf("%s\t", result[j].Pnum);
            printf("%s\t", result[j].Cinfo);
            printf("%s\t", result[j].Pid);
            printf("%s\t", result[j].Pid);
            printf("%d\t", result[j].Pio);
            printf("%s\n", result[j].Time);
        }
        if (IO==0) {
            printf("所有时段内共有%d人出校，所有数据已全部显示。\n",All);
        } else {
            printf("所有时段内共有%d人入校，所有数据已全部显示。\n",All);
        }
        printf("其中：学生%d人，教职工%d人，其他%d人。\n",Student,Teacher,Other);
    }
    return;
}

//count执行统计类型选择功能
void count()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内还没有任何数据，暂时无法统计！\n");
        return;
    }

    printf("A.统计当天出校总数\n");
    printf("B.统计当天入校总数\n");
    printf("C.统计所有时段出校人员总数\n");
    printf("D.统计所有时段入校人员总数\n");
    printf("E.退出\n");
    char code;
    do {
        printf("请选择（A~E）：");
        scanf("%s",&code);
        if (isABCDE(code)!=0) {
            printf("输入不合法，请重新输入！\n");
        }
    }while (isABCDE(code)!=0);
    
    switch (code) {
        case 'A':
            today(0);
            break;
        case 'B':
            today(1);
            break;
        case 'C':
            all(0);
            break;
        case 'D':
            all(1);
            break;
        case 'E':
            printf("即将返回主菜单。\n");
            return;
        default:
            printf("出现错误！即将返回主菜单。\n");
            return;
    }
    return;
}

//timecmp执行两个日期比较先后的功能，并返回结果代码
int timecmp(char time1[],char time2[])//相等返回0，左边早返回1，右边早返回-1
{
    //使用的字符串转结构体的魔法
    struct date{
        int year;
        int month;
        int day;
    } d1,d2;

    d1.year=time1[0]*1000+time1[1]*100+time1[2]*10+time1[3];
    d1.month=time1[5]*10+time1[6];
    d1.day=time1[8]*10+time1[9];

    d2.year=time2[0]*1000+time2[1]*100+time2[2]*10+time2[3];
    d2.month=time2[5]*10+time2[6];
    d2.day=time2[8]*10+time2[9];

    if (d1.year<d2.year) {
        return 1;
    } else if (d1.year>d2.year) {
        return -1;
    } else {
        if (d1.month<d2.month) {
            return 1;
        } else if (d1.month>d2.month) {
            return -1;
        } else {
            if (d1.day<d2.day) {
                return 1;
            } else if (d1.day>d2.day) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}

//sort执行数据排序功能
void sort(int order)//order：降序为1，升序为-1
{
    struct people new[100];
    int i=0,j=0;
    for (i=0; i<total; i++) {
        new[i]=list[i];
    }

    for (i=0; i<total-1; i++) {
        for (j=0; j<total-i-1; j++) {
            if (timecmp(new[j].Time,new[j+1].Time)==order) {
                struct people temp;
                temp=new[j];
                new[j]=new[j+1];
                new[j+1]=temp;
            }
        }
    }
    printf("--------------------------------------------------\n");
    for (j=0; j<total; j++) {
        printf("%s\t", new[j].Pjob);
        printf("%s\t", new[j].Pname);
        printf("%s\t", new[j].Pnum);
        printf("%s\t", new[j].Cinfo);
        printf("%s\t", new[j].Pid);
        printf("%s\t", new[j].Pid);
        printf("%d\t", new[j].Pio);
        printf("%s\n", new[j].Time);
    }
    if (order==1) {
    printf("已对%d条数据进行了降序排序，所有数据已全部显示。\n",total);
    } else {
    printf("已对%d条数据进行升序排序处理，所有数据已全部显示。\n",total);
    }
    return;
}

//reorder执行排序入口功能
void reorder()
{
    if (total==0) {
        read();
    }
    if (total==0) {
        printf("系统内还没有任何数据，暂时无法排序！\n");
        return;
    }

    printf("A.对出校人员按出校时间进行降序排序\n");
    printf("B.对出校人员按出校时间进行升序排序\n");
    printf("C.退出\n");
    char code;
    do {
        printf("请选择（A~C）：");
        scanf("%s",&code);
        if (isABC(code)!=0) {
            printf("输入不合法，请重新输入！\n");
        }
    }while (isABC(code)!=0);
    
    switch (code) {
        case 'A'://降序
            sort(1);
            break;
        case 'B'://升序
            sort(-1);
            break;
        case 'C':
            printf("即将返回主菜单。\n");
            return;
        default:
            printf("出现错误！即将返回主菜单。\n");
            return;
    }
    return;
}

//main函数，主程序
int main()
{
    for (;;) {
        int key=welcome();
        switch (key) {
            case 1://录入
                if (put_in()==0) {
                    save();
                }
                break;
            case 2://保存
                save();
                break;
            case 3://浏览
                view();
                break;
            case 4://查询
                search();
                break;
            case 5://增加
                if (add()==0) {
                    save();
                }
                break;
            case 6://删除
                if (delete()==0) {
                    save();
                }
                break;
            case 7://修改
                if (edit()==0) {
                    save();
                }
                break;
            case 8://统计
                count();
                break;
            case 9://排序
                reorder();
                break;
            case 10://退出
                printf("注意，你即将退出系统！");
                if (isyn()==0) {
                    return 0;
                } else {
                    printf("操作已取消！");
                    break;
                }
            default:
                printf("程序出错，即将重试！\n");
                break;
        }
        system("read -p '按回车键继续...' var");
    } 
}


// END 谢谢各位！！！我的代码 bug 修完了！！！！！！！！！！！！！！！！！！！！！！！
//激动的 Chris Liu 于 湖南
//时间：2022/12/09 凌晨 00:54
