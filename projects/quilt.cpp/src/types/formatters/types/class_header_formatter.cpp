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
#include <typeinfo>
#include <boost/make_shared.hpp>
#include "dogen/yarn/types/object.hpp"
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

class provider_hack final :
        public formattables::provider_interface<yarn::primitive> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const yarn::primitive& p) const override;

    formattables::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const formattables::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const formattables::locator& l,
        const yarn::name& n) const override;
};

std::string provider_hack::facet_name() const {
    return traits::facet_name();
}

std::string provider_hack::formatter_name() const {
    return class_header_formatter::static_formatter_name();
}

std::list<std::string> provider_hack::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& /*f*/,
    const yarn::primitive& /*p*/) const {
    static std::list<std::string> r;
    return r;
}

formattables::inclusion_path_support provider_hack::
inclusion_path_support() const {
    return formattables::inclusion_path_support::is_default;
}

boost::filesystem::path
provider_hack::provide_inclusion_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, formatter_name());
}

boost::filesystem::path
provider_hack::provide_full_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, formatter_name());
}

class provider final :
        public formattables::provider_interface<yarn::object> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const formattables::inclusion_dependencies_builder_factory& f,
        const yarn::object& o) const override;

    formattables::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const formattables::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const formattables::locator& l,
        const yarn::name& n) const override;
};

std::string provider::facet_name() const {
    return traits::facet_name();
}

std::string provider::formatter_name() const {
    return class_header_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::object& o) const {

    auto builder(f.make());

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    const auto io_fn(formatters::io::traits::class_header_formatter_name());
    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), io_fn));
    const bool requires_io(io_enabled && in_inheritance);

    const auto ios(inclusion_constants::std::iosfwd());
    if (requires_io)
        builder.add(ios);

    using ser = formatters::serialization::traits;
    const auto ser_fwd_fn(ser::forward_declarations_formatter_name());
    builder.add(o.name(), ser_fwd_fn);

    const auto self_fn(class_header_formatter::static_formatter_name());
    const auto fwd_fn(traits::forward_declarations_formatter_name());
    builder.add(o.transparent_associations(), traits::facet_name());
    builder.add(o.opaque_associations(), fwd_fn);
    builder.add(o.parent(), self_fn);

    using hash = formatters::hash::traits;
    builder.add(o.associative_container_keys(), hash::traits::facet_name());

    if (o.is_visitation_root() || o.is_visitation_leaf()) {
        /*
         * On the header files we only care about the base visitor for
         * all visitation cases; as such we can get away with a
         * forward declaration.
         */
        builder.add(*o.base_visitor(), fwd_fn);
    }
    return builder.build();
}

formattables::inclusion_path_support provider::inclusion_path_support() const {
    return formattables::inclusion_path_support::is_default;
}

boost::filesystem::path
provider::provide_inclusion_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, formatter_name());
}

boost::filesystem::path
provider::provide_full_path(const formattables::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, formatter_name());
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

std::type_index class_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

std::list<std::string> class_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {

    const auto& o(assistant::as<yarn::object>(static_formatter_name(), e));
    auto builder(f.make());

    // algorithm: domain headers need it for the swap function.
    builder.add(inclusion_constants::std::algorithm());

    const auto io_fn(formatters::io::traits::class_header_formatter_name());
    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), io_fn));
    const bool requires_io(io_enabled && in_inheritance);

    const auto ios(inclusion_constants::std::iosfwd());
    if (requires_io)
        builder.add(ios);

    using ser = formatters::serialization::traits;
    const auto ser_fwd_fn(ser::forward_declarations_formatter_name());
    builder.add(o.name(), ser_fwd_fn);

    const auto self_fn(class_header_formatter::static_formatter_name());
    const auto fwd_fn(traits::forward_declarations_formatter_name());
    builder.add(o.transparent_associations(), traits::facet_name());
    builder.add(o.opaque_associations(), fwd_fn);
    builder.add(o.parent(), self_fn);

    using hash = formatters::hash::traits;
    builder.add(o.associative_container_keys(), hash::traits::facet_name());

    if (o.is_visitation_root() || o.is_visitation_leaf()) {
        /*
         * On the header files we only care about the base visitor for
         * all visitation cases; as such we can get away with a
         * forward declaration.
         */
        builder.add(*o.base_visitor(), fwd_fn);
    }
    return builder.build();

}

inclusion_support_types class_header_formatter::
inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_formatter_name());
}

boost::filesystem::path class_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_formatter_name());
}

void class_header_formatter::
register_provider(formattables::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
    rg.register_provider(boost::make_shared<provider_hack>());
}

dogen::formatters::file class_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, ownership_hierarchy(), true/*requires_header_guard*/, id);
    const auto& o(a.as<yarn::object>(static_formatter_name(), e));
    const auto r(class_header_formatter_stitch(a, o));
    return r;
}

} } } } }
