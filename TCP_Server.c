#include "TCP_Server.h"

int main()
{
	WSADATA wsa = { 0 };
	SOCKET skt_ServerSocket = 0, skt_ClientSocket = 0;
	S_FRAME m_SFrame = { 0 };
	S_ARITHMETIC m_SArithmetic = { 0 };
	S_STUDENT m_SStudent = { 0 };
	int iReturnValue = 0, iClientAddressSize = 0;
	void* pS_Struct = NULL;
	char arr_cResBuffer[sizeof(S_FRAME)] = { 0 };
	struct sockaddr_in m_SClient = { 0 };

	printf("\r\n----------TCP SERVER----------\r\n");

	printf("\r\nInitializing Winsock!\r\n");

	/*winsock initialization*/
	iReturnValue = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iReturnValue != 0)
	{
		printf("\r\nError Winsock not Initialized! Code: %d.\r\n", WSAGetLastError());

		return DP_FAILURE;
	}

	printf("\r\nWinsock Initialized!\r\n");

	/*creating socket for server*/
	skt_ServerSocket = DP_CreateTCPSocket();
	if ((skt_ServerSocket == INVALID_SOCKET) || (skt_ServerSocket == SOCKET_ERROR))
	{
		printf("\r\nError Creating Socket! Code: %d.\r\n", WSAGetLastError());
		closesocket(skt_ServerSocket);
		WSACleanup();
		_getch();
		return DP_FAILURE;
	}

	printf("\r\nTCP Server Socket Created!\r\n");

	printf("\r\nBind to the Port Number: %d\r\n", DP_PORT);

	/*listen for incoming client connections*/
	iReturnValue = listen(skt_ServerSocket, DP_CONNECTIONS);
	if (iReturnValue == SOCKET_ERROR)
	{
		printf("\r\nError While Listening! Code: %d\r\n", WSAGetLastError());
		closesocket(skt_ServerSocket);
		WSACleanup();

		return DP_FAILURE;
	}

	printf("\r\nServer is listening for incoming connections...\r\n");

	iClientAddressSize = sizeof(m_SClient);

	while (1)
	{
		printf("\r\nWaiting to Accept Client...\r\n");

		/*accept connection request from client*/
		skt_ClientSocket = accept(skt_ServerSocket, (struct sockaddr*)&m_SClient, &iClientAddressSize);
		if (skt_ClientSocket == INVALID_SOCKET)
		{
			printf("\r\nError Accepting Connnection! Code: %d\r\n", WSAGetLastError());
			/*keep waiting for new connections*/
			continue;
		}

		printf("\r\nClient Connected!\r\n");

		while (1)
		{
			fflush(stdin);

			/*Receiving Requests from Client and sending Ackwnoledge*/
			iReturnValue = DP_Receive(skt_ClientSocket, &m_SFrame);
			if (iReturnValue != DP_SUCCESS)
			{
				printf("\r\nError in Receiving Message! Code: %d\r\n", WSAGetLastError());
				break;
			}

			/*Changing void pointer to structure pointer according to
			received input from client*/
			switch (m_SFrame.usGroupId)
			{
			case DP_STRUCT1:

				pS_Struct = (S_ARITHMETIC*)pS_Struct;
				pS_Struct = &m_SArithmetic;
				break;

			case DP_STRUCT2:

				pS_Struct = (S_STUDENT*)pS_Struct;
				pS_Struct = &m_SStudent;
				break;
			}

			/*Storing the Values in Appropriate Structures*/
			DP_CommandHandler(&m_SFrame, pS_Struct);

			/*Creating Response Frame for Client*/
			DP_CreateReplyTxBuffer(m_SFrame, arr_cResBuffer);

			/*Sending Acknowledgement*/
			DP_SendAck(skt_ClientSocket, arr_cResBuffer, sizeof(arr_cResBuffer));
		}

		/*close client connection*/
		iReturnValue = closesocket(skt_ClientSocket);
		if (iReturnValue != 0)
		{
			printf("\r\nFailed to close socket. Error Code: %d\r\n", WSAGetLastError());
			WSACleanup();
			return DP_FAILURE;
		}

		printf("\r\nClient disconnected.\r\n");


	}

	/*close server socket*/
	iReturnValue = closesocket(skt_ServerSocket);
	if (iReturnValue != 0)
	{
		printf("\r\nFailed to close socket. Error Code: %d\r\n", WSAGetLastError());
		WSACleanup();
		return DP_FAILURE;
	}

	/*perform cleanup*/
	WSACleanup();

	_getch();
	return DP_SUCCESS;
}

