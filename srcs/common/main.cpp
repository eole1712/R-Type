#include "ILibLoader.hpp"

#if defined(__linux__) || (defined __APPLE__)
#include "linux_specific/CULibLoader.hpp"
#elif defined(_WIN32)
#include "windows_specific/CWLibLoader.hpp"
#endif

int	main()
{
  ILibLoader*	libLoader;

#if defined(__linux__) || (defined __APPLE__)
  libLoader = new CULibLoader("MonsterTest", "NewMonster", "DeleteMonster");
#elif defined(_WIN32)
  libLoader = new CWLibLoader("MonsterTest", "NewMonster", "DeleteMonster");
#endif

  (void)libLoader;
  return (0);
}
