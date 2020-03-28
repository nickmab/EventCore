#pragma once

#define WIN32_LEAN_AND_MEAN   
#include <windows.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <signal.h>

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <variant>
#include <vector>

#include "Core/Logger.h"
#include "Core/Instrumentor.h"
#include "Proto/DemoProto/DemoProto.pb.h"
#include "Proto/MathProto/MathProto.pb.h"
#include "Proto/ProtoParser.h"