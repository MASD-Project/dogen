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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter.hpp"

namespace {

using namespace dogen::utility::log;
using namespace dogen::quilt::cpp::formatters::io;
static logger lg(
    logger_factory(class_implementation_formatter::static_artefact()));

const std::string not_supported("Inclusion path is not supported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string class_implementation_formatter::static_artefact() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
class_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(formatters::traits::kernel(), traits::facet(),
            class_implementation_formatter::static_artefact());
    return r;
}

std::type_index class_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto& o(assistant::as<yarn::object>(static_artefact(), e));
    auto builder(f.make());
    const auto ch_fn(traits::class_header_archetype());
    builder.add(o.name(), ch_fn);

    builder.add(o.opaque_associations(), ch_fn);

    const auto io_cfmtn(formatters::io::traits::canonical_archetype());
    const auto self_fn(class_implementation_formatter::static_artefact());
    const bool io_enabled(builder.is_enabled(o.name(), self_fn));

    if (!io_enabled)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);

    const auto si(builder.make_special_includes(o));
    if (si.requires_stream_manipulators)
        builder.add(inclusion_constants::boost::io::ios_state());

    if (si.has_std_string)
        builder.add(inclusion_constants::boost::algorithm::string());

    if (si.has_ptree) {
        builder.add(inclusion_constants::std::sstream());
        builder.add(inclusion_constants::boost::algorithm::string());
    }

    if (si.has_variant)
        builder.add(inclusion_constants::boost::visitor::apply_visitor());

    builder.add(o.transparent_associations(), io_cfmtn);
    builder.add(o.opaque_associations(), io_cfmtn);
    builder.add(o.parent(), io_cfmtn);

    return builder.build();
}

inclusion_support_types
class_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {
    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path class_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

dogen::formatters::artefact class_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& o(a.as<yarn::object>(static_artefact(), e));
    const auto r(class_implementation_formatter_stitch(a, o));
    return r;
}

} } } } }
