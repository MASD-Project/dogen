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
#ifndef DOGEN_QUILT_CPP_TYPES_SETTINGS_ELEMENT_SETTINGS_HPP
#define DOGEN_QUILT_CPP_TYPES_SETTINGS_ELEMENT_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen/quilt.cpp/types/settings/aspect_settings.hpp"
#include "dogen/quilt.cpp/types/settings/opaque_settings_fwd.hpp"
#include "dogen/quilt.cpp/serialization/settings/element_settings_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

class element_settings final {
public:
    element_settings() = default;
    element_settings(const element_settings&) = default;
    element_settings(element_settings&&) = default;
    ~element_settings() = default;

public:
    element_settings(
        const dogen::quilt::cpp::settings::aspect_settings& aspect_settings,
        const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& opaque_settings,
        const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& opaque_settings_for_property);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::settings::element_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::settings::element_settings& v, unsigned int version);

public:
    const dogen::quilt::cpp::settings::aspect_settings& aspect_settings() const;
    dogen::quilt::cpp::settings::aspect_settings& aspect_settings();
    void aspect_settings(const dogen::quilt::cpp::settings::aspect_settings& v);
    void aspect_settings(const dogen::quilt::cpp::settings::aspect_settings&& v);

    const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& opaque_settings() const;
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& opaque_settings();
    void opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >& v);
    void opaque_settings(const std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> >&& v);

    const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& opaque_settings_for_property() const;
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& opaque_settings_for_property();
    void opaque_settings_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >& v);
    void opaque_settings_for_property(const std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > >&& v);

public:
    bool operator==(const element_settings& rhs) const;
    bool operator!=(const element_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_settings& other) noexcept;
    element_settings& operator=(element_settings other);

private:
    dogen::quilt::cpp::settings::aspect_settings aspect_settings_;
    std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > opaque_settings_;
    std::unordered_map<std::string, std::unordered_map<std::string, boost::shared_ptr<dogen::quilt::cpp::settings::opaque_settings> > > opaque_settings_for_property_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::settings::element_settings& lhs,
    dogen::quilt::cpp::settings::element_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
