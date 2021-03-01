// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#include "ValueSerializer.h"

#include <phantom/lang/Constant.h>
#include <phantom/lang/Enum.h>

namespace phantom
{
namespace serialization
{
ValueSerializer::ValueSerializer(Value& a_Out, Mode a_eMode /*=Mode::Write*/) : Serializer(a_eMode)
{
    m_ValueStack.push_back(&a_Out);
}

ValueSerializer::ValueSerializer(const Value& a_In) : Serializer(Mode::Read)
{
    m_ValueStack.push_back((Value*)&a_In);
}

ValueSerializer::~ValueSerializer()
{
    m_ValueStack.pop_back();
    PHANTOM_ASSERT(m_ValueStack.empty());
}

SerializerStatus ValueSerializer::beginArray()
{
    m_ArrayIndexStack.push_back(0);
    if (isWriting())
    {
        PHANTOM_ASSERT(!m_ValueStack.back()->isDefined());
        m_ValueStack.back()->setArray();
    }
    else
    {
        if (m_ValueStack.back()->getType() != Value::e_array)
        {
            setLastError(SerializerError::ExpectedArray);
            return SerializerStatus::Error;
        }
    }
    return SerializerStatus::OK;
}

void ValueSerializer::endArray()
{
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_array);
    PHANTOM_ASSERT(m_ValueStack.back()->asArray().size() == m_ArrayIndexStack.back());
    m_ArrayIndexStack.pop_back();
}

SerializerStatus ValueSerializer::beginArrayElement()
{
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_array);
    if (isWriting())
    {
        m_ValueStack.push_back(&m_ValueStack.back()->addValue());
    }
    else
    {
        if (m_ValueStack.back()->asArray().size() == m_ArrayIndexStack.back())
        {
            m_ValueStack.push_back((Value*)&Value::null);
            return SerializerStatus::OptionalEntryNotFound;
        }
        else
            m_ValueStack.push_back((Value*)&m_ValueStack.back()->getValue(m_ArrayIndexStack.back()));
    }
    return SerializerStatus::OK;
}

void ValueSerializer::endArrayElement()
{
    m_ValueStack.pop_back();
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_array);
    if (m_ArrayIndexStack.back() < m_ValueStack.back()->asArray().size())
    {
        ++m_ArrayIndexStack.back();
    }
}

SerializerStatus ValueSerializer::beginStructure()
{
    if (isWriting())
    {
        PHANTOM_ASSERT(!m_ValueStack.back()->isDefined());
        m_ValueStack.back()->setStruct();
    }
    else
    {
        if (m_ValueStack.back()->getType() != Value::e_struct)
        {
            setLastError(SerializerError::ExpectedStruct);
            return SerializerStatus::Error;
        }
    }
    return SerializerStatus::OK;
}

void ValueSerializer::endStructure()
{
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_struct);
}

SerializerStatus ValueSerializer::beginMember(StringView name)
{
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_struct);
    if (isWriting())
    {
        m_ValueStack.push_back(&m_ValueStack.back()->addValue(name));
    }
    else
    {
        m_ValueStack.push_back((Value*)&m_ValueStack.back()->getValue(name));
        if (m_ValueStack.back()->isNull())
        {
            return SerializerStatus::OptionalEntryNotFound;
        }
    }
    return SerializerStatus::OK;
}

void ValueSerializer::endMember()
{
    m_ValueStack.pop_back();
    PHANTOM_ASSERT(m_ValueStack.back()->getType() == Value::e_struct);
}

SerializerStatus ValueSerializer::write(void* const& v, lang::Type*)
{
    return write((size_t)v);
}

SerializerStatus ValueSerializer::write(void const* a_pValue, lang::Enum* a_pEnumType)
{
    if (lang::Constant* pConstant = a_pEnumType->getFirstConstant(a_pValue))
    {
        auto name = pConstant->getName();
        write(name);
        return SerializerStatus::OK;
    }
    setLastError(SerializerError::UnknownEnumValue);
    return SerializerStatus::Error;
}

SerializerStatus ValueSerializer::write(StringView str)
{
    PHANTOM_ASSERT(!m_ValueStack.back()->isDefined());
    *m_ValueStack.back() = Value(str);
    return SerializerStatus::OK;
}

SerializerStatus ValueSerializer::write(uint8 const* a_pBytes, size_t a_Count)
{
    m_ValueStack.back()->setArray(a_Count);
    auto& arr = m_ValueStack.back()->asArray();
    for (size_t i = 0; i < a_Count; ++i)
        arr[i] = *a_pBytes++;
    return SerializerStatus::OK;
}

SerializerStatus ValueSerializer::read(void*& a_pPtr, lang::Type*)
{
    return read((size_t&)a_pPtr);
}

SerializerStatus ValueSerializer::read(void* a_pValue, lang::Enum* a_pEnumType)
{
    StringView str;
    read(str);
    if (lang::Constant* pCons = a_pEnumType->getConstant(str))
    {
        pCons->getValue(a_pValue);
        return SerializerStatus::OK;
    }
    setLastError(SerializerError::UnknownEnumValue);
    return SerializerStatus::Error;
}

SerializerStatus ValueSerializer::read(uint8* a_pBytes, size_t a_Count)
{
    if (m_ValueStack.back()->isArray())
    {
        auto const& arr = m_ValueStack.back()->asArray();
        for (size_t i = 0; i < std::min(a_Count, arr.size()); ++i)
            arr[i].as(*a_pBytes++);
        return SerializerStatus::OK;
    }
    setLastError(SerializerError::ExpectedArray);
    return SerializerStatus::Error;
}

} // namespace serialization

} // namespace phantom
