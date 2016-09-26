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
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/file_path_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.file_path_expander"));

const std::string missing_formatter_name("Formatter name not found: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void file_path_expander::
expand(const formatters::container& fc, const locator& l,
    std::unordered_map<std::string, formattable>& formattables) const {

    const auto fffn(fc.file_formatters_by_formatter_name());
    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        /*
         * All segments are mapped to the same name, so we can pick
         * one at random. A formattable must have at least one
         * segment, so we can rely on its presence.
         */
        const auto& e(*formattable.element_segments().front());
        const auto n(e.name());
        auto& cfg(formattable.configuration());

        /*
         * Go thorough all the formatter configurations. For each,
         * find the associated formatter and ask it to generate the
         * full path for the file.
         */
        for (auto& fmt_cfg_pair : cfg.formatter_configuration()) {
            const auto fmtn(fmt_cfg_pair.first);
            auto& fmt_cfg(fmt_cfg_pair.second);

            const auto i(fffn.find(fmtn));
            if (i == fffn.end()) {
                BOOST_LOG_SEV(lg, error) << missing_formatter_name << fmtn;
                BOOST_THROW_EXCEPTION(
                    expansion_error(missing_formatter_name + fmtn));
            }

            const auto& fmt(i->second);
            fmt_cfg.file_path(fmt->full_path(l, n));
        }
    }
}

} } } }
