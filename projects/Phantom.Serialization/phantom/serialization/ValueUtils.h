// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

/* ****************** Includes ******************* */
#include "IValueStream.h"
#include "OValueStream.h"

#include <fstream>
#include <phantom/serialization/SerializerVisitor.h>
#include <phantom/serialization/ValueSerializer.h>
/* *********************************************** */

namespace phantom
{
namespace serialization
{
class PHANTOM_EXPORT_PHANTOM_SERIALIZATION ValueUtils
{
public:
    using ValueSerializer = serialization::ValueSerializer;
    using SerializerStatus = serialization::SerializerStatus;
    using SerializerError = serialization::SerializerError;
    using SerializerVisitor = serialization::SerializerVisitor;

    template<class T>
    static bool Deserialize(T& a_Out, Value const& a_Value, uint32 a_MemberFilterFlags = ~0u)
    {
        ValueSerializer   serial(a_Value);
        SerializerVisitor visitor(serial, a_MemberFilterFlags);
        return visitor.visit(&a_Out, PHANTOM_TYPEOF(T)) != SerializerStatus::Error;
    }
    template<class T>
    static bool Serialize(T const& a_In, Value& a_Value, uint32 a_MemberFilterFlags = ~0u)
    {
        ValueSerializer   serial(a_Value);
        SerializerVisitor visitor(serial, a_MemberFilterFlags);
        return visitor.visit(&a_In, PHANTOM_TYPEOF(T)) != SerializerStatus::Error;
    }
    static bool SaveToFile(StringView a_FilePath, const Value& a_Val)
    {
        std::ofstream out(String(a_FilePath).c_str());
        if (!out.is_open())
            return false;
        OValueStream vout(out);
        vout << a_Val;
        return true;
    }
    template<class T>
    static bool SaveToFile(StringView a_FilePath, T const& a_In, uint32 a_MemberFilterFlags = ~uint32(-1))
    {
        Value v;
        if (!Serialize(a_In, v, a_MemberFilterFlags))
            return false;
        std::ofstream out(String(a_FilePath).c_str());
        if (!out.is_open())
            return false;
        OValueStream vout(out);
        vout << v;
        return true;
    }
    static bool LoadFromFile(StringView a_FilePath, Value& a_Out)
    {
        std::ifstream input(String(a_FilePath).c_str());
        if (!input.is_open())
            return false;
        IValueStream vin(input);
        vin >> a_Out;
        return true;
    }
    template<class T>
    static bool LoadFromFile(StringView a_FilePath, T& a_Out, uint32 a_MemberFilterFlags = ~uint32(-1))
    {
        std::ifstream input(String(a_FilePath).c_str());
        if (!input.is_open())
            return false;
        IValueStream vin(input);
        Value        v;
        vin >> v;
        return Deserialize(a_Out, v);
    }
};
} // namespace serialization
} // namespace phantom
