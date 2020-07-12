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
#include "dogen.templating/types/wale/instantiator.hpp"
#include "dogen.text.cpp/types/formattables/artefact_properties.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/wale_transform.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.transforms.wale_transform"));

const std::string missing_input("Missing formatting input");

}

namespace dogen::text::cpp::transforms {

bool wale_transform::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

void wale_transform::apply(const formattables::locator& l,
    const model_to_text_transform& stock_transform, const context& ctx,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    const auto pn(stock_transform.archetype().meta_name());
    const auto needs_guard(is_header(stock_transform.inclusion_support_type()));
    assistant ast(ctx, e, pn, needs_guard, a);

    const auto kvps = std::unordered_map<std::string, std::string> {
        { "class.simple_name", e.name().simple() }
    };

    utility::formatters::utility_formatter uf(ast.stream());
    {
        const auto& n(e.name());
        const auto qn(ast.get_qualified_name(n));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(n));
            auto snf(ast.make_scoped_namespace_formatter(ns));

            const auto fi(a.artefact_properties().formatting_input());
            if (fi.empty()) {
                BOOST_LOG_SEV(lg, error) << missing_input;
                BOOST_THROW_EXCEPTION(formatting_error(missing_input));
            }

            const auto p(l.templates_project_path() / fi);
            BOOST_LOG_SEV(lg, debug) << "Using template path: "
                                     << p.generic_string();

            uf.insert_end_line();
            templating::wale::instantiator inst;
            ast.stream() << inst.instantiate(p, kvps);
            uf.insert_end_line();
        }
        uf.insert_end_line();
    }
    ast.update_artefact();
}

}
