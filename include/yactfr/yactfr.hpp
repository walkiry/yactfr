/*
 * Master header.
 *
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

/*!
@file
@brief  Master header.
*/

#ifndef _YACTFR_YACTFR_HPP
#define _YACTFR_YACTFR_HPP

#include "aliases.hpp"
#include "data-block.hpp"
#include "data-source-factory.hpp"
#include "data-source.hpp"
#include "decoding-errors.hpp"
#include "element-visitor.hpp"
#include "element.hpp"
#include "io-error.hpp"
#include "memory-mapped-file-view-factory.hpp"
#include "metadata/aliases.hpp"
#include "metadata/array-sequence-type-base.hpp"
#include "metadata/array-type.hpp"
#include "metadata/bit-array-type.hpp"
#include "metadata/byte-order.hpp"
#include "metadata/clock-type.hpp"
#include "metadata/compound-type.hpp"
#include "metadata/data-stream-type.hpp"
#include "metadata/data-type-visitor.hpp"
#include "metadata/data-type.hpp"
#include "metadata/encoding.hpp"
#include "metadata/enum-type.hpp"
#include "metadata/event-record-type.hpp"
#include "metadata/field-ref.hpp"
#include "metadata/float-type.hpp"
#include "metadata/fwd.hpp"
#include "metadata/int-type.hpp"
#include "metadata/invalid-metadata-stream.hpp"
#include "metadata/invalid-metadata.hpp"
#include "metadata/io.hpp"
#include "metadata/metadata-parse-error.hpp"
#include "metadata/metadata-stream.hpp"
#include "metadata/metadata-text-location.hpp"
#include "metadata/named-data-type.hpp"
#include "metadata/no-such-index.hpp"
#include "metadata/no-such-name.hpp"
#include "metadata/no-such-type-id.hpp"
#include "metadata/packetized-metadata-stream.hpp"
#include "metadata/plain-text-metadata-stream.hpp"
#include "metadata/scalar-type.hpp"
#include "metadata/scope.hpp"
#include "metadata/sequence-type.hpp"
#include "metadata/string-type.hpp"
#include "metadata/struct-type-field.hpp"
#include "metadata/struct-type.hpp"
#include "metadata/struct-variant-type-base.hpp"
#include "metadata/text-array-type.hpp"
#include "metadata/text-sequence-type.hpp"
#include "metadata/trace-type-env.hpp"
#include "metadata/trace-type-from-metadata-text.hpp"
#include "metadata/trace-type.hpp"
#include "metadata/variant-type-choice.hpp"
#include "metadata/variant-type.hpp"
#include "packet-sequence-iterator-position.hpp"
#include "packet-sequence-iterator.hpp"
#include "packet-sequence.hpp"

#endif // _YACTFR_YACTFR_HPP
