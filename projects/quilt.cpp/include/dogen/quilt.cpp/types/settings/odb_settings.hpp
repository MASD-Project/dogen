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
#ifndef DOGEN_QUILT_CPP_TYPES_SETTINGS_ODB_SETTINGS_HPP
#define DOGEN_QUILT_CPP_TYPES_SETTINGS_ODB_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/types/settings/opaque_settings.hpp"
#include "dogen/quilt.cpp/serialization/settings/odb_settings_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

/**
 * @brief Settings for ODB formatters.
 */
class odb_settings final : public dogen::quilt::cpp::settings::opaque_settings {
public:
    odb_settings() = default;
    odb_settings(const odb_settings&) = default;
    odb_settings(odb_settings&&) = default;

    virtual ~odb_settings() noexcept { }

public:
    explicit odb_settings(const std::list<std::string>& pragmas);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::settings::odb_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::settings::odb_settings& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief ODB pragmas.
     */
    /**@{*/
    const std::list<std::string>& pragmas() const;
    std::list<std::string>& pragmas();
    void pragmas(const std::list<std::string>& v);
    void pragmas(const std::list<std::string>&& v);
    /**@}*/

public:
    bool operator==(const odb_settings& rhs) const;
    bool operator!=(const odb_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::quilt::cpp::settings::opaque_settings& other) const override;

public:
    void swap(odb_settings& other) noexcept;
    odb_settings& operator=(odb_settings other);

private:
    std::list<std::string> pragmas_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::settings::odb_settings& lhs,
    dogen::quilt::cpp::settings::odb_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
