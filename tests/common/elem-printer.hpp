/*
 * Copyright (C) 2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TESTS_ELEM_PRINTER_HPP
#define _YACTFR_TESTS_ELEM_PRINTER_HPP

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iomanip>
#include <ostream>

#include <yactfr/elem-visitor.hpp>
#include <yactfr/elem.hpp>

class ElemPrinter :
    public yactfr::ElementVisitor
{
public:
    explicit ElemPrinter(std::ostream& os, const unsigned long indentWidth = 2) :
        _os {&os},
        _indentWidth {indentWidth}
    {
    }

    void visit(const yactfr::PacketBeginningElement& elem) override
    {
        this->_indent();
        *_os << "P {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::ScopeBeginningElement& elem) override
    {
        this->_indent();
        *_os << "SC:" << static_cast<int>(elem.scope()) << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::PacketContentBeginningElement& elem) override
    {
        this->_indent();
        *_os << "PC {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::EventRecordBeginningElement& elem) override
    {
        this->_indent();
        *_os << "ER {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DataStreamIdElement& elem) override
    {
        this->_indent();
        *_os << "DSID:" << elem.id() << '\n';
    }

    void visit(const yactfr::PacketOriginIndexElement& elem) override
    {
        this->_indent();
        *_os << "POI:" << elem.index() << '\n';
    }

    void visit(const yactfr::ExpectedPacketTotalLengthElement& elem) override
    {
        this->_indent();
        *_os << "EPTL:" << elem.expectedLength() << '\n';
    }

    void visit(const yactfr::ExpectedPacketContentLengthElement& elem) override
    {
        this->_indent();
        *_os << "EPCL:" << elem.expectedLength() << '\n';
    }

    void visit(const yactfr::PacketMagicNumberElement& elem) override
    {
        this->_indent();
        *_os << "PMN:" << elem.value() << '\n';
    }

    void visit(const yactfr::TraceTypeUuidElement& elem) override
    {
        this->_indent();
        *_os << "TTU:" << elem.uuid() << '\n';
    }

    void visit(const yactfr::ClockValueElement& elem) override
    {
        this->_indent();
        *_os << "CV:" << *elem.clockType().name() << ":" << elem.cycles() << '\n';
    }

    void visit(const yactfr::PacketEndClockValueElement& elem) override
    {
        this->_indent();
        *_os << "PECV:" << *elem.clockType().name() << ":" << elem.cycles() << '\n';
    }

    void visit(const yactfr::DataStreamTypeElement& elem) override
    {
        this->_indent();
        *_os << "DST:" << elem.dataStreamType().id() << '\n';
    }

    void visit(const yactfr::EventRecordTypeElement& elem) override
    {
        this->_indent();
        *_os << "ERT:" << elem.eventRecordType().id();

        if (elem.eventRecordType().name()) {
            *_os << ':' << *elem.eventRecordType().name();
        }

        *_os << '\n';
    }

    void visit(const yactfr::SignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "SI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::UnsignedIntegerElement& elem) override
    {
        this->_visitDataElem(elem, "UI");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::SignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "SE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::UnsignedEnumerationElement& elem) override
    {
        this->_visitDataElem(elem, "UE");
        *_os << ':' << elem.value() << '\n';
    }

    void visit(const yactfr::FloatingPointNumberElement& elem) override
    {
        this->_visitDataElem(elem, "FPN");
        *_os << ':' << std::setprecision(6) << elem.value() << '\n';
    }

    void visit(const yactfr::StringBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "STR");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::SubstringElement& elem) override
    {
        this->_indent();
        *_os << "SS:" << elem.size() << ":";

        for (auto ch = elem.begin(); *ch != '\0' && ch != elem.end(); ++ch) {
            *_os << *ch;
        }

        *_os << '\n';
    }

    void visit(const yactfr::StaticArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "SA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::StaticTextArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "STA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DynamicArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "DA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::DynamicTextArrayBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "DTA");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::StructureBeginningElement& elem) override
    {
        this->_visitDataElem(elem, "ST");
        *_os << " {\n";
        ++_indentLevel;
    }

    void visit(const yactfr::VariantWithSignedSelectorBeginningElement& elem) override
    {
        this->_visit(elem, "VS");
    }

    void visit(const yactfr::VariantWithUnsignedSelectorBeginningElement& elem) override
    {
        this->_visit(elem, "VU");
    }

    void visit(const yactfr::EndElement& elem) override
    {
        --_indentLevel;
        this->_indent();
        *_os << "}\n";
    }

private:
    template <typename VarBegElemT>
    void _visit(const VarBegElemT& elem, const char * const id)
    {
        this->_visitDataElem(elem, id);
        *_os << ':' << elem.selectorValue() << " {\n";
        ++_indentLevel;
    }

    void _visitDataElem(const yactfr::DataElement& elem, const char * const id)
    {
        this->_indent();
        *_os << id;

        if (elem.structureMemberType()) {
            *_os << ':' << elem.structureMemberType()->displayName();
        }
    }

    void _indent()
    {
        for (auto i = 0U; i < _indentLevel * _indentWidth; ++i) {
            *_os << ' ';
        }
    }

private:
    std::ostream * const _os;
    const unsigned long _indentWidth;
    unsigned long _indentLevel = 0;
};

#endif // _YACTFR_TESTS_ELEM_PRINTER_HPP