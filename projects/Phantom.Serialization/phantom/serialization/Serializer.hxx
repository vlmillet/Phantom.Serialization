#pragma once

// haunt {

// clang-format off

#include "Serializer.h"

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
#include <phantom/struct>
#include <phantom/enum_class>
#include <phantom/method>
#include <phantom/constructor>
#include <phantom/friend>

#include <phantom/template-only-push>

#include <phantom/utils/StringView.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("Serializer")

        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_CLASS(Serializer)
        {
            using ArrayElementScope = typedef_<_::ArrayElementScope>;
            using ArrayScope = typedef_<_::ArrayScope>;
            using MemberScope = typedef_<_::MemberScope>;
            using Scope = typedef_<_::Scope>;
            using StringView = typedef_< phantom::StringView>;
            using StructureScope = typedef_<_::StructureScope>;
            this_()
        .public_()
            .enum_<Mode>().values({
                {"Read",_::Mode::Read},
                {"Write",_::Mode::Write}})
            .end()
            .constructor<void(Mode)>()({"a_eMode"})
            .method<Mode() const>("getMode", &_::getMode)
            .method<void(Mode)>("setMode", &_::setMode)({"_mode"})
            .method<bool() const>("isWriting", &_::isWriting)
            .method<bool() const>("isReading", &_::isReading)
            .method<void(SerializerError)>("setLastError", &_::setLastError)({"a_eError"})
            .method<SerializerError() const>("getLastError", &_::getLastError)
            .struct_<Scope>()
                .method<bool() const>("operator bool", &_::Scope::operator notypedef<bool>)
                .method<SerializerStatus() const>("getStatus", &_::Scope::getStatus)
            .end()
            .struct_<ArrayScope>()
                .inherits<::phantom::serialization::Serializer::Scope>()
                .constructor<void(Serializer&)>()({"a_S"})
                .constructor<void(ArrayScope&&)>()({"a_Temp"})
            .end()
            .method<ArrayScope()>("scopedArray", &_::scopedArray)
            .struct_<StructureScope>()
                .inherits<::phantom::serialization::Serializer::Scope>()
                .constructor<void(Serializer&)>()({"a_S"})
                .constructor<void(StructureScope&&)>()({"a_Temp"})
            .end()
            .method<StructureScope()>("scopedStructure", &_::scopedStructure)
            .struct_<ArrayElementScope>()
                .inherits<::phantom::serialization::Serializer::Scope>()
                .constructor<void(Serializer&)>()({"a_S"})
                .constructor<void(ArrayElementScope&&)>()({"a_Temp"})
            .end()
            .method<ArrayElementScope()>("scopedArrayElement", &_::scopedArrayElement)
            .struct_<MemberScope>()
                .inherits<::phantom::serialization::Serializer::Scope>()
                .constructor<void(Serializer&, StringView)>()({"a_S","a_Name"})
                .constructor<void(MemberScope&&)>()({"a_Temp"})
                .method<bool() const>("operator bool", &_::MemberScope::operator notypedef<bool>)
            .end()
            .method<MemberScope(StringView)>("scopedMember", &_::scopedMember)({"a_Name"})
            .method<::phantom::serialization::SerializerStatus(), pure_virtual>("beginArray", &_::beginArray)
            .method<void(), virtual_>("endArray", &_::endArray)
            .method<::phantom::serialization::SerializerStatus(), pure_virtual>("beginArrayElement", &_::beginArrayElement)
            .method<void(), virtual_>("endArrayElement", &_::endArrayElement)
            .method<::phantom::serialization::SerializerStatus(), pure_virtual>("beginStructure", &_::beginStructure)
            .method<void(), virtual_>("endStructure", &_::endStructure)
            .method<::phantom::serialization::SerializerStatus(StringView), pure_virtual>("beginMember", &_::beginMember)({"name"})
            .method<void(), virtual_>("endMember", &_::endMember)
            .method<::phantom::serialization::SerializerStatus(bool&), pure_virtual>("read", &_::read)({"a_bool"})
            .method<::phantom::serialization::SerializerStatus(char&), pure_virtual>("read", &_::read)({"a_char"})
            .method<::phantom::serialization::SerializerStatus(uint8&), pure_virtual>("read", &_::read)({"a_uchar"})
            .method<::phantom::serialization::SerializerStatus(int8&), pure_virtual>("read", &_::read)({"a_schar"})
            .method<::phantom::serialization::SerializerStatus(int16&), pure_virtual>("read", &_::read)({"a_int16"})
            .method<::phantom::serialization::SerializerStatus(uint16&), pure_virtual>("read", &_::read)({"a_uint16"})
            .method<::phantom::serialization::SerializerStatus(int32&), pure_virtual>("read", &_::read)({"a_int"})
            .method<::phantom::serialization::SerializerStatus(uint32&), pure_virtual>("read", &_::read)({"a_uint"})
            .method<::phantom::serialization::SerializerStatus(int64&), pure_virtual>("read", &_::read)({"a_int64"})
            .method<::phantom::serialization::SerializerStatus(uint64&), pure_virtual>("read", &_::read)({"a_uint64"})
            /// invalid declaration, some symbols have not been parsed correctly probably due to missing include path or missing #include in the .h
            // .method<SerializerStatus(long long&)>("read", &_::read)({"a_long"})
            /// invalid declaration, some symbols have not been parsed correctly probably due to missing include path or missing #include in the .h
            // .method<SerializerStatus(unsigned long long&)>("read", &_::read)({"a_ulong"})
            .method<::phantom::serialization::SerializerStatus(float&), pure_virtual>("read", &_::read)({"a_float"})
            .method<::phantom::serialization::SerializerStatus(double&), pure_virtual>("read", &_::read)({"a_double"})
            .method<::phantom::serialization::SerializerStatus(longdouble&), pure_virtual>("read", &_::read)({"a_longdouble"})
            .method<::phantom::serialization::SerializerStatus(StringView&), pure_virtual>("read", &_::read)({"a_str"})
            .method<::phantom::serialization::SerializerStatus(void*&, ::phantom::lang::Type *), pure_virtual>("read", &_::read)({"a_pPtr","a_pPointeeType"})
            .method<::phantom::serialization::SerializerStatus(void*, ::phantom::lang::Enum *), pure_virtual>("read", &_::read)({"a_pValue","a_pEnumType"})
            .method<::phantom::serialization::SerializerStatus(uint8*, size_t), pure_virtual>("read", &_::read)({"a_pBytes","a_FixedSize"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<::phantom::serialization::SerializerStatus(hex64&), pure_virtual>("read", &_::read)({"v"})
            .method<::phantom::serialization::SerializerStatus(wchar_t&), pure_virtual>("read", &_::read)({"a_wchar_t"})
            .method<::phantom::serialization::SerializerStatus(char16_t&), pure_virtual>("read", &_::read)({"a_char16_t"})
            .method<::phantom::serialization::SerializerStatus(char32_t&), pure_virtual>("read", &_::read)({"a_char32_t"})
            .method<::phantom::serialization::SerializerStatus(const bool&), pure_virtual>("write", &_::write)({"a_bool"})
            .method<::phantom::serialization::SerializerStatus(const char&), pure_virtual>("write", &_::write)({"a_char"})
            .method<::phantom::serialization::SerializerStatus(const int8&), pure_virtual>("write", &_::write)({"a_schar"})
            .method<::phantom::serialization::SerializerStatus(const uint8&), pure_virtual>("write", &_::write)({"a_uchar"})
            .method<::phantom::serialization::SerializerStatus(const int16&), pure_virtual>("write", &_::write)({"a_int16"})
            .method<::phantom::serialization::SerializerStatus(const uint16&), pure_virtual>("write", &_::write)({"a_uint16"})
            .method<::phantom::serialization::SerializerStatus(const int32&), pure_virtual>("write", &_::write)({"a_int"})
            .method<::phantom::serialization::SerializerStatus(const uint32&), pure_virtual>("write", &_::write)({"a_uint"})
            .method<::phantom::serialization::SerializerStatus(const int64&), pure_virtual>("write", &_::write)({"a_int64"})
            .method<::phantom::serialization::SerializerStatus(const uint64&), pure_virtual>("write", &_::write)({"a_uint64"})
            /// invalid declaration, some symbols have not been parsed correctly probably due to missing include path or missing #include in the .h
            // .method<SerializerStatus(const long long&)>("write", &_::write)({"a_long"})
            /// invalid declaration, some symbols have not been parsed correctly probably due to missing include path or missing #include in the .h
            // .method<SerializerStatus(const unsigned long long&)>("write", &_::write)({"a_ulong"})
            .method<::phantom::serialization::SerializerStatus(const float&), pure_virtual>("write", &_::write)({"a_float"})
            .method<::phantom::serialization::SerializerStatus(const double&), pure_virtual>("write", &_::write)({"a_double"})
            .method<::phantom::serialization::SerializerStatus(const longdouble&), pure_virtual>("write", &_::write)({"a_longdouble"})
            .method<::phantom::serialization::SerializerStatus(StringView), pure_virtual>("write", &_::write)({""})
            .method<::phantom::serialization::SerializerStatus(const char*, size_t), virtual_>("write", &_::write)({"a_pStr","a_Size"})
            .method<::phantom::serialization::SerializerStatus(void* const&, ::phantom::lang::Type *), pure_virtual>("write", &_::write)({"a_pPtr","a_pPointeeType"})
            .method<::phantom::serialization::SerializerStatus(void const*, ::phantom::lang::Enum *), pure_virtual>("write", &_::write)({"a_pValue","a_pEnumType"})
            .method<::phantom::serialization::SerializerStatus(uint8 const*, size_t), pure_virtual>("write", &_::write)({"a_pBytes","a_FixedSize"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<::phantom::serialization::SerializerStatus(hex64 const&), pure_virtual>("write", &_::write)({"v"})
            /// missing symbol(s) reflection (std::nullptr_t) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<SerializerStatus(const std::nullptr_t &)>("write", &_::write)({"a_nullptr"})
            /// missing symbol(s) reflection (std::nullptr_t) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<SerializerStatus(std::nullptr_t &)>("read", &_::read)({"a_nullptr"})
            .method<::phantom::serialization::SerializerStatus(const wchar_t&), pure_virtual>("write", &_::write)({"a_wchar_t"})
            .method<::phantom::serialization::SerializerStatus(const char16_t&), pure_virtual>("write", &_::write)({"a_char16_t"})
            .method<::phantom::serialization::SerializerStatus(const char32_t&), pure_virtual>("write", &_::write)({"a_char32_t"})
            .method<void(void*)>("pushUserData", &_::pushUserData)({"a_pData"})
            .method<void()>("popUserData", &_::popUserData)
            .method<void*() const>("topUserData", &_::topUserData)
            ;
        }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("Serializer")
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
