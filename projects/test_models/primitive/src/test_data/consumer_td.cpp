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
#include "dogen/test_models/primitive/test_data/consumer_td.hpp"
#include "dogen/test_models/primitive/test_data/int_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/bool_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/char_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/long_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/uint_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/float_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/short_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/uchar_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/ulong_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/double_primitive_td.hpp"
#include "dogen/test_models/primitive/test_data/ushort_primitive_td.hpp"

namespace {

dogen::test_models::primitive::short_primitive
create_dogen_test_models_primitive_short_primitive(const unsigned int position) {
    return dogen::test_models::primitive::short_primitive_generator::create(position);
}

dogen::test_models::primitive::ushort_primitive
create_dogen_test_models_primitive_ushort_primitive(const unsigned int position) {
    return dogen::test_models::primitive::ushort_primitive_generator::create(position);
}

dogen::test_models::primitive::long_primitive
create_dogen_test_models_primitive_long_primitive(const unsigned int position) {
    return dogen::test_models::primitive::long_primitive_generator::create(position);
}

dogen::test_models::primitive::ulong_primitive
create_dogen_test_models_primitive_ulong_primitive(const unsigned int position) {
    return dogen::test_models::primitive::ulong_primitive_generator::create(position);
}

dogen::test_models::primitive::int_primitive
create_dogen_test_models_primitive_int_primitive(const unsigned int position) {
    return dogen::test_models::primitive::int_primitive_generator::create(position);
}

dogen::test_models::primitive::uint_primitive
create_dogen_test_models_primitive_uint_primitive(const unsigned int position) {
    return dogen::test_models::primitive::uint_primitive_generator::create(position);
}

dogen::test_models::primitive::char_primitive
create_dogen_test_models_primitive_char_primitive(const unsigned int position) {
    return dogen::test_models::primitive::char_primitive_generator::create(position);
}

dogen::test_models::primitive::uchar_primitive
create_dogen_test_models_primitive_uchar_primitive(const unsigned int position) {
    return dogen::test_models::primitive::uchar_primitive_generator::create(position);
}

dogen::test_models::primitive::double_primitive
create_dogen_test_models_primitive_double_primitive(const unsigned int position) {
    return dogen::test_models::primitive::double_primitive_generator::create(position);
}

dogen::test_models::primitive::float_primitive
create_dogen_test_models_primitive_float_primitive(const unsigned int position) {
    return dogen::test_models::primitive::float_primitive_generator::create(position);
}

dogen::test_models::primitive::bool_primitive
create_dogen_test_models_primitive_bool_primitive(const unsigned int position) {
    return dogen::test_models::primitive::bool_primitive_generator::create(position);
}

}

namespace dogen {
namespace test_models {
namespace primitive {

consumer_generator::consumer_generator() : position_(0) { }

void consumer_generator::
populate(const unsigned int position, result_type& v) {
    v.prop0(create_dogen_test_models_primitive_short_primitive(position + 0));
    v.prop1(create_dogen_test_models_primitive_ushort_primitive(position + 1));
    v.prop2(create_dogen_test_models_primitive_long_primitive(position + 2));
    v.prop3(create_dogen_test_models_primitive_ulong_primitive(position + 3));
    v.prop4(create_dogen_test_models_primitive_int_primitive(position + 4));
    v.prop5(create_dogen_test_models_primitive_uint_primitive(position + 5));
    v.prop6(create_dogen_test_models_primitive_char_primitive(position + 6));
    v.prop7(create_dogen_test_models_primitive_uchar_primitive(position + 7));
    v.prop8(create_dogen_test_models_primitive_double_primitive(position + 8));
    v.prop9(create_dogen_test_models_primitive_float_primitive(position + 9));
    v.prop10(create_dogen_test_models_primitive_bool_primitive(position + 10));
}

consumer_generator::result_type
consumer_generator::create(const unsigned int position) {
    consumer r;
    consumer_generator::populate(position, r);
    return r;
}

consumer_generator::result_type*
consumer_generator::create_ptr(const unsigned int position) {
    consumer* p = new consumer();
    consumer_generator::populate(position, *p);
    return p;
}

consumer_generator::result_type
consumer_generator::operator()() {
    return create(position_++);
}

} } }
