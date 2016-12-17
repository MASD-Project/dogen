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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FABRIC_GENERATOR_HELPER_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FABRIC_GENERATOR_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.csharp/serialization/fabric/generator_helper_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

class generator_helper final : public dogen::yarn::element {
public:
    generator_helper() = default;
    generator_helper(const generator_helper&) = default;
    generator_helper(generator_helper&&) = default;

    virtual ~generator_helper() noexcept { }

public:
    generator_helper(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::csharp::fabric::generator_helper& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::csharp::fabric::generator_helper& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const generator_helper& rhs) const;
    bool operator!=(const generator_helper& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(generator_helper& other) noexcept;
    generator_helper& operator=(generator_helper other);

};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::csharp::fabric::generator_helper& lhs,
    dogen::quilt::csharp::fabric::generator_helper& rhs) {
    lhs.swap(rhs);
}

}

#endif
