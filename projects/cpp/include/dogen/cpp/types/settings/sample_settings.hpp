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
#ifndef DOGEN_CPP_TYPES_SETTINGS_SAMPLE_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_SAMPLE_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/settings/sample_settings_fwd_ser.hpp"
#include "dogen/cpp/types/settings/special_formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Hack for now just to force the base class not to be final.
 */
class sample_settings final : public dogen::cpp::settings::special_formatter_settings {
public:
    sample_settings() = default;
    sample_settings(const sample_settings&) = default;
    sample_settings(sample_settings&&) = default;
    sample_settings& operator=(const sample_settings&) = default;

    virtual ~sample_settings() noexcept { }

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const sample_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, sample_settings& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const sample_settings& rhs) const;
    bool operator!=(const sample_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::cpp::settings::special_formatter_settings& other) const override;

};

} } }

#endif
