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
#ifndef DOGEN_CPP_TYPES_ENTITY_HPP
#define DOGEN_CPP_TYPES_ENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/cpp/serialization/entity_fwd_ser.hpp"
#include "dogen/cpp/types/entity_visitor.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Anything which can be in a scope.
 *
 *
 * Maps to the Member class in the Columbus schema, but in order to avoid
 * confusion with member variables, etc we renamed it to element.
 *
 * §3.1.1:
 *
 * An entity is a value, object, subobject, base class subobject, array element,
 * variable, function, instance of a function, enumerator, type, class member,
 * template, or namespace.
 */
class entity {
public:
    entity() = default;
    entity(const entity&) = default;
    entity(entity&&) = default;

    virtual ~entity() noexcept = 0;

public:
    explicit entity(const std::string& documentation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entity& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const = 0;
    virtual void accept(entity_visitor& v) const = 0;
    virtual void accept(const entity_visitor& v) = 0;
    virtual void accept(entity_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

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

protected:
    bool compare(const entity& rhs) const;
public:
    virtual bool equals(const entity& other) const = 0;

protected:
    void swap(entity& other) noexcept;

private:
    std::string documentation_;
};

inline entity::~entity() noexcept { }

inline bool operator==(const entity& lhs, const entity& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
