#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "Sudoku Game");

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color(240, 240, 240));
		window.display();
	}
	return 0;
}