/*!
* / Function Name: DP_CreateTCPSocket()
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to create a TCP Socket
* / Return       : A server socket
*/

SOCKET DP_CreateTCPSocket()
{
	SOCKET	skt_ServerSocket;
	int	iReturnValue = 0;
	struct sockaddr_in m_SServer = { 0 };

	/*Creating a TCP Server Socket */
	skt_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (skt_ServerSocket == INVALID_SOCKET)
	{
		printf("\nSocket Creation Failed: %d\n", WSAGetLastError());
		return skt_ServerSocket;
	}

	/*Assigning IP Famile, Client IP Address and PORT Number*/
	m_SServer.sin_family = AF_INET;
	m_SServer.sin_addr.S_un.S_addr = INADDR_ANY;
	m_SServer.sin_port = htons(DP_PORT);

	/*Binding Server Socket with IP Address*/
	iReturnValue = bind(skt_ServerSocket, (struct sockaddr*)&m_SServer, sizeof(m_SServer));
	if (iReturnValue == SOCKET_ERROR)
	{
		printf("\nBinding Failed: %d\n", WSAGetLastError());
		return skt_ServerSocket;
	}

	return skt_ServerSocket;
}


/*!
* / Function Name: DP_Receive(SOCKET skt_ClientSocket, S_FRAME *out_m_SFrame)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to make communication with client and server
* / param[in]    : SOCKET skt_ClientSocket	- Client Socket to Receive
* / param[out]   : S_FRAME *out_m_SFrame	- Output Frame
* / return		 : DP_SUCCESS, DP_FAILURE.
*/

