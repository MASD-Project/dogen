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
#include <list>
#include <string>
#include "dogen/cpp/serialization/entity_fwd_ser.hpp"
#include "dogen/cpp/types/entity_visitor.hpp"
#include "dogen/formatters/types/entity.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Top-level formatable entity in the C++ model.
 */
class entity : public formatters::entity {
public:
    entity() = default;
    entity(const entity&) = default;
    entity(entity&&) = default;
    virtual ~entity() noexcept;

public:
    entity(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces);

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
     * @brief Name of the entity.
     *
     * Must be valid according to the rules for C++ names.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

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
     * @brief List of all namespaces containing the type. Last namespace is the target.
     */
    /**@{*/
    const std::list<std::string>& namespaces() const;
    std::list<std::string>& namespaces();
    void namespaces(const std::list<std::string>& v);
    void namespaces(const std::list<std::string>&& v);
    /**@}*/

protected:
    bool compare(const entity& rhs) const;
public:
    virtual bool equals(const entity& other) const = 0;

protected:
    void swap(entity& other) noexcept;

private:
    std::string name_;
    std::string documentation_;
    std::list<std::string> namespaces_;
};

inline entity::~entity() noexcept { }

inline bool operator==(const entity& lhs, const entity& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
