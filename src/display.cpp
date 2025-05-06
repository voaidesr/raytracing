#include "display.h"
#include <algorithm>

Display::Display(int width, int height) : w_(width), h_(height),
      pixels_(static_cast<std::size_t>(width) * height * 4),
      window_(sf::VideoMode(width, height),
              "Live Preview",
              sf::Style::Titlebar | sf::Style::Close)
{
    window_.setVerticalSyncEnabled(false);
    tex_.create(width, height);
    sprite_.setTexture(tex_);
}

void Display::update() {
    if (!window_.isOpen()) return;

    tex_.update(pixels_.data());
    window_.clear();
    window_.draw(sprite_);
    window_.display();

    sf::Event e;
    while (window_.pollEvent(e))
        if (e.type == sf::Event::Closed)
            window_.close();
}
