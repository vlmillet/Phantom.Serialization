#pragma once

// haunt {

// clang-format off

#include "ValueUtils.h"

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
#include <phantom/class>
#include <phantom/static_method>
#include <phantom/typedef>

#include <phantom/template-only-push>

#include <phantom/utils/StringView.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("ValueUtils")

        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_CLASS(ValueUtils)
        {
            using SerializerError = typedef_<_::SerializerError>;
            using SerializerStatus = typedef_<_::SerializerStatus>;
            using SerializerVisitor = typedef_<_::SerializerVisitor>;
            using StringView = typedef_< phantom::StringView>;
            using ValueSerializer = typedef_<_::ValueSerializer>;
            this_()
        .public_()
            .typedef_<ValueSerializer>("ValueSerializer")
            .typedef_<SerializerStatus>("SerializerStatus")
            .typedef_<SerializerError>("SerializerError")
            .typedef_<SerializerVisitor>("SerializerVisitor")
            .staticMethod<bool(StringView, const Value&)>("SaveToFile", &_::SaveToFile)({"a_FilePath","a_Val"})
            .staticMethod<bool(StringView, Value&)>("LoadFromFile", &_::LoadFromFile)({"a_FilePath","a_Out"})
            ;
        }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("ValueUtils")
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
