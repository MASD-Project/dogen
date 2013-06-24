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
#ifndef DOGEN_SML_TYPES_TYPE_HPP
#define DOGEN_SML_TYPES_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include <utility>
#include <vector>
#include "dogen/sml/serialization/type_fwd_ser.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a type within the type system.
 */
class type {
public:
    type(const type&) = default;
    type(type&&) = default;

public:
    type();

    virtual ~type() noexcept = 0;

public:
    type(
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const type& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, type& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammer of the comment processing tools
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
     * @brief Associated generic parameters which may be opaque.
     */
    /**@{*/
    const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters() const;
    std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters();
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >& v);
    void implementation_specific_parameters(const std::vector<std::pair<std::string, std::string> >&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     *
     */
    /**@{*/
    const dogen::sml::qname& name() const;
    dogen::sml::qname& name();
    void name(const dogen::sml::qname& v);
    void name(const dogen::sml::qname&& v);
    /**@}*/

    /**
     * @brief What to do with this pod in terms of code generation,
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

protected:
    bool compare(const type& rhs) const;
public:
    virtual bool equals(const type& other) const = 0;

protected:
    void swap(type& other) noexcept;

private:
    std::string documentation_;
    std::vector<std::pair<std::string, std::string> > implementation_specific_parameters_;
    dogen::sml::qname name_;
    dogen::sml::generation_types generation_type_;
};

inline type::~type() noexcept { }

inline bool operator==(const type& lhs, const type& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
