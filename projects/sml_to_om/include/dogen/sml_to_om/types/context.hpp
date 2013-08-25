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
#ifndef DOGEN_SML_TO_OM_TYPES_CONTEXT_HPP
#define DOGEN_SML_TO_OM_TYPES_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/om/types/cpp_project.hpp"
#include "dogen/sml_to_om/serialization/context_fwd_ser.hpp"

namespace dogen {
namespace sml_to_om {

class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    explicit context(const dogen::om::cpp_project& project);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, context& v, unsigned int version);

public:
    const dogen::om::cpp_project& project() const;
    dogen::om::cpp_project& project();
    void project(const dogen::om::cpp_project& v);
    void project(const dogen::om::cpp_project&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    dogen::om::cpp_project project_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml_to_om::context& lhs,
    dogen::sml_to_om::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
