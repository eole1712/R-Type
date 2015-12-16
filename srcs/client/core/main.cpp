#include "Menu.hpp"
#include "Client.hpp"

int	main(int ac, char **av)
{
  if (ac == 2)
    {
      Client cl(std::atoi(av[1]));
      cl.start();
      Menu menu(720, 480, &cl);
    }

  //  menu.initMainView();

}
