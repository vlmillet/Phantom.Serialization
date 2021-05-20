#pragma once

// haunt {

// clang-format off

#include "BinarySerializer.h"

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
#include <phantom/method>
#include <phantom/constructor>
#include <phantom/using>

#include <phantom/template-only-push>

#include <phantom/utils/StringView.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("BinarySerializer")

        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_CLASS(BinarySerializer)
        {
            using StringView = typedef_< phantom::StringView>;
            this_()
            .inherits<::phantom::serialization::Serializer>()
        .public_()
            .constructor<void()>()
            .constructor<void(const byte*, size_t)>()({"a_pBuffer","a_uiBufferSize"})["~size_t(0)"]
            /// missing symbol(s) reflection (phantom::BufferData) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .constructor<void(const BufferData&)>()({"a_Buffer"})
            .method<const byte*() const>("getBuffer", &_::getBuffer)
            .method<size_t() const>("getSize", &_::getSize)
            /// missing symbol(s) reflection (phantom::BufferData) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<void(BufferData&)>("takeWriteBuffer", &_::takeWriteBuffer)({"a_Buffer"})
            .method<byte*(size_t&)>("takeWriteBuffer", &_::takeWriteBuffer)({"a_uiSize"})
            .method<::phantom::serialization::SerializerStatus(), virtual_|override_>("beginArray", &_::beginArray)
            .method<void(), virtual_|override_>("endArray", &_::endArray)
            .method<::phantom::serialization::SerializerStatus(), virtual_|override_>("beginArrayElement", &_::beginArrayElement)
            .method<void(), virtual_|override_>("endArrayElement", &_::endArrayElement)
            .method<::phantom::serialization::SerializerStatus(), virtual_|override_>("beginStructure", &_::beginStructure)
            .method<void(), virtual_|override_>("endStructure", &_::endStructure)
            .method<::phantom::serialization::SerializerStatus(StringView), virtual_|override_>("beginMember", &_::beginMember)({"name"})
            .method<void(), virtual_|override_>("endMember", &_::endMember)
            .using_("Serializer::read")
            .method<::phantom::serialization::SerializerStatus(bool&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(char&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(uint8&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(int8&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(int16&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(uint16&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(int32&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(uint32&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(int64&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(uint64&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(float&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(double&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(longdouble&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(StringView&), virtual_|override_>("read", &_::read)({"v"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<::phantom::serialization::SerializerStatus(hex64&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(void*&, ::phantom::lang::Type *), virtual_|override_>("read", &_::read)({"a_pPtr","a_pPointeeType"})
            .method<::phantom::serialization::SerializerStatus(void*, ::phantom::lang::Enum *), virtual_|override_>("read", &_::read)({"a_pValue","a_pEnumType"})
            .method<::phantom::serialization::SerializerStatus(wchar_t&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(char16_t&), virtual_|override_>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(char32_t&), virtual_|override_>("read", &_::read)({"v"})
            .using_("Serializer::write")
            .method<::phantom::serialization::SerializerStatus(const bool&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const char&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const uint8&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const int8&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const int16&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const uint16&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const int32&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const uint32&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const int64&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const uint64&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const float&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const double&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const longdouble&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(StringView), virtual_|override_>("write", &_::write)({"str"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<::phantom::serialization::SerializerStatus(const hex64&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(void* const&, ::phantom::lang::Type *), virtual_|override_>("write", &_::write)({"v","a_pPointeeType"})
            .method<::phantom::serialization::SerializerStatus(void const*, ::phantom::lang::Enum *), virtual_|override_>("write", &_::write)({"v","a_pEnumType"})
            .method<::phantom::serialization::SerializerStatus(const wchar_t&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const char16_t&), virtual_|override_>("write", &_::write)({"v"})
            .method<::phantom::serialization::SerializerStatus(const char32_t&), virtual_|override_>("write", &_::write)({"v"})
            ;
        }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("BinarySerializer")
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
