#define _CRT_SECURE_NO_WARNINGS
#include "C_for_log202012.h"


u32 addToFile(FILE* pFile, u8* info)
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

u32 delLog(u32 i)
{
	log[i].statu = LOG_DEL;//没有必要因为一条数据，去重新排序数据内存
	return FUN_SUCCESS;
}

u32 readLog(FILE* pFile)
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