int DP_Receive(SOCKET skt_ClientSocket, S_FRAME* out_m_SFrame)
{
	int iReturnValue = 0, iStage = DP_HEADER_STATE, iReceivedMsgLength = 0;
	S_FRAME m_SFrame = { 0 };

	/*Receiving Header from the Client stores it in A_Frame Structureand Checking if it is
	Correct and try untill correct Client Connects*/
	while (1)
	{
		switch (iStage)
		{
		case DP_HEADER_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.uiHeader, sizeof(m_SFrame.uiHeader), 0);
			m_SFrame.uiHeader = htonl((unsigned long)m_SFrame.uiHeader);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			if (m_SFrame.uiHeader != DP_HEADER)
			{
				break;
			}

			printf("\r\n Header: %x\r\n ", m_SFrame.uiHeader);
			iStage = DP_GID_STATE;

		case DP_GID_STATE:

			/*Receiving Message ID from Server and stores it in S_Frames Structure*/
			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.usGroupId, sizeof(m_SFrame.usGroupId), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			m_SFrame.usGroupId = htons((unsigned short)m_SFrame.usGroupId);
			if (iReturnValue != sizeof(unsigned short))
			{
				break;
			}

			printf("\r\nGroup ID: %d\r\n", m_SFrame.usGroupId);
			iStage = DP_UID_STATE;

		case DP_UID_STATE:

			/*Receiving Message ID from Server and stores it in S_Frames Structure*/
			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.usUnitId, sizeof(m_SFrame.usUnitId), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			m_SFrame.usUnitId = htons((unsigned short)m_SFrame.usUnitId);
			if (iReturnValue != sizeof(unsigned short))
			{
				break;
			}

			printf("\r\nUnit ID: %d\r\n", m_SFrame.usUnitId);
			iStage = DP_MSG_LEN_STATE;

		case DP_MSG_LEN_STATE:

			/*Receiving Message Length and store it in S_Frames.MessageLength*/
			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.uiMessageLength, sizeof(m_SFrame.uiMessageLength), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}
			else if (iReturnValue > DP_MSG_LEN)
			{
				printf("\r\nHigh Incomming Packets\r\n");
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			m_SFrame.uiMessageLength = htonl((unsigned long)m_SFrame.uiMessageLength);

			printf("\r\nMessage Length: %d \r\n", m_SFrame.uiMessageLength);
			iStage = DP_DATA_STATE;

		case DP_DATA_STATE:

			/*Receiving Actual Data and store it in */
			while ((unsigned int)iReceivedMsgLength < m_SFrame.uiMessageLength)
			{
				iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.m_UData.arr_cBuffer, m_SFrame.uiMessageLength, 0);
				if (iReturnValue <= 0)
				{
					iStage = DP_CLIENT_CLOSED;
					break;
				}

				iReceivedMsgLength += iReturnValue;
			}

			printf("\n BUFFER: %s \n", m_SFrame.m_UData.arr_cBuffer);
			iStage = DP_CSUM_STATE;

		case DP_CSUM_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.uiCheckSum, sizeof(m_SFrame.uiCheckSum), 0);
			m_SFrame.uiCheckSum = htonl((unsigned long)m_SFrame.uiCheckSum);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			printf("\r\nChecksum: %x\r\n ", m_SFrame.uiCheckSum);
			iStage = DP_FOOTER_STATE;

		case DP_FOOTER_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&m_SFrame.uiFooter, sizeof(m_SFrame.uiFooter), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			m_SFrame.uiFooter = htonl((unsigned long)m_SFrame.uiFooter);
			if ((m_SFrame.uiFooter != DP_FOOTER) || (iReturnValue != sizeof(m_SFrame.uiFooter)))
			{
				break;
			}

			printf("\n FOOTER: %d \n", m_SFrame.uiFooter);
			iStage += 1;
		}

		if (iStage == DP_FOOTER_STATE + 1)
		{
			*out_m_SFrame = m_SFrame;
			break;
		}
		else if (iStage == DP_CLIENT_CLOSED)
		{
			printf("\n\nConnection Closed by Client\n");
			return DP_FAILURE;
		}
	}

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_CommandHandler(S_FRAME m_SFrame, void *in_pS_Struct)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Storing the Values in Structure
* / param[in]    : in_S_Frame			- Frame received from Client
* / param[out]   : out_S_StructAddr  	- Created Structure using Frame
* / return		 : DP_SUCCESS, DP_FAILURE.
*/

