#pragma once
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

/*link winsock2 library*/
#pragma pack(1)
#pragma comment(lib, "Ws2_32.lib")

#define DP_SUCCESS					0
#define DP_CONNECTIONS				1
#define DP_GID_ARITHMETIC			1
#define DP_GID_EXIT                 5
#define DP_MAX_NAME_LENGTH          20
#define DP_BUFFER_SIZE              25
#define DP_MAX						100
#define DP_UID_ADD					101
#define DP_UID_SUB					102
#define DP_UID_MUL					103
#define DP_UID_DIV					104
#define DP_UID_MOD					105
#define DP_FAILURE					-1
#define DP_NULL_POINTER_ACCESS      -99
#define DP_PORT						8989
#define DP_HEADER					0x1ABC
#define DP_FOOTER					0x9CDE
#define DP_MAX_TCP_TRANSMISSION		65535	
#define DP_SERVER_IP				"127.0.0.1"

/*Message ID for S_STRUCTURE 1, 2 and 3*/
#define DP_STRUCT1					101
#define DP_STRUCT2					102

/*Receiving States*/
#define DP_CLIENT_CLOSED    404
#define DP_HEADER_STATE		1001
#define DP_GID_STATE		1002
#define DP_UID_STATE        1003
#define DP_MSG_LEN_STATE	1004
#define DP_DATA_STATE		1005
#define DP_CSUM_STATE       1006
#define DP_FOOTER_STATE		1007

#define DP_PLUS             201
#define DP_MINUS            202
#define DP_MUL              203
#define DP_DIV              204
#define DP_MOD              205

/*MACRO for converting float to Network Byte Order*/
#define htonf(fData) ( *( unsigned long *)&fData = htonl(*(unsigned long *)&fData) )

/*Arithmetic structure*/
typedef struct
{
	short					sOperand1;
	short					sOperand2;
}S_ARITHMETIC;

/*Student structure*/
typedef struct
{
	char					arr_cName[DP_MAX_NAME_LENGTH];
	float					fMark1;
	float					fMark2;
	float					fMark3;
	float					fMark4;
	float					fMark5;

}S_STUDENT;

#define DP_MAX_STRUCT sizeof(S_STUDENT)

/*Creating Union for Storing Structure Values*/
typedef union
{
	S_ARITHMETIC				m_SArithmetic;
	S_STUDENT					m_SStudent;
	char						arr_cBuffer[DP_MAX_STRUCT];
}U_DATA;

/*Frame*/
typedef struct
{
	unsigned int		uiHeader;
	unsigned short		usGroupId;
	unsigned short		usUnitId;
	unsigned int		uiMessageLength;
	U_DATA				m_UData;
	unsigned int	    uiCheckSum;
	unsigned int	    uiFooter;

}S_FRAME;

#define DP_MSG_LEN	sizeof(U_DATA)

SOCKET DP_CreateTCPSocket();
int DP_Receive(SOCKET ClientSocket, S_FRAME* S_Frame);
int DP_CommandHandler(S_FRAME* in_S_Frame, void* in_S_Struct);
int DP_Convert_NtoH_Bytes(int in_ID, void* out_pS_Struct);
int DP_CalcTotal(S_STUDENT* in_S_Stud, float* out_dAvg);
int DP_CreateReplyTxBuffer(S_FRAME in_S_Frame, char* out_arr_cTxBuff);
int DP_SendAck(SOCKET in_ClientSocket, char* in_arr_cBuffer, int in_iSize);
int DP_ArithmeticOperation(S_ARITHMETIC* pStu1, unsigned int in_uiUnitId);