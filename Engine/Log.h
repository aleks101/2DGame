#pragma once

#include <iostream>

#ifdef DEBUG
#define LOG(msg) std::cout << msg
#else
#define LOG(msg)
#endif // !DEBUG