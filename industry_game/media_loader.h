#ifndef MEDIA_LOADER_H
#define MEDIA_LOADER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MediaLoader {
public:
    template <typename T>
    static bool loadSoundBuffer(T& resource, const std::string& filename) {
        if (!resource.loadFromFile(filename)) {
            std::cerr << "Error loading " << filename << "!" << std::endl;
            return false;
        }
        return true;
    }
};

#endif // MEDIA_LOADER_H
