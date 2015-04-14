/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STITCH_TYPES_SETTINGS_BUNDLE_HPP
#define DOGEN_STITCH_TYPES_SETTINGS_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/stitch/types/stitching_settings.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/stitch/serialization/settings_bundle_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class settings_bundle final {
public:
    settings_bundle() = default;
    settings_bundle(const settings_bundle&) = default;
    ~settings_bundle() = default;

public:
    settings_bundle(settings_bundle&& rhs);

public:
    settings_bundle(
        const boost::optional<dogen::formatters::general_settings>& general_settings,
        const dogen::stitch::stitching_settings& stitching_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const settings_bundle& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, settings_bundle& v, unsigned int version);

public:
    const boost::optional<dogen::formatters::general_settings>& general_settings() const;
    boost::optional<dogen::formatters::general_settings>& general_settings();
    void general_settings(const boost::optional<dogen::formatters::general_settings>& v);
    void general_settings(const boost::optional<dogen::formatters::general_settings>&& v);

    const dogen::stitch::stitching_settings& stitching_settings() const;
    dogen::stitch::stitching_settings& stitching_settings();
    void stitching_settings(const dogen::stitch::stitching_settings& v);
    void stitching_settings(const dogen::stitch::stitching_settings&& v);

public:
    bool operator==(const settings_bundle& rhs) const;
    bool operator!=(const settings_bundle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(settings_bundle& other) noexcept;
    settings_bundle& operator=(settings_bundle other);

private:
    boost::optional<dogen::formatters::general_settings> general_settings_;
    dogen::stitch::stitching_settings stitching_settings_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::settings_bundle& lhs,
    dogen::stitch::settings_bundle& rhs) {
    lhs.swap(rhs);
}

}

#endif
