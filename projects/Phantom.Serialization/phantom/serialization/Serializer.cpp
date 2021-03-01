// license [
// This file is part of the Phantom project. Copyright 2011-2020 Vivien Millet.
// Distributed under the MIT license. Text available here at
// https://github.com/vlmillet/phantom
// ]

#include "Serializer.h"

#include <phantom/typeof>

namespace phantom
{
namespace serialization
{
SerializerStatus Serializer::write(const std::nullptr_t&)
{
    return write(nullptr, PHANTOM_TYPEOF(void));
}

void Serializer::setMode(Mode _mode)
{
    if (m_eMode == _mode)
        return;
    m_eMode = _mode;
    onModeChanged(m_eMode);
}

SerializerStatus Serializer::read(std::nullptr_t& a_nullptr)
{
    a_nullptr = nullptr;
    return SerializerStatus::OK;
}
} // namespace serialization
} // namespace phantom
