#include "ecs/Entity.hpp"
#include "ecs/Registry.hpp"
#include <iostream>



int main(){
    Registry registry;
    Entity e = registry.create();
    std::cout << "Created entity: " << e << std::endl;
    registry.printRegistry();
    registry.destroy(e);
    std::cout << "Destroyed entity: " << e << std::endl;
    registry.printRegistry();
    return 0;
}