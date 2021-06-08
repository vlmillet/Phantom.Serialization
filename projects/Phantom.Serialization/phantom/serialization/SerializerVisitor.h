// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

#include "Serializer.h"
#include "SerializerConstants.h"

#include <phantom/lang/Namespace.h>
#include <phantom/lang/RecursiveInstanceVisitorT.h>
#include <phantom/lang/TemplateSpecialization.h>
#include <phantom/utils/SmallVector.h>
#include <phantom/utils/String.h>

namespace phantom
{
namespace serialization
{
class Serializer;

template<class Derived = void, class SerializerType = Serializer>
class SerializerVisitorT;

namespace _SerializerVisitorT
{
template<class T>
struct DerivedSelector
{
    using type = lang::RecursiveInstanceVisitorT<T>;
};

template<>
struct DerivedSelector<void>
{
    using type = lang::RecursiveInstanceVisitorT<SerializerVisitorT<void>>;
};
} // namespace _SerializerVisitorT

template<class Derived, class SerializerT>
class SerializerVisitorT : public _SerializerVisitorT::DerivedSelector<Derived>::type
{
#if PHANTOM_COMPILER == PHANTOM_COMPILER_VISUAL_STUDIO &&                                                              \
PHANTOM_COMPILER_VERSION >= PHANTOM_COMPILER_VISUAL_STUDIO_VERSION_2017
    friend class _SerializerVisitorT::DerivedSelector<Derived>::type;
#else
    friend _SerializerVisitorT::DerivedSelector<Derived>::type;
#endif

public:
    using Default = typename _SerializerVisitorT::DerivedSelector<Derived>::type;

    using BaseClass = phantom::lang::BaseClass;
    using StringClass = phantom::lang::StringClass;
    using VectorClass = phantom::lang::VectorClass;
    using MapClass = phantom::lang::MapClass;
    using SetClass = phantom::lang::SetClass;
    using ContainerClass = phantom::lang::ContainerClass;
    template<class T>
    using InstanceT = phantom::lang::InstanceT<T>;
    template<class T>
    using MemberAccessT = phantom::lang::MemberAccessT<T>;
    using Type = lang::Type;
    using Class = lang::Class;
    using ClassType = lang::ClassType;
    using Array = lang::Array;
    using Enum = lang::Enum;
    using Field = lang::Field;
    using Property = lang::Property;
    using ValueMember = lang::ValueMember;
    using Template = lang::Template;
    using Pointer = lang::Pointer;

    using SerializerType = SerializerT;
    using EntryPoint = Functor<SerializerStatus(SerializerType&, uint32)>;

    static_assert(std::is_base_of<Serializer, SerializerType>::value,
                  "SerializerT must derive from phantom::reflection::Serializer");

    SerializerVisitorT(SerializerType& a_Serializer, uint32 a_MemberFilterMask, bool a_bLogEnabled = false)
        : m_Serializer((Serializer&)(a_Serializer)),
          m_MemberFilterMask(a_MemberFilterMask),
          m_bLogEnabled(a_bLogEnabled)
    {
    }
    ~SerializerVisitorT() {}

    SerializerStatus visit(void* a_pInstance, lang::Type* a_pType)
    {
        m_Status = SerializerStatus::OK;
        Default::visit(a_pInstance, a_pType);
        if (m_Serializer.getLastError() != SerializerError::None)
            return SerializerStatus::Error;
        return m_Status;
    }

    SerializerStatus visit(const void* a_pInstance, lang::Type* a_pType)
    {
        PHANTOM_ASSERT(m_Serializer.isWriting());
        m_Status = SerializerStatus::OK;
        Default::visit((void*)a_pInstance,
                       a_pType); // force non const to work transparently with read/write
        if (m_Serializer.getLastError() != SerializerError::None)
            return SerializerStatus::Error;
        return m_Status;
    }

    SerializerType&       getSerializer() { return static_cast<SerializerType&>(m_Serializer); }
    SerializerType const& getSerializer() const { return static_cast<SerializerType const&>(m_Serializer); }

    uint32 getMemberFilterMask() const { return m_MemberFilterMask; }

protected:
    bool visitContainer(InstanceT<Type>) { return checkStatus(m_Serializer.beginArray()); }

    bool endContainer(InstanceT<Type>)
    {
        m_Serializer.endArray();
        return true;
    }

