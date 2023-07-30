/*
这是一个头文件，内含函数声明、宏定义、结构体定义等内容
*/

//图书结构体：图书编号，书名，作者，出版社信息，库存量，下一个节点指针
typedef struct book{
    int bID;
    char bName[20];
    char author[15];
    char press[20];
    int amount;
    struct book* next;
}Book;
//读者结构体：读者id，姓名，性别，可借书数，已借书的编号，下一个节点指针
typedef struct reader{
    int rID;
    char name[20];
    char sex[10];
    int max_amount;
    int bIDs[3];
    struct reader* next;
}Reader;

//相关函数声明
void showMenu();

void showLibInfo(Book* book_head, Reader* reader_head);
void showBooks(Book* book_head);

Book* addBook(Book* book_head);
Book* delBook(Book* book_head);
void findBook(Book* book_head);
int borrowBook(Book* book_head, int book_id);
int returnBook(Book* book_head,int book_id);

Reader* addReader(Reader* reader_head);
Reader* delReader(Reader* reader_head);
void findReader(Reader* reader_head);
void borrowReader(Reader* reader_head,Book* book_head,int book_id);
void returnReader(Reader* reader_head,Book* book_head,int book_id);

void saveBook(Book* book_head);
Book* readBook();
void saveReader(Reader* reader_head);
Reader* readReader();
