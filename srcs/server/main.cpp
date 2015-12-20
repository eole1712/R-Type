//
//  main.cpp
//  R-Type
//
//  Created by Grisha Ghukasyan on 25/11/2015.
//  Copyright © 2015 Grisha Ghukasyan. All rights reserved.
//

#include <iostream>
#include "Server.hpp"

int main(int , const char **) {
    // insert code here...
    std::cout << "Hello, World!\n";

    try {
      Server      server;

      server.start();
    }
    catch (std::exception const& e) {
      std::cerr << e.what() << std::endl;
    }
    return 0;
}
