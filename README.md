# C_for_log
一个非常简单增删改

**C_for_log202012.h**

```c
#ifndef C_FOR_LOG
#define C_FOR_LOG

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <time.h>
#include <windows.h> 

#define LOG_NUM 4

enum LOG_STATU {
	LOG_SAVE = 0,//对于重要的日志是需要实时保存的
	LOG_DEL = 1,//对于删除可以定时删除，修改状态来隐藏数据
};//日志状态枚举

enum FUN_STATU {
	FUN_SUCCESS = 0,
	FUN_NOT_FIND_FILE = 1,
	FUN_STR_LEN_THAN_256 = 2,
	FUN_INFO_NULL = 3,
	FUN_WRITE_FAIL = 4,
	FUN_READ_FAIL = 5
};//函数错误枚举

typedef char s8;//8位 => (-128 - 127)
typedef short s16;//16位 => (-32768 - 32767)
typedef int s32;//32位 => (-2147483648-2147483647) => 21亿
typedef long long s64;//32位 => (-2147483648-2147483647)
typedef unsigned char u8;//8位 => (0 - 255)
typedef unsigned short u16;//16位 => (0-65535)
typedef unsigned int u32;//32位 => (0-4294967295) => 42亿
typedef unsigned long long u64;//32位 => (0-4294967295)

typedef struct Log {
	u8 log[256];//日志信息
	u8 statu;//日志状态
	u8 align[3];//保持4字节对齐
	u32 time;//时间戳

}Log;

Log log[LOG_NUM];//计划存储4条日志
u32 logIndex = 0;//日志当前的下标

//新增日志,追加在日志尾部
int addToFile(FILE* pFile, u8* info);

//删除日志
int delLog(u32 i);

//读取日志
int readLog(FILE* pFile);


#ifdef __cplusplus
}
#endif

#endif
```

**C_for_log202012.c**

```c
#define _CRT_SECURE_NO_WARNINGS
#include "C_for_log202012.h"


int addToFile(FILE* pFile, u8* info)
{
	if (NULL == pFile)
		return FUN_NOT_FIND_FILE;

	if (NULL == info)
		return FUN_INFO_NULL;
	
	if(strlen(info) > 256)
		return FUN_STR_LEN_THAN_256;
	
	strcpy(log[logIndex].log, info);
	
	time_t t;
	t = time(NULL);
	log[logIndex].time = time(&t);
	
	log[logIndex].statu = LOG_SAVE;
	
	logIndex++;
	logIndex = logIndex % LOG_NUM;
	
	if (fwrite(&log, 264, LOG_NUM, pFile) == LOG_NUM)
		return FUN_SUCCESS;
	
	return FUN_READ_FAIL;
}

int delLog(u32 i)
{
	log[i].statu = LOG_DEL;//没有必要因为一条数据，去重新排序数据内存
	return FUN_SUCCESS;
}

int readLog(FILE* pFile)
{
	u32 num = 0, i = 0;
	if (NULL == pFile)
		return FUN_NOT_FIND_FILE;

	while (fread(&log, 264, LOG_NUM, pFile) > 0)
	{
	}
	
	return FUN_SUCCESS;

}

void testRead()
{
	FILE* p;
	p = fopen("./log.txt", "a+");
	printf("状态:%d\n",readLog(p));
	fclose(p);
}


void testWrite()
{
	FILE* p;
	p = fopen("./log.txt", "w+");
	for (u32 i = 0; i < LOG_NUM; i++)
	{
		printf("状态:%d\n",addToFile(p, "往WINDOW磁盘里面写入一条日志信息"));
		Sleep(1000);
	}
	fclose(p);
}
void main()
{
	memset(&log, 0, sizeof(log));
	//testWrite();
	testRead();
	delLog(0);
	

	for (u32 i = 0; i < LOG_NUM; i++)
	{
		if (log[i].statu == LOG_SAVE)
		{
			printf("日志信息:%s	|	时间:%d\n", log[i].log, log[i].time);
		}
	}
}
```