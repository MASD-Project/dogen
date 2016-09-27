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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_OPAQUE_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_OPAQUE_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/quilt.cpp/types/annotations/opaque_annotations_fwd.hpp"
#include "dogen/quilt.cpp/serialization/formattables/opaque_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class opaque_configuration final {
public:
    opaque_configuration() = default;
    opaque_configuration(const opaque_configuration&) = default;
    opaque_configuration(opaque_configuration&&) = default;
    ~opaque_configuration() = default;

public:
    opaque_configuration(
        const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& top_level,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& property_level);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::opaque_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::opaque_configuration& v, unsigned int version);

public:
    const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& top_level() const;
    boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& top_level();
    void top_level(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>& v);
    void top_level(const boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations>&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& property_level() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& property_level();
    void property_level(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >& v);
    void property_level(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> >&& v);

public:
    bool operator==(const opaque_configuration& rhs) const;
    bool operator!=(const opaque_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(opaque_configuration& other) noexcept;
    opaque_configuration& operator=(opaque_configuration other);

private:
    boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> top_level_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::annotations::opaque_annotations> > property_level_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::opaque_configuration& lhs,
    dogen::quilt::cpp::formattables::opaque_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
