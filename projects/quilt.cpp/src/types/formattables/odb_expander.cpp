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
#include <sstream>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.odb_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class odb_properties_generator : public yarn::element_visitor {
public:
    explicit odb_properties_generator(const odb_expander::type_group& tg);

private:
    std::list<std::string> make_odb_pragmas(const odb_expander::type_group& tg,
        const annotations::annotation& o) const;

public:
    /*
     * We are only interested in yarn objects and primitives; all
     * other element types do not need helpers.
     */
    using yarn::element_visitor::visit;
    void visit(const yarn::object& o);
    void visit(const yarn::primitive& p);

public:
    const boost::optional<odb_properties>& result() const;

private:
    const odb_expander::type_group& type_group_;
    boost::optional<odb_properties> result_;
};

odb_properties_generator::odb_properties_generator(
    const odb_expander::type_group& tg) : type_group_(tg) {}

std::list<std::string>
odb_properties_generator::make_odb_pragmas(const odb_expander::type_group& tg,
    const annotations::annotation& o) const {

    const annotations::entry_selector s(o);
    if (!s.has_entry(tg.odb_pragma))
        return std::list<std::string>();

    return s.get_text_collection_content(tg.odb_pragma);
}

void odb_properties_generator::visit(const yarn::object& o) {
    odb_properties op;
    op.top_level_odb_pragmas(make_odb_pragmas(type_group_, o.annotation()));
    for (const auto& attr : o.local_attributes()) {
        const auto id(attr.name().id());
        const auto pragmas(make_odb_pragmas(type_group_, attr.annotation()));
        if (pragmas.empty())
            continue;

        op.attribute_level_odb_pragmas()[id] = pragmas;
    }

    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    const bool has_attribute_pragmas(!op.attribute_level_odb_pragmas().empty());
    const bool has_pragmas(has_top_level_pragmas || has_attribute_pragmas);

    if (has_pragmas)
        result_ = op;
}

void odb_properties_generator::visit(const yarn::primitive& p) {
    odb_properties op;
    op.top_level_odb_pragmas(make_odb_pragmas(type_group_, p.annotation()));
    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    if (!has_top_level_pragmas)
        return;

    /*
     * For primitives, we need to inject manually the attribute level
     * pragmas, if there was a top-level pragma. This is because users
     * cannot see the internal attribute.
     *
     * We add this pragma so as to name the primitive's internal value
     * attribute with the name of the primitive itself. This is done
     * so that when ODB maps the value type, it generates a column
     * name with just the primitive simple name - rather than
     * primitive simple name plus the postfix "_value".
     */
    std::ostringstream s;
    const auto& attr(p.value_attribute());
    s << "column(\"" << p.name().simple() << "\")";
    const auto pragmas(std::list<std::string> { s.str() });

    const auto id(attr.name().id());
    op.attribute_level_odb_pragmas()[id] = pragmas;
    result_ = op;
}

const boost::optional<odb_properties>&
odb_properties_generator::result() const {
    return result_;
}

std::ostream& operator<<(std::ostream& s,
    const odb_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "odb_expander::type_group\"" << ", "
      << "\"odb_pragma\": " << v.odb_pragma
      << " }";

    return s;
}

odb_expander::type_group odb_expander::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto& cc(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.select_type_by_name(cc);

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;
    return r;
}

void odb_expander::
expand(const annotations::type_repository& atrp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding odb configuration.";

    const auto tg(make_type_group(atrp));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the element
         * extensions can be ignored.
         */
        auto segment(formattable.master_segment());

        /*
         * We only need to generate the aspect configuration for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect configurations must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        if (segment->origin_type() != yarn::origin_types::target)
            continue;


        /*
         * Update the odb properties, if any exist.
         */
        const auto& e(*segment);
        odb_properties_generator g(tg);
        e.accept(g);

        if (!g.result())
            continue;

        auto& eprops(formattable.element_properties());
        eprops.odb_properties(*g.result());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb configuration. ";
}

} } } }
