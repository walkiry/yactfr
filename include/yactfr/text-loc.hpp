/*
 * Copyright (C) 2016-2018 Philippe Proulx <eepp.ca>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#ifndef _YACTFR_TEXT_LOC_HPP
#define _YACTFR_TEXT_LOC_HPP

#include "aliases.hpp"

namespace yactfr {

/*!
@brief
    Location in a multiline text.

@ingroup common
*/
class TextLocation final
{
public:
    /*
    @brief
        Builds a default text location (first line, first column).
    */
    TextLocation() = default;

    /*
    @brief
        Builds a text location which targets zero-based line number
        \p lineNumber and column number \p columnNumber.

    @param[in] lineNumber
        Line number (zero-based) of the text location.
    @param[in] columnNumber
        Column number (zero-based) of the text location.
    */
    explicit TextLocation(Index lineNumber, Index columnNumber) noexcept;

    TextLocation(const TextLocation&) = default;
    TextLocation(TextLocation&&) = default;
    TextLocation& operator=(const TextLocation&) = default;
    TextLocation& operator=(TextLocation&&) = default;

    /// Line number (zero-based).
    Index lineNumber() const noexcept
    {
        return _lineNumber;
    }

    /// Column number (zero-based).
    Index columnNumber() const noexcept
    {
        return _colNumber;
    }

    /// Line number (one-based).
    Index naturalLineNumber() const noexcept
    {
        return _lineNumber + 1;
    }

    /// Column number (one-based).
    Index naturalColumnNumber() const noexcept
    {
        return _colNumber + 1;
    }

private:
    Index _lineNumber = 0, _colNumber = 0;
};

} // namespace yactfr

#endif // _YACTFR_TEXT_LOC_HPP