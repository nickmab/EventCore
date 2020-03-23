#include "DemoProtoParser.h"

namespace EventCore {

	bool DemoProtoParser::ConsumeFrom(TCPSession& session)
	{
		mInputBuffer << session.GetAllRecvBufferContents();

		// should have i) message size (4 bytes) then a ii) WrappedMessage.
		// check the type of the WrappedMessage, then farm out events accordingly.
		// ...obviously we might have message fragmentation too.
		
		std::string data = mInputBuffer.str();
		size_t dataIndex = 0;
		const size_t dataLength = data.length();

		for (;;)
		{
			const size_t bytesLeft = dataLength - dataIndex;
			if (mNextInputMessageSize)
			{
				// This toggles between 0 and an actual number;
				// a non-zero value means we've already read what the 
				// size of the next message is and can now go ahead and
				// attempt to parse it (iff there are enough bytes left
				// in the stream).
				if (bytesLeft < mNextInputMessageSize)
				{
					// Message fragmentation. We can do no more at this time.
					break;
				}
				else
				{
					if (!mWrappedMessage.ParseFromArray(&data[dataIndex], mNextInputMessageSize))
					{
						LOG_ERROR("Could not parse message from buffer!");
						return false;
					}
					if (mWrappedMessage.has_numeric_message())
					{
						OnNumericMessage(mWrappedMessage.numeric_message());
					}
					else if (mWrappedMessage.has_textual_message())
					{
						OnTextualMessage(mWrappedMessage.textual_message());
					}
					else
					{
						ASSERT(false, "This should be unreachable code.");
						return false;
					}

					dataIndex += mNextInputMessageSize;
					mNextInputMessageSize = 0;
				}
			}
			else
			{
				// We have not yet read what the next message's size is.
				if (bytesLeft < sizeof(int))
				{
					// not enough bytes. We've finished parsing,
					// and/or we have message fragmentation in the "message
					// size" part of the stream.
					break;
				}
				else
				{
					mNextInputMessageSize = *static_cast<int*>(static_cast<void*>(&data[dataIndex]));
					dataIndex += sizeof(int);
				}
			}
		}

		// whatever fragment remains, write it to the buffer for next time.
		mInputBuffer.write(&data[dataIndex], dataLength - dataIndex);
		return true;
	}

	bool DemoProtoParser::QueueMessageToWrite(const MsgVariant& inMsg)
	{
		WrappedMessage wrapped;
		
		// first we populate our own member variables with the right data...
		// this could easily be macro-ified if we end up with
		// lots of different message types...
		if (std::holds_alternative<NumericMessage>(inMsg))
		{
			NumericMessage* msg = new NumericMessage(std::get<NumericMessage>(inMsg));
			wrapped.set_allocated_numeric_message(msg);
			LOG_WARN("Queue Numeric");
		}
		else if (std::holds_alternative<TextualMessage>(inMsg))
		{
			TextualMessage* msg = new TextualMessage(std::get<TextualMessage>(inMsg));
			wrapped.set_allocated_textual_message(msg);
			LOG_WARN("Queue Textual");
		}
		else
		{
			ASSERT(false, "This should be unreachable code.");
			return false;
		}

		// Now we write the data to the output sstream. First the
		// message size, then the serialized message data.
		const int byteSize = wrapped.ByteSize();
		LOGF_WARN("ByteSize: {}", byteSize);
		mOutputBuffer.write(reinterpret_cast<const char*>(&byteSize), sizeof(int));
		LOG_WARN("Tryserialize...");
		const bool success = wrapped.SerializeToOstream(&mOutputBuffer);
		LOGF_WARN("Tried; success? {}", success);
		LOGF_WARN("Cleared; gggrrrrreturning.");
		return success;
	}

	bool DemoProtoParser::WriteTo(TCPSession& session)
	{
		LOG_WARN("Writeto...");
		std::string data(mOutputBuffer.str());
		mOutputBuffer.clear();
		if (!data.empty())
			return session.Send(data);
		return true;
	}

	void DemoProtoParser::OnNumericMessage(const NumericMessage& msg) const
	{
		LOGF_WARN("Received numeric message: {}", msg.DebugString());
	}
	
	void DemoProtoParser::OnTextualMessage(const TextualMessage& msg) const
	{
		LOGF_WARN("Received textual message: {}", msg.DebugString());
	}

}