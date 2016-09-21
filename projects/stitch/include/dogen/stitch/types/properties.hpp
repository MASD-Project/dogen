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
#ifndef DOGEN_STITCH_TYPES_PROPERTIES_HPP
#define DOGEN_STITCH_TYPES_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/stitch/types/stitching_settings.hpp"
#include "dogen/stitch/serialization/properties_fwd_ser.hpp"
#include "dogen/formatters/types/decoration_configuration.hpp"

namespace dogen {
namespace stitch {

class properties final {
public:
    properties() = default;
    properties(const properties&) = default;
    ~properties() = default;

public:
    properties(properties&& rhs);

public:
    properties(
        const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration,
        const dogen::stitch::stitching_settings& stitching_settings);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::stitch::properties& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::stitch::properties& v, unsigned int version);

public:
    const boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration() const;
    boost::optional<dogen::formatters::decoration_configuration>& decoration_configuration();
    void decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>& v);
    void decoration_configuration(const boost::optional<dogen::formatters::decoration_configuration>&& v);

    const dogen::stitch::stitching_settings& stitching_settings() const;
    dogen::stitch::stitching_settings& stitching_settings();
    void stitching_settings(const dogen::stitch::stitching_settings& v);
    void stitching_settings(const dogen::stitch::stitching_settings&& v);

public:
    bool operator==(const properties& rhs) const;
    bool operator!=(const properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(properties& other) noexcept;
    properties& operator=(properties other);

private:
    boost::optional<dogen::formatters::decoration_configuration> decoration_configuration_;
    dogen::stitch::stitching_settings stitching_settings_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::properties& lhs,
    dogen::stitch::properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
