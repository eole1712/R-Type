#include <chrono>
#include "Time.hpp"

Time::stamp Time::getTimeStamp()
{
  return static_cast<Time::stamp>(std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1));
}
