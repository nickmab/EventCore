#pragma once

#include <WS2tcpip.h>

#include <string>

namespace EventCore {

	// sanity check as we keep allocing more if the buffer needs to grow. 
	const size_t MAX_RECV_BUF_SIZE = 65536;
	const unsigned short MAX_WRITE_ATTEMPTS = 10;
		
	// When either a TCPServer or TCPClient actually initiates a connection 
	// on a port (i.e. once a conn is accepted on the listening port),
	// use one of these to manage the communication from there on.
	class TCPSession
	{
	public:
		using SessionId = int;

		TCPSession(SOCKET, size_t initialRecvBufSize = 1024);
		~TCPSession(); // Frees the buffer and closes the socket.
		
		// Calls WSAPoll and recv multiple times under the hood to read everything from the socket.
		// Returning true means client is still alive (and that there is data in the buffer).
		// Returning false means client is closed and/or there was an error.
		// If an error is encountered it will call "void EventCore::TCPError()" to fetch 
		// and log the error/reason.
		// Simply attempts to read as much as possible from the socket and will overwrite any 
		// existing contents of the buffer from the start. 
		// Will keep doubling the size of the buffer if required up to a pre-configured max,
		// at which point the we declare that an error has happened and shut the client off.
		bool Recv(int recvFlags = 0);

		// This is the thing that zeroes the buffer. Calls to recv will just keep appending to it,
		// so you need to periodically call this to get the data out and then clear the buffer.
		std::string GetAllRecvBufferContents();
		inline bool BufferHasData() const { return mNumBytesInRecvBuffer > 0; }
		inline SessionId GetSessionId() const { return mSessionId; }

		// Keeps trying to write until all bytes written, up to a preconfigured 
		// max number of attempts. True means success.
		// Returning false means client is closed and/or there was an error.
		// If an error is encountered it will call "void EventCore::TCPError()" to fetch 
		// and log the error/reason.
		bool Send(const std::string&, int sendFlags = 0);

	private:
		static SessionId sSessionIdCounter;
		SessionId mSessionId;

		SOCKET mSocket;
		size_t mRecvBufSize;
		char* mRecvBuffer;
		size_t mNumBytesInRecvBuffer{0};

		void ClearRecvBuffer();
		
		// Returns false if couldn't realloc (i.e. buffer got too big, indicating
		// something must be wrong).
		bool ReallocRecvBufferByDoublingSizeAndMovingContents();
	};

}