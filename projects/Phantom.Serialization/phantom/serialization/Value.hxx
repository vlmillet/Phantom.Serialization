#pragma once

// haunt {

// clang-format off

#include "Value.h"

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
#include <phantom/enum>
#include <phantom/static_field>
#include <phantom/method>
#include <phantom/static_method>
#include <phantom/constructor>
#include <phantom/field>
#include <phantom/typedef>

#include <phantom/template-only-push>

#include <phantom/utils/SmallMap.hxx>
#include <phantom/utils/SmallString.hxx>
#include <phantom/utils/SmallVector.hxx>
#include <phantom/utils/StringView.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("Value")

        PHANTOM_STRUCT_T((class, class, bool, bool), (T0, T1, T0_unsigned, T1_unsigned), ValuePrimitiveEqualityPromoterSignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, true, false), ValuePrimitiveEqualityPromoterSignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, false, true), ValuePrimitiveEqualityPromoterSignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, false, false), ValuePrimitiveEqualityPromoterSignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_T((class, class), (T0, T1), ValuePrimitiveEqualityPromoter)
        {
            this_()
            .PHANTOM_T inherits<::phantom::serialization::ValuePrimitiveEqualityPromoterSignDependant<T0, T1, std::is_unsigned<T0>::value, std::is_unsigned<T1>::value>>()
            ;
        }
        PHANTOM_STRUCT_S((char, bool), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((bool, char), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((unsigned char, bool), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((bool, unsigned char), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((signed char, bool), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((bool, signed char), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long double, unsigned long long), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((unsigned long long, long double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((double, unsigned long long), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((unsigned long long, double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long double, long long), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long long, long double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((double, long long), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long long, double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long double, double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((double, long double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((long double, float), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((float, long double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((double, float), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((float, double), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_TS((class), (T0), (T0, T0), ValuePrimitiveEqualityPromoter)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_T((class, class, bool, bool), (T0, T1, T0_unsigned, T1_unsigned), ValuePrimitiveEqualitySignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            .PHANTOM_T staticMethod<bool(T0, T1)>("isSame", &_::isSame)({"v0","v1"})
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, false, false), ValuePrimitiveEqualitySignDependant)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            .PHANTOM_T staticMethod<bool(T0, T1)>("isSame", &_::isSame)({"v0","v1"})
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, true, false), ValuePrimitiveEqualitySignDependant)
        {
            using promoted_type = typedef_<PHANTOM_TYPENAME _::promoted_type>;
            this_()
            .PHANTOM_T typedef_<promoted_type>("promoted_type")
            .PHANTOM_T staticMethod<bool(T0, T1)>("isSame", &_::isSame)({"v0","v1"})
            ;
        }
        PHANTOM_STRUCT_TS((class, class), (T0, T1), (T0, T1, false, true), ValuePrimitiveEqualitySignDependant)
        {
            using promoted_type = typedef_<PHANTOM_TYPENAME _::promoted_type>;
            this_()
            .PHANTOM_T typedef_<promoted_type>("promoted_type")
            .PHANTOM_T staticMethod<bool(T0, T1)>("isSame", &_::isSame)({"v0","v1"})
            ;
        }
        PHANTOM_STRUCT_T((class, class), (T0, T1), ValuePrimitiveEquality)
        {
            this_()
            .PHANTOM_T inherits<::phantom::serialization::ValuePrimitiveEqualitySignDependant<T0, T1, std::is_unsigned<T0>::value, std::is_unsigned<T1>::value>>()
            ;
        }
        PHANTOM_STRUCT_S((float, float), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(float, float, float)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((long double, long double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(long double, long double, long double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((double, double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(double, double, double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((float, long double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(float, long double, long double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((long double, float), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(long double, float, long double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((double, long double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(double, long double, long double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((long double, double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(long double, double, long double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((float, double), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(float, double, double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_S((double, float), ValuePrimitiveEquality)
        {
            this_()
            .staticMethod<bool(double, float, double)>("isSame", &_::isSame)({"v0","v1","epsilon"})
            ;
        }
        PHANTOM_STRUCT_TS((class), (T0), (T0, T0), ValuePrimitiveEquality)
        {
            this_()
            .PHANTOM_T staticMethod<bool(T0, T0)>("isSame", &_::isSame)({"v0","v1"})
            ;
        }
        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_CLASS(Value)
        {
            using Array = typedef_<_::Array>;
            using EType = typedef_<_::EType>;
            using Separator = typedef_<_::Separator>;
            using String = typedef_< phantom::String>;
            using StringView = typedef_< phantom::StringView>;
            using Struct = typedef_<_::Struct>;
            this_()
        .public_()
            .struct_<Separator>()
                .constructor<void(char), explicit_>()({"c"})
                .field("c", &_::Separator::c)
            .end()
            .enum_<EType>().values({
                {"e_undefined",_::e_undefined},
                {"e_bool",_::e_bool},
                {"e_char",_::e_char},
                {"e_uint8",_::e_uint8},
                {"e_int8",_::e_int8},
                {"e_int16",_::e_int16},
                {"e_uint16",_::e_uint16},
                {"e_int32",_::e_int32},
                {"e_uint32",_::e_uint32},
                {"e_int64",_::e_int64},
                {"e_uint64",_::e_uint64},
                {"e_float",_::e_float},
                {"e_double",_::e_double},
                {"e_longdouble",_::e_longdouble},
                {"e_wchar_t",_::e_wchar_t},
                {"e_char16_t",_::e_char16_t},
                {"e_char32_t",_::e_char32_t},
                {"e_hex64",_::e_hex64},
                {"e_cstr",_::e_cstr},
                {"e_struct",_::e_struct},
                {"e_array",_::e_array}})
            .end()
            .typedef_<Struct>("Struct")
            .typedef_<Array>("Array")
            .staticField("null", &_::null)
            .constructor<void()>()
            .constructor<void(const Value&)>()({"copied"})
            .constructor<void(Value&&)>()({"temp"})
            .constructor<void(StringView), explicit_>()({"cstr"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .constructor<void(hex64), explicit_>()({"hex"})
            .method<Value&(Value&&)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"temp"})
            .method<Value&(const Value&)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"copied"})
            .method<Value&(String)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"c"})
            .method<Value&(StringView)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"c"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<Value&(hex64)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"x"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<bool(hex64&) const>("as", &_::as)({"val"})
            .method<StringView() const>("str", &_::str)
            .constructor<void(bool)>()({"val"})
            .method<Value&(bool)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(bool&) const>("as", &_::as)({"val"})
            .constructor<void(char)>()({"val"})
            .method<::phantom::serialization::Value &(char)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(char&) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::uint8)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::uint8)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::uint8 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::int8)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::int8)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::int8 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::int16)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::int16)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::int16 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::uint16)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::uint16)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::uint16 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::int32)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::int32)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::int32 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::uint32)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::uint32)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::uint32 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::int64)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::int64)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::int64 &) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::uint64)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::uint64)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::uint64 &) const>("as", &_::as)({"val"})
            .constructor<void(float)>()({"val"})
            .method<::phantom::serialization::Value &(float)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(float&) const>("as", &_::as)({"val"})
            .constructor<void(double)>()({"val"})
            .method<::phantom::serialization::Value &(double)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(double&) const>("as", &_::as)({"val"})
            .constructor<void(::phantom::longdouble)>()({"val"})
            .method<::phantom::serialization::Value &(::phantom::longdouble)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(::phantom::longdouble &) const>("as", &_::as)({"val"})
            .constructor<void(wchar_t)>()({"val"})
            .method<::phantom::serialization::Value &(wchar_t)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(wchar_t&) const>("as", &_::as)({"val"})
            .constructor<void(char16_t)>()({"val"})
            .method<::phantom::serialization::Value &(char16_t)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(char16_t&) const>("as", &_::as)({"val"})
            .constructor<void(char32_t)>()({"val"})
            .method<::phantom::serialization::Value &(char32_t)>("operator=", &PHANTOM_REFLECTED_TYPE::operator=)({"val"})
            .method<bool(char32_t&) const>("as", &_::as)({"val"})
            .method<bool(StringView&) const>("as", &_::as)({"val"})
            .method<bool(String&) const>("as", &_::as)({"val"})
            /// missing symbol(s) reflection (phantom::hex64) -> use the 'haunt.bind' to bind symbols with your custom haunt files
            // .method<bool(hex64) const>("isSame", &_::isSame)({"v"})
            .method<bool(StringView) const>("isSame", &_::isSame)({"v"})
            .method<bool(const Value&) const>("isSame", &_::isSame)({"other"})
            .method<bool(bool) const>("isSame", &_::isSame)({"v"})
            .method<bool(char) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::uint8) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::int8) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::int16) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::uint16) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::int32) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::uint32) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::int64) const>("isSame", &_::isSame)({"v"})
            .method<bool(::phantom::uint64) const>("isSame", &_::isSame)({"v"})
            .method<bool(float, float) const>("isSame", &_::isSame)({"v","epsilon"})
            .method<bool(double, double) const>("isSame", &_::isSame)({"v","epsilon"})
            .method<bool(::phantom::longdouble, ::phantom::longdouble) const>("isSame", &_::isSame)({"v","epsilon"})
            .method<bool(wchar_t) const>("isSame", &_::isSame)({"v"})
            .method<bool(char16_t) const>("isSame", &_::isSame)({"v"})
            .method<bool(char32_t) const>("isSame", &_::isSame)({"v"})
            .method<void()>("reset", &_::reset)
            .method<::phantom::serialization::Value::EType() const>("getType", &_::getType)
            .method<bool() const>("isArray", &_::isArray)
            .method<bool() const>("isStruct", &_::isStruct)
            .method<bool() const>("isDefined", &_::isDefined)
            .method<Array&()>("asArray", &_::asArray)
            .method<Struct&()>("asStruct", &_::asStruct)
            .method<const Array&() const>("asArray", &_::asArray)
            .method<const Struct&() const>("asStruct", &_::asStruct)
            .method<void(Value&&)>("addValue", &_::addValue)({"val"})
            .method<::phantom::serialization::Value &()>("addValue", &_::addValue)
            .method<void(StringView)>("removeValue", &_::removeValue)({"name"})
            .method<void(size_t)>("removeValue", &_::removeValue)({"index"})
            .method<::phantom::serialization::Value &(StringView)>("addValue", &_::addValue)({"a_strName"})
            .method<::phantom::serialization::Value &()>("addStructValue", &_::addStructValue)
            .method<::phantom::serialization::Value &(StringView)>("addStructValue", &_::addStructValue)({"a_Name"})
            .method<::phantom::serialization::Value &()>("addArrayValue", &_::addArrayValue)
            .method<::phantom::serialization::Value &(StringView)>("addArrayValue", &_::addArrayValue)({"a_pName"})
            .method<void(size_t)>("setArray", &_::setArray)({"count"})["0"]
            .method<void()>("setStruct", &_::setStruct)
            .method<void(const Value&)>("addValue", &_::addValue)({"val"})
            .method<bool() const>("isNull", &_::isNull)
            .method<bool() const>("isValid", &_::isValid)
            .method<::phantom::serialization::Value &(StringView, Separator)>("addValue", &_::addValue)({"name","s"})
            .method<const ::phantom::serialization::Value &(StringView, Separator) const>("getValue", &_::getValue)({"name","s"})
            .method<::phantom::serialization::Value &(StringView, Separator)>("getValue", &_::getValue)({"name","s"})
            .method<::phantom::serialization::Value &(StringView)>("getValue", &_::getValue)({"name"})
            .method<const ::phantom::serialization::Value &(StringView) const>("getValue", &_::getValue)({"name"})
            .method<const ::phantom::serialization::Value &(size_t) const>("getValue", &_::getValue)({"index"})
            .method<void(StringView, const Value&)>("addValue", &_::addValue)({"a_strName","val"})
            .method<void(StringView, Value&&)>("addValue", &_::addValue)({"a_strName","val"})
            ;
        }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("Value")
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
