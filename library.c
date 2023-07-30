#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include "library.h"

int main(){
    entry: system("clear");
    printf("欢迎登录图书管理系统，请输入管理员帐号与密码\n");
    char account[10];
    char pwd[10];
    printf("帐号: ");
    scanf("%s",account);
    getchar();
    printf("密码: ");
    scanf("%s",pwd);
    if(strcmp(account,"admin")==0 && strcmp(pwd,"123456")==0){
        showMenu(); //绘制菜单
        int choice;
        scanf("%d",&choice);
        Book* bhead = readBook();
        Reader* rhead = readReader();
        int id;
        while(1){
            switch(choice)
            {
            case 0:
                return 0;
                break;
            case 1:
                showLibInfo(bhead,rhead);
                break;
            case 2:
                showBooks(bhead);
                break;
            case 3:
                addBook(bhead);
                break;
            case 4:
                delBook(bhead);
                break;
            case 5:
                findBook(bhead);
                break;
            case 6:
                addReader(rhead);
                break;
            case 7:
                delReader(rhead);
                break;
            case 8:
                findReader(rhead);
                break;
            case 9:
                printf("输入要借图书的编号:");
                scanf("%d",&id);
                getchar();
                borrowReader(rhead,bhead,id);
                break;
            case 10:
                printf("输入要还图书的编号:");
                scanf("%d",&id);
                getchar();
                returnReader(rhead,bhead,id);
                break;
            default:
                printf("输入有误，请重新输入!\n");
                sleep(2);
            }
            system("clear");
            showMenu();
            scanf("%d",&choice);
        }
    }else{
        printf("请输入正确的帐号与密码!\n");
        fflush (stdin);
        printf("\n按任意键继续!");
        getchar();
        goto entry;
    }
    return 0;
}

//相关函数实现
//展示菜单
void showMenu(){
	printf("----------------------欢迎进入---------------------------\n");
	printf("                    图书管理系统                              \n");
	printf("                  1、查询总信息                         \n");
	printf("                  2、查询藏书信息                          \n");
	printf("                  3、增加新书                                  \n");
	printf("                  4、删除旧书                                  \n");
	printf("                  5、查找书籍                                  \n");
	printf("                  6、增加新读者                                  \n");
	printf("                  7、删除读者                                  \n");
	printf("                  8、查找读者                                  \n");
	printf("                  9、读者借书                                 \n");
	printf("                  10、读者还书                                 \n");
	printf("                  0、退出                                     \n");
	printf("---------------------------------------------------------\n");
	printf("请选择(0-10): ");
}

//显示图书馆的书本数量和读者数量信息
void showLibInfo(Book* book_head, Reader* reader_head){
    book_head = readBook();
    reader_head = readReader();
    Book* book = book_head;
    Reader* reader = reader_head;
    int book_num=0;
    int reader_num=0;
    while(book!=NULL){
        book_num++;
        book = book->next;
    }
    while(reader!=NULL){
        reader_num++;
        reader = reader->next;
    }
    printf("本图书馆共有藏书%d本,读者%d人\n",book_num,reader_num);
    fflush (stdin);
    printf("\n按任意键继续!");
    getchar();
    return;
}
//显示所有图书信息
void showBooks(Book* book_head){
    book_head = readBook();
    Book* book = book_head;
    printf("图书编号 书名 作者 出版社信息 库存量\n");
    while(book!=NULL){
        printf("%d %s %s %s %d\n",book->bID,book->bName,book->author,book->press,book->amount);
        book = book->next;
    }
    fflush (stdin);
    printf("\n按任意键继续!");
    getchar();
    return;
}

