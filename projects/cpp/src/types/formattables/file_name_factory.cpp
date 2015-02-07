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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_types_io.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/name_builder.hpp"
#include "dogen/cpp/io/formatters/formatter_types_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/file_name_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.file_name_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string duplicate_qname("Duplicate qname: ");
const std::string unsupported_object_type("Object type is not supported: ");
const std::string unsupported_formatter_type(
    "Formatter type is not supported: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Generates all of the file names for the formatters and
 * qualified name.
 */
template<typename FormatterInterfacePtr>
std::pair<sml::qname,
          std::unordered_map<std::string, boost::filesystem::path>
          >
generate(const settings::selector& s,
    const std::forward_list<FormatterInterfacePtr>& formatters,
    const sml::qname& qn) {

    std::unordered_map<std::string, boost::filesystem::path> r;

    for (const auto f : formatters) {
        const auto fn(f->make_file_name(s, qn));
        const auto i(r.insert(std::make_pair(f->formatter_name(), fn)));

        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << f->formatter_name();
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + f->formatter_name()));
        }
    }
    return std::make_pair(qn, r);
};


formatters::formatter_types file_name_factory::
formatter_type_for_object_type(const sml::object_types ot) const {
    switch(ot) {
    case sml::object_types::factory:
    case sml::object_types::user_defined_service:
    case sml::object_types::user_defined_value_object:
    case sml::object_types::entity:
    case sml::object_types::keyed_entity:
    case sml::object_types::versioned_key:
    case sml::object_types::unversioned_key:
    case sml::object_types::visitor:
        return formatters::formatter_types::class_formatter;
        break;

    case sml::object_types::exception:
        return formatters::formatter_types::exception_formatter;
        break;

    default:
        BOOST_LOG_SEV(lg, error) << unsupported_object_type << ot;
        BOOST_THROW_EXCEPTION(building_error(unsupported_object_type +
                boost::lexical_cast<std::string>(ot)));
    };
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, boost::filesystem::path>
    >
file_name_factory::file_name_for_objects(
    const settings::selector& s, const formatters::container& c,
    const std::unordered_map<sml::qname, sml::object>& objects) const {

    std::unordered_map<sml::qname,
                       std::unordered_map<std::string, boost::filesystem::path>
                       > r;

    for (const auto& pair : objects) {
        bool inserted(false);
        const auto qn(pair.first);
        const auto o(pair.second);

        const auto ng(sml::generation_types::no_generation);
        if (o.generation_type() == ng)
            continue;

        const auto ft(formatter_type_for_object_type(o.object_type()));
        switch(ft) {
        case formatters::formatter_types::class_formatter:
            inserted = r.insert(generate(s, c.class_formatters(), qn)).second;
            break;
        default: {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << unsupported_formatter_type << ft
                                     << " name: " << n;
            // FIXME
            inserted = true;
            // BOOST_THROW_EXCEPTION(building_error(unsupported_formatter_type +
            //         boost::lexical_cast<std::string>(ft)));
        } };

        if (!inserted) {
            const auto n(sml::string_converter::convert(o.name()));
            BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
        }
    }

    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, boost::filesystem::path>
    >
file_name_factory::build(const settings::selector& s,
    const formatters::container& c, const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Building all file names.";

    const auto r(file_name_for_objects(s, c, m.objects()));

    BOOST_LOG_SEV(lg, debug) << "Finished building file names.";
    BOOST_LOG_SEV(lg, debug) << "File names: " << r;
    return r;
}

} } }
