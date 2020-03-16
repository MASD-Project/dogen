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
#ifndef DOGEN_LOGICAL_TYPES_META_MODEL_DECORATION_MODELINE_HPP
#define DOGEN_LOGICAL_TYPES_META_MODEL_DECORATION_MODELINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/meta_model/element.hpp"
#include "dogen.logical/types/meta_model/technical_space.hpp"
#include "dogen.logical/types/meta_model/decoration/editor.hpp"
#include "dogen.logical/types/meta_model/decoration/modeline_field.hpp"
#include "dogen.logical/types/meta_model/decoration/modeline_location.hpp"

namespace dogen::logical::meta_model::decoration {

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
class modeline final : public dogen::logical::meta_model::element {
public:
    modeline(const modeline&) = default;
    modeline(modeline&&) = default;

public:
    modeline();

    virtual ~modeline() noexcept { }

public:
    modeline(
        const dogen::logical::meta_model::name& name,
        const std::string& documentation,
        const dogen::logical::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::logical::meta_model::name& meta_name,
        const dogen::logical::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const std::unordered_map<std::string, dogen::logical::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::logical::meta_model::technical_space, boost::optional<dogen::logical::meta_model::decoration::element_properties> >& decoration,
        const dogen::logical::meta_model::decoration::editor editor,
        const dogen::logical::meta_model::decoration::modeline_location location,
        const std::list<dogen::logical::meta_model::decoration::modeline_field>& fields,
        const dogen::logical::meta_model::technical_space technical_space);

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
    dogen::logical::meta_model::decoration::editor editor() const;
    void editor(const dogen::logical::meta_model::decoration::editor v);
    /**@}*/

    /**
     * @brief Where to place the modeline.
     */
    /**@{*/
    dogen::logical::meta_model::decoration::modeline_location location() const;
    void location(const dogen::logical::meta_model::decoration::modeline_location v);
    /**@}*/

    /**
     * @brief List of all the parameters in the preamble, in order of appearence.
     */
    /**@{*/
    const std::list<dogen::logical::meta_model::decoration::modeline_field>& fields() const;
    std::list<dogen::logical::meta_model::decoration::modeline_field>& fields();
    void fields(const std::list<dogen::logical::meta_model::decoration::modeline_field>& v);
    void fields(const std::list<dogen::logical::meta_model::decoration::modeline_field>&& v);
    /**@}*/

    /**
     * @brief Technical space that this modeline targets.
     */
    /**@{*/
    dogen::logical::meta_model::technical_space technical_space() const;
    void technical_space(const dogen::logical::meta_model::technical_space v);
    /**@}*/

public:
    bool operator==(const modeline& rhs) const;
    bool operator!=(const modeline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::meta_model::element& other) const override;

public:
    void swap(modeline& other) noexcept;
    modeline& operator=(modeline other);

private:
    dogen::logical::meta_model::decoration::editor editor_;
    dogen::logical::meta_model::decoration::modeline_location location_;
    std::list<dogen::logical::meta_model::decoration::modeline_field> fields_;
    dogen::logical::meta_model::technical_space technical_space_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::meta_model::decoration::modeline& lhs,
    dogen::logical::meta_model::decoration::modeline& rhs) {
    lhs.swap(rhs);
}

}

#endif