    bool traverseBaseClass(InstanceT<BaseClass> a_Input)
    {
        if (auto member = m_Serializer.scopedMember(a_Input.getBaseClass().baseClass->getName()))
        {
            return Default::traverseBaseClass(a_Input);
        }
        else
        {
            return member.getStatus() == SerializerStatus::OptionalEntryNotFound;
        }
    }

    bool visitClassType(InstanceT<ClassType>) { return checkStatus(m_Serializer.beginStructure()); }

    bool endClassType(InstanceT<ClassType>)
    {
        m_Serializer.endStructure();
        return true;
    }

    bool traverseContainerElement(InstanceT<Type> a_Input, size_t a_uiIndex)
    {
        if (m_Serializer.isReading()) // when reading, we don't want to this->traverse container
                                      // elements, but only add them
            return true;
        return Default::traverseContainerElement(a_Input, a_uiIndex);
    }

    void clear(InstanceT<ContainerClass> a_Input) { a_Input.getMeta()->clear(a_Input.getAddress()); }

    bool traverseVectorClass(InstanceT<VectorClass> a_Input)
    {
        if (m_Serializer.isWriting())
            return Default::traverseVectorClass(a_Input);

        if (auto arr = m_Serializer.scopedArray())
        {
            clear(a_Input);
            auto  pMeta = a_Input.getMeta();
            auto  pAddress = a_Input.getAddress();
            Type* pValueType = pMeta->getValueType();
            void* pVal = PHANTOM_ALLOCA(pValueType->getSize());
            while (true)
            {
                if (auto elem = m_Serializer.scopedArrayElement())
                {
                    if (elem.getStatus() == SerializerStatus::OptionalEntryNotFound)
                        return true;

                    auto guard = pValueType->scopedConstruct(pVal);

                    auto newElement = InstanceT<Type>(pValueType, pVal);
                    if (!this->traverse(newElement))
                        return false;
                    pMeta->push_back(pAddress, pVal);
                }
            }
        }
        return false;
    }

    bool readSetContainer(InstanceT<SetClass> a_Input)
    {
        if (auto arr = m_Serializer.scopedArray())
        {
            auto  pMeta = a_Input.getMeta();
            auto  pAddress = a_Input.getAddress();
            Type* pValueType = pMeta->getValueType();
            void* pVal = PHANTOM_ALLOCA(pValueType->getSize()); // new pair
            while (true)
            {
                if (auto elem = m_Serializer.scopedArrayElement())
                {
                    if (elem.getStatus() == SerializerStatus::OptionalEntryNotFound)
                        return true;

                    auto guard = pValueType->scopedConstruct(pVal);

                    auto newElement = InstanceT<Type>(pValueType, pVal);
                    if (!this->traverse(newElement))
                        return false;
                    pMeta->insert(pAddress, pVal);
                }
            }
        }
        return false;
    }

    bool readMapContainer(InstanceT<MapClass> a_Input)
    {
        if (auto arr = m_Serializer.scopedArray())
        {
            auto  pMeta = a_Input.getMeta();
            auto  pAddress = a_Input.getAddress();
            Type* pValueType = pMeta->getValueType();
            void* pVal = PHANTOM_ALLOCA(pValueType->getSize()); // new pair
            while (true)
            {
                if (auto elem = m_Serializer.scopedArrayElement())
                {
                    if (elem.getStatus() == SerializerStatus::OptionalEntryNotFound)
                        return true;

                    auto guard = pValueType->scopedConstruct(pVal);

                    auto newElement = InstanceT<Type>(pValueType, pVal);
                    if (!this->traverse(newElement))
                        return false;
                    pMeta->assign(pAddress, pVal);
                }
            }
        }
        return false;
    }

    bool traverseMapClass(InstanceT<MapClass> a_Input)
    {
        if (m_Serializer.isWriting())
            return Default::traverseMapClass(a_Input);
        return readMapContainer(a_Input);
    }

    bool traverseSetClass(InstanceT<SetClass> a_Input)
    {
        if (m_Serializer.isWriting())
            return Default::traverseSetClass(a_Input);
        return readSetContainer(a_Input);
    }

    bool traverseArray(InstanceT<Array> a_Input)
    {
        if (m_Serializer.isWriting())
            return Default::traverseArray(a_Input);

        if (auto arr = m_Serializer.scopedArray())
        {
            auto   pMeta = a_Input.getMeta();
            auto   pAddress = a_Input.getAddress();
            Type*  pValueType = pMeta->getItemType();
            void*  pVal = PHANTOM_ALLOCA(pValueType->getSize());
            size_t i = 0;
            while (true)
            {
                if (auto elem = m_Serializer.scopedArrayElement())
                {
                    if (elem.getStatus() == SerializerStatus::OptionalEntryNotFound)
                        return true;
                    auto guard = pValueType->scopedConstruct(pVal);
                    auto newElement = InstanceT<Type>(pValueType, pVal);
                    if (!this->traverse(newElement))
                        return false;
                    pMeta->setItemValue(pAddress, i, pVal);
                    ++i;
                }
            }
        }
        return false;
    }

