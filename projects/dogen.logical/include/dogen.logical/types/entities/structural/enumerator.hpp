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

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.logical/types/entities/stereotypes.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
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
        const dogen::identification::entities::logical_name& name,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::logical::entities::stereotypes& stereotypes,
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
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);
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
     * @brief All stereotypes associated with this element.
     */
    /**@{*/
    const dogen::logical::entities::stereotypes& stereotypes() const;
    dogen::logical::entities::stereotypes& stereotypes();
    void stereotypes(const dogen::logical::entities::stereotypes& v);
    void stereotypes(const dogen::logical::entities::stereotypes&& v);
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
    dogen::identification::entities::logical_name name_;
    boost::shared_ptr<dogen::variability::entities::configuration> configuration_;
    dogen::logical::entities::stereotypes stereotypes_;
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
