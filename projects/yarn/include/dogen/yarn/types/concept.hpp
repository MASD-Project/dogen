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
#ifndef DOGEN_YARN_TYPES_CONCEPT_HPP
#define DOGEN_YARN_TYPES_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <unordered_map>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/serialization/concept_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Represents a concept in the generic programming sense.
 *
 * In generic programming, a concept is a description of supported operations on
 * a type, including syntax and semantics. In this way, concepts are related to
 * abstract base classes but concepts do not require a subtype relationship.
 *
 * A concept is used for two reasons in terms of modeling:
 *
 * @li to model the set of requirements a generic method has on a type;
 * @li to model commonalities between types that are not expressed using
 * generalisation relationships.
 */
class concept final : public dogen::yarn::element {
public:
    concept(const concept&) = default;
    concept(concept&&) = default;

public:
    concept();

    virtual ~concept() noexcept { }

public:
    concept(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const std::list<dogen::yarn::attribute>& all_attributes,
        const std::list<dogen::yarn::attribute>& local_attributes,
        const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes,
        const bool is_immutable,
        const bool is_fluent,
        const std::list<dogen::yarn::name>& refines,
        const bool is_child);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::concept& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::concept& v, unsigned int version);

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
     * @brief All attributes associated with this type.
     *
     * This is a union of the following sets:
     *
     * @li the set of all attributes obtained via inheritance relationships;
     * @li the set of all attributes obtained via modeling of concepts, including any refinements;
     * @li the set of all attributes directly associated with the type (local).
     *
     * The first and third sets are cached in this object. The second isn't as we do
     * not have a need for it.
     */
    /**@{*/
    const std::list<dogen::yarn::attribute>& all_attributes() const;
    std::list<dogen::yarn::attribute>& all_attributes();
    void all_attributes(const std::list<dogen::yarn::attribute>& v);
    void all_attributes(const std::list<dogen::yarn::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::yarn::attribute>& local_attributes() const;
    std::list<dogen::yarn::attribute>& local_attributes();
    void local_attributes(const std::list<dogen::yarn::attribute>& v);
    void local_attributes(const std::list<dogen::yarn::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes obtained via inheritance, by parent name.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes() const;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes();
    void inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& v);
    void inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >&& v);
    /**@}*/

    /**
     * @brief If true, do not generate setters for the element's attributes.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, generate fluent setters.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief List of concepts that this concept is a refinement of.
     *
     * A concept B is said to refine a concept A if B has all of the same type
     * requirements as A and possibly more. It is the generalisation relationship
     * applied to concepts.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& refines() const;
    std::list<dogen::yarn::name>& refines();
    void refines(const std::list<dogen::yarn::name>& v);
    void refines(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief If true, the concept has at least one parent.
     *
     * Children are concepts that refine at least one other concept.
     */
    /**@{*/
    bool is_child() const;
    void is_child(const bool v);
    /**@}*/

public:
    bool operator==(const concept& rhs) const;
    bool operator!=(const concept& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(concept& other) noexcept;
    concept& operator=(concept other);

private:
    std::list<dogen::yarn::attribute> all_attributes_;
    std::list<dogen::yarn::attribute> local_attributes_;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> > inherited_attributes_;
    bool is_immutable_;
    bool is_fluent_;
    std::list<dogen::yarn::name> refines_;
    bool is_child_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::concept& lhs,
    dogen::yarn::concept& rhs) {
    lhs.swap(rhs);
}

}

#endif
