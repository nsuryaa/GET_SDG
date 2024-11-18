#include "TCP_Client.h"

int main()
{
	WSADATA wsa = { 0 };
	SOCKET skt_ClientSocket = DP_INVALID_SOCKET;
	S_FRAME m_SFrame = { 0 };
	S_FRAME m_SResFrame = { 0 };
	U_DATA	m_UData = { 0 };
	char cOption = 0;
	int isExitFlag = 0, iRetry = 0, iReturnValue = 0;
	int iOption = 0;
	unsigned short usUnitId = 0;
	unsigned char ucIsValidOperand1 = 0, ucIsValidOperand2 = 0;
	unsigned char ucIsValidGroupId = 0, ucIsValidUnitId = 0;
	char arr_cSendBuffer[DP_BUFFER_SIZE] = { 0 }, arr_cRecvBuffer[DP_BUFFER_SIZE] = { 0 };
	char arr_cTxBuffer[sizeof(S_FRAME)] = { 0 };

	printf("\r\n----------TCP CLIENT----------\r\n");
	printf("\r\nInitializing Winsock...\r\n");

	/*winsock initialization*/
	iReturnValue = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (iReturnValue != 0)
	{
		printf("\r\nError: Winsock not Initialized. Error Code: %d\r\n", WSAGetLastError());
		_getch();
		return DP_FAILURE;
	}

	printf("\r\nWinsock Initialized...\r\n");

	while (1)
	{
		/*create client socket*/
		skt_ClientSocket = DP_CreateTCPSocket();
		if (skt_ClientSocket == INVALID_SOCKET)
		{
			printf("\r\nCould not create socket. Error Code: %d\r\n", WSAGetLastError());
			WSACleanup();
			_getch();
			return DP_FAILURE;
		}

		printf("\r\nTCP Client Socket Created!\r\n");

		/*retry connecting clientsocket with server socket until DP_MAX_RETRIES*/
		while (iRetry < DP_MAX_RETRIES)
		{
			/*Connectiong to Server using IP*/
			iReturnValue = DP_ConnectToServer(skt_ClientSocket);
			if (iReturnValue != DP_SUCCESS)
			{
				printf("\r\nConnection with server failed, Retry %d/%d...\r\n", (iRetry + 1), DP_MAX_RETRIES);
				iRetry++;
				closesocket(skt_ClientSocket);
				Sleep(DP_RETRY_DELAY);
				//continue

				/*create client socket*/
				skt_ClientSocket = DP_CreateTCPSocket();
				if (skt_ClientSocket == INVALID_SOCKET)
				{
					printf("\r\nCould not recreate socket. Error Code: %d\r\n", WSAGetLastError());
					WSACleanup();
					return DP_FAILURE;
				}
			}
			else
			{
				printf("\r\nConnected to Server After %d retires\r\n", iRetry);
				break;
			}
		}

		/*when maximum retry reached close the client socket!*/
		if (iRetry == DP_MAX_RETRIES)
		{
			printf("\r\nMax retry attempts reached. Exiting...\r\n");
			closesocket(skt_ClientSocket);
			if (iReturnValue != 0)
			{
				printf("\r\nFailed to close socket. Error Code: %d\r\n", WSAGetLastError());
				WSACleanup();
				return DP_FAILURE;
			}

			break;
		}

		while (1)
		{
			/*get input from user*/
			printf("\r\nEnter 1 For Arithmetic Operation.\r\n");
			printf("\r\nEnter 2 To Send Student Details.\r\n");
			printf("\r\nEnter 3 To Exit\r\n");

			scanf_s(" %d", &iOption);

			switch (iOption)
			{
			case 1:

				iOption = DP_STRUCT1;
				break;
			case 2:

				iOption = DP_STRUCT2;
				break;
			case 3:
				/*closing client*/
				printf("\r\nClosing Client....\r\n");
				//Sleep(2000);
				_getch();
				return DP_FAILURE;
			}

			iReturnValue = DP_GetUserInput(iOption, &m_UData, &usUnitId);
			if (iReturnValue == DP_FAILURE)
			{
				closesocket(skt_ClientSocket);
				WSACleanup();
				return DP_SUCCESS;
			}

			printf("\r\nGet User Input Done\r\n");//TODO

			/*creating buffer to send via network*/
			DP_CreateBuffer(iOption, &m_UData, arr_cTxBuffer, usUnitId);

			/*send msg to server*/
			iReturnValue = DP_SendMessage(skt_ClientSocket, arr_cTxBuffer, sizeof(arr_cTxBuffer));
			if (iReturnValue != DP_SUCCESS)
			{
				break;
			}

			/*Receive Acknowlwdgement from Server*/
			iReturnValue = DP_ReceiveMessage(skt_ClientSocket, &m_SResFrame);
			if (iReturnValue != DP_SUCCESS)
			{
				printf("\nConnection Lost\n");

				/*Trying to Reconnect to Server if Connection is Lost*/
				printf(" \nWant to Reconnect? y or n\n");
				scanf_s(" %c", &cOption);

				if (cOption == 'n')
				{
					exit(0);
				}

				printf("\nRetrying to Connect...\n");
				closesocket(skt_ClientSocket);
				Sleep(2000);
				break;
			}

			/*Printing Reply from Server*/
			DP_PrintReply(m_SResFrame);
		}
	}

	closesocket(skt_ClientSocket);
	/*clean up winsock*/
	WSACleanup();

	_getch();
	return DP_SUCCESS;
}

