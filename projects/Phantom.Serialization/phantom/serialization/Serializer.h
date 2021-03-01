// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

#include "SerializerConstants.h"

#include <phantom/utils/SmallVector.h>
#include <phantom/utils/String.h>

namespace phantom
{
namespace serialization
{
class PHANTOM_EXPORT_PHANTOM_SERIALIZATION Serializer
{
public:
    enum class Mode
    {
        Read,
        Write,
    };

    Serializer(Mode a_eMode) : m_eMode(a_eMode) {}

    Mode getMode() const { return m_eMode; }

    void setMode(Mode _mode);

    bool isWriting() const { return m_eMode == Mode::Write; }
    bool isReading() const { return m_eMode == Mode::Read; }

    void            setLastError(SerializerError a_eError) { m_eLastError = a_eError; }
    SerializerError getLastError() const { return m_eLastError; }

    struct Scope
    {
                         operator bool() const { return m_Status != SerializerStatus::Error; }
        SerializerStatus getStatus() const { return m_Status; }

    protected:
        Scope(SerializerStatus a_Status) : m_Status(a_Status) {}
        Scope(Scope&& a_Temp) : m_Status(a_Temp.m_Status) { a_Temp.m_bCancelled = true; }
        Scope(Scope const&) = delete;
        Scope&           operator=(Scope const&) = delete;
        Scope&           operator=(Scope&&) = delete;
        SerializerStatus m_Status;
        bool             m_bCancelled = false;
    };

    struct ArrayScope : Scope
    {
        ArrayScope(Serializer& a_S) : Scope(a_S.beginArray()), m_S(a_S) {}
        ~ArrayScope()
        {
            if (getStatus() != SerializerStatus::Error && !m_bCancelled)
                m_S.endArray();
        }
        ArrayScope(ArrayScope&& a_Temp) : Scope(std::move(a_Temp)), m_S(a_Temp.m_S) {}

    private:
        Serializer& m_S;
    };

    ArrayScope scopedArray() { return ArrayScope(*this); }

    struct StructureScope : Scope
    {
        StructureScope(Serializer& a_S) : Scope(a_S.beginStructure()), m_S(a_S) {}
        ~StructureScope()
        {
            if (getStatus() != SerializerStatus::Error && !m_bCancelled)
                m_S.endStructure();
        }
        StructureScope(StructureScope&& a_Temp) : Scope(std::move(a_Temp)), m_S(a_Temp.m_S) {}

    private:
        Serializer& m_S;
    };

    StructureScope scopedStructure() { return StructureScope(*this); }

    struct ArrayElementScope : Scope
    {
        ArrayElementScope(Serializer& a_S) : Scope(a_S.beginArrayElement()), m_S(a_S) {}
        ~ArrayElementScope()
        {
            if (getStatus() != SerializerStatus::Error && !m_bCancelled)
                m_S.endArrayElement();
        }
        ArrayElementScope(ArrayElementScope&& a_Temp) : Scope(std::move(a_Temp)), m_S(a_Temp.m_S) {}

    private:
        Serializer& m_S;
    };

    ArrayElementScope scopedArrayElement() { return ArrayElementScope(*this); }

    struct MemberScope : Scope
    {
        MemberScope(Serializer& a_S, StringView a_Name) : Scope(a_S.beginMember(a_Name)), m_S(a_S) {}
        ~MemberScope()
        {
            if (getStatus() != SerializerStatus::Error && !m_bCancelled)
                m_S.endMember();
        }
        MemberScope(MemberScope&& a_Temp) : Scope(std::move(a_Temp)), m_S(a_Temp.m_S) {}

        operator bool() const { return m_Status == SerializerStatus::OK; }

    private:
        Serializer& m_S;
    };

    MemberScope scopedMember(StringView a_Name) { return MemberScope(*this, a_Name); }

    virtual SerializerStatus beginArray() = 0;
    virtual void             endArray() {}

    virtual SerializerStatus beginArrayElement() = 0;
    virtual void             endArrayElement() {}

    virtual SerializerStatus beginStructure() = 0;
    virtual void             endStructure() {}

    virtual SerializerStatus beginMember(StringView name) = 0;
    virtual void             endMember() {}