//增加新书,返回头指针
Book* addBook(Book* book_head){
    book_head = readBook();
    Book* book = book_head;
    //若此时是空链表，则直接添加新节点
    if(book==NULL){
        //开辟新的节点空间
        Book* tmp = (Book*)malloc(sizeof(Book));
        assert(tmp);    //判断分配空间是否成功
        printf("输入图书的编号:");
        scanf("%d",&tmp->bID);//这里假设图书的编号都是唯一的，不作判断
        getchar();
        printf("输入图书的名称:");
        scanf("%s",tmp->bName);
        printf("输入图书的作者:");
        scanf("%s",tmp->author);
        printf("输入图书的出版社:");
        scanf("%s",tmp->press);
        printf("输入图书的库存量:");
        scanf("%d",&tmp->amount);
        getchar();
        tmp->next = NULL;
        book = tmp;
        saveBook(book);
        printf("添加成功，按任意键返回\n");
        getchar();
        return book;
    }
    //若不是空链表，则需要找到最后一个节点
    while(book->next!=NULL){
        book = book->next;
    }
    //此时找到的book为最后一个节点
    //开辟新的节点空间
    int flag = 1;
    while(flag){
        Book* tmp = (Book*)malloc(sizeof(Book));
        assert(tmp);    //判断分配空间是否成功
        printf("输入图书的编号:");
        scanf("%d",&tmp->bID);//这里假设图书的编号都是唯一的，不作判断
        getchar();
        printf("输入图书的名称:");
        scanf("%s",tmp->bName);
        printf("输入图书的作者:");
        scanf("%s",tmp->author);
        printf("输入图书的出版社:");
        scanf("%s",tmp->press);
        printf("输入图书的库存量:");
        scanf("%d",&tmp->amount);
        getchar();
        tmp->next = NULL;
        book->next = tmp;
        book = tmp;
        saveBook(book_head);

        printf("添加成功，是否继续输入:1=>继续\t 0=>结束\n");
        scanf("%d",&flag);
        getchar();
        if(flag==0){
            printf("按任意键返回\n");
            getchar();
            return book_head;
        }
    }
    return book_head;
}   //链表的尾插法要记得判断头指针是否为空！！！
//删除图书，返回头指针
Book* delBook(Book* book_head){
    book_head = readBook();
    Book* book = book_head;
    Book* prev = book_head;
    printf("输入要删除旧书的编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该编号是否存在，然后进行删除
    while(book!=NULL){
        if(book->bID==id){
            if(book==book_head){
                book = book->next;
                free(prev);
                printf("已将旧书删除！\n");
                remove("book.txt");
                printf("按任意键返回\n");
                getchar();
                return book;
            }
            prev->next = book->next;
            free(book);
            printf("已将旧书删除！\n");
            saveBook(book_head);
            printf("按任意键返回\n");
            getchar();
            return book_head;
        }
        prev = book;
        book = book->next;
    }
    printf("没有找到该图书\n");
    printf("按任意键返回\n");
    getchar();
    return book_head;
}
//查找某图书的信息
void findBook(Book* book_head){
    book_head = readBook();
    Book* book = book_head;
    printf("输入要查找图书的编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该编号是否存在
    while(book!=NULL){
        if(book->bID==id){
            printf("图书编号\t书名\t作者\t出版社信息\t库存量\n");
            printf("%d\t%s\t%s\t%s\t%d\n",book->bID,book->bName,book->author,book->press,book->amount);
            printf("按任意键返回\n");
            getchar();
            return;
        }
        book = book->next;
    }
    printf("没有找到该图书\n");
    printf("按任意键返回\n");
    getchar();
    return;
}
//借书，若成功则返回1
int borrowBook(Book* book_head, int book_id){
    book_head = readBook();
    Book* book = book_head;
    //遍历链表判断该编号是否存在
    while(book!=NULL){
        if(book->bID==book_id){
            //判断书籍所剩库存量
            if(book->amount>0){
                book->amount--;
                saveBook(book_head);
                printf("该书所剩库存量减一\n");
                return 1;
            }
            printf("该书所剩库存量为0,无法再借!\n");
            return 0;
        }
        book = book->next;
    }
    printf("不存在该图书！\n");
    return 0;
}
//还书，若成功则返回1
int returnBook(Book* book_head,int book_id){
    book_head = readBook();
    Book* book = book_head;
    //遍历链表判断该编号是否存在
    while(book!=NULL){
        if(book->bID==book_id){ //存在该编号的图书
            book->amount++;
            saveBook(book_head);
            printf("该书所剩库存量加一\n");
            return 1;
        }
        book = book->next;
    }
    printf("不存在该图书！\n");
    return 0;
}

//增加新读者，返回头指针
Reader* addReader(Reader* reader_head){
    reader_head = readReader();
    Reader* reader = reader_head;
    //若此时是空链表，则直接添加新节点
    if(reader==NULL){
        //开辟新的节点空间
        Reader* tmp = (Reader*)malloc(sizeof(reader));
        assert(tmp);    //判断分配空间是否成功
        printf("输入读者的编号:");
        scanf("%d",&tmp->rID);//这里假设图书的编号都是唯一的，不作判断
        getchar();
        printf("输入读者的姓名:");
        scanf("%s",tmp->name);
        printf("输入读者的性别:");
        scanf("%s",tmp->sex);
        tmp->max_amount = 3;
        int i;
        for(i=0;i<3;i++){
            tmp->bIDs[i] = -1;
        }
        tmp->next = NULL;
        reader = tmp;
        saveReader(reader);

        printf("添加成功，按任意键返回\n");
        getchar();
        return reader;
    }
    //若不是空链表，则需要找到最后一个节点
    while(reader->next!=NULL){
        reader = reader->next;
    }
    //此时找到的reader为最后一个节点
    //开辟新的节点空间
    int flag = 1;
    while(flag){
        Reader* tmp = (Reader*)malloc(sizeof(reader));
        assert(tmp);    //判断分配空间是否成功
        printf("输入读者的编号:");
        scanf("%d",&tmp->rID);//这里假设图书的编号都是唯一的，不作判断
        getchar();
        printf("输入读者的姓名:");
        scanf("%s",tmp->name);
        printf("输入读者的性别:");
        scanf("%s",tmp->sex);
        tmp->max_amount = 3;
        int i;
        for(i=0;i<3;i++){
            tmp->bIDs[i] = -1;
        }
        tmp->next = NULL;
        reader->next = tmp;
        reader = tmp;
        saveReader(reader_head);
        printf("添加成功，是否继续添加:1=>继续\t 0=>结束\n");
        scanf("%d",&flag);
        getchar();
        if(flag==0){
            printf("按任意键返回\n");
            getchar();
            return reader_head;
        }
    }
    return reader_head;
}

//删除读者，返回头指针
Reader* delReader(Reader* reader_head){
    reader_head = readReader();
    Reader* reader = reader_head;
    Reader* prev = reader_head;
    printf("输入要删除读者的编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该编号是否存在，然后进行删除
    while(reader!=NULL){
        if(reader->rID==id){
            //判断此时读者是否还持有所借图书
            int i;
            for(i=0;i<3;i++){
                if(reader->bIDs[i]>=0){
                    printf("该读者还持有所借图书，不可删除！\n");
                    return reader_head;
                }
            }
            //若未持有则继续判断是否是头节点
            if(reader==reader_head){
                reader = reader->next;
                free(prev);
                printf("已将读者删除！\n");
                remove("reader.txt");
                printf("按任意键返回\n");
                getchar();
                return reader;
            }
            prev->next = reader->next;
            free(reader);
            printf("已将读者删除！\n");
            saveReader(reader_head);
            printf("按任意键返回\n");
            getchar();
            return reader_head;
        }
        prev = reader;
        reader = reader->next;
    }
    printf("没有找到该读者\n");
    printf("按任意键返回\n");
    getchar();
    return reader_head;
}

//查找某读者的信息
void findReader(Reader* reader_head){
    reader_head = readReader();
    Reader* reader = reader_head;
    printf("输入要查找读者的编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该编号是否存在
    while(reader!=NULL){
        if(reader->rID==id){
            printf("读者编号 读者姓名 读者性别\n");
            printf("%d %s %s\n",reader->rID,reader->name,reader->sex);
            printf("读者目前所借图书有：\n");
            int i=0;
            while(i<3){
                if(reader->bIDs[i]>=0){
                    printf("%d\n",reader->bIDs[i]);
                }
                i++;
            }
            printf("\n按任意键返回\n");
            getchar();
            return;
        }
        reader = reader->next;
    }
    printf("没有找到该读者\n");
    printf("按任意键返回\n");
    getchar();
    return;
}

//借还书修改读者信息
//借书
void borrowReader(Reader* reader_head,Book* book_head,int book_id){
    reader_head = readReader();
    Reader* reader = reader_head;
    printf("输入读者编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该读者编号是否存在
    while(reader!=NULL){
        if(reader->rID==id){
            //判断读者是否还能借书
            if(reader->max_amount==0){
                printf("该读者所借书量已达上限，无法再借！\n");
                fflush (stdin);
                printf("\n按任意键继续!");
                getchar();
                return;
            }
            //若未达上限，则继续判断
            int i;
            for(i=0;i<3;i++){
                if(reader->bIDs[i]==-1){ //满足条件，可借
                    //判断书籍情况
                    if(borrowBook(book_head,book_id)==0){
                        return;
                    }
                    //修改读者相关数据信息
                    reader->bIDs[i]=book_id;
                    reader->max_amount--;
                    saveReader(reader_head);
                    printf("该读者已成功借阅！\n");
                    fflush (stdin);
                    printf("\n按任意键继续!");
                    getchar();
                    return;
                }
            }
            fflush (stdin);
            printf("按任意键返回\n");
            getchar();
            return;
        }
        reader = reader->next;
    }
    printf("不存在该读者！\n");
    printf("按任意键返回\n");
    getchar();
    return;
}

//还书
void returnReader(Reader* reader_head,Book* book_head,int book_id){
    reader_head = readReader();
    Reader* reader = reader_head;
    printf("输入读者编号:");
    int id;
    scanf("%d",&id);
    getchar();
    //遍历链表判断该读者编号是否存在
    while(reader!=NULL){
        if(reader->rID==id){
            //判断读者是否借过该书
            int i;
            for(i=0;i<3;i++){
                if(reader->bIDs[i]==book_id){
                    //若有相关记录，则判断书籍信息
                    if(returnBook(book_head,book_id)==0){
                        return;
                    }
                    reader->bIDs[i]=-1;
                    reader->max_amount++;
                    saveReader(reader_head);
                    printf("该读者已成功归还！\n");
                    fflush (stdin);
                    printf("\n按任意键继续!");
                    getchar();
                    return;
                }
            }
            printf("该读者尚未借过该图书！\n");
            fflush (stdin);
            printf("\n按任意键继续!");
            getchar();
            return;
        }
        reader = reader->next;
    }
    printf("不存在该读者！\n");
    fflush (stdin);
    printf("\n按任意键继续!");
    getchar();
    return;
}

//将链表中的书籍信息存入文件中
void saveBook(Book* book_head){
    FILE* fp;
    Book* pCur = book_head;
    int count=0;

    if(pCur == NULL){
        printf("暂无书籍信息，无法存储！\n");
        return;
    }
    //若头指针不为空，创建文件存储，每次都重新存储所有信息
    if((fp=fopen("book.txt","wb"))==NULL){
        printf("创建文件失败!\n");
        getchar();
        exit(1); //退出程序，并将参数1的值返回给主调进程,0表示正常退出,1/-1表示异常退出
    }
    //若成功创建新文件，将所有节点信息写入
    while(pCur){
        fwrite(pCur,sizeof(Book),1,fp);
        pCur = pCur->next;
        count++;
    }
    printf("保存书籍的节点数目为:%d\n",count);
    fclose(fp);
}
//从文件中读取全部的书籍链表信息，返回头指针
Book* readBook(){
    FILE* fp;
    Book* pHead = NULL;
    Book* pTemp = NULL;
    Book* pCur = NULL;
    if((fp=fopen("book.txt","rb"))==NULL){
        // printf("文件打开失败，请检查文件名!\n");
        return NULL;
    }
    //开辟节点空间来存储节点元素
    pTemp = (Book*)malloc(sizeof(Book));
    while(fread(pTemp,sizeof(Book),1,fp)){
        if(!pHead){
            pHead = pTemp;
            pCur = pTemp;
        }else{
            pCur->next = pTemp;
            pCur = pTemp;
        }
        pTemp = (Book*)malloc(sizeof(Book));
    }
    fclose(fp);
    return pHead;
}

//将链表中的读者信息存入文件中
void saveReader(Reader* reader_head){
    FILE* fp;
    Reader* pCur = reader_head;
    int count=0;

    if(pCur == NULL){
        printf("暂无读者信息，无法存储！\n");
        return;
    }
    //若头指针不为空，创建文件存储，每次都重新存储所有信息
    if((fp=fopen("reader.txt","wb"))==NULL){
        printf("创建文件失败!\n");
        getchar();
        exit(1); //退出程序，并将参数1的值返回给主调进程,0表示正常退出,1/-1表示异常退出
    }
    //若成功创建新文件，将所有节点信息写入
    while(pCur){
        fwrite(pCur,sizeof(Reader),1,fp);
        pCur = pCur->next;
        count++;
    }
    printf("保存读者的节点数目为:%d\n",count);
    fclose(fp);
}
//从文件中读取全部的读者链表信息，返回头指针
Reader* readReader(){
    FILE* fp;
    Reader* pHead = NULL;
    Reader* pTemp = NULL;
    Reader* pCur = NULL;
    if((fp=fopen("reader.txt","rb"))==NULL){
        // printf("文件打开失败，请检查文件名!\n");
        return NULL;
    }
    //开辟节点空间来存储节点元素
    pTemp = (Reader*)malloc(sizeof(Reader));
    while(fread(pTemp,sizeof(Reader),1,fp)){
        if(!pHead){
            pHead = pCur = pTemp;
        }else{
            pCur->next = pTemp;
            pCur = pTemp;
        }
        pTemp = (Reader*)malloc(sizeof(Reader));
    }
    fclose(fp);
    return pHead;
}