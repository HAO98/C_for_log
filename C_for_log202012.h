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
	LOG_SAVE = 0,//������Ҫ����־����Ҫʵʱ�����
	LOG_DEL = 1,//����ɾ�����Զ�ʱɾ�����޸�״̬����������
};//��־״̬ö��

enum FUN_STATU {
	FUN_SUCCESS = 0,
	FUN_NOT_FIND_FILE = 1,
	FUN_STR_LEN_THAN_256 = 2,
	FUN_INFO_NULL = 3,
	FUN_WRITE_FAIL = 4,
	FUN_READ_FAIL = 5
};//��������ö��

typedef char s8;//8λ => (-128 - 127)
typedef short s16;//16λ => (-32768 - 32767)
typedef int s32;//32λ => (-2147483648-2147483647) => 21��
typedef long long s64;//32λ => (-2147483648-2147483647)
typedef unsigned char u8;//8λ => (0 - 255)
typedef unsigned short u16;//16λ => (0-65535)
typedef unsigned int u32;//32λ => (0-4294967295) => 42��
typedef unsigned long long u64;//32λ => (0-4294967295)

typedef struct Log {
	u8 log[256];//��־��Ϣ
	u8 statu;//��־״̬
	u8 align[3];//����4�ֽڶ���
	u32 time;//ʱ���

}Log;

Log log[LOG_NUM];//�ƻ��洢4����־
u32 logIndex = 0;//��־��ǰ���±�

//������־,׷������־β��
u32 addToFile(FILE* pFile, u8* info);

//ɾ����־
u32 delLog(u32 i);

//��ȡ��־
u32 readLog(FILE* pFile);

















#ifdef __cplusplus
}
#endif

#endif
