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
#ifndef DOGEN_YARN_TYPES_ATTRIBUTE_HPP
#define DOGEN_YARN_TYPES_ATTRIBUTE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/annotations/types/object.hpp"
#include "dogen/yarn/serialization/attribute_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents an attribute in an object.
 */
class attribute final {
public:
    attribute(const attribute&) = default;
    attribute(attribute&&) = default;
    ~attribute() = default;

public:
    attribute();

public:
    attribute(
        const std::string& documentation,
        const dogen::annotations::object& annotation,
        const dogen::yarn::name& name,
        const std::string& unparsed_type,
        const dogen::yarn::name_tree& parsed_type,
        const bool is_immutable,
        const bool is_fluent);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::attribute& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::attribute& v, unsigned int version);

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
     * @brief Annotation for this element.
     */
    /**@{*/
    const dogen::annotations::object& annotation() const;
    dogen::annotations::object& annotation();
    void annotation(const dogen::annotations::object& v);
    void annotation(const dogen::annotations::object&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief Original type name as it appeared in the source, without any parsing.
     *
     * Name must be in one of the supported notations.
     */
    /**@{*/
    const std::string& unparsed_type() const;
    std::string& unparsed_type();
    void unparsed_type(const std::string& v);
    void unparsed_type(const std::string&& v);
    /**@}*/

    /**
     * @brief Tree of names that represent the type of the attribute, after suitable parsing.
     */
    /**@{*/
    const dogen::yarn::name_tree& parsed_type() const;
    dogen::yarn::name_tree& parsed_type();
    void parsed_type(const dogen::yarn::name_tree& v);
    void parsed_type(const dogen::yarn::name_tree&& v);
    /**@}*/

    /**
     * @brief If true, the attribute can only be read but not set.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the attribute's setter will return the object iteself.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

public:
    bool operator==(const attribute& rhs) const;
    bool operator!=(const attribute& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(attribute& other) noexcept;
    attribute& operator=(attribute other);

private:
    std::string documentation_;
    dogen::annotations::object annotation_;
    dogen::yarn::name name_;
    std::string unparsed_type_;
    dogen::yarn::name_tree parsed_type_;
    bool is_immutable_;
    bool is_fluent_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::attribute& lhs,
    dogen::yarn::attribute& rhs) {
    lhs.swap(rhs);
}

}

#endif