    bool visitContainerElement(InstanceT<Type>, size_t)
    {
        PHANTOM_ASSERT(m_Serializer.isWriting());
        if (m_Serializer.beginArrayElement() == SerializerStatus::Error)
        {
            m_Serializer.endArrayElement();
            return false;
        }
        return true;
    }

    bool endContainerElement(InstanceT<Type>, size_t)
    {
        m_Serializer.endArrayElement();
        return true;
    }

    bool traverseClass(InstanceT<Class> a_Input)
    {
        static Template* PairTemplate =
        phantom::lang::Namespace::Global()->getNamespace("phantom")->getTemplate("Pair");
        PHANTOM_ASSERT(PairTemplate);
        if (a_Input.getMeta()->getTemplate() == PairTemplate)
        {
            Class* pairClass = a_Input.getMeta();
            if (auto arr = m_Serializer.scopedArray())
            {
                for (size_t i = 0; i < 2; ++i)
                {
                    Type* type = static_cast<Type*>(a_Input.getMeta()->getTemplateSpecialization()->getArgument(i));
                    void* instance = PHANTOM_ALLOCA(type->getSize());
                    auto  guard = type->scopedConstruct(instance);
                    if (m_Serializer.isWriting())
                        pairClass->getField(i)->getValue(a_Input.getAddress(), instance);
                    if (auto elem = m_Serializer.scopedArrayElement())
                    {
                        if (!this->traverse(InstanceT<Type>(type, instance)))
                            return false;
                        if (m_Serializer.isReading())
                            pairClass->getField(i)->setValue(a_Input.getAddress(), instance);
                    }
                    else
                        return false;
                }
                if (auto elem = m_Serializer.scopedArrayElement())
                {
                    return elem.getStatus() ==
                    SerializerStatus::OptionalEntryNotFound; // ensure we have only two elements (a pair no
                                                             // ?)
                }
                return false;
            }
            return false;
        }
        else
            return Default::traverseClass(a_Input);
    }

    bool traverseValueMembers(InstanceT<ClassType> a_Input)
    {
        for (ValueMember* pVM : a_Input.getMeta()->getValueMembers())
        {
            if (!(pVM->isTransient()) && (pVM->getFilterMask() & m_MemberFilterMask) == pVM->getFilterMask())
            {
                // allows to fork serializer into some user code
                if (pVM->getValueType()->isSame(PHANTOM_TYPEOF(EntryPoint)))
                {
                    EntryPoint entryPoint;
                    pVM->getValue(a_Input.getAddress(), &entryPoint);
                    if (entryPoint)
                        entryPoint(getSerializer(), m_MemberFilterMask);
                }
                else if (pVM->isWrittable() && pVM->isReadable())
                {
                    if (auto member = m_Serializer.scopedMember(pVM->getName()))
                    {
                        if (!this->traverse(MemberAccessT<ValueMember>(a_Input, pVM)))
                            return false;
                    }
                    else
                    {
                        if (member.getStatus() == SerializerStatus::Error)
                            return false;
                    }
                }
            }
        }
        return true;
    }
    bool traverseField(MemberAccessT<Field> a_Input)
    {
        if (a_Input.getMemberMeta()->isTransient() ||
            (a_Input.getMemberMeta()->getFilterMask() & m_MemberFilterMask) != a_Input.getMemberMeta()->getFilterMask())
        {
            return true;
        }
        return Default::traverseField(a_Input);
    }

    bool shouldWriteValueMember(MemberAccessT<ValueMember>) const { return m_Serializer.isReading(); }
    bool shouldReadValueMember(MemberAccessT<ValueMember>) const { return true; }

    bool checkStatus(SerializerStatus a_Status) { return (m_Status = a_Status) != SerializerStatus::Error; }

    bool traverseStringClass(InstanceT<StringClass> a_Input)
    {
        if (m_Serializer.isWriting())
        {
            char*  pMemory = (char*)a_Input.getMeta()->c_str(a_Input.getAddress());
            size_t count = a_Input.getMeta()->size(a_Input.getAddress());
            return checkStatus(m_Serializer.write(pMemory, count));
        }
        else
        {
            StringView str;
            if (!checkStatus(m_Serializer.read(str)))
                return false;
            a_Input.getMeta()->assign(a_Input.getAddress(), str.data(), str.size());
            return true;
        }
    }

