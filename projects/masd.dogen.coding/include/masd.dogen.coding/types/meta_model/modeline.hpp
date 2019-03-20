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
#include <string>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/editor.hpp"
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
class modeline final {
public:
    modeline(const modeline&) = default;
    modeline(modeline&&) = default;
    ~modeline() = default;

public:
    modeline();

public:
    modeline(
        const std::string& name,
        const masd::dogen::coding::meta_model::editor editor,
        const masd::dogen::coding::meta_model::modeline_location location,
        const std::list<masd::dogen::coding::meta_model::modeline_field>& fields);

public:
    /**
     * @brief Name of the modeline. Must be unique within a group.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

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

public:
    bool operator==(const modeline& rhs) const;
    bool operator!=(const modeline& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(modeline& other) noexcept;
    modeline& operator=(modeline other);

private:
    std::string name_;
    masd::dogen::coding::meta_model::editor editor_;
    masd::dogen::coding::meta_model::modeline_location location_;
    std::list<masd::dogen::coding::meta_model::modeline_field> fields_;
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
