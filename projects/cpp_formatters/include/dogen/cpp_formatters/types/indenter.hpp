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
#ifndef DOGEN_CPP_FOMATTERS_TYPES_INDENTER_HPP
#define DOGEN_CPP_FOMATTERS_TYPES_INDENTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace cpp_formatters {

class indenter {
public:
    indenter(const indenter&) = default;
    ~indenter() = default;
    indenter(indenter&&) = default;
    indenter& operator=(const indenter&) = default;

public:
    indenter() : indent_level_(0) {}

public:
    indenter& operator++() {
        ++indent_level_;
        return *this;
    }

    indenter& operator--() {
        if (indent_level_ > 0)
            --indent_level_;
        return *this;
    }

    bool empty() const { return indent_level_ == 0; }
    void to_stream(std::ostream& stream) const;

private:
    unsigned int indent_level_;
};

class positive_indenter_scope {
public:
    positive_indenter_scope(indenter& i) : indenter_(i) { ++indenter_; }
    ~positive_indenter_scope() { --indenter_; }

private:
    indenter& indenter_;
};

class negative_indenter_scope {
public:
    negative_indenter_scope(indenter& i) :
    indenter_(i), started_empty_(i.empty()) {
        --indenter_;
    }

    ~negative_indenter_scope() {
        if (!started_empty_)
            ++indenter_;
    }

private:
    indenter& indenter_;
    const bool started_empty_;
};

std::ostream& operator<<(std::ostream& stream, indenter indenter);

} }

#endif
