/*
 * Copyright (C) 2022 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include <yactfr/metadata/sl-blob-type.hpp>

namespace yactfr {

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           std::string mediaType, const bool hasTraceTypeUuidRole) :
    BlobType {_KIND_SL_BLOB, align, std::move(mediaType)},
    _len {len},
    _hasTraceTypeUuidRole {hasTraceTypeUuidRole}
{
}

StaticLengthBlobType::StaticLengthBlobType(const unsigned int align, const Size len,
                                           const bool hasTraceTypeUuidRole) :
    BlobType {_KIND_SL_BLOB, align},
    _len {len},
    _hasTraceTypeUuidRole {hasTraceTypeUuidRole}
{
}

DataType::UP StaticLengthBlobType::_clone() const
{
    return std::make_unique<StaticLengthBlobType>(this->alignment(), _len, this->mediaType());
}

bool StaticLengthBlobType::_isEqual(const DataType& other) const noexcept
{
    auto& otherSlBlobType = static_cast<const StaticLengthBlobType&>(other);

    return BlobType::_isEqual(other) && _len == otherSlBlobType._len &&
           otherSlBlobType._hasTraceTypeUuidRole == _hasTraceTypeUuidRole;
}

} // namespace yactfr