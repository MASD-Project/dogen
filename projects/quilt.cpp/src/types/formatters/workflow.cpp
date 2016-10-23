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
#include "dogen/quilt.cpp/io/formattables/artefact_properties_io.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quit.cpp.formatters.workflow"));

const std::string archetype_not_found("Archetype not found: ");

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

bool workflow::is_archetype_enabled(const std::unordered_map<std::string,
    formattables::artefact_properties>& artefact_properties,
    const std::string& archetype) const {

    const auto i(artefact_properties.find(archetype));
    if (i == artefact_properties.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype;
        BOOST_THROW_EXCEPTION(workflow_error(archetype_not_found + archetype));
    }
    return i->second.enabled();
}

dogen::formatters::artefact workflow::format(
    const formattables::model& fm, const yarn::element& e,
    const formattables::element_properties& ep,
    const artefact_formatter_interface& formatter) const {

    const auto id(e.name().id());
    const auto fmtn(formatter.formatter_name());
    BOOST_LOG_SEV(lg, debug) << "Formatting with " << fmtn;

    const auto& frp(registrar().formatter_repository());
    context ctx(ep, fm, frp.helper_formatters());
    const auto r(formatter.format(ctx, e));

    BOOST_LOG_SEV(lg, debug) << "Finished formatting. Path: " << r.path();

    return r;
}

std::forward_list<dogen::formatters::artefact>
workflow::format(const formattables::model& fm, const yarn::element& e,
    const formattables::element_properties& ep) const {

    const auto id(e.name().id());
    BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

    const auto ti(std::type_index(typeid(e)));
    BOOST_LOG_SEV(lg, debug) << "Type index: " << ti.name();

    std::forward_list<dogen::formatters::artefact> r;
    const auto& frp(registrar().formatter_repository());
    const auto i(frp.stock_artefact_formatters_by_type_index().find(ti));
    if (i == frp.stock_artefact_formatters_by_type_index().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for type: " << ti.name();
        return r;
    }

    const auto& fmts(i->second);
    for (const auto& ptr : fmts) {
        const auto& fmt(*ptr);
        const auto arch(fmt.archetype_location().archetype());
        if (!is_archetype_enabled(ep.artefact_properties(), arch)) {
            BOOST_LOG_SEV(lg, debug) << "Archetype is disabled: " << arch;
            continue;
        }

        const auto artefact(format(fm, e, ep, fmt));
        r.push_front(artefact);
    }
    return r;
}

std::forward_list<dogen::formatters::artefact>
workflow::execute(const formattables::model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started formatting. Model " << fm.name().id();
    std::forward_list<dogen::formatters::artefact> r;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& eprops(formattable.element_properties());
        for (const auto& segment : formattable.all_segments()) {
            const auto& e(*segment);
            r.splice_after(r.before_begin(), format(fm, e, eprops));
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished formatting.";
    return r;
}

} } } }
