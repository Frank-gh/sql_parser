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
