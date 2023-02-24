#ifndef CORE_MAP_GENERATOR_H
#define CORE_MAP_GENERATOR_H

#include "thread_pool.h"
#include <string>
#include <memory>
#include <vector>

namespace map_generator {
    class tile_loader {
    public:
        tile_loader(unsigned short scale);
        virtual ~tile_loader() noexcept;

        char* load_tile(unsigned short index);
    };

    class tile_handler {
    public:
        tile_loader add_tile(std::string path);
    };
}

#endif //CORE_MAP_GENERATOR_H
