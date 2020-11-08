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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_HELPER_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/physical/text_templating.hpp"

namespace dogen::logical::entities::physical {

class helper final : public dogen::logical::entities::element {
public:
    helper(const helper&) = default;
    helper(helper&&) = default;

public:
    helper();

    virtual ~helper() noexcept { }

public:
    helper(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::helper_properties>& helper_properties,
        const std::string& id,
        const dogen::identification::entities::technical_space major_technical_space,
        const std::string& part_id,
        const std::string& backend_name,
        const std::string& facet_name,
        const std::string& family,
        const std::list<std::string>& owning_formatters,
        const std::list<std::string>& owning_facets,
        const std::string& helper_name,
        const dogen::logical::entities::physical::text_templating& text_templating);

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
     * @brief Unique identifier in physical space for this element.
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Technical space to which this physical element belongs to.
     */
    /**@{*/
    dogen::identification::entities::technical_space major_technical_space() const;
    void major_technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

    const std::string& part_id() const;
    std::string& part_id();
    void part_id(const std::string& v);
    void part_id(const std::string&& v);

    const std::string& backend_name() const;
    std::string& backend_name();
    void backend_name(const std::string& v);
    void backend_name(const std::string&& v);

    const std::string& facet_name() const;
    std::string& facet_name();
    void facet_name(const std::string& v);
    void facet_name(const std::string&& v);

    const std::string& family() const;
    std::string& family();
    void family(const std::string& v);
    void family(const std::string&& v);

    const std::list<std::string>& owning_formatters() const;
    std::list<std::string>& owning_formatters();
    void owning_formatters(const std::list<std::string>& v);
    void owning_formatters(const std::list<std::string>&& v);

    const std::list<std::string>& owning_facets() const;
    std::list<std::string>& owning_facets();
    void owning_facets(const std::list<std::string>& v);
    void owning_facets(const std::list<std::string>&& v);

    const std::string& helper_name() const;
    std::string& helper_name();
    void helper_name(const std::string& v);
    void helper_name(const std::string&& v);

    const dogen::logical::entities::physical::text_templating& text_templating() const;
    dogen::logical::entities::physical::text_templating& text_templating();
    void text_templating(const dogen::logical::entities::physical::text_templating& v);
    void text_templating(const dogen::logical::entities::physical::text_templating&& v);

public:
    bool operator==(const helper& rhs) const;
    bool operator!=(const helper& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(helper& other) noexcept;
    helper& operator=(helper other);

private:
    std::string id_;
    dogen::identification::entities::technical_space major_technical_space_;
    std::string part_id_;
    std::string backend_name_;
    std::string facet_name_;
    std::string family_;
    std::list<std::string> owning_formatters_;
    std::list<std::string> owning_facets_;
    std::string helper_name_;
    dogen::logical::entities::physical::text_templating text_templating_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::helper& lhs,
    dogen::logical::entities::physical::helper& rhs) {
    lhs.swap(rhs);
}

}

#endif