    virtual SerializerStatus read(bool& a_bool) = 0;
    virtual SerializerStatus read(char& a_char) = 0;
    virtual SerializerStatus read(uint8& a_uchar) = 0;
    virtual SerializerStatus read(int8& a_schar) = 0;
    virtual SerializerStatus read(int16& a_int16) = 0;
    virtual SerializerStatus read(uint16& a_uint16) = 0;
    virtual SerializerStatus read(int32& a_int) = 0;
    virtual SerializerStatus read(uint32& a_uint) = 0;
    virtual SerializerStatus read(int64& a_int64) = 0;
    virtual SerializerStatus read(uint64& a_uint64) = 0;
#if PHANTOM_INT64_IS_LONGLONG
    SerializerStatus read(long& a_long) { return read((int32&)a_long); }
    SerializerStatus read(ulong& a_ulong) { return read((uint32&)a_ulong); }
#else
    SerializerStatus read(long long& a_long) { return read((int64&)a_long); }
    SerializerStatus read(unsigned long long& a_ulong) { return read((uint64&)a_ulong); }
#endif
    virtual SerializerStatus read(float& a_float) = 0;
    virtual SerializerStatus read(double& a_double) = 0;
    virtual SerializerStatus read(longdouble& a_longdouble) = 0;
    virtual SerializerStatus read(StringView& a_str) = 0;
    virtual SerializerStatus read(void*& a_pPtr, lang::Type* a_pPointeeType) = 0;
    virtual SerializerStatus read(void* a_pValue, lang::Enum* a_pEnumType) = 0;
    virtual SerializerStatus read(uint8* a_pBytes, size_t a_FixedSize) = 0;
    virtual SerializerStatus read(hex64& v) = 0;

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus read(wchar_t& a_wchar_t) = 0;);
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus read(char16_t& a_char16_t) = 0;);
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus read(char32_t& a_char32_t) = 0;);

    virtual SerializerStatus write(const bool& a_bool) = 0;
    virtual SerializerStatus write(const char& a_char) = 0;
    virtual SerializerStatus write(const int8& a_schar) = 0;
    virtual SerializerStatus write(const uint8& a_uchar) = 0;
    virtual SerializerStatus write(const int16& a_int16) = 0;
    virtual SerializerStatus write(const uint16& a_uint16) = 0;
    virtual SerializerStatus write(const int32& a_int) = 0;
    virtual SerializerStatus write(const uint32& a_uint) = 0;
    virtual SerializerStatus write(const int64& a_int64) = 0;
    virtual SerializerStatus write(const uint64& a_uint64) = 0;
#if PHANTOM_INT64_IS_LONGLONG
    SerializerStatus write(const long& a_long) { return write((const int32&)a_long); }
    SerializerStatus write(const ulong& a_ulong) { return write((const uint32&)a_ulong); }
#else
    SerializerStatus write(const long long& a_long) { return write((const int64&)a_long); }
    SerializerStatus write(const unsigned long long& a_ulong) { return write((const uint64&)a_ulong); }
#endif
    virtual SerializerStatus write(const float& a_float) = 0;
    virtual SerializerStatus write(const double& a_double) = 0;
    virtual SerializerStatus write(const longdouble& a_longdouble) = 0;
    virtual SerializerStatus write(StringView) = 0;
    virtual SerializerStatus write(const char* a_pStr, size_t a_Size) { return write(StringView(a_pStr, a_Size)); }
    virtual SerializerStatus write(void* const& a_pPtr, lang::Type* a_pPointeeType) = 0;
    virtual SerializerStatus write(void const* a_pValue, lang::Enum* a_pEnumType) = 0;
    virtual SerializerStatus write(uint8 const* a_pBytes, size_t a_FixedSize) = 0;
    virtual SerializerStatus write(hex64 const& v) = 0;
    SerializerStatus         write(const std::nullptr_t& a_nullptr);
    SerializerStatus         read(std::nullptr_t& a_nullptr);

    PHANTOM_IF_WCHAR_T(virtual SerializerStatus write(const wchar_t& a_wchar_t) = 0;);
    PHANTOM_IF_CHAR16_T(virtual SerializerStatus write(const char16_t& a_char16_t) = 0;);
    PHANTOM_IF_CHAR32_T(virtual SerializerStatus write(const char32_t& a_char32_t) = 0;);

    /// @brief write or read depending on current mode
    template<class... Args>
    SerializerStatus serialize(Args&&... a_Args)
    {
        if (m_eMode == Mode::Write)
            return write(std::forward<Args>(a_Args)...);
        return read(std::forward<Args>(a_Args)...);
    }

    void  pushUserData(void* a_pData) { m_UserDataStck.push_back(a_pData); }
    void  popUserData() { m_UserDataStck.pop_back(); }
    void* topUserData() const { return m_UserDataStck.size() ? m_UserDataStck.back() : nullptr; }

private:
    template<class T>
    friend class lang::FundamentalTypeT;
    friend class lang::Pointer;
    friend class lang::Enum;

    template<class T>
    SerializerStatus writePointer(T* const& a_pPtr, lang::Pointer* a_pPointerType)
    {
        return write((void* const&)a_pPtr, (lang::Type*)a_pPointerType);
    }
    template<class T>
    SerializerStatus readPointer(T*& a_pPtr, lang::Pointer* a_pPointerType)
    {
        return read((void*&)a_pPtr, (lang::Type*)a_pPointerType);
    }
    virtual void onModeChanged(Mode) {}

private:
    SerializerError       m_eLastError = SerializerError::None;
    Mode                  m_eMode = Mode::Read;
    SmallVector<void*, 1> m_UserDataStck;
};
} // namespace serialization
} // namespace phantom
