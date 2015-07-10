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
#ifndef DOGEN_CONFIG_TYPES_STITCHING_OPTIONS_HPP
#define DOGEN_CONFIG_TYPES_STITCHING_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/filesystem/path.hpp>
#include "dogen/config/serialization/stitching_options_fwd_ser.hpp"

namespace dogen {
namespace config {

class stitching_options final {
public:
    stitching_options(const stitching_options&) = default;
    ~stitching_options() = default;

public:
    stitching_options();

public:
    stitching_options(stitching_options&& rhs);

public:
    stitching_options(
        const bool verbose,
        const boost::filesystem::path& target,
        const bool force_write);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const stitching_options& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, stitching_options& v, unsigned int version);

public:
    bool verbose() const;
    void verbose(const bool v);

    const boost::filesystem::path& target() const;
    boost::filesystem::path& target();
    void target(const boost::filesystem::path& v);
    void target(const boost::filesystem::path&& v);

    bool force_write() const;
    void force_write(const bool v);

public:
    bool operator==(const stitching_options& rhs) const;
    bool operator!=(const stitching_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(stitching_options& other) noexcept;
    stitching_options& operator=(stitching_options other);

private:
    bool verbose_;
    boost::filesystem::path target_;
    bool force_write_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::config::stitching_options& lhs,
    dogen::config::stitching_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
