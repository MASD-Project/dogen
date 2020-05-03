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
#ifndef DOGEN_TEXT_TYPES_FORMATTERS_BOILERPLATE_PROPERTIES_HPP
#define DOGEN_TEXT_TYPES_FORMATTERS_BOILERPLATE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/technical_space.hpp"

namespace dogen::text::formatters {

class boilerplate_properties final {
public:
    boilerplate_properties(const boilerplate_properties&) = default;
    boilerplate_properties(boilerplate_properties&&) = default;
    ~boilerplate_properties() = default;

public:
    boilerplate_properties();

public:
    boilerplate_properties(
        const std::string& preamble,
        const std::string& postamble,
        const std::list<std::string>& dependencies,
        const std::string& header_guard,
        const dogen::logical::entities::technical_space technical_space,
        const bool generate_preamble,
        const bool generate_header_guards);

public:
    const std::string& preamble() const;
    std::string& preamble();
    void preamble(const std::string& v);
    void preamble(const std::string&& v);

    const std::string& postamble() const;
    std::string& postamble();
    void postamble(const std::string& v);
    void postamble(const std::string&& v);

    const std::list<std::string>& dependencies() const;
    std::list<std::string>& dependencies();
    void dependencies(const std::list<std::string>& v);
    void dependencies(const std::list<std::string>&& v);

    const std::string& header_guard() const;
    std::string& header_guard();
    void header_guard(const std::string& v);
    void header_guard(const std::string&& v);

    dogen::logical::entities::technical_space technical_space() const;
    void technical_space(const dogen::logical::entities::technical_space v);

    bool generate_preamble() const;
    void generate_preamble(const bool v);

    bool generate_header_guards() const;
    void generate_header_guards(const bool v);

public:
    bool operator==(const boilerplate_properties& rhs) const;
    bool operator!=(const boilerplate_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(boilerplate_properties& other) noexcept;
    boilerplate_properties& operator=(boilerplate_properties other);

private:
    std::string preamble_;
    std::string postamble_;
    std::list<std::string> dependencies_;
    std::string header_guard_;
    dogen::logical::entities::technical_space technical_space_;
    bool generate_preamble_;
    bool generate_header_guards_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::formatters::boilerplate_properties& lhs,
    dogen::text::formatters::boilerplate_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
