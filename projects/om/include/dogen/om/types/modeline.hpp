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
#ifndef DOGEN_OM_TYPES_MODELINE_HPP
#define DOGEN_OM_TYPES_MODELINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/om/serialization/modeline_fwd_ser.hpp"
#include "dogen/om/types/editors.hpp"
#include "dogen/om/types/modeline_field.hpp"
#include "dogen/om/types/modeline_locations.hpp"

namespace dogen {
namespace om {

/**
 * @brief Fields representing editor variables for emacs, vi, etc.
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
        const dogen::om::editors& editor,
        const dogen::om::modeline_locations& location,
        const std::list<dogen::om::modeline_field>& fields);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const modeline& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, modeline& v, unsigned int version);

public:
    /**
     * @brief The modeline will use the syntax for this editor.
     */
    /**@{*/
    dogen::om::editors editor() const;
    void editor(const dogen::om::editors& v);
    /**@}*/

    /**
     * @brief Where to place the modeline.
     */
    /**@{*/
    dogen::om::modeline_locations location() const;
    void location(const dogen::om::modeline_locations& v);
    /**@}*/

    /**
     * @brief List of all the parameters in the preamble, in order of appearence.
     */
    /**@{*/
    const std::list<dogen::om::modeline_field>& fields() const;
    std::list<dogen::om::modeline_field>& fields();
    void fields(const std::list<dogen::om::modeline_field>& v);
    void fields(const std::list<dogen::om::modeline_field>&& v);
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
    dogen::om::editors editor_;
    dogen::om::modeline_locations location_;
    std::list<dogen::om::modeline_field> fields_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::modeline& lhs,
    dogen::om::modeline& rhs) {
    lhs.swap(rhs);
}

}

#endif
