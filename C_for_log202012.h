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
