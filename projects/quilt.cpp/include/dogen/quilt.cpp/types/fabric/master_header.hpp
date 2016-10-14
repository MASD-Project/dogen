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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_MASTER_HEADER_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_MASTER_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/serialization/fabric/master_header_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class master_header final : public dogen::yarn::element {
public:
    master_header() = default;
    master_header(const master_header&) = default;
    master_header(master_header&&) = default;

    virtual ~master_header() noexcept { }

public:
    master_header(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::unordered_set<std::string>& stereotypes,
        const bool is_element_extension,
        const std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > >& inclusion_by_facet);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::master_header& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::master_header& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > >& inclusion_by_facet() const;
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > >& inclusion_by_facet();
    void inclusion_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > >& v);
    void inclusion_by_facet(const std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > >&& v);

public:
    bool operator==(const master_header& rhs) const;
    bool operator!=(const master_header& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(master_header& other) noexcept;
    master_header& operator=(master_header other);

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::list<dogen::yarn::name> > > inclusion_by_facet_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::master_header& lhs,
    dogen::quilt::cpp::fabric::master_header& rhs) {
    lhs.swap(rhs);
}

}

#endif
