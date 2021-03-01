// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

/* ****************** Includes ******************* */
#include "Serializer.h"
#include "Value.h"

#include <phantom/lang/TypeOf.h>
/* *********************************************** */

namespace phantom
{
namespace serialization
{
class PHANTOM_EXPORT_PHANTOM_SERIALIZATION ValueSerializer : public Serializer
{
public:
    ValueSerializer(Value& a_Out, Mode a_eMode = Mode::Write);
    ValueSerializer(const Value& a_In);
    ~ValueSerializer();

    virtual SerializerStatus beginArray() override;
    virtual void             endArray() override;

    virtual SerializerStatus beginArrayElement() override;
    virtual void             endArrayElement() override;

    virtual SerializerStatus beginStructure() override;
    virtual void             endStructure() override;

    virtual SerializerStatus beginMember(StringView name) override;
    virtual void             endMember() override;

    using Serializer::read;
    virtual SerializerStatus read(bool& v) override { return _read(v); }
    virtual SerializerStatus read(char& v) override { return _read(v); }
    virtual SerializerStatus read(uint8& v) override { return _read(v); }
    virtual SerializerStatus read(int8& v) override { return _read(v); }
    virtual SerializerStatus read(int16& v) override { return _read(v); }
    virtual SerializerStatus read(uint16& v) override { return _read(v); }
    virtual SerializerStatus read(int32& v) override { return _read(v); }
    virtual SerializerStatus read(uint32& v) override { return _read(v); }
    virtual SerializerStatus read(int64& v) override { return _read(v); }
    virtual SerializerStatus read(uint64& v) override { return _read(v); }
    virtual SerializerStatus read(float& v) override { return _read(v); }
    virtual SerializerStatus read(double& v) override { return _read(v); }
    virtual SerializerStatus read(longdouble& v) override { return _read(v); }
    virtual SerializerStatus read(StringView& v) override { return _read(v); }
    virtual SerializerStatus read(hex64& v) override { return _read(v); }
    virtual SerializerStatus read(void*& a_pPtr, lang::Type* a_pPointeeType) override;
    virtual SerializerStatus read(void* a_pValue, lang::Enum* a_pEnumType) override;
    virtual SerializerStatus read(uint8* a_pBytes, size_t a_Count) override;

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus read(wchar_t& v) override { return _read(v); });
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus read(char16_t& v) override { return _read(v); });
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus read(char32_t& v) override { return _read(v); });

    using Serializer::write;
    virtual SerializerStatus write(const bool& v) override { return _write(v); }
    virtual SerializerStatus write(const char& v) override { return _write(v); }
    virtual SerializerStatus write(const uint8& v) override { return _write(v); }
    virtual SerializerStatus write(const int8& v) override { return _write(v); }
    virtual SerializerStatus write(const int16& v) override { return _write(v); }
    virtual SerializerStatus write(const uint16& v) override { return _write(v); }
    virtual SerializerStatus write(const int32& v) override { return _write(v); }
    virtual SerializerStatus write(const uint32& v) override { return _write(v); }
    virtual SerializerStatus write(const int64& v) override { return _write(v); }
    virtual SerializerStatus write(const uint64& v) override { return _write(v); }
    virtual SerializerStatus write(const float& v) override { return _write(v); }
    virtual SerializerStatus write(const double& v) override { return _write(v); }
    virtual SerializerStatus write(const longdouble& v) override { return _write(v); }
    virtual SerializerStatus write(StringView str) override;
    virtual SerializerStatus write(const hex64& v) override { return _write(v); }
    virtual SerializerStatus write(void* const& v, lang::Type* a_pPointeeType) override;
    virtual SerializerStatus write(void const* v, lang::Enum* a_pEnumType) override;
    virtual SerializerStatus write(uint8 const* a_pBytes, size_t a_Count) override;

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus write(const wchar_t& v) { return _write(v); });
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus write(const char16_t& v) { return _write(v); });
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus write(const char32_t& v) { return _write(v); });

private:
    template<class T>
    PHANTOM_FORCEINLINE SerializerStatus _write(const T& val)
    {
        PHANTOM_ASSERT(!m_ValueStack.back()->isDefined());
        *m_ValueStack.back() = val;
        return SerializerStatus::OK;
    }
    template<class T>
    PHANTOM_FORCEINLINE SerializerStatus _read(T& val)
    {
        if (m_ValueStack.back()->as(val))
            return SerializerStatus::OK;
        setLastError(SerializerError::NoValidConversion);
        return SerializerStatus::Error;
    }

private:
    SmallVector<Value*, 10> m_ValueStack;
    SmallVector<String, 10> m_MemberStack;
    SmallVector<size_t, 10> m_ArrayIndexStack;
};

template<class T>
inline Value::Value(const T& val)
{
    serialization::ValueSerializer serializer(*this);
    PHANTOM_TYPEOF(T)->serialize(serializer, &val);
}

template<class T>
inline Value& Value::operator=(T const& val)
{
    PHANTOM_ASSERT(!isNull());
    _release();
    serialization::ValueSerializer serializer(*this);
    PHANTOM_VERIFY(PHANTOM_TYPEOF(T)->serialize(serializer, &val) == serialization::SerializerStatus::OK);
    return *this;
}

template<class T>
inline bool Value::as(T& val) const
{
    PHANTOM_ASSERT(!isNull());
    serialization::ValueSerializer  serializer(*this);
    serialization::SerializerStatus status = PHANTOM_TYPEOF(T)->deserialize(serializer, &val);
    return status == serialization::SerializerStatus::OK;
}

} // namespace serialization
} // namespace phantom
