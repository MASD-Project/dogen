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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_MODELINE_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_MODELINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/editor.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_field.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_location.hpp"

namespace masd::dogen::coding::meta_model {

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
class modeline final : public masd::dogen::coding::meta_model::element {
public:
    modeline(const modeline&) = default;
    modeline(modeline&&) = default;

public:
    modeline();

    virtual ~modeline() noexcept { }

public:
    modeline(
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
        const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
        const masd::dogen::coding::meta_model::editor editor,
        const masd::dogen::coding::meta_model::modeline_location location,
        const std::list<masd::dogen::coding::meta_model::modeline_field>& fields,
        const std::list<std::string>& applicable_meta_elements);

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
    masd::dogen::coding::meta_model::editor editor() const;
    void editor(const masd::dogen::coding::meta_model::editor v);
    /**@}*/

    /**
     * @brief Where to place the modeline.
     */
    /**@{*/
    masd::dogen::coding::meta_model::modeline_location location() const;
    void location(const masd::dogen::coding::meta_model::modeline_location v);
    /**@}*/

    /**
     * @brief List of all the parameters in the preamble, in order of appearence.
     */
    /**@{*/
    const std::list<masd::dogen::coding::meta_model::modeline_field>& fields() const;
    std::list<masd::dogen::coding::meta_model::modeline_field>& fields();
    void fields(const std::list<masd::dogen::coding::meta_model::modeline_field>& v);
    void fields(const std::list<masd::dogen::coding::meta_model::modeline_field>&& v);
    /**@}*/

    /**
     * @brief Meta-names for all of the elements to which this modeline can be applied to.
     */
    /**@{*/
    const std::list<std::string>& applicable_meta_elements() const;
    std::list<std::string>& applicable_meta_elements();
    void applicable_meta_elements(const std::list<std::string>& v);
    void applicable_meta_elements(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const modeline& rhs) const;
    bool operator!=(const modeline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::element& other) const override;

public:
    void swap(modeline& other) noexcept;
    modeline& operator=(modeline other);

private:
    masd::dogen::coding::meta_model::editor editor_;
    masd::dogen::coding::meta_model::modeline_location location_;
    std::list<masd::dogen::coding::meta_model::modeline_field> fields_;
    std::list<std::string> applicable_meta_elements_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::modeline& lhs,
    masd::dogen::coding::meta_model::modeline& rhs) {
    lhs.swap(rhs);
}

}

#endif
