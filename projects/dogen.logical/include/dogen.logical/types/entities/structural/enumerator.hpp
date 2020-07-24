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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_ENUMERATOR_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_ENUMERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.identification/types/entities/stereotype.hpp"
#include "dogen.logical/types/entities/static_stereotypes.hpp"
#include "dogen.variability/types/entities/configuration_fwd.hpp"

namespace dogen::logical::entities::structural {

/**
 * @brief One of a set of valid values that an enumeration can assume.
 *
 * The enumerator defines an element in the domain of the enumeration.
 */
class enumerator final {
public:
    enumerator() = default;
    enumerator(const enumerator&) = default;
    enumerator(enumerator&&) = default;
    ~enumerator() = default;

public:
    enumerator(
        const std::string& documentation,
        const dogen::logical::entities::name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes,
        const std::string& value);

public:
    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing tools
     * of the technical space in question, e.g. Doxygen for C++, JavaDoc for Java,
     * etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::logical::entities::name& name() const;
    dogen::logical::entities::name& name();
    void name(const dogen::logical::entities::name& v);
    void name(const dogen::logical::entities::name&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration() const;
    boost::shared_ptr<dogen::variability::entities::configuration>& configuration();
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v);
    void configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are part of the dogen UML profile, and so are well-known to the
     * model.
     */
    /**@{*/
    const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes() const;
    std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes();
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>& v);
    void static_stereotypes(const std::list<dogen::logical::entities::static_stereotypes>&& v);
    /**@}*/

    /**
     * @brief Stereotypes that are not part of the masd UML profile. These are user defined.
     */
    /**@{*/
    const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes() const;
    std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes();
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>& v);
    void dynamic_stereotypes(const std::list<dogen::identification::entities::stereotype>&& v);
    /**@}*/

    /**
     * @brief Value for the enumerator.
     *
     * It must be castable to instance of the type defined in the enumeration.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const enumerator& rhs) const;
    bool operator!=(const enumerator& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(enumerator& other) noexcept;
    enumerator& operator=(enumerator other);

private:
    std::string documentation_;
    dogen::logical::entities::name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    std::list<dogen::logical::entities::static_stereotypes> static_stereotypes_;
    std::list<dogen::identification::entities::stereotype> dynamic_stereotypes_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::enumerator& lhs,
    dogen::logical::entities::structural::enumerator& rhs) {
    lhs.swap(rhs);
}

}

#endif
