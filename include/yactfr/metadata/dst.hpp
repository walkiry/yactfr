/*
 * Copyright (C) 2015-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_METADATA_DST_HPP
#define _YACTFR_METADATA_DST_HPP

#include <memory>
#include <unordered_map>
#include <set>
#include <boost/noncopyable.hpp>

#include "dt.hpp"
#include "aliases.hpp"
#include "ert.hpp"
#include "struct-type.hpp"

namespace yactfr {
namespace internal {

class TraceTypeImpl;

struct ErtIdComp final
{
    bool operator()(const std::unique_ptr<const EventRecordType>& a,
                    const std::unique_ptr<const EventRecordType>& b) const
    {
        return a->id() < b->id();
    }
};

} // namespace internal

class TraceType;
class StructureType;
class DataLocation;

/*!
@brief
    Set of event record types with unique IDs.

@ingroup metadata
*/
using EventRecordTypeSet = std::set<std::unique_ptr<const EventRecordType>, internal::ErtIdComp>;

/*!
@brief
    Data stream type.

@ingroup metadata

A data stream type describes data streams.
*/
class DataStreamType final :
    boost::noncopyable
{
    friend class internal::TraceTypeImpl;

public:
    /*!
    @brief
        Builds a data stream type.

    @param[in] id
        Data stream type ID.
    @param[in] eventRecordTypes
        Children event record types (moved to this type).
    @param[in] packetContextType
        Packet context type, or \c nullptr if none.
    @param[in] eventRecordHeaderType
        Event record header type, or \c nullptr if none.
    @param[in] eventRecordCommonContextType
        Event record common context type, or \c nullptr if none.
    */
    explicit DataStreamType(TypeId id, EventRecordTypeSet&& eventRecordTypes,
                            StructureType::UP packetContextType,
                            StructureType::UP eventRecordHeaderType,
                            StructureType::UP eventRecordCommonContextType);

    /// Numeric ID, unique amongst the IDs of all the data stream types
    /// which are part of the same \link TraceType trace type\endlink.
    TypeId id() const noexcept
    {
        return _id;
    }

    /// Contained event record types.
    const EventRecordTypeSet& eventRecordTypes() const noexcept
    {
        return _erts;
    }

    /*!
    @brief
        Returns the event record type having the ID \p id,
        or \c nullptr if not found.

    @param[in] id
        ID of the event record type to find.

    @returns
        Event record type with ID \p id, or \c nullptr if not found.
    */
    const EventRecordType *operator[](TypeId id) const;

    /// Event record type constant iterator set at the first event
    /// record type of this type.
    EventRecordTypeSet::const_iterator begin() const noexcept
    {
        return _erts.begin();
    }

    /// Event record type constant iterator set \em after the last event
    /// record type of this type.
    EventRecordTypeSet::const_iterator end() const noexcept
    {
        return _erts.end();
    }

    /// Type of the context structure following the header structure of
    /// the packets of the data streams described by this type, or
    /// \c nullptr if there's no packet context type.
    const StructureType *packetContextType() const noexcept
    {
        return _pktCtxType.get();
    }

    /// Type of the header structure of all the event records contained in
    /// the packets of the data streams described by this type, or
    /// \c nullptr if there's no event record header type.
    const StructureType *eventRecordHeaderType() const noexcept
    {
        return _erHeaderType.get();
    }

    /// Type of the common context structure following the header structure of
    /// all the event records contained in the packets of
    /// the data streams described by this type, or
    /// \c nullptr if there's no event record common context type.
    const StructureType *eventRecordCommonContextType() const noexcept
    {
        return _erCommonCtxType.get();
    }

    /// Parent trace type of this type, or \c nullptr if this type is
    /// not part of a trace type yet.
    const TraceType *traceType() const noexcept
    {
        return _traceType;
    }

private:
    void _buildErtMap();
    bool _isDataTypeEmpty(const DataType *type) const;
    void _setTraceType(const TraceType& traceType) const;

private:
    const TypeId _id;
    const EventRecordTypeSet _erts;
    std::unordered_map<TypeId, const EventRecordType *> _idsToErts;
    StructureType::UP _pktCtxType;
    StructureType::UP _erHeaderType;
    StructureType::UP _erCommonCtxType;
    mutable const TraceType *_traceType = nullptr;
};

} // namespace yactfr

#endif // _YACTFR_METADATA_DST_HPP