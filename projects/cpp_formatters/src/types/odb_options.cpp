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
#include <ostream>
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen/cpp_formatters/types/odb_options.hpp"

namespace {

const std::string empty("");
const std::string underscore("_");
const std::string unnamed_model("unnamed_model");

}

namespace dogen {
namespace cpp_formatters {

odb_options::odb_options(std::ostream& stream) : stream_(stream) {}

void odb_options::format(const cpp::formattables::odb_options_info& ooi) {
    const std::string mn(ooi.model_name().empty() ?
        unnamed_model :
        ooi.model_name());


    stream_ << "# -*- mode: sh; tab-width: 4; indent-tabs-mode: nil -*-"
            << std::endl;

    stream_ << "#" << std::endl
            << "# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>" << std::endl
            << "#" << std::endl
            << "# This program is free software; you can redistribute it and/or"
            << " modify" << std::endl
            << "# it under the terms of the GNU General Public License as"
            << " published by" << std::endl
            << "# the Free Software Foundation; either version 3 of the License"
            << ", or" << std::endl
            << "# (at your option) any later version." << std::endl
            << "#" << std::endl
            << "# This program is distributed in the hope that it will be"
            << " useful," << std::endl
            << "# but WITHOUT ANY WARRANTY; without even the implied warranty"
            << " of" << std::endl
            << "# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the"
            << std::endl
            << "# GNU General Public License for more details." << std::endl
            << "#" << std::endl
            << "# You should have received a copy of the GNU General "
            << "Public License" << std::endl
            << "# along with this program; if not, write to the Free Software"
            << std::endl
            << "# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,"
            << std::endl << "# MA 02110-1301, USA." << std::endl
            << "#" << std::endl;

    stream_ << "# enable C++11. FIXME: causes ODB crash in options file."
            << std::endl
            << "# --std c++11" << std::endl << std::endl;

    stream_ << "# target postgres" << std::endl
            << "--database pgsql" << std::endl << std::endl;

    stream_ << "# use the boost profile" << std::endl
            << "--profile boost" << std::endl << std::endl;

    stream_ << "# generate queries and embedded schemas" << std::endl
            << "--generate-query" << std::endl
            << "--generate-schema" << std::endl
            << "--schema-format embedded" << std::endl << std::endl;

    stream_ << "# use extensions similar to the dogen ones" << std::endl
            << "# --ixx-suffix .ipp" << std::endl
            << "# --hxx-suffix .hpp" << std::endl
            << "--cxx-suffix .cpp" << std::endl << std::endl;

    stream_ << "# fix domain includes" << std::endl
            << "--include-regex '%(.*).hpp%" << ooi.product_name()
            << "/" << ooi.model_name() << "/types/$1.hpp%'"
            << std::endl << std::endl;

    stream_ << "# fix odb generated includes" << std::endl
            << "--include-regex '%(^[a-zA-Z0-9_]+)-odb.(.*)%"
            << ooi.product_name() << "/" << ooi.model_name() << "/"
            << ooi.odb_folder() << "/$1-odb.$2%'" << std::endl
            << "--include-regex '%" << ooi.product_name()
            << "/" << ooi.model_name() << "/types/(.*)-odb.(.*)%"
            << ooi.product_name() << "/" << ooi.model_name()
            << "/" << ooi.odb_folder() << "/$1-odb.$2%'"
            << std::endl << std::endl;

    stream_ << "# debug regexes" << std::endl
            << "# --include-regex-trace" << std::endl << std::endl;

    stream_ << "# make the header guards similar to dogen ones" << std::endl
            << "--guard-prefix " << boost::to_upper_copy(ooi.product_name())
            << "_" << boost::to_upper_copy(ooi.model_name()) << "_"
            << boost::to_upper_copy(ooi.odb_folder())
            << std::endl;

}

} }