int DP_CommandHandler(S_FRAME* in_S_Frame, void* in_pS_Struct)
{
	S_ARITHMETIC* pStu1 = NULL;
	S_STUDENT* pStu2 = NULL;

	float		fTotal = 0.0;

	switch (in_S_Frame->usGroupId)
	{
	case DP_STRUCT1:

		pStu1 = (S_ARITHMETIC*)in_pS_Struct;

		memcpy(pStu1, &in_S_Frame->m_UData.m_SArithmetic, sizeof(S_ARITHMETIC));

		/*Converting to Host Byte Order*/
		DP_Convert_NtoH_Bytes(in_S_Frame->usGroupId, pStu1);

		printf("\nValue Stored in Structure\n");
		printf("\nOperand 1: %u\n", pStu1->sOperand1);
		printf("\nOperand 2: %u\n", pStu1->sOperand2);

		DP_ArithmeticOperation(pStu1, in_S_Frame->usUnitId);

		/*Creating Reply Message*/
		memset(&in_S_Frame->m_UData, 0, sizeof(in_S_Frame->m_UData));
		memset(&in_S_Frame->uiMessageLength, 0, sizeof(in_S_Frame->uiMessageLength));

		//strcpy_s(in_S_Frame->m_UData.arr_cBuffer, "Operands Received!");
		//in_S_Frame->m_UData.arr_cBuffer, sizeof(in_S_Frame->m_UData.arr_cBuffer);
		
		in_S_Frame->m_UData.m_SArithmetic.sOperand1 = pStu1->sOperand1;
		in_S_Frame->m_UData.m_SArithmetic.sOperand1 = htons(in_S_Frame->m_UData.m_SArithmetic.sOperand1);		
		in_S_Frame->uiMessageLength = sizeof(S_ARITHMETIC);
		break;

	case DP_STRUCT2:

		pStu2 = (S_STUDENT*)in_pS_Struct;

		memcpy(pStu2, &in_S_Frame->m_UData.m_SStudent, sizeof(S_STUDENT));

		/*Converting to Host Byte Order*/
		DP_Convert_NtoH_Bytes(in_S_Frame->usGroupId, pStu2);

		printf("\nValue Stored in Structure\n");
		printf("\nStudent Name  : %s\n", pStu2->arr_cName);
		printf("\nStudent Mark 1: %.2f\n", pStu2->fMark1);
		printf("\nStudent Mark 2: %.2f\n", pStu2->fMark2);
		printf("\nStudent Mark 3: %.2f\n", pStu2->fMark3);
		printf("\nStudent Mark 4: %.2f\n", pStu2->fMark4);
		printf("\nStudent Mark 5: %.2f\n", pStu2->fMark5);

		/*Creating reply Message*/
		DP_CalcTotal(pStu2, &fTotal);

		memset(&in_S_Frame->m_UData, 0, sizeof(in_S_Frame->m_UData));
		memset(&in_S_Frame->uiMessageLength, 0, sizeof(in_S_Frame->uiMessageLength));

		in_S_Frame->m_UData.m_SStudent.fMark1 = fTotal;
		htonf(in_S_Frame->m_UData.m_SStudent.fMark1);
		//in_S_Frame->uiMessageLength = sizeof(in_S_Frame->m_UData.arr_cBuffer);
		in_S_Frame->uiMessageLength = sizeof(S_STUDENT);
		break;
	}

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_Convert_NtoH_Bytes(S_FRAME *out_S_Frame)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Converting Host to Network Bytes
* / param[in]    : in_ID			-  Message ID for Converting
* / param[out]   : *out_pS_Struct	-  pointer to Convert Values
* / return		 : DP_SUCCESS
*/

int DP_Convert_NtoH_Bytes(int in_ID, void* out_pS_Struct)
{

	S_ARITHMETIC* pS_Arithmetic = NULL;
	S_STUDENT* pS_Student = NULL;

	switch (in_ID)
	{
	case DP_STRUCT1:

		pS_Arithmetic = (S_ARITHMETIC*)out_pS_Struct;

		htonl(pS_Arithmetic->sOperand1);
		htonl(pS_Arithmetic->sOperand2);

		break;

	case DP_STRUCT2:

		pS_Student = (S_STUDENT*)out_pS_Struct;

		htonf(pS_Student->fMark1);
		htonf(pS_Student->fMark2);
		htonf(pS_Student->fMark3);
		htonf(pS_Student->fMark4);
		htonf(pS_Student->fMark5);
		break;

	}

	return DP_SUCCESS;
}

/*!
* / Function Name: int DP_CalcTotal(S_STUDENT *in_S_Stud, float *out_dAvg)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Calculating Total Marks of DP_STRUCT2
* / param[in]    : *in_S_Stud	- pointer for Student Structure
* / param[out]   : *out_dAvg	- pointer to Store Average
* / return		 : DP_SUCCESS
*/

int DP_CalcTotal(S_STUDENT* in_S_Stud, float* out_fTotal)
{
	*out_fTotal = (float)(in_S_Stud->fMark1 + in_S_Stud->fMark2 + in_S_Stud->fMark3
		+ in_S_Stud->fMark4 + in_S_Stud->fMark5);
	htonf(*out_fTotal);

	return DP_SUCCESS;
}

/*!
* / Function Name: int DP_CalcTotal(S_STUDENT *in_S_Stud, float *out_dAvg)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Calculating Total Marks of DP_STRUCT2
* / param[in]    : *in_S_Stud	- pointer for Student Structure
* / param[out]   : *out_dAvg	- pointer to Store Average
* / return		 : DP_SUCCESS
*/

int DP_CreateReplyTxBuffer(S_FRAME in_m_SFrame, char* out_arr_cTxBuff)
{
	int iBuffIndex = 0;
	unsigned int uiTemp = 0;

	in_m_SFrame.uiHeader = htonl((unsigned long)in_m_SFrame.uiHeader);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.uiHeader, sizeof(in_m_SFrame.uiHeader));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.uiHeader);

	in_m_SFrame.usGroupId = htons((unsigned short)in_m_SFrame.usGroupId);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.usGroupId, sizeof(in_m_SFrame.usGroupId));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.usGroupId);

	in_m_SFrame.usUnitId = htons((unsigned short)in_m_SFrame.usUnitId);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.usUnitId, sizeof(in_m_SFrame.usUnitId));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.usUnitId);

	uiTemp = in_m_SFrame.uiMessageLength;
	in_m_SFrame.uiMessageLength = htonl((unsigned long)in_m_SFrame.uiMessageLength);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.uiMessageLength, sizeof(in_m_SFrame.uiMessageLength));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.uiMessageLength);

	memcpy(&out_arr_cTxBuff[iBuffIndex], in_m_SFrame.m_UData.arr_cBuffer, uiTemp);
	iBuffIndex = iBuffIndex + uiTemp;

	in_m_SFrame.uiCheckSum = htonl((unsigned long)in_m_SFrame.uiCheckSum);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.uiCheckSum, sizeof(in_m_SFrame.uiCheckSum));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.uiCheckSum);

	in_m_SFrame.uiFooter = htonl((unsigned long)in_m_SFrame.uiFooter);

	memcpy(&out_arr_cTxBuff[iBuffIndex], &in_m_SFrame.uiFooter, sizeof(in_m_SFrame.uiFooter));
	iBuffIndex = iBuffIndex + sizeof(in_m_SFrame.uiFooter);

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_SendAck(SOCKET in_skt_ClientSocket char *in_arr_cTxBuffer, int in_iSize)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Send Request Message to Server
* / param[in]    : in_ClientSocket  - Client Socket to communicate
* / param[in]	 : in_arr_cTxBuffer	- Buffer which contains Reply data
* / param[in]    : in_iSize - Size of Buffer
* / return		 : DP_SUCCESS, DP_FAILURE
*/

