#pragma once
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>
#include <Windows.h>
#include <limits.h>
#include <stdlib.h>

/*link winsock2 library*/
#pragma pack(1)
#pragma comment(lib, "Ws2_32.lib")

#define DP_SUCCESS				0
#define DP_MIN_GID				1
#define DP_GID_ARITHMETIC       1
#define DP_MAX_GID				5
#define DP_GID_EXIT             5
#define DP_MAX_RETRIES			10
#define DP_BUFFER_SIZE          25
#define DP_MAX_NAME_LENGTH	    100
#define DP_MIN_ARITH_UID        101
#define DP_MAX_ARITH_UID		105
#define DP_RETRY_DELAY			1000
#define DP_PORT					8989
#define DP_FAILURE				-1
#define DP_INVALID_SOCKET       -99
#define DP_NULL_POINTER_ACCESS  -98
#define DP_IP					"127.0.0.1"
#define DP_MIN_NUMBER           SHRT_MIN
#define DP_MAX_NUMBER           SHRT_MAX
#define DP_HEADER               0x1ABC
#define DP_FOOTER               0x9CDE

/*Group ID for S_STRUCTURE 1 and 2*/
#define DP_STRUCT1				101 //Arithmetic
#define DP_STRUCT2				102 //Student Details

/*Receiving States*/
#define DP_CLIENT_CLOSED		404
#define DP_HEADER_STATE			1001
#define DP_GID_STATE			1002
#define DP_UID_STATE			1003
#define DP_MSG_LEN_STATE		1004
#define DP_DATA_STATE			1005
#define DP_CSUM_STATE			1006
#define DP_FOOTER_STATE			1007

/*MACRO for converting float to Network Byte Order*/
#define htonf(fData) ( *( unsigned long *)&fData = htonl(*(unsigned long *)&fData) )

/*Arithmetic structure*/
typedef struct
{
	short sOperand1;
	short sOperand2;
}S_ARITHMETIC;

/*Student structure*/
typedef struct
{
	char	arr_cName[DP_MAX_NAME_LENGTH];
	float	fMark1;
	float	fMark2;
	float   fMark3;
	float   fMark4;
	float   fMark5;

}S_STUDENT;

/*Finding structure with maximum size*/
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

#define DP_MSG_LENGTH	sizeof(U_DATA)

SOCKET DP_CreateTCPSocket();

int DP_ConnectToServer(SOCKET in_ClientSocket);

int DP_GetUserInput(int in_iOption, U_DATA* in_pU_Data, unsigned short* usUnitId);

int DP_ConvertToNetworkByteOrder(int in_iOption, void* out_pS_Struct);

int DP_CreateBuffer(int in_iID, U_DATA* in_pU_Data, char* out_arr_cTxBuff, unsigned short in_usUnitId);

int DP_SendMessage(SOCKET in_skt_ClientSocket, char* in_arr_cTxBuffer, int in_iSize);

int DP_PrintReply(S_FRAME in_S_ResFrame);
int DP_ReceiveMessage(SOCKET ClientSocket, S_FRAME* out_S_Frame);