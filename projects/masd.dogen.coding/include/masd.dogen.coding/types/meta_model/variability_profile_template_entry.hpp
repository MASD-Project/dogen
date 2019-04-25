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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_PROFILE_TEMPLATE_ENTRY_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_PROFILE_TEMPLATE_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_fwd.hpp"

namespace masd::dogen::coding::meta_model {

class variability_profile_template_entry final {
public:
    variability_profile_template_entry() = default;
    variability_profile_template_entry(const variability_profile_template_entry&) = default;
    variability_profile_template_entry(variability_profile_template_entry&&) = default;
    ~variability_profile_template_entry() = default;

public:
    variability_profile_template_entry(
        const masd::dogen::variability::annotation& annotation,
        const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
        const std::string& name,
        const std::list<std::string>& value);

public:
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

    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<std::string>& value() const;
    std::list<std::string>& value();
    void value(const std::list<std::string>& v);
    void value(const std::list<std::string>&& v);

public:
    bool operator==(const variability_profile_template_entry& rhs) const;
    bool operator!=(const variability_profile_template_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(variability_profile_template_entry& other) noexcept;
    variability_profile_template_entry& operator=(variability_profile_template_entry other);

private:
    masd::dogen::variability::annotation annotation_;
    boost::shared_ptr<masd::dogen::variability::meta_model::configuration> configuration_;
    std::string name_;
    std::list<std::string> value_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::variability_profile_template_entry& lhs,
    masd::dogen::coding::meta_model::variability_profile_template_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
