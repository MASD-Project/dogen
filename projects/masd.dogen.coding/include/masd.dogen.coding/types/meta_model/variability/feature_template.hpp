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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.variability/types/meta_model/binding_point.hpp"
#include "masd.dogen.variability/types/meta_model/template_kind.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace masd::dogen::coding::meta_model::variability {

class feature_template final {
public:
    feature_template(const feature_template&) = default;
    feature_template(feature_template&&) = default;
    ~feature_template() = default;

public:
    feature_template();

public:
    feature_template(
        const std::string& documentation,
        const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
        const masd::dogen::coding::meta_model::name& name,
        const std::string& type,
        const masd::dogen::archetypes::location& location,
        const masd::dogen::variability::meta_model::template_kind template_kind,
        const masd::dogen::variability::meta_model::binding_point binding_point);

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
     * @brief Configuration for this element.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration() const;
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration();
    void configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& v);
    void configuration(const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>&& v);
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

    const std::string& type() const;
    std::string& type();
    void type(const std::string& v);
    void type(const std::string&& v);

    const masd::dogen::archetypes::location& location() const;
    masd::dogen::archetypes::location& location();
    void location(const masd::dogen::archetypes::location& v);
    void location(const masd::dogen::archetypes::location&& v);

    masd::dogen::variability::meta_model::template_kind template_kind() const;
    void template_kind(const masd::dogen::variability::meta_model::template_kind v);

    masd::dogen::variability::meta_model::binding_point binding_point() const;
    void binding_point(const masd::dogen::variability::meta_model::binding_point v);

public:
    bool operator==(const feature_template& rhs) const;
    bool operator!=(const feature_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(feature_template& other) noexcept;
    feature_template& operator=(feature_template other);

private:
    std::string documentation_;
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> configuration_;
    masd::dogen::coding::meta_model::name name_;
    std::string type_;
    masd::dogen::archetypes::location location_;
    masd::dogen::variability::meta_model::template_kind template_kind_;
    masd::dogen::variability::meta_model::binding_point binding_point_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::variability::feature_template& lhs,
    masd::dogen::coding::meta_model::variability::feature_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
