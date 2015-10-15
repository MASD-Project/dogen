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
#ifndef DOGEN_YARN_TYPES_PROPERTY_HPP
#define DOGEN_YARN_TYPES_PROPERTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/yarn/types/nested_name.hpp"
#include "dogen/yarn/serialization/property_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents an attribute in an object.
 */
class property final {
public:
    property(const property&) = default;
    property(property&&) = default;
    ~property() = default;

public:
    property();

public:
    property(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const std::string& name,
<<<<<<< 24090da86c0fe4a597dfa9c7b5e3ed377e4b57f4:projects/tack/include/dogen/tack/types/property.hpp
        const dogen::tack::nested_name& type,
        const std::string& unparsed_type,
=======
        const dogen::yarn::nested_name& type,
>>>>>>> rename tack to yarn:projects/yarn/include/dogen/yarn/types/property.hpp
        const bool is_immutable,
        const bool is_fluent);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const property& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, property& v, unsigned int version);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the programming language in question, e.g. Doxygen for C++, JavaDoc
     * for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Dynamic extensions for this element.
     */
    /**@{*/
    const dogen::dynamic::object& extensions() const;
    dogen::dynamic::object& extensions();
    void extensions(const dogen::dynamic::object& v);
    void extensions(const dogen::dynamic::object&& v);
    /**@}*/

    /**
     * @brief Name of the property.
     *
     * Must only contain characters that can be used for identifiers in the target backend.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name for the type of the property.
     */
    /**@{*/
    const dogen::yarn::nested_name& type() const;
    dogen::yarn::nested_name& type();
    void type(const dogen::yarn::nested_name& v);
    void type(const dogen::yarn::nested_name&& v);
    /**@}*/

    /**
     * @brief Original type as it appeared in the source, without any parsing.
     *
     * Type must be in one of the supported notations.
     */
    /**@{*/
    const std::string& unparsed_type() const;
    std::string& unparsed_type();
    void unparsed_type(const std::string& v);
    void unparsed_type(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, the property can only be read but not set.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the property's setter will return the object iteself.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

public:
    bool operator==(const property& rhs) const;
    bool operator!=(const property& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(property& other) noexcept;
    property& operator=(property other);

private:
    std::string documentation_;
    dogen::dynamic::object extensions_;
    std::string name_;
<<<<<<< 24090da86c0fe4a597dfa9c7b5e3ed377e4b57f4:projects/tack/include/dogen/tack/types/property.hpp
    dogen::tack::nested_name type_;
    std::string unparsed_type_;
=======
    dogen::yarn::nested_name type_;
>>>>>>> rename tack to yarn:projects/yarn/include/dogen/yarn/types/property.hpp
    bool is_immutable_;
    bool is_fluent_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::property& lhs,
    dogen::yarn::property& rhs) {
    lhs.swap(rhs);
}

}

#endif
