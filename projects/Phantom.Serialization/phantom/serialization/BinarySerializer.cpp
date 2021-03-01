// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#include "BinarySerializer.h"

#include "phantom/lang/Constant.h"
#include "phantom/lang/Enum.h"

namespace phantom
{
namespace serialization
{
BinarySerializer::BinarySerializer() : Serializer(Mode::Write), m_pBuffer(nullptr), m_uiBufferSize(0) {}

BinarySerializer::BinarySerializer(const byte* a_pBuffer, size_t a_uiBufferSize)
    : Serializer(Mode::Read), m_pBuffer((byte*)a_pBuffer), m_uiBufferSize(a_uiBufferSize)
{
}

BinarySerializer::BinarySerializer(const BufferData& a_Buffer)
    : Serializer(Mode::Read), m_pBuffer(a_Buffer.memory), m_uiBufferSize(a_Buffer.size)
{
}

BinarySerializer::~BinarySerializer()
{
    if (getMode() == Mode::Write)
    {
#ifdef ALIGNED_BUFFER
        PHANTOM_FREE(m_pBuffer);
#else
        PHANTOM_FREE_ALIGNED(m_pBuffer);
#endif
    }
}

SerializerStatus BinarySerializer::beginArray()
{
    return SerializerStatus::OK;
}

void BinarySerializer::endArray() {}

SerializerStatus BinarySerializer::beginArrayElement()
{
    return SerializerStatus::OK;
}

void BinarySerializer::endArrayElement() {}

SerializerStatus BinarySerializer::beginStructure()
{
    return SerializerStatus::OK;
}

void BinarySerializer::endStructure() {}

SerializerStatus BinarySerializer::beginMember(StringView)
{
    return SerializerStatus::OK;
}

void BinarySerializer::endMember() {}

SerializerStatus BinarySerializer::write(void* const& v, lang::Type*)
{
    return write(size_t(v));
}

SerializerStatus BinarySerializer::write(void const* a_pValue, lang::Enum* a_pEnumType)
{
    if (lang::Constant* pConstant = a_pEnumType->getFirstConstant(a_pValue))
    {
        int64 val;
        pConstant->getValue(&val);
        write(val);
        return SerializerStatus::OK;
    }
    setLastError(SerializerError::UnknownEnumValue);
    return SerializerStatus::Error;
}

SerializerStatus BinarySerializer::write(const bool& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const char& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const uint8& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const int8& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const int16& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const uint16& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const int32& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const uint32& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const int64& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const uint64& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const double& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const float& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(const longdouble& v)
{
    return _write(v);
}

SerializerStatus BinarySerializer::write(StringView str)
{
    if (_prepareWrite(str.size() + sizeof(size_t)))
    {
        write(str.size());
        memcpy(m_pCurrentAddress, str.data(), str.size());
        return SerializerStatus::OK;
    }
    setLastError(SerializerError::NotEnoughMemory);
    return SerializerStatus::Error;
}

bool BinarySerializer::_resize(size_t a_uiSize)
{
    if (m_uiBufferSize >= a_uiSize)
    {
        return true;
    }

    size_t newAllocatedSize = (m_uiBufferSize > 16) ? m_uiBufferSize : 16;
    while (newAllocatedSize < a_uiSize)
    {
        newAllocatedSize *= 2;
    }

    if ((m_pCurrentAddress + a_uiSize) > (m_pBuffer + m_uiBufferSize))
    {
        byte* oldBuffer = m_pBuffer;
        auto  oldSize = m_uiBufferSize;
        m_uiBufferSize = newAllocatedSize;
#ifdef ALIGNED_BUFFER
        m_pBuffer = (byte*)PHANTOM_MALLOC_ALIGNED(m_uiBufferSize, BUFFER_ALIGNMENT);
#else
        m_pBuffer = (byte*)PHANTOM_MALLOC(m_uiBufferSize);
        PHANTOM_ASSERT(m_pBuffer, "cant alloc %u", m_uiBufferSize);
#endif
        if (oldSize != 0)
        {
            memcpy(m_pBuffer, oldBuffer, oldSize);
            m_pCurrentAddress = m_pBuffer + oldSize;

#ifdef ALIGNED_BUFFER
            PHANTOM_FREE_ALIGNED(oldBuffer);
#else
            PHANTOM_FREE(oldBuffer);
#endif
        }
        else
        {
            m_pCurrentAddress = m_pBuffer;
        }
        PHANTOM_ASSERT(m_pBuffer);
    }
    else
    {
        PHANTOM_ASSERT(m_pBuffer);
    }
    return m_pBuffer != nullptr;
}

bool BinarySerializer::_prepareRead(size_t a_uiSize)
{
    byte* pEnd = m_pBuffer + m_uiBufferSize;
    if (m_pCurrentAddress + a_uiSize > pEnd)
        return false;
    return true;
}

bool BinarySerializer::_prepareWrite(size_t a_uiSize)
{
    byte* pEnd = m_pBuffer + m_uiBufferSize;
    if (m_pCurrentAddress + a_uiSize > pEnd)
    {
        if (!_resize((size_t)((m_pCurrentAddress + a_uiSize) - m_pBuffer)))
        {
            PHANTOM_ASSERT(false, "Unable to allocate");
            return false;
        }
        PHANTOM_ASSERT(m_pCurrentAddress);
    }
    return true;
}

SerializerStatus BinarySerializer::read(void*& a_pPtr, lang::Type*)
{
    return read((size_t&)a_pPtr);
}

SerializerStatus BinarySerializer::read(void* a_pValue, lang::Enum* a_pEnumType)
{
    int64 val;
    read(val);
    a_pEnumType->copy(a_pValue, &val);
    return SerializerStatus::OK;
}

SerializerStatus BinarySerializer::read(bool& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(char& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(int8& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(uint8& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(int16& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(uint16& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(int32& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(uint32& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(int64& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(uint64& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(float& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(double& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(longdouble& v)
{
    return _read(v);
}

SerializerStatus BinarySerializer::read(StringView& v)
{
    size_t size;
    if (read(size) != SerializerStatus::Error)
    {
        if (_prepareRead(size))
        {
            v = StringView((const char*)m_pCurrentAddress, size);
            m_pCurrentAddress += size;
            return SerializerStatus::OK;
        }
    }
    setLastError(SerializerError::BufferOverflow);
    return SerializerStatus::Error;
}

SerializerStatus BinarySerializer::read(hex64& v)
{
    return _read((uint64&)v);
}

void BinarySerializer::takeWriteBuffer(BufferData& a_Buffer)
{
    a_Buffer.memory = takeWriteBuffer(a_Buffer.size);
}

byte* BinarySerializer::takeWriteBuffer(size_t& a_uiSize)
{
    byte* pBuffer = m_pBuffer;
    m_pBuffer = nullptr;
    a_uiSize = m_pCurrentAddress - m_pBuffer;
    m_uiBufferSize = 0;
    m_pCurrentAddress = nullptr;
    return pBuffer;
}

} // namespace serialization
} // namespace phantom
