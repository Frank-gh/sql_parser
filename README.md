# sql_parser
> flex &amp;&amp; bison 实现的简单sql解析器

### 编译
```shell
$ make
-rw-rw-r-- 1 frank frank 414726 1月  22 10:32 libparsql.a
-rwxrwxr-x 1 frank frank 251408 1月  22 10:32 libparsql.so*
-rw-rw-r-- 1 frank frank    351 3月  24  2017 main.cpp
-rw-r--r-- 1 frank frank   1135 3月  12  2017 Makefile
-rwxrwxr-x 1 frank frank 241296 1月  22 10:32 parsql*
-rw-rw-r-- 1 frank frank 128414 1月  22 10:32 parsql.c
-rw-r--r-- 1 frank frank   9771 3月  11  2017 parsql.l
-rw-rw-r-- 1 frank frank 302415 1月  22 10:32 parsql.output
-rw-rw-r-- 1 frank frank 146940 1月  22 10:32 parsql.tab.c
-rw-rw-r-- 1 frank frank   6656 1月  22 10:32 parsql.tab.h
-rw-r--r-- 1 frank frank  28053 3月  24  2017 parsql.y
-rw-rw-r-- 1 frank frank   4626 3月  24  2017 SQLStmt.h
```

### 测试
** main.cpp **
```c++
#include <stdlib.h>                                                                                                                 
#include "SQLStmt.h"
#include "parsql.tab.h"
#include <iostream>
#include <stdio.h>
 
using namespace std;
 
int parser_sql(string sql);
extern CSQLStmt g_cSqlStmt;
 
int main(int ac, char **av)
{
    parser_sql("select a,a,b,c from b where i=3.2 or j=1 and k='2';");
 
    printf("%s\n", g_cSqlStmt.OutPut().c_str());
    return 0;
}
```
** 运行 **
```shell
$ ./parsql 
GET ALL FIELD : FALSE
TABLE: b
FIELDS: a	a	b	c	
THERE IS 3 CONDITIONS: 
	CONDITION 1 :
		NAME : i
		TYPE : 2
		VALUE : 3.2
		REL : 1
		NEXT : j
	CONDITION 2 :
		NAME : j
		TYPE : 1
		VALUE : 1
		REL : 0
		NEXT : k
	CONDITION 3 :
		NAME : k
		TYPE : 0
		VALUE : 2
		REL : 2

```
