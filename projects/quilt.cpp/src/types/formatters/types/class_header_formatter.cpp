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
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/properties/inclusion_dependencies_provider_interface.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/types/class_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

namespace {

class provider final : public properties::
        inclusion_dependencies_provider_interface<yarn::object> {
public:
    std::string formatter_name() const override;

    boost::optional<std::list<std::string> >
        provide(const properties::inclusion_dependencies_builder_factory& f,
        const yarn::object& o) const override;
};

std::string provider::formatter_name() const {
    return class_header_formatter::static_formatter_name();
}

boost::optional<std::list<std::string> >
provider::provide(const properties::inclusion_dependencies_builder_factory& f,
    const yarn::object& o) const {

    auto builder(f.make());

    // FIXME: if immutable there is no swap.
    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    const auto io_fctn(formatters::io::traits::facet_name());
    const auto self_fn(class_header_formatter::static_formatter_name());
    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), self_fn));
    const bool requires_io(io_enabled && in_inheritance);

    const auto ios(inclusion_constants::std::iosfwd());
    if (requires_io)
        builder.add(ios);

    using ser = formatters::serialization::traits;
    const auto ser_fwd_fn(ser::forward_declarations_formatter_name());
    builder.add(o.name(), ser_fwd_fn);

    const auto fwd_fn(traits::forward_declarations_formatter_name());
    builder.add(o.transparent_associations(), self_fn);
    builder.add(o.opaque_associations(), fwd_fn);
    builder.add(o.parent(), self_fn);

    using hash = formatters::hash::traits;
    const auto hash_fn(hash::traits::class_header_formatter_name());
    builder.add(o.associative_container_keys(), hash_fn);

    if (o.is_visitation_root()) {
        /*
         * For the root parent we can just do a forward declaration of
         * the visitor since we use it on pure virtual functions.
         */
        builder.add(*o.base_visitor(), fwd_fn);
    } else {
        if (o.is_visitation_leaf()) {
            /*
             * For leaves with a visitable root parent, we need to
             * include the visitor itself as we call methods on
             * it. Note that for visitor inheritance, this will result
             * on us including the visitor's descendant rather than
             * the visitor parent; as it happens, the code needs
             * both. This is the right thing to do because the
             * descendant includes the parent.
             */
            builder.add(*o.base_visitor(), self_fn);
        }
    }
    return builder.build();
}

}

std::string class_header_formatter::static_formatter_name() {
    return traits::class_header_formatter_name();
}

std::string class_header_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
class_header_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_header_formatter::static_formatter_name(),
            formatters::traits::header_formatter_group_name());
    return r;
}

file_types class_header_formatter::file_type() const {
    return file_types::cpp_header;
}

properties::origin_types
class_header_formatter::formattable_origin_type() const {
    return properties::origin_types::external;
}

void class_header_formatter::register_inclusion_dependencies_provider(
    properties::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file class_header_formatter::
format(const context& ctx, const yarn::object& o) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), o.name().id());
    const auto r(class_header_formatter_stitch(a, o));
    return r;
}

} } } } }
