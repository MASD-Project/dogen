/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_INDENT_FILTER_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_INDENT_FILTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <ios>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/operations.hpp>

namespace dogen::text::formatters {

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
private:
    void reset_blank_lines_management() {
        manage_blank_lines_ = false;
        found_cr_ = false;
        found_lf_ = false;
    }

public:
    template<typename Sink>
    bool put(Sink& dest, int i) {
        const char c(static_cast<char>(i));
        const char cr(0x0D);
        const char lf(0x0A);

        if (manage_blank_lines_) {
            if (c == cr) {
                found_cr_ = true;
                return true;
            } else if (c == lf) {
                found_lf_ = true;
                return true;
            }

            if (!is_first_character_) {
                if (found_cr_) {
                    found_cr_ = false;
                    boost::iostreams::put(dest, cr);
                }

                if (found_lf_) {
                    found_lf_ = false;
                    boost::iostreams::put(dest, lf);
                }
            }
            reset_blank_lines_management();
        }
        is_first_character_ = false;

        if (c == lf) {
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
    void decrement_indentation_level(const bool reset_management = true) {
        if (indentation_level_ > 0) {
            --indentation_level_;

            if (reset_management)
                reset_blank_lines_management();
        }
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
        const int pos(static_cast<int>(s.size()) - 1);
        indent_filter* filter(s.component<indent_filter>(pos));
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

    /**
     * @brief Try to suppress trailing blank lines.
     */
    void manage_blank_lines() {
        reset_blank_lines_management();
        manage_blank_lines_ = true;
    }

private:
    explicit indent_filter(const unsigned int indentation_size)
    : indentation_level_(0), at_line_start_(true), is_first_character_(true),
      indentation_size_(indentation_size), stream_(0),
      manage_blank_lines_(false), found_cr_(false), found_lf_(false) { }

private:
    unsigned int indentation_level_;
    bool at_line_start_;
    bool is_first_character_;
    const unsigned int indentation_size_;
    std::ostream* stream_;
    bool manage_blank_lines_;
    bool found_cr_;
    bool found_lf_;
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

template<class CharType, class TraitsType = std::char_traits<CharType> >
inline std::basic_ostream<CharType, TraitsType>&
manage_blank_lines(std::basic_ostream<CharType, TraitsType>& s) {
    indent_filter* filter((indent_filter*)s.pword(xdent<int>()()));
    if (filter)
        filter->manage_blank_lines();
    return s;
}


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
    basic_negative_indenter_scope(std::basic_ostream<CharType, TraitsType>& s,
        const bool reset_management = false)
        : stream_(s), started_at_zero_(false) {

        indent_filter* filter((indent_filter*)s.pword(xdent<int>()()));
        if (filter) {
            started_at_zero_ = filter->indentation_level() == 0;
            filter->decrement_indentation_level(reset_management);
        }
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

}

/**
 * @brief Helper operators that wrap the manipulators.
 *
 * This idea was copied from Larry Evans's code.
 */
/**@{*/
template<class char_type, class traits_type>
inline std::basic_ostream<char_type, traits_type>&
operator++(std::basic_ostream<char_type, traits_type>& s) {
    s << dogen::text::formatters::indent_in;
    return s;
}

template<class char_type, class traits_type>
inline std::basic_ostream<char_type, traits_type>&
operator--(std::basic_ostream<char_type, traits_type>& s) {
    s << dogen::text::formatters::indent_out;
    return s;
}
/**@}*/

#endif
