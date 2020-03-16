#pragma once
// Pre-Compiled Headers to increase performance, must include Xpch.h in every source file(.cpp)
// C++ Libraires
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
// Log System Files
#include "XEngine/LogSystem/Log.h"
// Libraries exclusive to the Windows Platform
#ifdef X_PLATFORM_WINDOWS
	#include <Windows.h>
#endif