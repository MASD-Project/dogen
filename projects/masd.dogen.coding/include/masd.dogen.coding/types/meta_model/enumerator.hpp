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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ENUMERATOR_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ENUMERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace masd::dogen::coding::meta_model {

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
        const masd::dogen::coding::meta_model::name& name,
        const masd::dogen::variability::annotation& annotation,
        const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
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
    const masd::dogen::coding::meta_model::name& name() const;
    masd::dogen::coding::meta_model::name& name();
    void name(const masd::dogen::coding::meta_model::name& v);
    void name(const masd::dogen::coding::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Annotation for this element.
     */
    /**@{*/
    const masd::dogen::variability::annotation& annotation() const;
    masd::dogen::variability::annotation& annotation();
    void annotation(const masd::dogen::variability::annotation& v);
    void annotation(const masd::dogen::variability::annotation&& v);
    /**@}*/

    /**
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration() const;
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration();
    void configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& v);
    void configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>&& v);
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
    masd::dogen::coding::meta_model::name name_;
    masd::dogen::variability::annotation annotation_;
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> configuration_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::enumerator& lhs,
    masd::dogen::coding::meta_model::enumerator& rhs) {
    lhs.swap(rhs);
}

}

#endif
