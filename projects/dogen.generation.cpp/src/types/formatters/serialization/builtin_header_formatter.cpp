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
#include "dogen.logical/types/meta_model/structural/builtin.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/builtin_header_formatter.hpp"

namespace dogen::generation::cpp::formatters::serialization {

std::string builtin_header_formatter::static_id() {
    return traits::builtin_header_archetype();
}

std::string builtin_header_formatter::id() const {
    return static_id();
}

physical::location
builtin_header_formatter::archetype_location() const {
    static physical::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          builtin_header_formatter::static_id());
    return r;
}

const logical::meta_model::name& builtin_header_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_builtin_name());
    return r;
}

std::string builtin_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types builtin_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path builtin_header_formatter::inclusion_path(
    const formattables::locator& l, const logical::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path builtin_header_formatter::full_path(
    const formattables::locator& l, const logical::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> builtin_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::meta_model::element& /*e*/) const {
    static const std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact builtin_header_formatter::
format(const context& /*ctx*/, const logical::meta_model::element& e) const {
    extraction::meta_model::artefact r;
    r.origin_element_id(e.origin_element_id());
    r.origin_sha1_hash(e.origin_sha1_hash());
    return r;
}

}
