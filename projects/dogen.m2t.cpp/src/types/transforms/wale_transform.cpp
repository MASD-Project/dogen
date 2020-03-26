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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/utility_formatter.hpp"
#include "dogen.templating/types/wale/workflow.hpp"
#include "dogen.m2t.cpp/types/formattables/artefact_properties.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/wale_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("m2t.cpp.formatters.wale_transform"));

const std::string missing_input("Missing formatting input");

}

namespace dogen::m2t::cpp::transforms {

bool wale_transform::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

physical::entities::artefact
wale_transform::apply(const formattables::locator& l,
    const model_to_text_transform& stock_transform, const context& ctx,
    const logical::entities::element& e) const {
    const auto al(stock_transform.physical_name().location());
    const auto needs_guard(is_header(stock_transform.inclusion_support_type()));
    assistant a(ctx, e, al, needs_guard);

    const auto kvps = std::unordered_map<std::string, std::string> {
        { "class.simple_name", e.name().simple() }
    };

    utility::formatters::utility_formatter uf(a.stream());
    {
        const auto& n(e.name());
        const auto qn(a.get_qualified_name(n));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(n));
            auto snf(a.make_scoped_namespace_formatter(ns));

            const auto fi(a.new_artefact_properties().formatting_input());
            if (fi.empty()) {
                BOOST_LOG_SEV(lg, error) << missing_input;
                BOOST_THROW_EXCEPTION(formatting_error(missing_input));
            }

            const auto p(l.templates_project_path() / fi);
            BOOST_LOG_SEV(lg, debug) << "Using template path: "
                                     << p.generic_string();

            uf.insert_end_line();
            templating::wale::workflow w;
            a.stream() << w.execute(p, kvps);
            uf.insert_end_line();
        }
        uf.insert_end_line();
    }
    return a.make_artefact();
}

}
