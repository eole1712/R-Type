#include "ILibLoader.hpp"

#if defined(__linux__)
#include "CULibLoader.hpp"
#elif defined(_WIN32)
#include "CWLibLoader.hpp"
#endif

int	main()
{
  ILibLoader*	loader;

#if defined(__linux__)
  libLoader = new CULibLoader(libName, "NewMonster", "DeleteMonster");
#elif defined(_WIN32)
  libLoader = new CWLibLoader(libName, "NewMonster", "DeleteMonster");
#endif

  (void)loader;
  return (0);
}
