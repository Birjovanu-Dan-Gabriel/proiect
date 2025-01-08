//
// Created by birjo on 1/8/2025.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

template<typename T>
class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<T>> resources;

public:
    void loadResource(const std::string& name, const std::string& filename) {
        auto resource = std::make_unique<T>();
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error("Could not load resource: " + filename);
        }
        resources[name] = std::move(resource);
    }

    T* getResource(const std::string& name) {
        auto it = resources.find(name);
        if (it != resources.end()) {
            return it->second.get();
        }
        return nullptr;
    }

    ~ResourceManager() = default;
};

#endif //RESOURCEMANAGER_H
