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
#ifndef DOGEN_SML_TYPES_PRIMITIVE_HPP
#define DOGEN_SML_TYPES_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/sml/serialization/primitive_fwd_ser.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a type that is built-in to the language.
 */
class primitive final {
public:
    primitive(const primitive&) = default;
    primitive(primitive&&) = default;
    ~primitive() = default;

public:
    primitive();

public:
    primitive(
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, primitive& v, unsigned int version);

public:
    /**
     * @brief Qualified name for the type.
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief What to do with this primitive in terms of code generation.
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

    /**
     * @brief Doxygen documentation for the type.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const primitive& rhs) const;
    bool operator!=(const primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(primitive& other) noexcept;
    primitive& operator=(primitive other);

private:
    dogen::sml::qname name_;
    dogen::sml::generation_types generation_type_;
    std::string documentation_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::primitive& lhs,
    dogen::sml::primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
