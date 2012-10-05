/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#include "dogen/all_primitives/test_data/a_class_td.hpp"
#include "dogen/all_primitives/test_data/versioned_key_td.hpp"

namespace dogen {
namespace all_primitives {
namespace detail {

a_class_generator::value_type
a_class_generator::next_term(const unsigned int position) {
    a_class r;

    if (position == 0) {
        r.bool_property(static_cast<bool>(0));
        r.char_property(static_cast<char>(1));
        r.uchar_property(static_cast<unsigned char>(2));
        r.int_property(static_cast<int>(3));
        r.uint_property(static_cast<unsigned int>(4));
        r.long_property(static_cast<long>(5));
        r.ulong_property(static_cast<unsigned long>(6));
        r.long_long_property(static_cast<long long>(7));
        r.ulong_long_property(static_cast<unsigned long long>(8));
        r.short_property(static_cast<short>(9));
        r.ushort_property(static_cast<unsigned short>(10));
    } else if (position == 1) {
        r.bool_property(static_cast<bool>(30));
        r.char_property(static_cast<char>(31));
        r.uchar_property(static_cast<unsigned char>(32));
        r.int_property(static_cast<int>(33));
        r.uint_property(static_cast<unsigned int>(34));
        r.long_property(static_cast<long>(35));
        r.ulong_property(static_cast<unsigned long>(36));
        r.long_long_property(static_cast<long long>(37));
        r.ulong_long_property(static_cast<unsigned long long>(38));
        r.short_property(static_cast<short>(39));
        r.ushort_property(static_cast<unsigned short>(40));
    } else if (position == 2) {
        r.bool_property(static_cast<bool>(60));
        r.char_property(static_cast<char>(61));
        r.uchar_property(static_cast<unsigned char>(62));
        r.int_property(static_cast<int>(63));
        r.uint_property(static_cast<unsigned int>(64));
        r.long_property(static_cast<long>(65));
        r.ulong_property(static_cast<unsigned long>(66));
        r.long_long_property(static_cast<long long>(67));
        r.ulong_long_property(static_cast<unsigned long long>(68));
        r.short_property(static_cast<short>(69));
        r.ushort_property(static_cast<unsigned short>(70));
    }

    return r;
}

unsigned int a_class_generator::length() const { return(3); }

} } }
