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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_MODELINE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_MODELINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/decoration/editor.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/entities/decoration/modeline_field.hpp"
#include "dogen.logical/types/entities/decoration/modeline_location.hpp"

namespace dogen::logical::entities::decoration {

/**
 * @brief Groups all the fields representing editor variables for emacs, vi, etc.
 *
 * A field is a key-value pair (KVP), where name is the first element and its value
 * the second.
 *
 * Example: -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * In this particular case, both prefix and postfix are @e -*-; @e mode is the first
 * field name and its value is @e c++; the KVP separator is @e : and the field
 * separator is @e ;.
 */
class modeline final : public dogen::logical::entities::element {
public:
    modeline(const modeline&) = default;
    modeline(modeline&&) = default;

public:
    modeline();

    virtual ~modeline() noexcept { }

public:
    modeline(
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
        const dogen::logical::entities::decoration::editor editor,
        const dogen::logical::entities::decoration::modeline_location location,
        const std::list<dogen::logical::entities::decoration::modeline_field>& fields,
        const dogen::identification::entities::technical_space technical_space);

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
     * @brief The modeline will use the syntax for this editor.
     */
    /**@{*/
    dogen::logical::entities::decoration::editor editor() const;
    void editor(const dogen::logical::entities::decoration::editor v);
    /**@}*/

    /**
     * @brief Where to place the modeline.
     */
    /**@{*/
    dogen::logical::entities::decoration::modeline_location location() const;
    void location(const dogen::logical::entities::decoration::modeline_location v);
    /**@}*/

    /**
     * @brief List of all the parameters in the preamble, in order of appearence.
     */
    /**@{*/
    const std::list<dogen::logical::entities::decoration::modeline_field>& fields() const;
    std::list<dogen::logical::entities::decoration::modeline_field>& fields();
    void fields(const std::list<dogen::logical::entities::decoration::modeline_field>& v);
    void fields(const std::list<dogen::logical::entities::decoration::modeline_field>&& v);
    /**@}*/

    /**
     * @brief Technical space that this modeline targets.
     */
    /**@{*/
    dogen::identification::entities::technical_space technical_space() const;
    void technical_space(const dogen::identification::entities::technical_space v);
    /**@}*/

public:
    bool operator==(const modeline& rhs) const;
    bool operator!=(const modeline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(modeline& other) noexcept;
    modeline& operator=(modeline other);

private:
    dogen::logical::entities::decoration::editor editor_;
    dogen::logical::entities::decoration::modeline_location location_;
    std::list<dogen::logical::entities::decoration::modeline_field> fields_;
    dogen::identification::entities::technical_space technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::decoration::modeline& lhs,
    dogen::logical::entities::decoration::modeline& rhs) {
    lhs.swap(rhs);
}

}

#endif
