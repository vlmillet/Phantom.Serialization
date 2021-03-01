// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

#include "Serializer.h"
#include "Value.h"

namespace phantom
{
namespace serialization
{
class PHANTOM_EXPORT_PHANTOM_SERIALIZATION BinarySerializer : public Serializer
{
public:
    BinarySerializer();
    BinarySerializer(const byte* a_pBuffer, size_t a_uiBufferSize = ~size_t(0));
    BinarySerializer(const BufferData& a_Buffer);
    ~BinarySerializer();

    const byte* getBuffer() const { return m_pBuffer; }
    size_t      getSize() const { return m_pCurrentAddress - m_pBuffer; }

    void  takeWriteBuffer(BufferData& a_Buffer);
    byte* takeWriteBuffer(size_t& a_uiSize);

    virtual SerializerStatus beginArray() override;

    virtual void endArray() override;

    virtual SerializerStatus beginArrayElement() override;

    virtual void endArrayElement() override;

    virtual SerializerStatus beginStructure() override;
    virtual void             endStructure() override;

    virtual SerializerStatus beginMember(StringView name) override;
    virtual void             endMember() override;

    using Serializer::read;
    virtual SerializerStatus read(bool& v) override;
    virtual SerializerStatus read(char& v) override;
    virtual SerializerStatus read(uint8& v) override;
    virtual SerializerStatus read(int8& v) override;
    virtual SerializerStatus read(int16& v) override;
    virtual SerializerStatus read(uint16& v) override;
    virtual SerializerStatus read(int32& v) override;
    virtual SerializerStatus read(uint32& v) override;
    virtual SerializerStatus read(int64& v) override;
    virtual SerializerStatus read(uint64& v) override;
    virtual SerializerStatus read(float& v) override;
    virtual SerializerStatus read(double& v) override;
    virtual SerializerStatus read(longdouble& v) override;
    virtual SerializerStatus read(StringView& v) override;
    virtual SerializerStatus read(hex64& v) override;
    virtual SerializerStatus read(void*& a_pPtr, lang::Type* a_pPointeeType) override;
    virtual SerializerStatus read(void* a_pValue, lang::Enum* a_pEnumType) override;

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus read(wchar_t& v) override { return _read((uint16&)v); });
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus read(char16_t& v) override { return _read((uint16&)v); });
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus read(char32_t& v) override { return _read((uint32&)v); });

    using Serializer::write;
    virtual SerializerStatus write(const bool& v) override;
    virtual SerializerStatus write(const char& v) override;
    virtual SerializerStatus write(const uint8& v) override;
    virtual SerializerStatus write(const int8& v) override;
    virtual SerializerStatus write(const int16& v) override;
    virtual SerializerStatus write(const uint16& v) override;
    virtual SerializerStatus write(const int32& v) override;
    virtual SerializerStatus write(const uint32& v) override;
    virtual SerializerStatus write(const int64& v) override;
    virtual SerializerStatus write(const uint64& v) override;
    virtual SerializerStatus write(const float& v) override;
    virtual SerializerStatus write(const double& v) override;
    virtual SerializerStatus write(const longdouble& v) override;
    virtual SerializerStatus write(StringView str) override;
    virtual SerializerStatus write(const hex64& v) override { return _write(uint64(v)); }
    virtual SerializerStatus write(void* const& v, lang::Type* a_pPointeeType) override;
    virtual SerializerStatus write(void const* v, lang::Enum* a_pEnumType) override;

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus write(const wchar_t& v) override { return _write((uint16 const&)v); });
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus write(const char16_t& v)
                        override { return _write((uint16 const&)v); });
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus write(const char32_t& v)
                        override { return _write((uint32 const&)v); });

private:
    bool _resize(size_t a_uiSize);
    bool _prepareRead(size_t a_uiSize);
    bool _prepareWrite(size_t a_uiSize);

#if PHANTOM_ENDIANESS_SWAP
    template<size_t size>
    struct EndianSwap;
    template<>
    struct EndianSwap<16>
    {
        template<class T>
        static T swap(const T& val)
        {
            return PHANTOM_SWAP16(val);
        }
        template<class T>
        static void swap(T& val)
        {
            val = PHANTOM_SWAP16(val);
        }
    };

    template<>
    struct EndianSwap<32>
    {
        template<class T>
        static T swap(const T& val)
        {
            return PHANTOM_SWAP32(val);
        }
        template<class T>
        static void swap(T& val)
        {
            val = PHANTOM_SWAP32(val);
        }
    };

    template<>
    struct EndianSwap<64>
    {
        template<class T>
        static T swap(const T& val)
        {
            return PHANTOM_SWAP64(val);
        }
        template<class T>
        static void swap(T& val)
        {
            val = PHANTOM_SWAP64(val);
        }
    };
#else

    template<size_t size>
    struct EndianSwap
    {
        template<class T>
        static const T& swap(const T& val)
        {
            return val;
        }
        template<class T>
        static void swap(T&)
        {
        }
    };
#endif

    template<class T>
    SerializerStatus _write(const T& val)
    {
        if (_prepareWrite(sizeof(T)))
        {
            const T& endianVal = EndianSwap<sizeof(T)>::swap(val);
            memcpy(m_pCurrentAddress, &endianVal, sizeof(T));
            m_pCurrentAddress += sizeof(T);
            return SerializerStatus::OK;
        }
        setLastError(SerializerError::NotEnoughMemory);
        return SerializerStatus::Error;
    }
    template<class T>
    SerializerStatus _read(T& val)
    {
        if (_prepareRead(sizeof(T)))
        {
            memcpy(&val, m_pCurrentAddress, sizeof(T));
            EndianSwap<sizeof(T)>::swap(val);
            m_pCurrentAddress += sizeof(T);
            return SerializerStatus::OK;
        }
        setLastError(SerializerError::BufferOverflow);
        return SerializerStatus::Error;
    }

private:
    byte*  m_pBuffer = 0;
    size_t m_uiBufferSize = 0;
    byte*  m_pCurrentAddress = 0;
};
} // namespace serialization

} // namespace phantom
