#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "utils.h"

class Display {
public:
    Display(int width, int height);
    ~Display() = default;

    inline void set_pixel(int x, int y, color& c) {
        std::size_t idx = 4ull * (static_cast<std::size_t>(y) * w_ + x);
        pixels_[idx + 0] = static_cast<uint8_t>(255.99f * std::clamp(static_cast<float>(c.x()), 0.0f, 1.0f));
        pixels_[idx + 1] = static_cast<uint8_t>(255.99f * std::clamp(static_cast<float>(c.y()), 0.0f, 1.0f));
        pixels_[idx + 2] = static_cast<uint8_t>(255.99f * std::clamp(static_cast<float>(c.z()), 0.0f, 1.0f));
        pixels_[idx + 3] = 255;
    }

    void update();

    bool is_open() const { return window_.isOpen(); }

private:
    int w_, h_;
    std::vector<uint8_t> pixels_; // 8 bytes int for rgb
    sf::RenderWindow window_;
    sf::Texture tex_;
    sf::Sprite sprite_;
};


#endif