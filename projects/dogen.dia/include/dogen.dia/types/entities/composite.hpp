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
#ifndef DOGEN_DIA_TYPES_ENTITIES_COMPOSITE_HPP
#define DOGEN_DIA_TYPES_ENTITIES_COMPOSITE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.dia/types/entities/attribute_fwd.hpp"
#include "dogen.dia/types/entities/composite_fwd.hpp"

namespace dogen::dia::entities {

/**
 * @brief Attribute value which is made up of other attributes.
 */
class composite final {
public:
    composite() = default;
    composite(const composite&) = default;
    composite(composite&&) = default;
    ~composite() = default;

public:
    composite(
        const std::string& type,
        const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& value,
        const boost::shared_ptr<dogen::dia::entities::composite>& inner_composite);

public:
    /**
     * @brief Type of the composite node
     */
    /**@{*/
    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);
    /**@}*/

    /**
     * @brief Underlying Dia attributes.
     */
    /**@{*/
    const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& value() const;
    std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& value();
    void value(const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >& v);
    void value(const std::vector<boost::shared_ptr<dogen::dia::entities::attribute> >&& v);
    /**@}*/

    /**
     * @brief Some composites contain an inner composite field.
     */
    /**@{*/
    const boost::shared_ptr<dogen::dia::entities::composite>& inner_composite() const;
    boost::shared_ptr<dogen::dia::entities::composite>& inner_composite();
    void inner_composite(const boost::shared_ptr<dogen::dia::entities::composite>& v);
    void inner_composite(const boost::shared_ptr<dogen::dia::entities::composite>&& v);
    /**@}*/

public:
    bool operator==(const composite& rhs) const;
    bool operator!=(const composite& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(composite& other) noexcept;
    composite& operator=(composite other);

private:
    std::string type_;
    std::vector<boost::shared_ptr<dogen::dia::entities::attribute> > value_;
    boost::shared_ptr<dogen::dia::entities::composite> inner_composite_;
};

}

namespace std {

template<>
inline void swap(
    dogen::dia::entities::composite& lhs,
    dogen::dia::entities::composite& rhs) {
    lhs.swap(rhs);
}

}

#endif
