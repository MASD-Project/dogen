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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_FORMATTABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/meta_model/element_fwd.hpp"
#include "dogen.generation.cpp/types/formattables/element_properties.hpp"

namespace dogen::generation::cpp::formattables {

class formattable final {
public:
    formattable() = default;
    formattable(const formattable&) = default;
    formattable(formattable&&) = default;
    ~formattable() = default;

public:
    formattable(
        const boost::shared_ptr<dogen::logical::meta_model::element>& element,
        const dogen::generation::cpp::formattables::element_properties& element_properties);

public:
    const boost::shared_ptr<dogen::logical::meta_model::element>& element() const;
    boost::shared_ptr<dogen::logical::meta_model::element>& element();
    void element(const boost::shared_ptr<dogen::logical::meta_model::element>& v);
    void element(const boost::shared_ptr<dogen::logical::meta_model::element>&& v);

    const dogen::generation::cpp::formattables::element_properties& element_properties() const;
    dogen::generation::cpp::formattables::element_properties& element_properties();
    void element_properties(const dogen::generation::cpp::formattables::element_properties& v);
    void element_properties(const dogen::generation::cpp::formattables::element_properties&& v);

public:
    bool operator==(const formattable& rhs) const;
    bool operator!=(const formattable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(formattable& other) noexcept;
    formattable& operator=(formattable other);

private:
    boost::shared_ptr<dogen::logical::meta_model::element> element_;
    dogen::generation::cpp::formattables::element_properties element_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::formattables::formattable& lhs,
    dogen::generation::cpp::formattables::formattable& rhs) {
    lhs.swap(rhs);
}

}

#endif
