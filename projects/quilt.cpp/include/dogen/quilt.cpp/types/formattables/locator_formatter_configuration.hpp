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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCATOR_FORMATTER_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_LOCATOR_FORMATTER_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/locator_formatter_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class locator_formatter_configuration final {
public:
    locator_formatter_configuration() = default;
    locator_formatter_configuration(const locator_formatter_configuration&) = default;
    locator_formatter_configuration(locator_formatter_configuration&&) = default;
    ~locator_formatter_configuration() = default;

public:
    locator_formatter_configuration(
        const std::string& facet_directory,
        const std::string& facet_postfix,
        const std::string& formatter_postfix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::locator_formatter_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::locator_formatter_configuration& v, unsigned int version);

public:
    const std::string& facet_directory() const;
    std::string& facet_directory();
    void facet_directory(const std::string& v);
    void facet_directory(const std::string&& v);

    const std::string& facet_postfix() const;
    std::string& facet_postfix();
    void facet_postfix(const std::string& v);
    void facet_postfix(const std::string&& v);

    const std::string& formatter_postfix() const;
    std::string& formatter_postfix();
    void formatter_postfix(const std::string& v);
    void formatter_postfix(const std::string&& v);

public:
    bool operator==(const locator_formatter_configuration& rhs) const;
    bool operator!=(const locator_formatter_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(locator_formatter_configuration& other) noexcept;
    locator_formatter_configuration& operator=(locator_formatter_configuration other);

private:
    std::string facet_directory_;
    std::string facet_postfix_;
    std::string formatter_postfix_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::locator_formatter_configuration& lhs,
    dogen::quilt::cpp::formattables::locator_formatter_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
