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
#ifndef DOGEN_DIA_TO_SML_TYPES_PROFILE_HPP
#define DOGEN_DIA_TO_SML_TYPES_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/dia_to_sml/serialization/profile_fwd_ser.hpp"

namespace dogen {
namespace dia_to_sml {

/**
 * @brief Provides a more useful view of processed objects.
 */
class profile final {
public:
    profile(const profile&) = default;
    profile(profile&&) = default;
    ~profile() = default;

public:
    profile();

public:
    profile(
        const bool is_uml_large_package,
        const bool is_uml_class,
        const bool is_uml_generalization,
        const bool is_uml_association,
        const bool is_uml_note,
        const bool is_uml_message,
        const bool is_uml_realization,
        const bool is_enumeration,
        const bool is_exception,
        const bool is_entity,
        const bool is_value,
        const bool is_service,
        const bool is_non_generatable,
        const bool is_versioned,
        const bool is_keyed,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_fluent,
        const bool is_aggregate_root,
        const bool is_string_table,
        const bool is_concept,
        const std::list<std::string>& unknown_stereotypes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, profile& v, unsigned int version);

public:
    /**
     * @brief If true, the underlying object is an UML large package.
     */
    /**@{*/
    bool is_uml_large_package() const;
    void is_uml_large_package(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML class.
     */
    /**@{*/
    bool is_uml_class() const;
    void is_uml_class(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML generalisation.
     */
    /**@{*/
    bool is_uml_generalization() const;
    void is_uml_generalization(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML association.
     */
    /**@{*/
    bool is_uml_association() const;
    void is_uml_association(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML note.
     */
    /**@{*/
    bool is_uml_note() const;
    void is_uml_note(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML message.
     */
    /**@{*/
    bool is_uml_message() const;
    void is_uml_message(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an UML realisation.
     */
    /**@{*/
    bool is_uml_realization() const;
    void is_uml_realization(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an enumeration.
     */
    /**@{*/
    bool is_enumeration() const;
    void is_enumeration(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an exception
     */
    /**@{*/
    bool is_exception() const;
    void is_exception(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is an entity.
     */
    /**@{*/
    bool is_entity() const;
    void is_entity(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is a value object.
     */
    /**@{*/
    bool is_value() const;
    void is_value(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is a service.
     */
    /**@{*/
    bool is_service() const;
    void is_service(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is non-generatable.
     */
    /**@{*/
    bool is_non_generatable() const;
    void is_non_generatable(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is versioned.
     */
    /**@{*/
    bool is_versioned() const;
    void is_versioned(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is has keyes for its identity function.
     */
    /**@{*/
    bool is_keyed() const;
    void is_keyed(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object can be visited as per visitor pattern.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is immutable.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is fluent.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is the root of an aggregate.
     */
    /**@{*/
    bool is_aggregate_root() const;
    void is_aggregate_root(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object is a table of strings.
     */
    /**@{*/
    bool is_string_table() const;
    void is_string_table(const bool v);
    /**@}*/

    /**
     * @brief If true, the underlying object represents a concept.
     */
    /**@{*/
    bool is_concept() const;
    void is_concept(const bool v);
    /**@}*/

    /**
     * @brief List of all unknown stereotypes.
     */
    /**@{*/
    const std::list<std::string>& unknown_stereotypes() const;
    std::list<std::string>& unknown_stereotypes();
    void unknown_stereotypes(const std::list<std::string>& v);
    void unknown_stereotypes(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const profile& rhs) const;
    bool operator!=(const profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile& other) noexcept;
    profile& operator=(profile other);

private:
    bool is_uml_large_package_;
    bool is_uml_class_;
    bool is_uml_generalization_;
    bool is_uml_association_;
    bool is_uml_note_;
    bool is_uml_message_;
    bool is_uml_realization_;
    bool is_enumeration_;
    bool is_exception_;
    bool is_entity_;
    bool is_value_;
    bool is_service_;
    bool is_non_generatable_;
    bool is_versioned_;
    bool is_keyed_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_fluent_;
    bool is_aggregate_root_;
    bool is_string_table_;
    bool is_concept_;
    std::list<std::string> unknown_stereotypes_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dia_to_sml::profile& lhs,
    dogen::dia_to_sml::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
