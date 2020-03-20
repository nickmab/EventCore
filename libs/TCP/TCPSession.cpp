#include "TCPSession.h"
#include "TCPUtils.h"

#include <iostream>

namespace EventCore {

	TCPSession::TCPSession(SOCKET sock, size_t initialRecvBufSize)
		: mSocket(sock)
		, mRecvBufSize(initialRecvBufSize)
		, mRecvBuffer(new char[initialRecvBufSize])
	{
		ClearRecvBuffer();
	}

	TCPSession::~TCPSession()
	{
		ClearRecvBuffer();
		delete[] mRecvBuffer;
		// Try to do a graceful disconnect ...but doesn't seem to work very well.
		BOOL optVal = TRUE;
		const int optLen = sizeof(BOOL);
		setsockopt(mSocket, SOL_SOCKET, SO_DONTLINGER, (char*)&optVal, optLen);
		closesocket(mSocket);
	}

	bool TCPSession::Recv(int recvFlags)
	{
		// Keep reading 
		for (;;)
		{
			pollfd fdarray;
			fdarray.fd = mSocket;
			fdarray.events = POLLRDNORM;
			fdarray.revents = 0;
			const int pollResult = WSAPoll(&fdarray, 1, 0);
			
			if (pollResult == SOCKET_ERROR)
			{
				std::string msg = "Error encountered calling WSAPoll on socket.";
				TCPError(msg);
				return false;
			}
			
			// Nothing left to read, we are done here.
			if (pollResult == 0)
				return true;
			
			// recv returns 0 if closed gracefully, SOCKET_ERROR if error, or num bytes.
			int bytesOrError = recv(
				mSocket,
				mRecvBuffer + mNumBytesInRecvBuffer,
				mRecvBufSize - mNumBytesInRecvBuffer,
				recvFlags);

			if (bytesOrError == 0)
			{
				std::cout << "The other side has disconnected gracefully." << std::endl;
				return false;
			}
			
			if (bytesOrError == SOCKET_ERROR)
			{
				std::string msg = "Error encountered calling recv on socket.";
				TCPError(msg);
				return false;
			}

			mNumBytesInRecvBuffer += bytesOrError;

			if (mNumBytesInRecvBuffer > (0.66 * mRecvBufSize)
				&& !ReallocRecvBufferByDoublingSizeAndMovingContents())
				return false;
		}
	}

	std::string TCPSession::GetAllRecvBufferContents()
	{
		std::cout << "Bytes in buffer... " << mNumBytesInRecvBuffer << std::endl;
		std::string returnString(mRecvBuffer);
		ClearRecvBuffer();
		std::cout << "Now should be zero: " << mNumBytesInRecvBuffer << std::endl;
		return returnString;
	}

	bool TCPSession::Send(const std::string& data, int sendFlags)
	{
		unsigned short attemptCount = 0;
		int totalBytesSent = 0;
		const int totalBytesToSend = data.size() + 1;
		
		while (attemptCount++ < MAX_WRITE_ATTEMPTS)
		{
			int bytesOrError = send(
				mSocket, 
				data.c_str() + totalBytesSent, 
				totalBytesToSend - totalBytesSent, 
				sendFlags);
			
			if (bytesOrError == SOCKET_ERROR)
			{
				std::string msg = "Error encountered calling send on socket.";
				TCPError(msg);
				return false;
			}

			totalBytesSent += bytesOrError;
			if (totalBytesSent == totalBytesToSend)
				return true;
		}

		std::cout << "Unable to send after " << attemptCount << " attempts." << std::endl;
		return false;
	}

	bool TCPSession::ReallocRecvBufferByDoublingSizeAndMovingContents()
	{
		std::cout << "Realloc upwards from... " << mRecvBufSize << std::endl;

		size_t newRecvBufSize = 2 * mRecvBufSize;
		
		if (newRecvBufSize > MAX_RECV_BUF_SIZE)
		{
			std::cout << "Receive buffer size got unusually big; this should not happen." << std::endl;
			return false;
		}
		
		char* newRecvBuffer = new char[newRecvBufSize];
		ZeroMemory(newRecvBuffer, newRecvBufSize);
		CopyMemory(newRecvBuffer, mRecvBuffer, mNumBytesInRecvBuffer);
		delete[] mRecvBuffer;
		mRecvBuffer = newRecvBuffer;
		mRecvBufSize = newRecvBufSize;
		return true;
	}

	void TCPSession::ClearRecvBuffer()
	{
		ZeroMemory(mRecvBuffer, mRecvBufSize);
		mNumBytesInRecvBuffer = 0;
	}
}