#pragma once

#include "Core/Event.h"
#include "Proto/DemoProto/DemoProto.pb.h"

namespace EventCore {

	class DemoProtoMessageEvent : public Event
	{
	public:
		// ALL messages MUST be added to this enum.
		enum class MessageType
		{
			Begin = 0,

			// Insert messages in here. "Begin" and "End" are used just for iteration.
			NumericMessage,
			TextualMessage,

			// Insert messages in the section above. "Begin" and "End" are used just for iteration.
			End
		};
		
		DemoProtoMessageEvent(MessageType, google::protobuf::Message*);
		
		inline virtual Event::Type GetType() const override { return Event::Type::OnDemoProtoMessage; }
		inline virtual const char* const GetName() const override { return "OnDemoProtoMessageEvent"; }

	private:

	};

}