/*!
* / Function Name: DP_CalculateCheckSum(S_MESSAGE *in_m_SMessage)
* / Author       : 3232
* / Date         : 14/11/24
* / Brief        : Function to calculate checksum for send and receive message
* / param[out]   : in_m_SMessage - received message from sever or send message from client
* / Return       : checksum value
*/

/*
int DP_CalculateCheckSum(S_MESSAGE *in_m_SMessage)
{
	return (in_m_SMessage->uiHeader + in_m_SMessage->usGroupId + in_m_SMessage->usUnitId + in_m_SMessage->uiMessageLength
		+ in_m_SMessage->sOperand1 + in_m_SMessage->sOperand2 + in_m_SMessage->uiFooter);
}
*/

/*!
* / Function Name: DP_CreateTCPSocket()
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to create a TCP Socket
* / Return       : skt_ClientSocket
*/

SOCKET DP_CreateTCPSocket()
{
	SOCKET skt_ClientSocket;

	skt_ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

	return skt_ClientSocket;
}

/*!
* / Function Name: DP_ConnectToServer(SOCKET skt_ClientSocket)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to make connection to client and server
* / param[in]	 : in_ClientSocket - socket to connect
* / Return       : DP_SUCCESS, DP_FAILURE
*/

int DP_ConnectToServer(SOCKET skt_ClientSocket)
{
	int iReturnValue = 0;

	/*A Structure Instance for Storing IP Family, Server IP Address and PORT Number*/
	struct sockaddr_in m_SServer;

	m_SServer.sin_family = AF_INET;
	m_SServer.sin_port = htons((unsigned short)DP_PORT);
	inet_pton(AF_INET, DP_IP, &(m_SServer.sin_addr.S_un.S_addr));
	//m_SServer.sin_addr.S_un.S_addr = inet_pton(DP_IP);

	/*Searching for the Server and Connect to it*/
	iReturnValue = connect(skt_ClientSocket, (struct sockaddr*)&m_SServer, sizeof(m_SServer));
	if (iReturnValue == SOCKET_ERROR)
	{
		return DP_FAILURE;
	}

	printf("\nServer Connected\n");

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_GetUserInput(int in_iOption, U_DATA *out_pU_Data)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to take input from user and store it in Structure
* / param[in]	 : in_iOption	- Structure to Create
* / param[out]	 : *out_pU_Data	- pointer of Union Structure
* / Return       : DP_SUCCESS
*/

int DP_GetUserInput(int in_iOption, U_DATA* out_pU_Data, unsigned short *usUnitId)
{
	S_ARITHMETIC m_SArithmetic = { 0 };
	S_STUDENT    m_SStudent = { 0 };

	switch (in_iOption)
	{

	case DP_STRUCT1:

		printf("\r\nEnter Value for Operand1\r\n");
		scanf_s(" %hd", &m_SArithmetic.sOperand1);

		printf("\nEnter Value for Operand2\n");
		scanf_s(" %hd", &m_SArithmetic.sOperand2);

		printf("\r\nEnter Unit Id(201-205):\r\n");
		scanf_s(" %hu", usUnitId);

		/*converting elements of struct to network byte order*/
		DP_ConvertToNetworkByteOrder(in_iOption, &m_SArithmetic);

		memcpy(&out_pU_Data->m_SArithmetic, &m_SArithmetic, sizeof(S_ARITHMETIC));
		break;

	case DP_STRUCT2:

		m_SStudent.fMark1 = 0.0;
		m_SStudent.fMark2 = 0.0;
		m_SStudent.fMark3 = 0.0;
		m_SStudent.fMark4 = 0.0;
		m_SStudent.fMark5 = 0.0;

		printf("\nEnter Name of Student\n");
		scanf_s(" %[^\n]s", m_SStudent.arr_cName);

		printf("\nEnter Mark 1 of Student\n");
		scanf_s(" %f", &m_SStudent.fMark1);

		printf("\nEnter Mark 2 of Student\n");
		scanf_s(" %f", &m_SStudent.fMark2);

		printf("\nEnter Mark 3 of Student\n");
		scanf_s(" %f", &m_SStudent.fMark3);

		printf("\nEnter Mark 4 of Student\n");
		scanf_s(" %f", &m_SStudent.fMark4);

		printf("\nEnter Mark 5 of Student\n");
		scanf_s(" %f", &m_SStudent.fMark5);

		/*converting elements of struct to network byte order*/
		DP_ConvertToNetworkByteOrder(in_iOption, &m_SStudent);

		memcpy(&out_pU_Data->m_SStudent, &m_SStudent, sizeof(S_STUDENT));
		break;
	}

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_ConvertToNetworkByteOrder(int in_iOption, void *out_pS_Struct)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to convert from host to network byte order
* / param[in]	 : in_iOption	- Structure to Convert
* / param[out]	 : out_pS_Struct - Structure to Convert from Host to Network Order
* / Return       : DP_SUCCESS
*/

int DP_ConvertToNetworkByteOrder(int in_iOption, void* out_pS_Struct)
{
	S_ARITHMETIC* pS_Arithmetic = NULL;
	S_STUDENT* pS_Student = NULL;

	switch (in_iOption)
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
* / Function Name: DP_CreateBuffer(int in_iID, U_DATA *in_pU_Data, char *out_arr_cTxBufffer)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to create buffer to send via network
* / param[in]	 : in_iID - Option to Structure
* / param[in]	 : *in_pU_Data	- Pointer to Union Data
* / param[out]	 : *out_arr_cTxBufffer	- Transmission Buffer to be sent via network
* / Return       : DP_SUCCESS
*/

int DP_CreateBuffer(int in_iID, U_DATA* in_pU_Data, char* out_arr_cTxBufffer, unsigned short in_usUnitId)
{
	S_FRAME	m_SFrame = { 0 };
	int	iBufferIndex = 0, iTemp = 0, iMessageLength = 0;
	unsigned short usGroupID = 0;

	m_SFrame.uiHeader = DP_HEADER;

	m_SFrame.uiHeader = htonl((unsigned long)m_SFrame.uiHeader);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.uiHeader, sizeof(m_SFrame.uiHeader));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.uiHeader);

	switch (in_iID)
	{
	case DP_STRUCT1:

		usGroupID = DP_STRUCT1;
		iMessageLength = sizeof(S_ARITHMETIC);
		break;

	case DP_STRUCT2:

		usGroupID = DP_STRUCT2;
		iMessageLength = sizeof(S_STUDENT);
		break;
	}

	m_SFrame.usGroupId = usGroupID;

	m_SFrame.usGroupId = htons((unsigned short)m_SFrame.usGroupId);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.usGroupId, sizeof(m_SFrame.usGroupId));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.usGroupId);

	m_SFrame.usUnitId = in_usUnitId;

	m_SFrame.usUnitId = htons((unsigned short)m_SFrame.usUnitId);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.usUnitId, sizeof(m_SFrame.usUnitId));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.usUnitId);

	m_SFrame.uiMessageLength = iTemp = iMessageLength;
	printf("%d", iMessageLength);
	m_SFrame.uiMessageLength = htonl((unsigned long)m_SFrame.uiMessageLength);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.uiMessageLength, sizeof(m_SFrame.uiMessageLength));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.uiMessageLength);

	//memcpy(&m_SFrame.m_UData, in_pU_Data->arr_cBuffer, iTemp);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], in_pU_Data->arr_cBuffer, iTemp);
	iBufferIndex = iBufferIndex + iTemp;

	m_SFrame.uiCheckSum = htonl((unsigned long)m_SFrame.uiCheckSum);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.uiCheckSum, sizeof(m_SFrame.uiCheckSum));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.uiCheckSum);

	m_SFrame.uiFooter = DP_FOOTER;

	m_SFrame.uiFooter = htonl((unsigned long)m_SFrame.uiFooter);
	memcpy(&out_arr_cTxBufffer[iBufferIndex], &m_SFrame.uiFooter, sizeof(m_SFrame.uiFooter));
	iBufferIndex = iBufferIndex + sizeof(m_SFrame.uiFooter);

	printf("%d", iBufferIndex);

	return DP_SUCCESS;
}