    template<class T>
    bool traverseFundamental(T* a_Input)
    {
        return checkStatus(m_Serializer.serialize(*a_Input));
    }

#if PHANTOM_HAS_BUILT_IN_WCHAR_T
    bool traverseFundamental(wchar_t* a_Input) { return traverseFundamental((short*)a_Input); }
#endif
#if PHANTOM_HAS_BUILT_IN_CHAR16_T
    bool traverseFundamental(char16_t* a_Input) { return traverseFundamental((short*)a_Input); }
#endif
#if PHANTOM_HAS_BUILT_IN_CHAR32_T
    bool traverseFundamental(char32_t* a_Input) { return traverseFundamental((int*)a_Input); }
#endif
    bool traversePointer(InstanceT<Pointer> a_Input)
    {
        void**           addr = (void**)a_Input.getAddress();
        SerializerStatus status;
        if (m_Serializer.isReading())
            status = m_Serializer.read(*addr, a_Input.getMeta()->getPointeeType());
        else
            status = m_Serializer.write(*addr, a_Input.getMeta()->getPointeeType());
        return checkStatus(status);
    }

    bool traverseEnum(InstanceT<Enum> a_Input)
    {
        if (m_Serializer.isReading())
        {
            StringView name;
            auto       st = m_Serializer.read(name);
            if (!checkStatus(st))
                return false;
            auto pConst = a_Input.getMeta()->getConstant(name);
            if (pConst == nullptr)
            {
                PHANTOM_LOG(Error, "No enum value '%.*s' found in enum '%.*s', we fallback to the first enum value",
                            PHANTOM_STRING_AS_PRINTF_ARG(name),
                            PHANTOM_STRING_AS_PRINTF_ARG(a_Input.getMeta()->getName()));
                pConst = a_Input.getMeta()->getConstant(0);
            }
            pConst->getValue(a_Input.getAddress());
            return true;
        }
        else
        {
            auto pConst = a_Input.getMeta()->getFirstConstant(a_Input.getAddress());
            if (pConst == nullptr)
            {
                PHANTOM_LOG(Error,
                            "Enum value written in memory '%d' was not recognized as a known value "
                            "in enum '%.*s', we fallback to the first enum value",
                            *(int*)a_Input.getAddress(), PHANTOM_STRING_AS_PRINTF_ARG(a_Input.getMeta()->getName()));
                pConst = a_Input.getMeta()->getConstant(0);
            }
            String str = String(StringView());
            return checkStatus(m_Serializer.write(pConst->getName()));
        }
    }
    bool walkUpVisitFromVectorClass(InstanceT<VectorClass> a_Input) { return this->this_()->visitVectorClass(a_Input); }
    bool walkUpEndFromVectorClass(InstanceT<VectorClass> a_Input) { return this->this_()->endVectorClass(a_Input); }
    bool walkUpVisitFromMapClass(InstanceT<MapClass> a_Input) { return this->this_()->visitMapClass(a_Input); }
    bool walkUpEndFromMapClass(InstanceT<MapClass> a_Input) { return this->this_()->endMapClass(a_Input); }
    bool walkUpVisitFromSetClass(InstanceT<SetClass> a_Input) { return this->this_()->visitSetClass(a_Input); }
    bool walkUpEndFromSetClass(InstanceT<SetClass> a_Input) { return this->this_()->endSetClass(a_Input); }
    bool walkUpVisitFromStringClass(InstanceT<StringClass> a_Input) { return this->this_()->visitStringClass(a_Input); }
    bool walkUpEndFromStringClass(InstanceT<StringClass> a_Input) { return this->this_()->endStringClass(a_Input); }

private:
    Serializer&      m_Serializer;
    SerializerStatus m_Status = SerializerStatus::OK;
    uint32           m_MemberFilterMask = = ~0u;
    bool             m_bLogEnabled = false;
};

class PHANTOM_EXPORT_PHANTOM_SERIALIZATION SerializerVisitor : public SerializerVisitorT<SerializerVisitor>
{
public:
    SerializerVisitor(Serializer& a_Serializer, uint32 a_MemberFilterMask)
        : SerializerVisitorT<SerializerVisitor>(a_Serializer, a_MemberFilterMask)
    {
    }
};
} // namespace serialization
} // namespace phantom
