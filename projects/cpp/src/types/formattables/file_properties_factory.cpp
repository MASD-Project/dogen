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
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/io/formattables/file_properties_io.hpp"
#include "dogen/cpp/types/formattables/file_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.file_properties_factory"));

const std::string duplicate_formatter_name("Formatter name already inserted: ");
const std::string formatter_not_found("Formatter not found: ");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::unordered_map<std::string,
                   std::shared_ptr<formattables::includes_factory_interface>
                   > file_properties_factory::
create_includes_factories(const formatters::container& c) const {
    BOOST_LOG_SEV(lg, debug) << "Creating a map of includes factories by id.";

    std::unordered_map<
        std::string,
        std::shared_ptr<formattables::includes_factory_interface>
        > r;

    for (const auto f : c.class_formatters()) {
        auto b(f->make_includes_factory());
        const auto pair(r.insert(std::make_pair(f->formatter_name(), b)));
        if (!pair.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_formatter_name
                                     << f->formatter_name();
            BOOST_THROW_EXCEPTION(building_error(duplicate_formatter_name +
                    f->formatter_name()));
        }
    }

    BOOST_LOG_SEV(lg, debug)
        << "Finished creating a map of includes factories by id.";
    return r;
}

std::unordered_map<
    sml::qname,
    std::unordered_map<std::string, formattables::file_properties> >
file_properties_factory::build(
    const formatters::container& c,
    const std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, boost::filesystem::path> >&
    file_names,
    const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining file settings.";

    std::unordered_map<
        sml::qname,
        std::unordered_map<std::string, formattables::file_properties> > r;

    const auto includes_factories(create_includes_factories(c));
    for (const auto pair : file_names) {
        const auto& qn(pair.first);
        std::unordered_map<std::string, formattables::file_properties> all_props;
        for (const auto other_pair : pair.second) {
            formattables::file_properties fp;
            fp.relative_path(other_pair.second);

            const auto& formatter_name(other_pair.first);
            const auto i(includes_factories.find(formatter_name));
            if (i == includes_factories.end()) {
                BOOST_LOG_SEV(lg, error) << formatter_not_found
                                         << formatter_name;
                BOOST_THROW_EXCEPTION(building_error(formatter_not_found +
                        formatter_name));
            }

            const auto& f(*(i->second));
            auto inc(f.build(m, qn, file_names));
            fp.includes(inc);
            all_props[formatter_name] = fp;
        }
        r[qn] = all_props;
    }

    BOOST_LOG_SEV(lg, debug) << "File settings names: " << r;
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining file settings.";
    return r;
}

} } }
