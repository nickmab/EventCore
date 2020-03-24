#pragma once

#include "Core/Logger.h"
#include "TCP/TCPSession.h"
#include "Proto/ProtoParser.h"
#include "DemoProto.pb.h"

#include <sstream>
#include <variant>

using namespace demoproto;

namespace EventCore {

	class DemoProtoParser : public ProtoParser
	{
	public:

		static ProtoParser* New();
		
		// false indicates error.
		virtual bool ConsumeFrom(TCPSession&) override;
		virtual bool QueueMessageToWrite(const ProtoMsgVariant&) override;
		virtual bool WriteTo(TCPSession&) override;

		virtual inline bool HasData() override { return mOutputBuffer.peek() != std::char_traits<char>::eof(); }

	private:
		// these are used for i/o buffering and caching, saves you
		// repeatedly creating the same objects over and over. The protobuf
		// docs themselves suggest reusing message instances. 
		std::stringstream mInputBuffer;
		int mNextInputMessageSize{0};
		std::stringstream mOutputBuffer;
		WrappedMessage mWrappedMessage;
		NumericMessage mNumericMessage;
		TextualMessage mTextualMessage;
		// placeholder event handlers just for dev/testing right now.
		void OnNumericMessage(const NumericMessage&) const;
		void OnTextualMessage(const TextualMessage&) const;
	};

}