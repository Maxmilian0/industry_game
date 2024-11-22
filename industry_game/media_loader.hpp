#ifndef MEDIA_LOADER_HPP
#define MEDIA_LOADER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MediaLoader {
public:
    template <typename T>
    static bool loadMedia(T& resource, const std::string& filename) {
        if (!resource.loadFromFile(filename)) {
            std::cerr << "Error loading " << filename << "!" << std::endl;
            return false;
        }
        return true;
    }
};

#endif // MEDIA_LOADER_HPP
