/*
 * Copyright (C) 2015-2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <cassert>

#include <yactfr/metadata/fl-float-type.hpp>

namespace yactfr {

FixedLengthFloatingPointNumberType::FixedLengthFloatingPointNumberType(const unsigned int align,
                                                                       const unsigned int len,
                                                                       const ByteOrder bo) :
    FixedLengthBitArrayType {_KIND_FL_FLOAT, align, len, bo}
{
    assert(len == 32 || len == 64);
}

FixedLengthFloatingPointNumberType::FixedLengthFloatingPointNumberType(const FixedLengthFloatingPointNumberType& other) :
    FixedLengthFloatingPointNumberType {other.alignment(), other.length(), other.byteOrder()}
{
}

DataType::UP FixedLengthFloatingPointNumberType::_clone() const
{
    return std::make_unique<FixedLengthFloatingPointNumberType>(this->alignment(), this->length(),
                                                                this->byteOrder());
}

} // namespace yactfr
