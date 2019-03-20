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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_VISITOR_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <boost/optional.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"

namespace masd::dogen::coding::meta_model {

/**
 * @brief Represents a visitor in the GOF visitor design pattern.
 */
class visitor final : public masd::dogen::coding::meta_model::element {
public:
    visitor() = default;
    visitor(const visitor&) = default;

    virtual ~visitor() noexcept { }

public:
    visitor(visitor&& rhs);

public:
    visitor(
        const masd::dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const masd::dogen::annotations::annotation& annotation,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const masd::dogen::coding::meta_model::name& meta_name,
        const bool is_element_extension,
        const masd::dogen::extraction::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<masd::dogen::coding::meta_model::local_decoration>& decoration,
        const std::list<masd::dogen::coding::meta_model::name>& visits,
        const boost::optional<masd::dogen::coding::meta_model::name>& parent);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Elements that are visitable by the visitor.
     */
    /**@{*/
    const std::list<masd::dogen::coding::meta_model::name>& visits() const;
    std::list<masd::dogen::coding::meta_model::name>& visits();
    void visits(const std::list<masd::dogen::coding::meta_model::name>& v);
    void visits(const std::list<masd::dogen::coding::meta_model::name>&& v);
    /**@}*/

    const boost::optional<masd::dogen::coding::meta_model::name>& parent() const;
    boost::optional<masd::dogen::coding::meta_model::name>& parent();
    void parent(const boost::optional<masd::dogen::coding::meta_model::name>& v);
    void parent(const boost::optional<masd::dogen::coding::meta_model::name>&& v);

public:
    bool operator==(const visitor& rhs) const;
    bool operator!=(const visitor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::element& other) const override;

public:
    void swap(visitor& other) noexcept;
    visitor& operator=(visitor other);

private:
    std::list<masd::dogen::coding::meta_model::name> visits_;
    boost::optional<masd::dogen::coding::meta_model::name> parent_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::visitor& lhs,
    masd::dogen::coding::meta_model::visitor& rhs) {
    lhs.swap(rhs);
}

}

#endif
