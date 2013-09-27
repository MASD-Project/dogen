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
#ifndef DOGEN_SML_TYPES_CONCEPT_HPP
#define DOGEN_SML_TYPES_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include <unordered_map>
#include "dogen/sml/serialization/concept_fwd_ser.hpp"
#include "dogen/sml/types/generation_types.hpp"
#include "dogen/sml/types/operation.hpp"
#include "dogen/sml/types/origin_types.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a concept, similar to the C++ definition.
 */
class concept final {
public:
    concept(const concept&) = default;
    concept(concept&&) = default;
    ~concept() = default;

public:
    concept();

public:
    concept(
        const std::list<dogen::sml::property>& properties,
        const std::string& documentation,
        const std::unordered_map<std::string, std::string>& simple_tags,
        const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const dogen::sml::origin_types& origin_type,
        const std::list<dogen::sml::operation>& operations,
        const std::list<dogen::sml::qname>& refines);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const concept& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, concept& v, unsigned int version);

public:
    /**
     * @brief State of this entity.
     *
     * Does not include inherited attributes.
     */
    /**@{*/
    const std::list<dogen::sml::property>& properties() const;
    std::list<dogen::sml::property>& properties();
    void properties(const std::list<dogen::sml::property>& v);
    void properties(const std::list<dogen::sml::property>&& v);
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
     * @brief Tags associated with the object, opaque to SML.
     *
     * Tags are in the format key-value pair.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& simple_tags() const;
    std::unordered_map<std::string, std::string>& simple_tags();
    void simple_tags(const std::unordered_map<std::string, std::string>& v);
    void simple_tags(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

    /**
     * @brief Tags associated with the object, opaque to SML.
     *
     * Tags are in the format key, value 1, ... value n. Order of defintion is respected.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<std::string> >& complex_tags() const;
    std::unordered_map<std::string, std::list<std::string> >& complex_tags();
    void complex_tags(const std::unordered_map<std::string, std::list<std::string> >& v);
    void complex_tags(const std::unordered_map<std::string, std::list<std::string> >&& v);
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
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::sml::generation_types generation_type() const;
    void generation_type(const dogen::sml::generation_types& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::sml::origin_types origin_type() const;
    void origin_type(const dogen::sml::origin_types& v);
    /**@}*/

    /**
     * @brief Operations (methods) that can be executed.
     */
    /**@{*/
    const std::list<dogen::sml::operation>& operations() const;
    std::list<dogen::sml::operation>& operations();
    void operations(const std::list<dogen::sml::operation>& v);
    void operations(const std::list<dogen::sml::operation>&& v);
    /**@}*/

    /**
     * @brief List of concepts that this concept is a refinement of.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& refines() const;
    std::list<dogen::sml::qname>& refines();
    void refines(const std::list<dogen::sml::qname>& v);
    void refines(const std::list<dogen::sml::qname>&& v);
    /**@}*/

public:
    bool operator==(const concept& rhs) const;
    bool operator!=(const concept& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(concept& other) noexcept;
    concept& operator=(concept other);

private:
    std::list<dogen::sml::property> properties_;
    std::string documentation_;
    std::unordered_map<std::string, std::string> simple_tags_;
    std::unordered_map<std::string, std::list<std::string> > complex_tags_;
    dogen::sml::qname name_;
    dogen::sml::generation_types generation_type_;
    dogen::sml::origin_types origin_type_;
    std::list<dogen::sml::operation> operations_;
    std::list<dogen::sml::qname> refines_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::concept& lhs,
    dogen::sml::concept& rhs) {
    lhs.swap(rhs);
}

}

#endif
