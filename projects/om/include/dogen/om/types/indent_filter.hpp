/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

/**
 * @note The code in this file was copied from the boost mailing list
 * archives: http://lists.boost.org/Archives/boost/2008/02/133679.php
 *
 * The code was originally written by Roland Schwarz and carried no
 * licence.
 *
 * The code has been modified from its original.
 */
#ifndef DOGEN_OM_TYPES_INDENT_FILTER_HPP
#define DOGEN_OM_TYPES_INDENT_FILTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ios>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/operations.hpp>

namespace dogen {
namespace om {

/**
 * @brief Store a pointer to the indenter filter.
 *
 * xdent is small helper class to get global variable behaviour for
 * the stream pword index. Desgigned for header only
 * implementation. The expression xdent<int>()() will always get the
 * same unique index
 */
template <typename IndexType>
struct xdent {
    int operator()() {
        if (!initialized_) {
            index_ = std::ios::xalloc();
            initialized_ = true;
        }
        return index_;
    }
private:
    static IndexType index_;
    static bool initialized_;
};

template <typename IndexType> IndexType xdent<IndexType>::index_;
template <typename IndexType> bool xdent<IndexType>::initialized_;

/**
 * @brief The indent filter.
 *
 * The ctor is private, so the filter can only be created from its
 * static push function. This is to assert registration to the
 * stream.
 */
class indent_filter : public boost::iostreams::output_filter {
public:
    template<typename Sink>
    bool put(Sink& dest, int c) {
        if (c == '\n') {
            at_line_start_ = true;
            return boost::iostreams::put(dest, c);
        }

        if (at_line_start_) {
            at_line_start_ = false;
            const auto total_spaces(indentation_size_ * indentation_level_);
            for (unsigned int n(0); n < total_spaces; ++n)
                boost::iostreams::put(dest, ' ');
        }
        return boost::iostreams::put(dest, c);
    }

    template<typename Sink>
    void close(Sink&) {
        indentation_level_ = 0;
        at_line_start_ = true;
    }

public:
    /**
     * @brief Increase indentation level by one.
     */
    void increment_indentation_level() { ++indentation_level_; }

    /**
     * @brief Decrease indentation level by one.
     */
    void decrement_indentation_level() {
        if (indentation_level_ > 0)
            --indentation_level_;
    }

public:
    /**
     * @brief Register the filter into the filtering ostream.
     *
     * Of course it would be more elegant to modify the
     * filtering_ostream push function instead.
     */
    static void push(boost::iostreams::filtering_ostream& s,
        const unsigned int indentation_size = 4) {
        s.push(indent_filter(indentation_size));
        indent_filter* filter(s.component<indent_filter>(s.size() - 1));
        s.pword(xdent<int>()()) = filter;
        filter->stream_ = &s;
    }

    /**
     * @brief Unregister the filter.
     */
    ~indent_filter() {
        if (stream_)
            stream_->pword(xdent<int>()()) = 0;
    }

public:
    /**
     * @brief Returns the current level of indentation.
     */
    unsigned int indentation_level() const { return indentation_level_; }

private:
    explicit indent_filter(const unsigned int indentation_size)
    : indentation_level_(0), at_line_start_(true),
      indentation_size_(indentation_size), stream_(0) { }

private:
    unsigned int indentation_level_;
    bool at_line_start_;
    const unsigned int indentation_size_;
    std::ostream* stream_;
};

/**
 * @brief Manipulators that change indentation.
 *
 * Note that this will even work when the filter_stream is accessed
 * through its basic_ostream. Uniqueness of xdent<int>()() guarantees
 * correct cast from void* to indent_filter*.
 */
/**@{*/
template<class CharType, class TraitsType = std::char_traits<CharType> >
inline std::basic_ostream<CharType, TraitsType>&
indent_in(std::basic_ostream<CharType, TraitsType>& s) {
    indent_filter* filter((indent_filter*)s.pword(xdent<int>()()));
    if (filter) {
        s.flush();
        filter->increment_indentation_level();
    }
    return s;
}

template<class CharType, class TraitsType = std::char_traits<CharType> >
inline std::basic_ostream<CharType, TraitsType>&
indent_out(std::basic_ostream<CharType, TraitsType>& s) {
    indent_filter* filter((indent_filter*)s.pword(xdent<int>()()));
    if (filter) {
        s.flush();
        filter->decrement_indentation_level();
    }
    return s;
}
/**@}*/

/**
 * @brief Utility class that indents on construction and outdents on
 * destruction.
 */
template<class CharType, class TraitsType = std::char_traits<CharType> >
class basic_positive_indenter_scope {
public:
    basic_positive_indenter_scope(std::basic_ostream<CharType, TraitsType>& s)
        : stream_(s) { stream_ << indent_in; }
    ~basic_positive_indenter_scope() { stream_ << indent_out; }

private:
    std::basic_ostream<CharType, TraitsType>& stream_;
};

typedef basic_positive_indenter_scope<char> positive_indenter_scope;

/**
 * @brief Utility class that outdents on construction and indents on
 * destruction.
 */
template<class CharType, class TraitsType = std::char_traits<CharType> >
class basic_negative_indenter_scope {
public:
    basic_negative_indenter_scope(std::basic_ostream<CharType, TraitsType>& s)
        : stream_(s), started_at_zero_(false) {

        indent_filter* filter((indent_filter*)s.pword(xdent<int>()()));
        if (filter)
            started_at_zero_ = filter->indentation_level() == 0;

        stream_ << indent_out;
    }

    ~basic_negative_indenter_scope() {
        if (!started_at_zero_)
            stream_ << indent_in;
    }

private:
    std::basic_ostream<CharType, TraitsType>& stream_;
    bool started_at_zero_;
};

typedef basic_negative_indenter_scope<char> negative_indenter_scope;

} }

/**
 * @brief Helper operators that wrap the manipulators.
 *
 * This idea was copied from Larry Evans's code.
 */
template<class char_type, class traits_type>
inline void operator++(std::basic_ostream<char_type, traits_type>& s) {
    s << dogen::om::indent_in;
}

template<class char_type, class traits_type>
inline void operator--(std::basic_ostream<char_type, traits_type>& s) {
    s << dogen::om::indent_out;
}

#endif
