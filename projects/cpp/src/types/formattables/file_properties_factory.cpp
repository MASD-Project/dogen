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
#include "dogen/cpp/io/formattables/file_properties_io.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/file_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.file_properties_factory"));

const std::string duplicate_formatter_name("Duplicate formatter name: ");
const std::string duplicate_qname("Duplicate qname: ");
const std::string unsupported_object_type("Object type is not supported: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::pair<sml::qname,
          std::unordered_map<std::string, file_properties>
          >
file_properties_factory::generate(const settings::selector& s,
    const std::forward_list<
        std::shared_ptr<formattables::provider_interface> >& providers,
    const sml::qname& qn) const {

    std::unordered_map<std::string, file_properties> r;

    for (const auto p : providers) {
        const auto fp(p->provide_file_properties(s, qn));
        const auto i(r.insert(std::make_pair(p->formatter_name(), fp)));

        if (!i.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << p->formatter_name();
            BOOST_THROW_EXCEPTION(
                building_error(duplicate_formatter_name + p->formatter_name()));
        }
    }
    return std::make_pair(qn, r);
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, file_properties>
    >
file_properties_factory::file_properties_for_objects(
    const settings::selector& s,
    const provider_selector_interface& ps,
    const std::unordered_map<sml::qname, sml::object>& objects) const {

    std::unordered_map<sml::qname,
                       std::unordered_map<std::string, file_properties>
                       > r;

    for (const auto& pair : objects) {
        bool inserted(false);
        const auto qn(pair.first);
        const auto o(pair.second);

        const auto ng(sml::generation_types::no_generation);
        if (o.generation_type() == ng)
            continue;

        const auto ot(o.object_type());
        const auto& p(ps.select_providers_for_object(ot));
        // FIXME: ps can be empty for now
        if (!p.empty()) {
            inserted = r.insert(generate(s, p, qn)).second;

            if (!inserted) {
                const auto n(sml::string_converter::convert(o.name()));
                BOOST_LOG_SEV(lg, error) << duplicate_qname << n;
                BOOST_THROW_EXCEPTION(building_error(duplicate_qname + n));
            }
        }
    }

    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, file_properties>
    >
file_properties_factory::make(const settings::selector& s,
    const provider_selector_interface& ps, const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Building all file names.";

    const auto r(file_properties_for_objects(s, ps, m.objects()));

    BOOST_LOG_SEV(lg, debug) << "Finished building file names.";
    BOOST_LOG_SEV(lg, debug) << "File names: " << r;
    return r;
}

} } }
