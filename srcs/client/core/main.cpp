#include "Menu.hpp"
#include "Client.hpp"

int	main(int ac, char **av)
{
  int port = (ac > 1) ? std::atoi(av[1]) : 6137;
  try {
    Client cl(port);

    cl.start();
    std::cout << "finish" << std::endl;
  }
  catch (std::exception const&e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
