// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#pragma once

#include "plugin.h"

#include <phantom/utils/Functor.h>

namespace phantom
{
namespace serialization
{
class Serializer;

enum class SerializerStatus
{
    Error,
    OK,
    OptionalEntryNotFound
};

enum class SerializerError
{
    None,
    RequiredEntryNotFound,
    BadFormat,
    BadType,
    NotEnoughMemory,
    BufferOverflow,
    NoValidConversion,
    BadCount,
    NotSerializable,
    UnknownEnumValue,
    UnknownGUID,
    ExpectedArray,
    ExpectedStruct,
    UnexpectedEndOfFile
};

using SerializerEntryPoint = Functor<SerializerStatus(Serializer&)>;

} // namespace serialization
} // namespace phantom
