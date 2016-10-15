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
#ifndef DOGEN_YARN_DIA_TYPES_PROFILE_HPP
#define DOGEN_YARN_DIA_TYPES_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/yarn.dia/serialization/profile_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Provides a flattened view of processed objects.
 *
 * Profiles aggregate two types of information from processed objects:
 *
 * @li the UML type of the dia object
 * @li Yarn related information
 *
 * Most of this information is provided in flag form. All flags starting
 * with @e is_uml are of the first kind; the rest belong to the
 * latter.
 *
 * Yarn information is all gathered via processing the stereotype of the
 * object. There are two kinds of yarn information we're interested in:
 *
 * @li the type of the yarn modeling element, e.g. enumeration, value
 * object, etc.
 * @li any additional properties that yarn modeling elements may have,
 * dependent on type, such as versioning, etc.
 *
 * Any additional stereotypes which were not recognised by the system are
 * appended to the unknown stereotypes bucket. These are expected to map
 * to yarn concepts at a later stage.
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
        const bool is_object,
        const bool is_concept,
        const std::list<std::string>& unknown_stereotypes);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::dia::profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::dia::profile& v, unsigned int version);

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

    bool is_object() const;
    void is_object(const bool v);

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
    bool is_object_;
    bool is_concept_;
    std::list<std::string> unknown_stereotypes_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::dia::profile& lhs,
    dogen::yarn::dia::profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
