#include "Application.h"

#include <string>
#include <iostream>
#include "Proto/DemoProto/DemoProto.pb.h"

#include <array>
#include <bitset>
#include <charconv>
#include <cstring>
#include <sstream>

int main(int argc, char* argv[])
{
	demoproto::NumericMessage msg;
	msg.set_an_integer(6123);
	msg.set_a_double(42.1);
	std::string srlzMsg;
	msg.SerializeToString(&srlzMsg);
	demoproto::NumericMessage msg2;
	bool success = msg2.ParseFromString(srlzMsg);
	LOGF_INFO("Success: {} msg: {} size1: {} length1: {}", 
		success, msg2.DebugString(), msg.ByteSize(), srlzMsg.length());

	success = msg2.ParseFromArray(&srlzMsg[0], msg.ByteSize());
	LOGF_WARN("Success: {} msg: {}", success, msg2.DebugString());

	demoproto::TextualMessage msgt;
	msgt.set_a_sentence("Hello, world; my name is tutlunkun");
	msgt.SerializeToString(&srlzMsg);
	demoproto::TextualMessage msgt2;
	success = msgt2.ParseFromString(srlzMsg);
	LOGF_INFO("Success: {} msg: {}", success, msgt2.DebugString());
	
	int32_t x = 3982043;
	std::string sizeData;
	sizeData.reserve(4);
	memcpy(&sizeData[0], static_cast<void*>(&x), 4);
	int32_t x2 = *static_cast<int32_t*>(static_cast<void*>(&sizeData[0]));

	LOGF_INFO("intBytes: {} int: {}", sizeData, x2);

	std::stringstream ss;
	x = msg.ByteSize();
	LOGF_INFO("First msg size: {}", x);
	ss.write(reinterpret_cast<const char *>(&x), 4);
	msg.SerializeToOstream(&ss);
	x = msgt.ByteSize();
	LOGF_INFO("Second msg size: {}", x);
	ss.write(reinterpret_cast<const char*>(&x), 4);
	msgt.SerializeToOstream(&ss);
	LOGF_INFO("ss is: {}", ss.str());
	
	ss.read(&sizeData[0], 4);
	x2 = *static_cast<int32_t*>(static_cast<void*>(&sizeData[0]));
	LOGF_INFO("First msg size: {}", x2);
	std::string inData;
	inData.reserve(x2);
	ss.read(&inData[0], x2);

	success = msg2.ParseFromArray(&inData[0], x2);
	LOGF_INFO("Success: {} msg: {}", success, msg2.DebugString());

	ss.read(&sizeData[0], 4);
	x2 = *static_cast<int32_t*>(static_cast<void*>(&sizeData[0]));
	LOGF_INFO("Second msg size: {}", x2);
	inData.reserve(x2);
	ss.read(&inData[0], x2);

	success = msg2.ParseFromArray(&inData[0], x2);
	LOGF_INFO("Success: {} msg: {}", success, msg2.DebugString());

	LOG_INFO("Returning.");

	sizeData.reserve(8);
	x = 41592437;
	memcpy(&sizeData[0], static_cast<void*>(&x), 4);
	x = -3784;
	memcpy(&sizeData[4], static_cast<void*>(&x), 4);

	LOG_ERROR(*static_cast<int32_t*>(static_cast<void*>(&sizeData[0])));
	LOG_ERROR(*static_cast<int32_t*>(static_cast<void*>(&sizeData[4])));

	return EventCore::EntryPoint::MainFunction(argc, argv);
}

namespace EventCore {

	// see declaration of extern static Application* CreateApplication(); in Application.h
	Application* Application::sInstance = nullptr;
	
	Application::~Application()
	{
	}

	void Application::Shutdown(int exitCode)
	{
		mExitCode = exitCode; 
		mIsRunning = false;
	}

	void Application::RegisterEventProducer(std::shared_ptr<EventProducer> producer)
	{
		mEventProducers.push_back(producer);
	}

	void Application::UnregisterEventProducer(std::shared_ptr<EventProducer> producer)
	{
		// should check that this actually works...
		auto it = std::find(mEventProducers.begin(), mEventProducers.end(), producer);
		if (it != mEventProducers.end())
			mEventProducers.erase(it);
	}

	void Application::Run()
	{
		for (;;)
		{
			if (mIsRunning)
			{
				OnUpdate();
			}
			else
			{
				return;
			}

			for (std::shared_ptr<EventProducer> producer : mEventProducers)
			{
				if (mIsRunning)
				{
					producer->OnUpdate();
				}
				else
				{
					return;
				}
			}

			if (mIsRunning)
			{
				mEventQueue.PublishEvents();
			}
			else
			{
				return;
			}
		}
			
	}

	int EntryPoint::MainFunction(int argc, char* argv[])
	{
		Application* instance = CreateApplication();
		Application::sInstance = instance;
		instance->Init();
		instance->Run();
		int exitCode = instance->mExitCode;
		delete instance;
		return exitCode;
	}
		
}