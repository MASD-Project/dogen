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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_TEST_DATA_PROPERTIES_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_TEST_DATA_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::text::cpp::formattables {

class test_data_properties final {
public:
    test_data_properties(const test_data_properties&) = default;
    test_data_properties(test_data_properties&&) = default;
    ~test_data_properties() = default;

public:
    test_data_properties();

public:
    test_data_properties(
        const unsigned int maximum_size,
        const std::string& prefix);

public:
    unsigned int maximum_size() const;
    void maximum_size(const unsigned int v);

    const std::string& prefix() const;
    std::string& prefix();
    void prefix(const std::string& v);
    void prefix(const std::string&& v);

public:
    bool operator==(const test_data_properties& rhs) const;
    bool operator!=(const test_data_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(test_data_properties& other) noexcept;
    test_data_properties& operator=(test_data_properties other);

private:
    unsigned int maximum_size_;
    std::string prefix_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::test_data_properties& lhs,
    dogen::text::cpp::formattables::test_data_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
