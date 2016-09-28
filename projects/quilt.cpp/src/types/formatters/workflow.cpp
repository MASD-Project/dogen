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
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/workflow_error.hpp"
#include "dogen/quilt.cpp/io/formattables/formatter_configuration_io.hpp"
#include "dogen/quilt.cpp/types/formatters/context.hpp"
#include "dogen/quilt.cpp/types/formatters/element_formatter.hpp"
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

    const auto& fc(registrar().formatter_container());
    const auto& ffbfn(fc.file_formatters_by_formatter_name());

    std::forward_list<dogen::formatters::file> r;
    auto& fmtt_cfgs(ec.formatter_configuration());
    for (const auto& pair : fmtt_cfgs) {
        const auto& fmtn(pair.first);
        const auto& fmt_cfg(pair.second);
        const auto i(ffbfn.find(fmtn));
        if (i == ffbfn.end()) {
            BOOST_LOG_SEV(lg, error) << missing_formatter << fmtn;
            BOOST_THROW_EXCEPTION(
                workflow_error(missing_formatter + fmtn));
        }

        const auto& formatter(*i->second);
        BOOST_LOG_SEV(lg, debug) << "Formatting: '" << id << "' with '"
                                 << fmtn << "'";

        const auto is_formatter_enabled(fmt_cfg.enabled());
        if (!is_formatter_enabled) {
            BOOST_LOG_SEV(lg, debug) << "Formatter is disabled.";
            continue;
        }

        const auto& hf(fc.helper_formatters());
        const auto& sa(fm.streaming_annotations());
        const auto ffff(fm.facet_directory_for_facet());
        context ctx(sa, ec, ffff, hf);

        auto file(formatter.format(ctx, e));
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
workflow::execute_new(const formattables::model& fm) const {
    std::forward_list<dogen::formatters::file> r;
    for (const auto& formattable : fm.formattables()) {
        const auto& fmt_cfg(formattable.configuration());
        for (const auto& segment : formattable.element_segments()) {
            const auto& e(*segment);
            r.splice_after(r.before_begin(), format(fm, e, fmt_cfg));
        }
    }
    return r;
}

std::forward_list<dogen::formatters::file>
workflow::execute(const annotations::streaming_annotations_repository& ssrp,
    const formattables::element_properties_repository& eprp,
    const std::forward_list<
    boost::shared_ptr<yarn::element> >& elements) const {

    BOOST_LOG_SEV(lg, info) << "Starting workflow.";

    std::forward_list<dogen::formatters::file> r;
    context_factory factory(ssrp, eprp, registrar().formatter_helpers());
    element_formatter ef(factory, registrar().formatter_container());
    for (const auto e : elements) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e->name().id();
        r.splice_after(r.before_begin(), ef.format(*e));
    }

    BOOST_LOG_SEV(lg, debug) << "Files generated: ";
    for (const auto& file : r)
        BOOST_LOG_SEV(lg, debug) << "Name: " << file.path().generic_string();

    BOOST_LOG_SEV(lg, info) << "Finished workflow.";
    return r;
}

} } } }
