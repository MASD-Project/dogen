/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INDENTER_HPP
#define DOGEN_GENERATOR_BACKENDS_CPP_FORMATTERS_CPP_INDENTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>

namespace dogen {
namespace generator {
namespace backends {
namespace cpp {
namespace formatters {

class cpp_indenter {
public:
    cpp_indenter(const cpp_indenter&) = default;
    ~cpp_indenter() = default;
    cpp_indenter(cpp_indenter&&) = default;
    cpp_indenter& operator=(const cpp_indenter&) = default;

public:
    cpp_indenter() : indent_level_(0) {}

public:
    cpp_indenter& operator++() {
        ++indent_level_;
        return *this;
    }

    cpp_indenter& operator--() {
        if (indent_level_ > 0)
            --indent_level_;
        return *this;
    }

    bool empty() const { return indent_level_ == 0; }
    void to_stream(std::ostream& stream) const;

private:
    unsigned int indent_level_;
};

class cpp_positive_indenter_scope {
public:
    cpp_positive_indenter_scope(cpp_indenter& i) : indenter_(i) { ++indenter_; }
    ~cpp_positive_indenter_scope() { --indenter_; }

private:
    cpp_indenter& indenter_;
};

class cpp_negative_indenter_scope {
public:
    cpp_negative_indenter_scope(cpp_indenter& i) :
    indenter_(i), started_empty_(i.empty()) {
        --indenter_;
    }

    ~cpp_negative_indenter_scope() {
        if (!started_empty_)
            ++indenter_;
    }

private:
    cpp_indenter& indenter_;
    const bool started_empty_;
};

std::ostream& operator<<(std::ostream& stream, cpp_indenter indenter);

} } } } }

#endif
