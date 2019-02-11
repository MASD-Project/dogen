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
#include <ostream>
#include <boost/variant/apply_visitor.hpp>
#include "masd.dogen/io/configuration_io.hpp"
#include "masd.dogen/io/diffing_configuration_io.hpp"
#include "masd.dogen/io/logging_configuration_io.hpp"
#include "masd.dogen/io/tracing_configuration_io.hpp"
#include "masd.dogen/io/weaving_configuration_io.hpp"
#include "masd.dogen/io/conversion_configuration_io.hpp"
#include "masd.dogen/io/generation_configuration_io.hpp"

namespace boost {

struct boost_variant_masd_dogen_generation_configuration_masd_dogen_weaving_configuration_masd_dogen_conversion_configuration_visitor : public boost::static_visitor<> {
    boost_variant_masd_dogen_generation_configuration_masd_dogen_weaving_configuration_masd_dogen_conversion_configuration_visitor(std::ostream& s) : stream_(s) {
        s << "{ " << "\"__type__\": " << "\"boost::variant\"" << ", ";
        s << "\"data\": ";
    }

    ~boost_variant_masd_dogen_generation_configuration_masd_dogen_weaving_configuration_masd_dogen_conversion_configuration_visitor() { stream_ << " }"; }

    void operator()(const masd::dogen::generation_configuration& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::weaving_configuration& v) const {
        stream_ << v;
    }

    void operator()(const masd::dogen::conversion_configuration& v) const {
        stream_ << v;
    }

private:
    std::ostream& stream_;
};

inline std::ostream& operator<<(std::ostream& s, const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& v) {
    boost::apply_visitor(boost_variant_masd_dogen_generation_configuration_masd_dogen_weaving_configuration_masd_dogen_conversion_configuration_visitor(s), v);
    return s;
}

}

namespace masd::dogen {

std::ostream& operator<<(std::ostream& s, const configuration& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::configuration\"" << ", "
      << "\"activity\": " << v.activity() << ", "
      << "\"tracing\": " << v.tracing() << ", "
      << "\"logging\": " << v.logging() << ", "
      << "\"diffing\": " << v.diffing()
      << " }";
    return(s);
}

}
