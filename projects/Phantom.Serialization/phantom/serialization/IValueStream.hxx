#pragma once

// haunt {

// clang-format off

#include "IValueStream.h"

#if defined(_MSC_VER)
#   pragma warning(push, 0)
#elif defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wall"
#   pragma clang diagnostic ignored "-Wextra"
#endif

#include <phantom/namespace>
#include <phantom/package>
#include <phantom/source>
#include <phantom/variable>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("IValueStream")

        #if PHANTOM_NOT_TEMPLATE
        /// missing symbol(s) reflection (phantom::serialization::PHANTOM_VISIBILITY_EXPORT) -> use the 'haunt.bind' to bind symbols with your custom haunt files
        // PHANTOM_REGISTER(Variables) { this_().variable("IValueStream", &IValueStream); }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("IValueStream")
PHANTOM_END("phantom.serialization")
}
}

#if defined(_MSC_VER)
#   pragma warning(pop)
#elif defined(__clang__)
#   pragma clang diagnostic pop
#endif

// clang-format on

// haunt }
