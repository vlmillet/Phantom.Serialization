#pragma once

// haunt {

// clang-format off

#include "SerializerVisitor.h"

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
#include <phantom/method>
#include <phantom/constructor>
#include <phantom/field>
#include <phantom/typedef>
#include <phantom/alias_template>

#include <phantom/template-only-push>

#include <phantom/lang/RecursiveInstanceVisitorT.hxx>
#include <phantom/utils/Functor.hxx>

#include <phantom/template-only-pop>

namespace phantom {
namespace serialization {
namespace _SerializerVisitorT {
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("SerializerVisitor")

        PHANTOM_STRUCT_T((class), (T), DerivedSelector)
        {
            using type = typedef_<PHANTOM_TYPENAME _::type>;
            this_()
            .PHANTOM_T typedef_<type>("type")
            ;
        }
        PHANTOM_STRUCT_S((void), DerivedSelector)
        {
            using type = typedef_<_::type>;
            this_()
            .typedef_<type>("type")
            ;
        }
    PHANTOM_END("SerializerVisitor")
PHANTOM_END("phantom.serialization")
}
PHANTOM_PACKAGE("phantom.serialization")
    PHANTOM_SOURCE("SerializerVisitor")

        PHANTOM_CLASS_T((class, class), (Derived, SerializerT), SerializerVisitorT)
        {
            using Array = typedef_<PHANTOM_TYPENAME _::Array>;
            using BaseClass = typedef_<PHANTOM_TYPENAME _::BaseClass>;
            using Class = typedef_<PHANTOM_TYPENAME _::Class>;
            using ClassType = typedef_<PHANTOM_TYPENAME _::ClassType>;
            using ContainerClass = typedef_<PHANTOM_TYPENAME _::ContainerClass>;
            using Default = typedef_<PHANTOM_TYPENAME _::Default>;
            using EntryPoint = typedef_<PHANTOM_TYPENAME _::EntryPoint>;
            using Enum = typedef_<PHANTOM_TYPENAME _::Enum>;
            using Field = typedef_<PHANTOM_TYPENAME _::Field>;
            using MapClass = typedef_<PHANTOM_TYPENAME _::MapClass>;
            using Pointer = typedef_<PHANTOM_TYPENAME _::Pointer>;
            using Property = typedef_<PHANTOM_TYPENAME _::Property>;
            using SerializerType = typedef_<PHANTOM_TYPENAME _::SerializerType>;
            using SetClass = typedef_<PHANTOM_TYPENAME _::SetClass>;
            using StringClass = typedef_<PHANTOM_TYPENAME _::StringClass>;
            using Template = typedef_<PHANTOM_TYPENAME _::Template>;
            using Type = typedef_<PHANTOM_TYPENAME _::Type>;
            using ValueMember = typedef_<PHANTOM_TYPENAME _::ValueMember>;
            using VectorClass = typedef_<PHANTOM_TYPENAME _::VectorClass>;
            this_()
            .PHANTOM_T inherits<_SerializerVisitorT::DerivedSelector<Derived>::type>()
        .public_()
            .PHANTOM_T typedef_<Default>("Default")
            .PHANTOM_T typedef_<BaseClass>("BaseClass")
            .PHANTOM_T typedef_<StringClass>("StringClass")
            .PHANTOM_T typedef_<VectorClass>("VectorClass")
            .PHANTOM_T typedef_<MapClass>("MapClass")
            .PHANTOM_T typedef_<SetClass>("SetClass")
            .PHANTOM_T typedef_<ContainerClass>("ContainerClass")
            // InstanceT : nested alias templates not suppported
            // MemberAccessT : nested alias templates not suppported
            .PHANTOM_T typedef_<Type>("Type")
            .PHANTOM_T typedef_<Class>("Class")
            .PHANTOM_T typedef_<ClassType>("ClassType")
            .PHANTOM_T typedef_<Array>("Array")
            .PHANTOM_T typedef_<Enum>("Enum")
            .PHANTOM_T typedef_<Field>("Field")
            .PHANTOM_T typedef_<Property>("Property")
            .PHANTOM_T typedef_<ValueMember>("ValueMember")
            .PHANTOM_T typedef_<Template>("Template")
            .PHANTOM_T typedef_<Pointer>("Pointer")
            .PHANTOM_T typedef_<SerializerType>("SerializerType")
            .PHANTOM_T typedef_<EntryPoint>("EntryPoint")
            .PHANTOM_T constructor<void(SerializerType&, uint32, bool)>()({"a_Serializer","a_MemberFilterMask","a_bLogEnabled"})["false"]
            .PHANTOM_T method<SerializerStatus(void*, ::phantom::lang::Type *)>("visit", &_::visit)({"a_pInstance","a_pType"})
            .PHANTOM_T method<SerializerStatus(const void*, ::phantom::lang::Type *)>("visit", &_::visit)({"a_pInstance","a_pType"})
            .PHANTOM_T method<SerializerType&()>("getSerializer", &_::getSerializer)
            .PHANTOM_T method<SerializerType const&() const>("getSerializer", &_::getSerializer)
            .PHANTOM_T method<uint32() const>("getMemberFilterMask", &_::getMemberFilterMask)
        
        .protected_()
            .PHANTOM_T method<bool(InstanceT<Type>)>("visitContainer", &_::visitContainer)({""})
            .PHANTOM_T method<bool(InstanceT<Type>)>("endContainer", &_::endContainer)({""})
            .PHANTOM_T method<bool(InstanceT<BaseClass>)>("traverseBaseClass", &_::traverseBaseClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<ClassType>)>("visitClassType", &_::visitClassType)({""})
            .PHANTOM_T method<bool(InstanceT<ClassType>)>("endClassType", &_::endClassType)({""})
            .PHANTOM_T method<bool(InstanceT<Type>, size_t)>("traverseContainerElement", &_::traverseContainerElement)({"a_Input","a_uiIndex"})
            .PHANTOM_T method<void(InstanceT<ContainerClass>)>("clear", &_::clear)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<VectorClass>)>("traverseVectorClass", &_::traverseVectorClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<SetClass>)>("readSetContainer", &_::readSetContainer)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<MapClass>)>("readMapContainer", &_::readMapContainer)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<MapClass>)>("traverseMapClass", &_::traverseMapClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<SetClass>)>("traverseSetClass", &_::traverseSetClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<Array>)>("traverseArray", &_::traverseArray)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<Type>, size_t)>("visitContainerElement", &_::visitContainerElement)({"",""})
            .PHANTOM_T method<bool(InstanceT<Type>, size_t)>("endContainerElement", &_::endContainerElement)({"",""})
            .PHANTOM_T method<bool(InstanceT<Class>)>("traverseClass", &_::traverseClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<ClassType>)>("traverseValueMembers", &_::traverseValueMembers)({"a_Input"})
            .PHANTOM_T method<bool(MemberAccessT<Field>)>("traverseField", &_::traverseField)({"a_Input"})
            .PHANTOM_T method<bool(MemberAccessT<ValueMember>) const>("shouldWriteValueMember", &_::shouldWriteValueMember)({""})
            .PHANTOM_T method<bool(MemberAccessT<ValueMember>) const>("shouldReadValueMember", &_::shouldReadValueMember)({""})
            .PHANTOM_T method<bool(SerializerStatus)>("checkStatus", &_::checkStatus)({"a_Status"})
            .PHANTOM_T method<bool(InstanceT<StringClass>)>("traverseStringClass", &_::traverseStringClass)({"a_Input"})
            .PHANTOM_T method<bool(wchar_t*)>("traverseFundamental", &_::traverseFundamental)({"a_Input"})
            .PHANTOM_T method<bool(char16_t*)>("traverseFundamental", &_::traverseFundamental)({"a_Input"})
            .PHANTOM_T method<bool(char32_t*)>("traverseFundamental", &_::traverseFundamental)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<Pointer>)>("traversePointer", &_::traversePointer)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<Enum>)>("traverseEnum", &_::traverseEnum)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<VectorClass>)>("walkUpVisitFromVectorClass", &_::walkUpVisitFromVectorClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<VectorClass>)>("walkUpEndFromVectorClass", &_::walkUpEndFromVectorClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<MapClass>)>("walkUpVisitFromMapClass", &_::walkUpVisitFromMapClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<MapClass>)>("walkUpEndFromMapClass", &_::walkUpEndFromMapClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<SetClass>)>("walkUpVisitFromSetClass", &_::walkUpVisitFromSetClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<SetClass>)>("walkUpEndFromSetClass", &_::walkUpEndFromSetClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<StringClass>)>("walkUpVisitFromStringClass", &_::walkUpVisitFromStringClass)({"a_Input"})
            .PHANTOM_T method<bool(InstanceT<StringClass>)>("walkUpEndFromStringClass", &_::walkUpEndFromStringClass)({"a_Input"})
            /// invalid declaration, some symbols have not been parsed correctly probably due to missing include path or missing #include in the .h
            // .PHANTOM_T field("m_MemberFilterMask", &_::m_MemberFilterMask)
            ;
        }
        #if PHANTOM_NOT_TEMPLATE
        PHANTOM_CLASS(SerializerVisitor)
        {
            this_()
        .public_()
            .constructor<void(Serializer&, uint32)>()({"a_Serializer","a_MemberFilterMask"})
            ;
        }
        #endif // PHANTOM_NOT_TEMPLATE
    PHANTOM_END("SerializerVisitor")
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
