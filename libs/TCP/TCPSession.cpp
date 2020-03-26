#include "TCPSession.h"
#include "TCPUtils.h"
#include "Core/Logger.h"

namespace EventCore {

	TCPSession::SessionId TCPSession::sSessionIdCounter = 0;

	TCPSession::TCPSession(SOCKET sock, size_t initialRecvBufSize)
		: mSessionId(++sSessionIdCounter)
		, mSocket(sock)
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
		const int optVal = 1000;
		const int optLen = sizeof(int);
		setsockopt(mSocket, SOL_SOCKET, SO_LINGER, (char*)&optVal, optLen);
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
				LOG_INFO("The other side has disconnected gracefully.");
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
		std::string returnStr(mRecvBuffer, mNumBytesInRecvBuffer);
		ClearRecvBuffer();
		return returnStr;
	}

	bool TCPSession::Send(const std::string& data, int sendFlags)
	{
		unsigned short attemptCount = 0;
		int totalBytesSent = 0;
		const int totalBytesToSend = data.size();
		
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

		LOGF_WARN("Unable to send after {} attempts.", attemptCount);
		return false;
	}

	bool TCPSession::ReallocRecvBufferByDoublingSizeAndMovingContents()
	{
		LOGF_TRACE("Realloc upwards from {}", mRecvBufSize);

		size_t newRecvBufSize = 2 * mRecvBufSize;
		
		if (newRecvBufSize > MAX_RECV_BUF_SIZE)
		{
			LOG_ERROR("Receive buffer size got unusually big; this should not happen.");
			return false;
		}
		
		char* newRecvBuffer = new char[newRecvBufSize];
		memset(newRecvBuffer, '\0', newRecvBufSize);
		memcpy(newRecvBuffer, mRecvBuffer, mNumBytesInRecvBuffer);
		delete[] mRecvBuffer;
		mRecvBuffer = newRecvBuffer;
		mRecvBufSize = newRecvBufSize;
		return true;
	}

	void TCPSession::ClearRecvBuffer()
	{
		memset(mRecvBuffer, '\0', mRecvBufSize);
		mNumBytesInRecvBuffer = 0;
	}
}