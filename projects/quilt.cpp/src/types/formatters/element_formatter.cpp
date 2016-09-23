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
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.element_formatter"));

const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

element_formatter::
element_formatter(const context_factory& f, const container& c)
    : factory_(f), container_(c) { }

std::forward_list<dogen::formatters::file> element_formatter::format(
    const std::forward_list<std::shared_ptr<file_formatter_interface>>&
    formatters, const yarn::element& e) const {

    std::forward_list<dogen::formatters::file> r;
    for (const auto& ptr : formatters) {
        const auto& f(*ptr);
        const auto id(e.name().id());
        const auto fmtn(f.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << id << "' with '"
                                 << fmtn << "'";

        const auto ctx(factory_.make(e.name().id()));
        const auto fc(ctx.element_configuration().formatter_configuration());
        const auto i(fc.find(fmtn));
        if (i == fc.end()) {
            BOOST_LOG_SEV(lg, error) << formatter_properties_not_found << fmtn;
            BOOST_THROW_EXCEPTION(
                workflow_error(formatter_properties_not_found + fmtn));
        }

        const auto is_formatter_enabled(i->second.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter not enabled for type.";
            continue;
        }

        auto file(f.format(ctx, e));
        const auto pg(yarn::generation_types::partial_generation);
        file.overwrite(e.generation_type() != pg);

        // FIXME: hack to handle services
        if (e.generation_type() == pg) {
            BOOST_LOG_SEV(lg, debug) << "Emptying out content.";
            file.content().clear();
        }

        r.push_front(file);
        BOOST_LOG_SEV(lg, debug) << "Finished formatting: '" << id << "'"
                                 << " File path: " << file.path();
    }
    return r;
}

std::forward_list<dogen::formatters::file> element_formatter::
format(const yarn::element& e) const {
    const auto ti(std::type_index(typeid(e)));
    const auto& i(container_.file_formatters_by_type_index().find(ti));
    if (i == container_.file_formatters_by_type_index().end()) {
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, warn) << "No formatters found for element: " << id;
        return std::forward_list<dogen::formatters::file>();
    }

    const auto r(format(i->second, e));
    return r;
}

} } } }
