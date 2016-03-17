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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/quilt.cpp/types/settings/helper_settings.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_instance_properties.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_instance_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_instance final {
public:
    helper_instance() = default;
    helper_instance(const helper_instance&) = default;
    helper_instance(helper_instance&&) = default;
    ~helper_instance() = default;

public:
    helper_instance(
        const dogen::quilt::cpp::formattables::helper_instance_properties& properties,
        const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& associated_helpers,
        const dogen::quilt::cpp::settings::helper_settings& settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const helper_instance& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, helper_instance& v, unsigned int version);

public:
    const dogen::quilt::cpp::formattables::helper_instance_properties& properties() const;
    dogen::quilt::cpp::formattables::helper_instance_properties& properties();
    void properties(const dogen::quilt::cpp::formattables::helper_instance_properties& v);
    void properties(const dogen::quilt::cpp::formattables::helper_instance_properties&& v);

    const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& associated_helpers() const;
    std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& associated_helpers();
    void associated_helpers(const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>& v);
    void associated_helpers(const std::list<dogen::quilt::cpp::formattables::helper_instance_properties>&& v);

    /**
     * @brief Settings for this helper
     */
    /**@{*/
    const dogen::quilt::cpp::settings::helper_settings& settings() const;
    dogen::quilt::cpp::settings::helper_settings& settings();
    void settings(const dogen::quilt::cpp::settings::helper_settings& v);
    void settings(const dogen::quilt::cpp::settings::helper_settings&& v);
    /**@}*/

public:
    bool operator==(const helper_instance& rhs) const;
    bool operator!=(const helper_instance& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_instance& other) noexcept;
    helper_instance& operator=(helper_instance other);

private:
    dogen::quilt::cpp::formattables::helper_instance_properties properties_;
    std::list<dogen::quilt::cpp::formattables::helper_instance_properties> associated_helpers_;
    dogen::quilt::cpp::settings::helper_settings settings_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_instance& lhs,
    dogen::quilt::cpp::formattables::helper_instance& rhs) {
    lhs.swap(rhs);
}

}

#endif
