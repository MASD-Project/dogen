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
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/odb_options_formatter_stitch.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace odb {

dogen::formatters::file odb_options_formatter_stitch(
    formatters::trivial_formatting_assistant& fa,
    const formattables::odb_options_info& i) {

    {
        fa.make_annotation_preamble(i.general_settings());
fa.stream() << "# enable C++11. FIXME: causes ODB crash in options file." << std::endl;
fa.stream() << "# --std c++11" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# target postgres" << std::endl;
fa.stream() << "--database pgsql" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# use the boost profile" << std::endl;
fa.stream() << "--profile boost" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# generate queries and embedded schemas" << std::endl;
fa.stream() << "--generate-query" << std::endl;
fa.stream() << "--generate-schema" << std::endl;
fa.stream() << "--schema-format embedded" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# use extensions similar to the dogen ones" << std::endl;
fa.stream() << "# --ixx-suffix .ipp" << std::endl;
fa.stream() << "# --hxx-suffix .hpp" << std::endl;
fa.stream() << "--cxx-suffix .cpp" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# fix domain includes" << std::endl;
fa.stream() << "--include-regex '%(.*).hpp%" << i.product_name() << "/" << i.model_name() << "/types/$1.hpp%'" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# fix odb generated includes" << std::endl;
fa.stream() << "--include-regex '%(^[a-zA-Z0-9_]+)-odb.(.*)%" << i.product_name() << "/" << i.model_name() << "/odb/$1-odb.$2%'" << std::endl;
fa.stream() << "--include-regex '%" << i.product_name() << "/" << i.model_name() << "/types/(.*)-odb.(.*)%" << i.product_name() << "/" << i.model_name() << "/odb/$1-odb.$2%'" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# debug regexes" << std::endl;
fa.stream() << "# --include-regex-trace" << std::endl;
fa.stream() << std::endl;
fa.stream() << "# make the header guards similar to dogen ones" << std::endl;
fa.stream() << "--guard-prefix " << boost::to_upper_copy(i.product_name()) << "_" << boost::to_upper_copy(i.model_name()) << "_" << boost::to_upper_copy(i.odb_folder()) << std::endl;
    } // sbf
    return fa.make_file(i.file_path());
    // return fa.make_file(i.file_path(), false/*overwrite*/);
}
} } } }
