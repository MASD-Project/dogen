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
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_configuration.hpp"
#include "dogen/quilt.cpp/types/formattables/transformation_error.hpp"
#include "dogen/quilt.cpp/types/formattables/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.transformer"));

const std::string duplicate_formatter("Duplicate formatter name: ");
const std::string duplicate_element("Duplicate element id: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::unordered_map<std::string, formattable> transformer::
transform(const formatters::container& fc, const yarn::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Transforming yarn to formattables.";
    std::unordered_map<std::string, formattable> r;
    for (const auto& e : m.elements()) {
        const auto id(e->name().id());

        formattable fbl;
        fbl.element(e);

        const auto ti(std::type_index(typeid(e)));
        const auto i(fc.file_formatters_by_type_index().find(ti));
        if (i == fc.file_formatters_by_type_index().end()) {
            BOOST_LOG_SEV(lg, trace) << "Element has no formatters: " << id;
            continue;
        }

        auto& fmt_cfg(fbl.configuration().formatter_configuration());
        for (const auto& fmt : i->second) {
            const auto fmtn(fmt->ownership_hierarchy().formatter_name());
            const auto pair(std::make_pair(fmtn, formatter_configuration()));
            const auto ret(fmt_cfg.insert(pair));
            if (!ret.second) {
                BOOST_LOG_SEV(lg, error) << duplicate_formatter << fmtn;
                BOOST_THROW_EXCEPTION(
                    transformation_error(duplicate_formatter + fmtn));
            }
            BOOST_LOG_SEV(lg, trace) << "Added formatter: " << fmtn
                                     << " to element: " << id;
        }

        const auto pair(std::make_pair(id, fbl));
        const auto ret(r.insert(pair));
        if (!ret.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_element << id;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_element + id));
        }
        BOOST_LOG_SEV(lg, trace) << "Inserted element: " << id;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming yarn to formattables.";
    return r;
}

std::forward_list<formattable> transformer::transform(
    const std::unordered_map<std::string, formattable>& formattables) const {

    std::forward_list<formattable> r;
    for (const auto& pair : formattables)
        r.push_front(pair.second);

    return r;
}

} } } }
