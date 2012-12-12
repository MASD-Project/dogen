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
#include <boost/io/ios_state.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <ostream>
#include "dogen/boost_model/io/class_derived_io.hpp"
#include "dogen/boost_model/io/class_e_io.hpp"

namespace boost {

struct boost_variant_int_double_visitor : public boost::static_visitor<> {
    boost_variant_int_double_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_int_double_visitor() { stream_ << " }"; }

    void operator()(const int v) const {
        stream_ << "{ " << "\"__type__\": " << "\"int\"" << ", ";
        stream_ << "\"value\": ";
        stream_ << v;
        stream_ << " }";
    }

    void operator()(const double v) const {
        stream_ << "{ " << "\"__type__\": " << "\"double\"" << ", ";
        stream_ << "\"value\": ";
        stream_ << v;
        stream_ << " }";
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<int, double>& v) {
    boost::apply_visitor(boost_variant_int_double_visitor(s), v);
    return s;
}

}

namespace boost {

struct boost_variant_int_dogen_boost_model_class_derived_double_visitor : public boost::static_visitor<> {
    boost_variant_int_dogen_boost_model_class_derived_double_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_int_dogen_boost_model_class_derived_double_visitor() { stream_ << " }"; }

    void operator()(const int v) const {
        stream_ << "{ " << "\"__type__\": " << "\"int\"" << ", ";
        stream_ << "\"value\": ";
        stream_ << v;
        stream_ << " }";
    }

    void operator()(const dogen::boost_model::class_derived& v) const {
        stream_ << v;
    }

    void operator()(const double v) const {
        stream_ << "{ " << "\"__type__\": " << "\"double\"" << ", ";
        stream_ << "\"value\": ";
        stream_ << v;
        stream_ << " }";
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<int, dogen::boost_model::class_derived, double>& v) {
    boost::apply_visitor(boost_variant_int_dogen_boost_model_class_derived_double_visitor(s), v);
    return s;
}

}

namespace dogen {
namespace boost_model {

std::ostream& operator<<(std::ostream& s, const class_e& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::boost_model::class_e\"" << ", "
      << "\"prop_0\": " << v.prop_0() << ", "
      << "\"prop_1\": " << v.prop_1()
      << " }";
    return(s);
}

} }