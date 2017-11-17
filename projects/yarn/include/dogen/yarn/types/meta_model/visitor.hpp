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
#ifndef DOGEN_YARN_TYPES_META_MODEL_VISITOR_HPP
#define DOGEN_YARN_TYPES_META_MODEL_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/serialization/meta_model/visitor_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Represents a visitor in the GOF visitor design pattern.
 */
class visitor final : public dogen::yarn::meta_model::element {
public:
    visitor() = default;
    visitor(const visitor&) = default;

    virtual ~visitor() noexcept { }

public:
    visitor(visitor&& rhs);

public:
    visitor(
        const dogen::yarn::meta_model::name& name,
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::meta_model::origin_types origin_type,
        const boost::optional<dogen::yarn::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<dogen::yarn::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::yarn::meta_model::name& meta_name,
        const bool is_element_extension,
        const dogen::formatters::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::list<dogen::yarn::meta_model::name>& visits,
        const boost::optional<dogen::yarn::meta_model::name>& parent);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::visitor& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::visitor& v, unsigned int version);

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
    const std::list<dogen::yarn::meta_model::name>& visits() const;
    std::list<dogen::yarn::meta_model::name>& visits();
    void visits(const std::list<dogen::yarn::meta_model::name>& v);
    void visits(const std::list<dogen::yarn::meta_model::name>&& v);
    /**@}*/

    const boost::optional<dogen::yarn::meta_model::name>& parent() const;
    boost::optional<dogen::yarn::meta_model::name>& parent();
    void parent(const boost::optional<dogen::yarn::meta_model::name>& v);
    void parent(const boost::optional<dogen::yarn::meta_model::name>&& v);

public:
    bool operator==(const visitor& rhs) const;
    bool operator!=(const visitor& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::meta_model::element& other) const override;

public:
    void swap(visitor& other) noexcept;
    visitor& operator=(visitor other);

private:
    std::list<dogen::yarn::meta_model::name> visits_;
    boost::optional<dogen::yarn::meta_model::name> parent_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::visitor& lhs,
    dogen::yarn::meta_model::visitor& rhs) {
    lhs.swap(rhs);
}

}

#endif
