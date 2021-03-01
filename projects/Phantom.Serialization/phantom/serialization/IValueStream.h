// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

#include "plugin.h"

#include <istream>

namespace phantom
{
namespace serialization
{
class Value;
class PHANTOM_EXPORT_PHANTOM_SERIALIZATION IValueStream
{
public:
    static const char* last_error();

    IValueStream(std::istream& a_InStream);
    ~IValueStream();

    bool fail() const;

    bool operator>>(Value& value);

private:
    struct IValueStreamPrivate* _private;
    std::istream&               m_InStream;
    bool                        error = false;
};
} // namespace serialization
} // namespace phantom
