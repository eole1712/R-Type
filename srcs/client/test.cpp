#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
  // Create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  // Load a sprite to display
  sf::Texture texture;
  if (!texture.loadFromFile("bra.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(texture);
  // Start the game loop
  while (window.isOpen())
    {
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
        {
	  // Close window: exit
	  if (event.type == sf::Event::Closed)
	    window.close();
        }
      // Clear screen
      window.clear();
      // Draw the sprite
      window.draw(sprite);
      // Update the window
      window.display();
    }
  return EXIT_SUCCESS;
}
