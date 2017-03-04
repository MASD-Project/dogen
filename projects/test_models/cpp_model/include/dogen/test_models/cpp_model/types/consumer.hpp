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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CONSUMER_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CONSUMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/types/int_primitive.hpp"
#include "dogen/test_models/cpp_model/types/bool_primitive.hpp"
#include "dogen/test_models/cpp_model/types/char_primitive.hpp"
#include "dogen/test_models/cpp_model/types/long_primitive.hpp"
#include "dogen/test_models/cpp_model/types/uint_primitive.hpp"
#include "dogen/test_models/cpp_model/types/float_primitive.hpp"
#include "dogen/test_models/cpp_model/types/short_primitive.hpp"
#include "dogen/test_models/cpp_model/types/uchar_primitive.hpp"
#include "dogen/test_models/cpp_model/types/ulong_primitive.hpp"
#include "dogen/test_models/cpp_model/types/double_primitive.hpp"
#include "dogen/test_models/cpp_model/types/ushort_primitive.hpp"
#include "dogen/test_models/cpp_model/serialization/consumer_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief This type makes use of all primitves in this test model.
 */
class consumer final {
public:
    consumer() = default;
    consumer(const consumer&) = default;
    consumer(consumer&&) = default;
    ~consumer() = default;

public:
    consumer(
        const dogen::test_models::cpp_model::short_primitive& prop0,
        const dogen::test_models::cpp_model::ushort_primitive& prop1,
        const dogen::test_models::cpp_model::long_primitive& prop2,
        const dogen::test_models::cpp_model::ulong_primitive& prop3,
        const dogen::test_models::cpp_model::int_primitive& prop4,
        const dogen::test_models::cpp_model::uint_primitive& prop5,
        const dogen::test_models::cpp_model::char_primitive& prop6,
        const dogen::test_models::cpp_model::uchar_primitive& prop7,
        const dogen::test_models::cpp_model::double_primitive& prop8,
        const dogen::test_models::cpp_model::float_primitive& prop9,
        const dogen::test_models::cpp_model::bool_primitive& prop10);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::consumer& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::consumer& v, unsigned int version);

public:
    const dogen::test_models::cpp_model::short_primitive& prop0() const;
    dogen::test_models::cpp_model::short_primitive& prop0();
    void prop0(const dogen::test_models::cpp_model::short_primitive& v);
    void prop0(const dogen::test_models::cpp_model::short_primitive&& v);

    const dogen::test_models::cpp_model::ushort_primitive& prop1() const;
    dogen::test_models::cpp_model::ushort_primitive& prop1();
    void prop1(const dogen::test_models::cpp_model::ushort_primitive& v);
    void prop1(const dogen::test_models::cpp_model::ushort_primitive&& v);

    const dogen::test_models::cpp_model::long_primitive& prop2() const;
    dogen::test_models::cpp_model::long_primitive& prop2();
    void prop2(const dogen::test_models::cpp_model::long_primitive& v);
    void prop2(const dogen::test_models::cpp_model::long_primitive&& v);

    const dogen::test_models::cpp_model::ulong_primitive& prop3() const;
    dogen::test_models::cpp_model::ulong_primitive& prop3();
    void prop3(const dogen::test_models::cpp_model::ulong_primitive& v);
    void prop3(const dogen::test_models::cpp_model::ulong_primitive&& v);

    const dogen::test_models::cpp_model::int_primitive& prop4() const;
    dogen::test_models::cpp_model::int_primitive& prop4();
    void prop4(const dogen::test_models::cpp_model::int_primitive& v);
    void prop4(const dogen::test_models::cpp_model::int_primitive&& v);

    const dogen::test_models::cpp_model::uint_primitive& prop5() const;
    dogen::test_models::cpp_model::uint_primitive& prop5();
    void prop5(const dogen::test_models::cpp_model::uint_primitive& v);
    void prop5(const dogen::test_models::cpp_model::uint_primitive&& v);

    const dogen::test_models::cpp_model::char_primitive& prop6() const;
    dogen::test_models::cpp_model::char_primitive& prop6();
    void prop6(const dogen::test_models::cpp_model::char_primitive& v);
    void prop6(const dogen::test_models::cpp_model::char_primitive&& v);

    const dogen::test_models::cpp_model::uchar_primitive& prop7() const;
    dogen::test_models::cpp_model::uchar_primitive& prop7();
    void prop7(const dogen::test_models::cpp_model::uchar_primitive& v);
    void prop7(const dogen::test_models::cpp_model::uchar_primitive&& v);

    const dogen::test_models::cpp_model::double_primitive& prop8() const;
    dogen::test_models::cpp_model::double_primitive& prop8();
    void prop8(const dogen::test_models::cpp_model::double_primitive& v);
    void prop8(const dogen::test_models::cpp_model::double_primitive&& v);

    const dogen::test_models::cpp_model::float_primitive& prop9() const;
    dogen::test_models::cpp_model::float_primitive& prop9();
    void prop9(const dogen::test_models::cpp_model::float_primitive& v);
    void prop9(const dogen::test_models::cpp_model::float_primitive&& v);

    const dogen::test_models::cpp_model::bool_primitive& prop10() const;
    dogen::test_models::cpp_model::bool_primitive& prop10();
    void prop10(const dogen::test_models::cpp_model::bool_primitive& v);
    void prop10(const dogen::test_models::cpp_model::bool_primitive&& v);

public:
    bool operator==(const consumer& rhs) const;
    bool operator!=(const consumer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(consumer& other) noexcept;
    consumer& operator=(consumer other);

private:
    dogen::test_models::cpp_model::short_primitive prop0_;
    dogen::test_models::cpp_model::ushort_primitive prop1_;
    dogen::test_models::cpp_model::long_primitive prop2_;
    dogen::test_models::cpp_model::ulong_primitive prop3_;
    dogen::test_models::cpp_model::int_primitive prop4_;
    dogen::test_models::cpp_model::uint_primitive prop5_;
    dogen::test_models::cpp_model::char_primitive prop6_;
    dogen::test_models::cpp_model::uchar_primitive prop7_;
    dogen::test_models::cpp_model::double_primitive prop8_;
    dogen::test_models::cpp_model::float_primitive prop9_;
    dogen::test_models::cpp_model::bool_primitive prop10_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::consumer& lhs,
    dogen::test_models::cpp_model::consumer& rhs) {
    lhs.swap(rhs);
}

}

#endif
