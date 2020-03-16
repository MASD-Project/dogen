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
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/name_factory.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/templates/traits.hpp"
#include "dogen.generation.cpp/types/formatters/templates/logic_less_template_formatter.hpp"

namespace dogen::generation::cpp::formatters::templates {

std::string logic_less_template_formatter::static_id() {
    return traits::logic_less_template_archetype();
}

std::string logic_less_template_formatter::id() const {
    return static_id();
}

physical::entities::location
logic_less_template_formatter::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          logic_less_template_formatter::static_id());
    return r;
}

const logical::entities::name& logic_less_template_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_templating_logic_less_templates_name());
    return r;
}

std::string logic_less_template_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types logic_less_template_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path logic_less_template_formatter::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(logic_less_template_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path logic_less_template_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_templates(n, static_id());
}

std::list<std::string> logic_less_template_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::entities::artefact logic_less_template_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    auto r(a.make_artefact());
    r.overwrite(false);
    return r;
}
}
