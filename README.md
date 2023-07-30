# C-Library
小型的图书管理系统，涉及到c语言的结构体、指针、文件操作以及对链表的增删查改等，实现了基本的书籍信息、读者信息和借还书管理等功能。

### 图书管理系统设计
#### 1. 需要处理的对象有：
图书馆基本信息；书籍管理；管理员；读者信息。
#### 2. 需求分析：
查询图书馆的信息；书籍的增删查改；读者的增删查改；用文件充当数据库存储信息；
#### 3. 所涉及到的数据结构
图书结构体：图书编号，书名，作者，出版社信息，库存量，下一个节点指针  
读者结构体：读者id，姓名，性别，可借书数，已借书的编号，下一个节点指针
#### 4. 函数模块信息
a)主函数 int main()：调用Menu()函数，显示主界面  
b)查询图书馆信息——图书数量以及读者数量：  
void showLibInfo(Book* book_head,Reader* reader_head):  
函数接受两个形参，分别是图书的链表地址和读者的链表地址，并遍历两个链表，显示图书的数量和读者的数量。  
c)显示所有图书信息：  
void showBooks(Book* book_head):  
接受一个形参，图书的链表地址，遍历该链表，显示出所有图书的信息。  
// 关于图书的增删查改  
d)增加新图书  
Book* addBook(Book* book_head);  
利用尾插对链表进行修改，添加图书，并返回该图书的地址。  
e)删除图书  
Book* delBook(Book* book_head);  
遍历图书链表找到有一致编号的图书，然后删除返回空，否则失败返回图书地址。（要保证图书编号唯一）  
f)查找某图书的信息  
void findBook(Book* book_head):  
遍历图书链表找到有一致编号的图书，然后输出对应的信息。  
g)修改某图书的信息  
int borrowBook(Book* book_head)  
int returnBook(Book* book_head)  
遍历图书链表找到有一致编号的图书，然后修改对应的数量信息。  

// 关于读者的增删查改  
h)增加新的读者  
Reader* addReader();  
利用尾插对链表进行修改，添加读者，并返回该读者的地址。  
i)删除读者  
Reader* delReader(int readerID);  
接受一个形参，读者的id，遍历读者链表找到有一致id的读者，然后删除返回空，否则失败返回读者地址。（要保证图书编号唯一）  
j)查找某读者的信息  
void findReader(int readerID):  
接受一个形参，读者的id，遍历读者链表找到有一致id的读者，然后输出对应的信息。  
k)修改某读者的信息  
void changeReader(int readerID):  
接受一个形参，读者的id，遍历读者链表找到有一致id的读者，然后修改对应的信息。  

//读者借书模块  
void borrowBook(int readerID, int bookID):  
接受两个形参,读者id和图书编号，用读者的id进行匹配，找到该读者后，用图书的编号进行匹配，进行借书，否则返回  
//读者还书模块  
void returnBook(int readerID, int bookID):  
接受两个形参,读者id和图书编号，用读者的id进行匹配，找到该读者后，用图书的编号进行匹配，进行还书，否则返回  

//保存信息模块  
void saveBook()  
void saveReader()  

//读取信息模块  
Book* readBook()  
Reader* readReader()  

#### 5. 主要功能模块流程图
