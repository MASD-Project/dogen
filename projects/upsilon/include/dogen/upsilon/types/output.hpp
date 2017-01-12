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
#ifndef DOGEN_UPSILON_TYPES_OUTPUT_HPP
#define DOGEN_UPSILON_TYPES_OUTPUT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include "dogen/upsilon/types/representation.hpp"
#include "dogen/upsilon/serialization/output_fwd_ser.hpp"

namespace dogen {
namespace upsilon {

class output final {
public:
    output() = default;
    output(const output&) = default;
    output(output&&) = default;
    ~output() = default;

public:
    output(
        const std::string& schema_name,
        const std::vector<dogen::upsilon::representation>& representations);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::upsilon::output& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::upsilon::output& v, unsigned int version);

public:
    const std::string& schema_name() const;
    std::string& schema_name();
    void schema_name(const std::string& v);
    void schema_name(const std::string&& v);

    const std::vector<dogen::upsilon::representation>& representations() const;
    std::vector<dogen::upsilon::representation>& representations();
    void representations(const std::vector<dogen::upsilon::representation>& v);
    void representations(const std::vector<dogen::upsilon::representation>&& v);

public:
    bool operator==(const output& rhs) const;
    bool operator!=(const output& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(output& other) noexcept;
    output& operator=(output other);

private:
    std::string schema_name_;
    std::vector<dogen::upsilon::representation> representations_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::upsilon::output& lhs,
    dogen::upsilon::output& rhs) {
    lhs.swap(rhs);
}

}

#endif
