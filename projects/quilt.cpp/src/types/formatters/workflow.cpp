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
#include <iterator>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_configuration_io.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.workflow"));

const std::string missing_formatter("Formatter not found: ");
const std::string formatter_properties_not_found(
    "Could not find properties for formatter: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::shared_ptr<cpp::formatters::registrar> workflow::registrar_;

cpp::formatters::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<cpp::formatters::registrar>();

    return *registrar_;
}

std::forward_list<dogen::formatters::file>
workflow::format(const formattables::model& fm, const yarn::element& e,
    const formattables::element_configuration& ec) const {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    const auto ti(std::type_index(typeid(e)));
    BOOST_LOG_SEV(lg, debug) << "Type index: " << ti.name();

    std::forward_list<dogen::formatters::file> r;
    const auto& fc(registrar().formatter_container());
    const auto i(fc.file_formatters_by_type_index().find(ti));
    if (i == fc.file_formatters_by_type_index().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for type: " << ti.name();
        return r;
    }

    auto& fmt_cfgs(ec.formatter_configurations());
    const auto& fmts(i->second);
    for (const auto& fmt_ptr : fmts) {
        const auto& fmt(*fmt_ptr);
        const auto fmtn(fmt.ownership_hierarchy().formatter_name());
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << id << "' with '"
                                 << fmtn << "'";

        const auto j(fmt_cfgs.find(fmtn));
        if (j == fmt_cfgs.end()) {
            BOOST_LOG_SEV(lg, error) << missing_formatter << fmtn;
            BOOST_THROW_EXCEPTION(workflow_error(missing_formatter + fmtn));
        }

        const auto& fmt_cfg(j->second);
        const auto is_formatter_enabled(fmt_cfg.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter is disabled.";
            continue;
        }

        const auto& hlp_fmt(fc.helper_formatters());
        const auto fct_cfgs(fm.facet_configurations());
        context ctx(ec, fm, hlp_fmt);

        auto file(fmt.format(ctx, e));
        const auto pg(yarn::generation_types::partial_generation);
        file.overwrite(e.generation_type() != pg);

        // FIXME: hack to handle services
        if (e.generation_type() == pg) {
            BOOST_LOG_SEV(lg, debug) << "Emptying out content.";
            file.content().clear();
        }

        r.push_front(file);
        BOOST_LOG_SEV(lg, debug) << "Finished formatting. id: " << id
                                 << " File path: " << file.path();
    }
    return r;
}

std::forward_list<dogen::formatters::file>
workflow::execute(const formattables::model& fm) const {
    std::forward_list<dogen::formatters::file> r;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& ecfgs(formattable.element_configuration());
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            r.splice_after(r.before_begin(), format(fm, e, ecfgs));
        }
    }
    return r;
}

} } } }
