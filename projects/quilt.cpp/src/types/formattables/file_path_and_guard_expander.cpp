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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formatters/file_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/file_path_and_guard_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formattables.file_path_and_guard_expander"));

const std::string empty;
const std::string dot(".");
const std::string separator("_");
const std::string missing_archetype("Archetype not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::string file_path_and_guard_expander::
to_header_guard(const boost::filesystem::path& p) const {
    bool is_first(true);
    std::ostringstream ss;
    for (const auto& token : p) {
        std::string s(token.string());
        boost::replace_all(s, dot, separator);
        boost::to_upper(s);
        ss << (is_first ? empty : separator) << s;
        is_first = false;
    }
    return ss.str();
}


void file_path_and_guard_expander::
expand(const formatters::container& fc, const locator& l, model& fm) const {

    const auto fffn(fc.file_formatters_by_formatter_name());
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        /*
         * It doesn't really matter which segment we choose here since
         * they are both mapped to the same name.
         */
        const auto& e(*formattable.master_segment());
        const auto n(e.name());
        auto& eprops(formattable.element_properties());

        /*
         * Go thorough all the formatter configurations. For each,
         * find the associated formatter and ask it to generate the
         * full path for the file.
         */
        for (auto& fmt_props_pair : eprops.formatter_properties()) {
            const auto arch(fmt_props_pair.first);
            auto& fmt_props(fmt_props_pair.second);

            const auto i(fffn.find(arch));
            if (i == fffn.end()) {
                BOOST_LOG_SEV(lg, error) << missing_archetype << arch;
                BOOST_THROW_EXCEPTION(
                    expansion_error(missing_archetype + arch));
            }

            const auto& fmt(i->second);
            fmt_props.file_path(fmt->full_path(l, n));

            /*
             * If the formatter supports inclusion, we need to compute
             * the header guard as well.
             */
            const auto ns(formatters::inclusion_support_types::not_supported);
            if (fmt->inclusion_support_type() != ns) {
                const auto ip(fmt->inclusion_path(l, n));
                fmt_props.header_guard(to_header_guard(ip));
            }
        }
    }
}

} } } }
