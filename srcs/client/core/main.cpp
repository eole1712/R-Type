#include "Menu.hpp"
#include "Client.hpp"

int	main(int ac, char **av)
{
  int port = (ac > 1) ? std::atoi(av[1]) : 6137;
  Client cl(port);

  cl.start();
  Menu menu(720, 480, &cl);
}
