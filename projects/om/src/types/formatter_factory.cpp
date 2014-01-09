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
#include <boost/make_shared.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/om/types/cpp_types_main_header_file_formatter.hpp"
#include "dogen/om/types/formatter_factory.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("om.formatter_factory"));

}

namespace dogen {
namespace om {

formatter_factory::
formatter_factory(const sml::model& model,
    const boost::filesystem::path& project_directory,
    const boost::filesystem::path& cpp_source_directory,
    const boost::filesystem::path& cpp_include_directory,
    const bool legacy_mode)
    : model_(model), project_directory_(project_directory),
      cpp_source_directory_(cpp_source_directory),
      cpp_include_directory_(cpp_include_directory),
      legacy_mode_(legacy_mode) {

    BOOST_LOG_SEV(lg, debug) << "Factory setup. Project directory: "
                             << project_directory << " C++ source directory: "
                             << cpp_source_directory
                             << " C++ include directory: "
                             << cpp_include_directory
                             << " Legacy mode: " << legacy_mode_;
}

std::list<boost::shared_ptr<type_formatter_interface> >
formatter_factory::build_type_formatters() const {
    using namespace boost;
    std::list<shared_ptr<type_formatter_interface> > r;
    r.push_back(make_shared<cpp_types_main_header_file_formatter>(
            model_, cpp_include_directory_, legacy_mode_));
    return r;
}

std::list<boost::shared_ptr<module_formatter_interface> >
formatter_factory::build_module_formatters() const {
    using namespace boost;
    std::list<shared_ptr<module_formatter_interface> > r;
    r.push_back(make_shared<cpp_types_main_header_file_formatter>(
            model_, cpp_include_directory_));
    return r;
}

std::list<boost::shared_ptr<concept_formatter_interface> >
formatter_factory::build_concept_formatters() const {
    std::list<boost::shared_ptr<concept_formatter_interface> > r;
    return r;
}

} }
