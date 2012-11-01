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
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>
#include <boost/variant/get.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "dogen/dia/domain/object_types.hpp"
#include "dogen/dia/io/object_types_io.hpp"
#include "dogen/dia/domain/composite.hpp"
#include "dogen/dia/domain/attribute.hpp"
#include "dogen/dia/utility/dia_utility.hpp"
#include "dogen/dia/io/object_io.hpp"
#include "dogen/dia/io/diagram_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/transformation_error.hpp"
#include "dogen/generator/modeling/dia_object_to_sml_package.hpp"
#include "dogen/sml/utility/identifier_parser.hpp"
#include "dogen/generator/modeling/dia_to_sml.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dia_to_sml"));

const std::string error_parsing_object_type("Fail to parse object type: ");
const std::string unsupported_object_type("Dia object type is not supported: ");

using dogen::generator::modeling::transformation_error;

/**
 * @brief Parses a string representing an object type into its enum.
 *
 * @param s string with an object type
 */
dogen::dia::object_types parse_object_type(const std::string s) {
    dogen::dia::object_types r;
    try {
        using dogen::dia::utility::parse_object_type;
        r = parse_object_type(s);
    } catch(const std::exception& e) {
        std::ostringstream stream;
        stream << error_parsing_object_type << "'" << s
               << "'. Error: " << e.what();
        BOOST_LOG_SEV(lg, error) << stream.str();
        throw transformation_error(stream.str());
    }
    return r;
}

}

namespace dogen {
namespace generator {
namespace modeling {

dia_to_sml::
dia_to_sml(const dia::diagram& diagram, const std::string& model_name,
    const std::string& external_package_path, bool is_target, bool verbose)
    : diagram_(diagram),
      model_name_(model_name),
      external_package_path_(
          sml::utility::identifier_parser::parse_scoped_name(
              external_package_path)),
      is_target_(is_target),
      verbose_(verbose),
      package_transformer_(model_name_, external_package_path_, verbose_),
      pod_transformer_(model_name_, external_package_path_, is_target_,
          verbose_),
      enumeration_transformer_(model_name_, external_package_path_, is_target_,
          verbose_),
      exception_transformer_(model_name_, external_package_path_, is_target_,
          verbose_) {

    BOOST_LOG_SEV(lg, debug) << "Initialised with configuration:"
                             << " model_name: " << model_name_
                             << " external_package_path: "
                             << external_package_path
                             << " is_target: " << is_target_
                             << " verbose: " << verbose_;
}


bool dia_to_sml::is_ignorable_object(const dia::object& o) {
    using dia::object_types;
    const auto ot(parse_object_type(o.type()));
    return ot == object_types::uml_note || ot == object_types::uml_message;
}

void dia_to_sml::
setup_data_structures(const std::vector<dia::object>& objects) {
    BOOST_LOG_SEV(lg, debug) << "Setting up data structures";

    for (const auto o : objects) {
        if (is_ignorable_object(o))
            continue;

        if (package_transformer_.is_processable(o)) {
            package_transformer_.add_object(o);
            continue;
        }

        if (enumeration_transformer_.is_processable(o)) {
            enumeration_transformer_.add_object(o);
            continue;
        }

        if (exception_transformer_.is_processable(o)) {
            exception_transformer_.add_object(o);
            continue;
        }

        if (pod_transformer_.is_processable(o)) {
            pod_transformer_.add_object(o);
            continue;
        }

        throw transformation_error(unsupported_object_type + o.id());
    }
}

sml::model dia_to_sml::transform() {
    BOOST_LOG_SEV(lg, info) << "Transforming diagram: " << model_name_;
    BOOST_LOG_SEV(lg, debug) << "Contents: " << diagram_;

    for (dia::layer layer : diagram_.layers())
        setup_data_structures(layer.objects());
    packages_ = package_transformer_.transform();

    const auto pods(pod_transformer_.transform(packages_));
    const auto enumerations(enumeration_transformer_.transform(packages_));
    const auto exceptions(exception_transformer_.transform(packages_));

    std::unordered_map<dogen::sml::qualified_name, dogen::sml::package>
        packages;
    for (const auto p : packages_)
        packages.insert(std::make_pair(p.second.name(), p.second));

    std::unordered_map<dogen::sml::qualified_name, dogen::sml::primitive>
        primitives;

    using sml::model;
    return model(model_name_, packages, pods, primitives, enumerations,
        exceptions, external_package_path_);
}

} } }