/*!
* / Function Name: DP_SendMessage(SOCKET in_skt_ClientSocket, char *in_arr_cTxBuffer, int in_iSize)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to send request message to server
* / param[in]    : in_skt_ClientSocket - Client Socket to communicate
* / param[in]    : in_arr_cTxBuffer	- Buffer which contains Reply data
* / param[in]    : in_iSize - Size of the Buffer
* / Return       : DP_SUCCESS, DP_FAILURE
*/

int DP_SendMessage(SOCKET in_skt_ClientSocket, char* in_arr_cTxBuffer, int in_iSize)
{
	int iReturnValue = 0, iSentBytes = 0, iBytesToTransmit = in_iSize;

	/*send data until all bytes sent*/
	while (iSentBytes < in_iSize)
	{
		iReturnValue = send(in_skt_ClientSocket, &in_arr_cTxBuffer[iSentBytes], iBytesToTransmit, 0);
		if (iReturnValue == SOCKET_ERROR)
		{
			printf("\nFailed to Send Message: %d\n", WSAGetLastError());
			return DP_FAILURE;
		}

		iSentBytes = iSentBytes + iReturnValue;
	}

	printf("\r\nMessage Sent to Server\r\n");

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_ReceiveMessage(SOCKET skt_ClientSocket, S_FRAME *out_m_SFrame)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to receive acknowledgement from server
* / param[in]    : ClientSocket  - Client Socket to receive
* / param[out]   : *out_S_Frame	 -  Output Frame
* / Return       : DP_SUCCESS, DP_FAILURE
*/

int DP_ReceiveMessage(SOCKET skt_ClientSocket, S_FRAME* out_m_SFrame)
{
	int iReturnValue = 0, iStage = DP_HEADER_STATE, iReceivedMsgLength = 0;

	/*Receiving Header from the Client stores it in A_Frame Structureand Checking if it is
	Correct and try untill correct Client Connects*/
	while (1)
	{
		switch (iStage)
		{
		case DP_HEADER_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->uiHeader, sizeof(out_m_SFrame->uiHeader), 0);
			out_m_SFrame->uiHeader = htonl((unsigned long)out_m_SFrame->uiHeader);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			if (out_m_SFrame->uiHeader != DP_HEADER)
			{
				break;
			}

			printf("\r\nHeader: %x\r\n ", (out_m_SFrame->uiHeader));
			iStage = DP_GID_STATE;

		case DP_GID_STATE:

			/*Receiving Group ID from Server and stores it in S_FRAME Structure*/
			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->usGroupId, sizeof(out_m_SFrame->usGroupId), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			out_m_SFrame->usGroupId = htons((unsigned short)out_m_SFrame->usGroupId);
			if (iReturnValue != sizeof(unsigned short))
			{
				break;
			}

			printf("\r\nGroup ID: %d\r\n", out_m_SFrame->usGroupId);
			iStage = DP_UID_STATE;

		case DP_UID_STATE:

			/*Receiving Group ID from Server and stores it in S_FRAME Structure*/
			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->usUnitId, sizeof(out_m_SFrame->usUnitId), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			out_m_SFrame->usUnitId = htons((unsigned short)out_m_SFrame->usUnitId);
			if (iReturnValue != sizeof(unsigned short))
			{
				break;
			}

			printf("\r\nUnit Id: %d\r\n", out_m_SFrame->usUnitId);
			iStage = DP_MSG_LEN_STATE;

		case DP_MSG_LEN_STATE:

			/*Receiving Message Length and store it in S_Frames.MessageLength*/
			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->uiMessageLength, sizeof(out_m_SFrame->uiMessageLength), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}
			else if (iReturnValue > DP_MSG_LENGTH)
			{
				printf("\r\nHigh Incomming Packets\r\n");
				break;
			}

			/*Converting received Network Byte Data to host Byte data and Printing it*/
			out_m_SFrame->uiMessageLength = htonl((unsigned long)out_m_SFrame->uiMessageLength);

			printf("\r\nMessage Length: %d\r\n", out_m_SFrame->uiMessageLength);
			iStage = DP_DATA_STATE;

		case DP_DATA_STATE:

			/*Receiving Actual Data and store it in */
			while ((unsigned int)iReceivedMsgLength < (out_m_SFrame->uiMessageLength))
			{
				iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->m_UData, out_m_SFrame->uiMessageLength, 0);
				if (iReturnValue <= 0)
				{
					iStage = DP_CLIENT_CLOSED;
					break;
				}

				iReceivedMsgLength += iReturnValue;
			}

			printf("\r\nBUFFER: %s\r\n", out_m_SFrame->m_UData.arr_cBuffer);
			iStage = DP_CSUM_STATE;

		case DP_CSUM_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->uiCheckSum, sizeof(out_m_SFrame->uiCheckSum), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			out_m_SFrame->uiCheckSum = htonl((unsigned long)out_m_SFrame->uiCheckSum);
			if (iReturnValue != sizeof(out_m_SFrame->uiCheckSum))
			{
				break;
			}

			printf("\r\nCHECKSUM:%d\r\n", out_m_SFrame->uiFooter);
			iStage = DP_FOOTER_STATE;

		case DP_FOOTER_STATE:

			iReturnValue = recv(skt_ClientSocket, (char*)&out_m_SFrame->uiFooter, sizeof(out_m_SFrame->uiFooter), 0);
			if (iReturnValue <= 0)
			{
				iStage = DP_CLIENT_CLOSED;
				break;
			}

			out_m_SFrame->uiFooter = htonl((unsigned long)out_m_SFrame->uiFooter);
			if ((out_m_SFrame->uiFooter != DP_FOOTER) || (iReturnValue != sizeof(out_m_SFrame->uiFooter)))
			{
				break;
			}

			printf("\r\nFOOTER:%d\r\n", out_m_SFrame->uiFooter);
			iStage += 1;
		}

		if (iStage == DP_FOOTER_STATE + 1)
		{
			break;
		}
		else if (iStage == DP_CLIENT_CLOSED)
		{
			printf("Connection Closed by Client");
			return DP_FAILURE;
		}
	}

	return DP_SUCCESS;
}

/*!
* / Function Name: DP_PrintReply(S_FRAME in_m_SResFrame)
* / Author       : 3232
* / Date         : 15/11/24
* / Brief        : Function to print reply from server
* / param[in]    : in_m_SResFrame  -  Reply Frame from Server
* / Return       : DP_SUCCESS
*/

int DP_PrintReply(S_FRAME in_m_SResFrame)
{
	float fTotal = 0.0;
	unsigned short usResult = 0;

	switch (in_m_SResFrame.usGroupId)
	{
	case DP_STRUCT1:

		usResult = in_m_SResFrame.m_UData.m_SArithmetic.sOperand1;
		usResult = htons(usResult);
		printf("Result of Operation from Server: %u", usResult);
		break;

	case DP_STRUCT2:

		printf("\rReply From Client: \n", in_m_SResFrame.m_UData.arr_cBuffer);
		break;
	}

	return DP_SUCCESS;
}
