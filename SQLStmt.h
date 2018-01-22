/*************************************************************************                                                           
    > File Name: SQLStmt.h
    > Author: Shylock
    > Mail: xiake@dce.com.cn
    > Created Time: 2017-03-13 09:03:21
 ************************************************************************/

#ifndef __CSQLSTMT_H__
#define __CSQLSTMT_H__

#include <vector>
#include <string.h>
#include <list>
#include <iostream>
#include <stdio.h>

using namespace std;
/*
* 字段类型
*/
enum FLDTYPE{
    _STRING,
    _NUMBER,
    _DOUBLE,
    _NONE_FLD
};
/*
* where条件的逻辑关系
*/
enum WHERE_REL{
    _AND,
    _OR,
    _NONE_REL
};
/*
* where条件
*/
struct KWHERESTMT{
    string fld;
    FLDTYPE type;
    string value;
    WHERE_REL rel;
    KWHERESTMT *next;
    KWHERESTMT(){fld = ""; type = _NONE_FLD; value = ""; rel = _NONE_REL; next = NULL;};
};

class CSQLStmt
{
public:
    CSQLStmt(){m_bAllFlds = false; m_sTable = ""; m_pWhere = NULL; m_vSqlStmtError = false; m_iConditionCount = 0;};
    ~CSQLStmt()
    {
        while(m_pWhere)
        {
            KWHERESTMT* tmp;
            tmp = m_pWhere;
            m_pWhere = m_pWhere->next;
            delete tmp;
        }
    };
    /*
    * 输出类信息，调试时使用
    */
    string OutPut()
    {
        string str = "";
        if (m_vSqlStmtError)
            return "SQL STATMENT ERROR !\n";
        if (m_bAllFlds)
            str += "GET ALL FIELD : TRUE\n";
        else
            str += "GET ALL FIELD : FALSE\n";
        str += "TABLE: " + m_sTable + "\n";
        str += "FIELDS: ";
        for (vector<string>::iterator it = m_vFlds.begin(); it != m_vFlds.end(); it++)
        {
            str += *it + "\t";
        }
        char tmp_str[128];
        memset(tmp_str,0x0,sizeof(tmp_str));
        sprintf(tmp_str,"\nTHERE IS %d CONDITIONS: \n", m_iConditionCount);
        str += tmp_str;
        
        int i = 0;
        while(m_pWhere)
        {
            memset(tmp_str,0x0,sizeof(tmp_str));
            sprintf(tmp_str,"\tCONDITION %d :\n",++i);
            str += tmp_str;
            memset(tmp_str,0x0,sizeof(tmp_str));
            sprintf(tmp_str,"\t\tNAME : %s\n",m_pWhere->fld.c_str());
            str += tmp_str;
            memset(tmp_str,0x0,sizeof(tmp_str));
            sprintf(tmp_str,"\t\tTYPE : %d\n",m_pWhere->type);
            str += tmp_str;
            memset(tmp_str,0x0,sizeof(tmp_str));
            sprintf(tmp_str,"\t\tVALUE : %s\n",m_pWhere->value.c_str());
            str += tmp_str;
            memset(tmp_str,0x0,sizeof(tmp_str));
            sprintf(tmp_str,"\t\tREL : %d\n",m_pWhere->rel);
            str += tmp_str;
            if (m_pWhere->next)
            {
                memset(tmp_str,0x0,sizeof(tmp_str));
                sprintf(tmp_str,"\t\tNEXT : %s\n",m_pWhere->next->fld.c_str());
                str += tmp_str;
            }

            m_pWhere = m_pWhere->next;
        }
        
        return str;
    };
    /*
    * 添加条件之间的逻辑关系
    */
    void AddWhereRel(vector<WHERE_REL>& rel)
    {
        int i = 0;
        KWHERESTMT* tmp = m_pWhere;
        while(tmp->next)
        {
            tmp->rel = rel[++i];
            tmp = tmp->next;
        }
        return;
    }
    /*
    * 添加一个where条件
    */
    void AddWhereCondition(string fld,FLDTYPE type,string value)
    {
        m_iConditionCount++;
        KWHERESTMT* where = new KWHERESTMT();
        where->fld = fld;
        where->type = type;
        if (type == _STRING)
            where->value = value.substr(1,value.length()-2);
        else
            where->value = value;
        if (!m_pWhere)
        {
            m_pWhere = where;
        }
        else
        {
            KWHERESTMT* tmp = m_pWhere;
            while(tmp->next)
                tmp = tmp->next;
                
            tmp->next = where;
        }

        return;
    };
    /*
    * 清理环境
    */
    void Clear()
    {
        m_iConditionCount = 0;
        m_vSqlStmtError = false;
        m_bAllFlds = false;
        m_vFlds.clear();
        m_sTable = "";
        while(m_pWhere)
        {
            KWHERESTMT* tmp;
            tmp = m_pWhere;
            m_pWhere = m_pWhere->next;
            delete tmp;
        }
    }
public:
    int m_iConditionCount;  // where条件的数量
    bool m_vSqlStmtError;   // sql语法错误
    bool m_bAllFlds;        // 是否查询所有字段
    vector<string> m_vFlds; // 字段列表
    string m_sTable;        // 表名
    KWHERESTMT* m_pWhere;   // where条件链表头指针
};

#endif
