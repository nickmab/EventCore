#include "DemoProtoParser.h"

namespace EventCore {

	ProtoParser* DemoProtoParser::New()
	{
		return new DemoProtoParser();
	}

	bool DemoProtoParser::ConsumeFrom(TCPSession& session)
	{
		mInputBuffer << session.GetAllRecvBufferContents();

		// should have i) message size (4 bytes) then a ii) WrappedMessage.
		// check the type of the WrappedMessage, then farm out events accordingly.
		// ...obviously we might have message fragmentation too.
		
		std::string data = mInputBuffer.str();
		size_t dataIndex = 0;
		const size_t dataLength = data.length();
		WrappedMessage wrapped;

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
					if (!wrapped.ParseFromArray(&data[dataIndex], mNextInputMessageSize))
					{
						LOG_ERROR("Could not parse message from buffer!");
						return false;
					}
					if (wrapped.has_numeric_message())
					{
						OnNumericMessage(wrapped.numeric_message());
					}
					else if (wrapped.has_textual_message())
					{
						OnTextualMessage(wrapped.textual_message());
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

	bool DemoProtoParser::QueueMessageToWrite(const ProtoMsgVariant& inMsg)
	{
		WrappedMessage wrapped;
		
		// first we populate our own member variables with the right data...
		// this could easily be macro-ified if we end up with
		// lots of different message types...
		if (std::holds_alternative<NumericMessage>(inMsg))
		{
			NumericMessage* msg = new NumericMessage(std::get<NumericMessage>(inMsg));
			wrapped.set_allocated_numeric_message(msg);
		}
		else if (std::holds_alternative<TextualMessage>(inMsg))
		{
			TextualMessage* msg = new TextualMessage(std::get<TextualMessage>(inMsg));
			wrapped.set_allocated_textual_message(msg);
		}
		else
		{
			ASSERT(false, "This should be unreachable code.");
			return false;
		}

		// Now we write the data to the output sstream. First the
		// message size, then the serialized message data.
		const int byteSize = wrapped.ByteSize();
		mOutputBuffer.write(reinterpret_cast<const char*>(&byteSize), sizeof(int));
		return wrapped.SerializeToOstream(&mOutputBuffer);
	}

	bool DemoProtoParser::WriteTo(TCPSession& session)
	{
		std::string data(mOutputBuffer.str());
		mOutputBuffer.str(std::string()); // this is how you clear a stringstream.
		return session.Send(data);
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