int DP_SendAck(SOCKET in_skt_ClientSocket, char* in_arr_cTxBuffer, int in_iSize)
{
	int iReturnValue = 0, iSentBytes = 0, iBytesToTransmit = in_iSize;

	/*Send data untill all Bytes is sent if data is larger than 65535 sizeof(unsigned short)*/
	while (iSentBytes < in_iSize)
	{
		if (iBytesToTransmit < DP_MAX_TCP_TRANSMISSION)
		{
			iReturnValue = send(in_skt_ClientSocket, &in_arr_cTxBuffer[iSentBytes], iBytesToTransmit, 0);
			if (iReturnValue == SOCKET_ERROR)
			{
				printf("\nFailed to Send Message: %d\n", WSAGetLastError());
				return DP_FAILURE;
			}

			iSentBytes = iSentBytes + iReturnValue;
		}
		else
		{
			iReturnValue = send(in_skt_ClientSocket, &in_arr_cTxBuffer[iSentBytes], DP_MAX_TCP_TRANSMISSION, 0);
			if (iReturnValue == SOCKET_ERROR)
			{
				printf("\nFailed to Send Message: %d\n", WSAGetLastError());
				return DP_FAILURE;
			}

			iSentBytes = iSentBytes + iReturnValue;
			iBytesToTransmit = iBytesToTransmit - iReturnValue;
		}
	}

	printf("\nReply Sent to Client\n");

	return DP_SUCCESS;
}

int DP_ArithmeticOperation(S_ARITHMETIC* pStu1, unsigned int in_uiUnitId)
{
	switch (in_uiUnitId)
	{
	case DP_PLUS:
		pStu1->sOperand1 = pStu1->sOperand1 + pStu1->sOperand2;
		break;
	case DP_MINUS:
		pStu1->sOperand1 = pStu1->sOperand1 - pStu1->sOperand2;
		break;
	case DP_MUL:
		pStu1->sOperand1 = pStu1->sOperand1 * pStu1->sOperand2;
		break;
	case DP_DIV:
		pStu1->sOperand1 = pStu1->sOperand1 / pStu1->sOperand2;
		break;
	case DP_MOD:
		pStu1->sOperand1 = pStu1->sOperand1 % pStu1->sOperand2;
		break;
	default:
		printf("\r\nInvalid Unit Id!\r\n");
	}
}