#include <chrono>
#include "Time.hpp"

namespace RType
{
  Time::stamp Time::getTimeStamp()
  {
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
  }
}
