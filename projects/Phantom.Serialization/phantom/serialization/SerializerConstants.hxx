#pragma once

// haunt {

// clang-format off

#include "SerializerConstants.h"

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
#include <phantom/enum_class>
#include <phantom/typedef>

#include <phantom/template-only-push>

#include <phantom/utils/Functor.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("SerializerConstants")

        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_REGISTER(Enums) { this_().enum_<SerializerStatus>().values({
            {"Error",SerializerStatus::Error},
            {"OK",SerializerStatus::OK},
            {"OptionalEntryNotFound",SerializerStatus::OptionalEntryNotFound}});
        }
        PHANTOM_REGISTER(Enums) { this_().enum_<SerializerError>().values({
            {"None",SerializerError::None},
            {"RequiredEntryNotFound",SerializerError::RequiredEntryNotFound},
            {"BadFormat",SerializerError::BadFormat},
            {"BadType",SerializerError::BadType},
            {"NotEnoughMemory",SerializerError::NotEnoughMemory},
            {"BufferOverflow",SerializerError::BufferOverflow},
            {"NoValidConversion",SerializerError::NoValidConversion},
            {"BadCount",SerializerError::BadCount},
            {"NotSerializable",SerializerError::NotSerializable},
            {"UnknownEnumValue",SerializerError::UnknownEnumValue},
            {"UnknownGUID",SerializerError::UnknownGUID},
            {"ExpectedArray",SerializerError::ExpectedArray},
            {"ExpectedStruct",SerializerError::ExpectedStruct},
            {"UnexpectedEndOfFile",SerializerError::UnexpectedEndOfFile}});
        }
        PHANTOM_REGISTER(Typedefs) { this_().typedef_<SerializerEntryPoint>("SerializerEntryPoint"); }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("SerializerConstants")
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
