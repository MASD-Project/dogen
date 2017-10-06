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
#ifndef DOGEN_TEST_MODELS_ALL_PATH_AND_DIRECTORY_SETTINGS_TYPES_DIR_CLASS_0_0_5_0_THE_TYPES_HH
#define DOGEN_TEST_MODELS_ALL_PATH_AND_DIRECTORY_SETTINGS_TYPES_DIR_CLASS_0_0_5_0_THE_TYPES_HH

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/all_path_and_directory_settings/serialization_dir/class_0_0_3_6_the_serialization.hh"

namespace dogen {
namespace test_models {
namespace all_path_and_directory_settings {

class class_0 final {
public:
    class_0(const class_0&) = default;
    class_0(class_0&&) = default;
    ~class_0() = default;

public:
    class_0();

public:
    explicit class_0(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::all_path_and_directory_settings::class_0& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::all_path_and_directory_settings::class_0& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const class_0& rhs) const;
    bool operator!=(const class_0& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_0& other) noexcept;
    class_0& operator=(class_0 other);

private:
    int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::all_path_and_directory_settings::class_0& lhs,
    dogen::test_models::all_path_and_directory_settings::class_0& rhs) {
    lhs.swap(rhs);
}

}

#endif
