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
#ifndef DOGEN_OM_TYPES_ODB_GUARD_PREFIX_OPTION_HPP
#define DOGEN_OM_TYPES_ODB_GUARD_PREFIX_OPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <string>
#include "dogen/om/serialization/odb_guard_prefix_option_fwd_ser.hpp"
#include "dogen/om/types/odb_option.hpp"

namespace dogen {
namespace om {

class odb_guard_prefix_option final : public dogen::om::odb_option {
public:
    odb_guard_prefix_option() = default;
    odb_guard_prefix_option(const odb_guard_prefix_option&) = default;
    odb_guard_prefix_option(odb_guard_prefix_option&&) = default;

    virtual ~odb_guard_prefix_option() noexcept { }

public:
    odb_guard_prefix_option(
        const std::string& comment,
        const std::string& guard_prefix);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const odb_guard_prefix_option& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, odb_guard_prefix_option& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& guard_prefix() const;
    std::string& guard_prefix();
    void guard_prefix(const std::string& v);
    void guard_prefix(const std::string&& v);

public:
    bool operator==(const odb_guard_prefix_option& rhs) const;
    bool operator!=(const odb_guard_prefix_option& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::odb_option& other) const override;

public:
    void swap(odb_guard_prefix_option& other) noexcept;
    odb_guard_prefix_option& operator=(odb_guard_prefix_option other);

private:
    std::string guard_prefix_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::odb_guard_prefix_option& lhs,
    dogen::om::odb_guard_prefix_option& rhs) {
    lhs.swap(rhs);
}

}

#endif
