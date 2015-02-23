#ifndef COMPILATION_CONTEXT_HPP_
#define COMPILATION_CONTEXT_HPP_

#include <cstddef>

class compilation_context
{
public:
    compilation_context()
      : next_uuid(1)
    {}
    std::size_t uuid()
    {
        std::size_t this_uuid = next_uuid;
        ++next_uuid;
        return this_uuid;
    }
private:
    std::size_t next_uuid;
};

#endif
