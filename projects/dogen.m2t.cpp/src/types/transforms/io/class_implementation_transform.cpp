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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.m2t.cpp/types/transforms/io/class_implementation_transform.hpp"

namespace dogen::m2t::cpp::transforms::io {

std::string class_implementation_transform::static_id() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_transform::id() const {
    return static_id();
}

physical::entities::location
class_implementation_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          cpp::traits::implementation_part(), traits::facet(),
          class_implementation_transform::static_id());
    return r;
}

const logical::entities::name& class_implementation_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

inclusion_support_types class_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_transform::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> class_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    const auto& o(assistant::as<logical::entities::structural::object>(e));
    auto builder(f.make());
    const auto ch_fn(traits::class_header_archetype());
    builder.add(o.name(), ch_fn);

    builder.add(o.opaque_associations(), ch_fn);

    const auto io_carch(transforms::io::traits::canonical_archetype());
    const auto self_fn(class_implementation_transform::static_id());
    const bool io_enabled(builder.is_enabled(o.name(), self_fn));

    if (!io_enabled)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);
    builder.add(o.transparent_associations(), io_carch);
    builder.add(o.opaque_associations(), io_carch);
    builder.add(o.parents(), io_carch);

    return builder.build();
}

physical::entities::artefact class_implementation_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<logical::entities::structural::object>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        a.add_helper_methods(o.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto sn(o.name().simple());
            const auto qn(a.get_qualified_name(o.name()));
            const bool no_arg(!o.is_parent() && o.parents().empty() &&
                o.local_attributes().empty());
a.stream() << std::endl;
a.stream() << "std::ostream& operator<<(std::ostream& s, const " << sn << "&" << (no_arg ? "" : " v") << ") {" << std::endl;
            if (o.is_parent() || !o.parents().empty()) {
a.stream() << "    v.to_stream(s);" << std::endl;
a.stream() << "    return(s);" << std::endl;
            } else
                io::inserter_implementation_helper(a, o, false/*inside_class*/);
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}
