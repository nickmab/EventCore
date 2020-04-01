#include "pch.h"

#include "MathProtoParser.h"

namespace EventCore {

    ProtoParser* MathProtoParser::New()
    {
        return new MathProtoParser();
    }

    bool MathProtoParser::ConsumeFrom(TCPSession& session)
    {
        TIME_SCOPE;
        
        mInputBuffer << session.GetAllRecvBufferContents();

        // should have i) message size (4 bytes) then a ii) WrappedMessage.
        // check the type of the WrappedMessage, then farm out events accordingly.
        // ...obviously we might have message fragmentation too.

        std::string data = mInputBuffer.str();
        // clear the input buffer...
        mInputBuffer.str(std::string());
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

                    dataIndex += mNextInputMessageSize;
                    mNextInputMessageSize = 0;

                    RaiseEvent(ProtoMessageReceivedEvent::New(this, session.GetSessionId(), wrapped));
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

    bool MathProtoParser::QueueMessageToWrite(const ProtoMsgVariant& inMsg)
    {
        WrappedMessage wrapped;

        // populate wrapped message with the correct internal data
        // according to which "oneof" type the caller has provided...
        if (std::holds_alternative<ArithmeticRequest>(inMsg))
        {
            ArithmeticRequest* msg = wrapped.mutable_arithmetic_request();
            *msg = std::get<ArithmeticRequest>(inMsg);
        }
        else if (std::holds_alternative<ArithmeticResponse>(inMsg))
        {
            ArithmeticResponse* msg = wrapped.mutable_arithmetic_response();
            *msg = std::get<ArithmeticResponse>(inMsg);
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

    bool MathProtoParser::WriteTo(TCPSession& session)
    {
        std::string data(mOutputBuffer.str());
        // clear the output buffer
        mOutputBuffer.str(std::string());
        return session.Send(data);
    }

    bool MathProtoParser::HasData()
    {
        return mOutputBuffer.str().length() > 0;
    }

}