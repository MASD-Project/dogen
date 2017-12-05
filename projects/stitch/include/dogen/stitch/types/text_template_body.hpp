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
#ifndef DOGEN_STITCH_TYPES_TEXT_TEMPLATE_BODY_HPP
#define DOGEN_STITCH_TYPES_TEXT_TEMPLATE_BODY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/stitch/types/line.hpp"
#include "dogen/stitch/serialization/text_template_body_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class text_template_body final {
public:
    text_template_body() = default;
    text_template_body(const text_template_body&) = default;
    text_template_body(text_template_body&&) = default;
    ~text_template_body() = default;

public:
    text_template_body(
        const std::list<std::pair<std::string, std::string> >& tagged_values,
        const std::list<dogen::stitch::line>& lines);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::stitch::text_template_body& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::stitch::text_template_body& v, unsigned int version);

public:
    const std::list<std::pair<std::string, std::string> >& tagged_values() const;
    std::list<std::pair<std::string, std::string> >& tagged_values();
    void tagged_values(const std::list<std::pair<std::string, std::string> >& v);
    void tagged_values(const std::list<std::pair<std::string, std::string> >&& v);

    const std::list<dogen::stitch::line>& lines() const;
    std::list<dogen::stitch::line>& lines();
    void lines(const std::list<dogen::stitch::line>& v);
    void lines(const std::list<dogen::stitch::line>&& v);

public:
    bool operator==(const text_template_body& rhs) const;
    bool operator!=(const text_template_body& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template_body& other) noexcept;
    text_template_body& operator=(text_template_body other);

private:
    std::list<std::pair<std::string, std::string> > tagged_values_;
    std::list<dogen::stitch::line> lines_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::text_template_body& lhs,
    dogen::stitch::text_template_body& rhs) {
    lhs.swap(rhs);
}

}

#endif
