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
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_target.hpp"
#include "dogen/quilt.cpp/types/fabric/cmakelists.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_targets.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen/quilt.cpp/types/formattables/cmakelists_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.cmakelists_expander"));

const std::string missing_odb_options("Could not find the ODB Options element");
const std::string missing_qualified_name(
    "Qualified name not found for object: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class odb_targets_factory : public fabric::element_visitor {
public:
    odb_targets_factory(const locator& l, const yarn::name& model_name);

public:
    using fabric::element_visitor::visit;
    void visit(const fabric::odb_options& oo);
    void visit(const yarn::object& o);

public:
    const fabric::odb_targets& result() const;

private:
    const locator locator_;
    fabric::odb_targets result_;
};

odb_targets_factory::
odb_targets_factory(const locator& l, const yarn::name& model_name)
    : locator_(l) {
    result_.main_target_name("odb_" + model_name.identifiable());
}

void odb_targets_factory::visit(const fabric::odb_options& oo) {
    const auto arch(formatters::odb::traits::odb_options_archetype());
    result_.options_file(
        locator_.make_relative_path_for_odb_options(oo.name(), arch)
        .generic_string()
        );
}

void odb_targets_factory::visit(const yarn::object& o) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!o.orm_properties())
        return;

    fabric::odb_target t;
    const auto& n(o.name());
    t.name(n.identifiable());

    const auto i(n.qualified().find(yarn::languages::cpp));
    if (i == n.qualified().end()) {
        BOOST_LOG_SEV(lg, error) << missing_qualified_name << n.id();
        BOOST_THROW_EXCEPTION(expansion_error(missing_qualified_name + n.id()));
    }
    const auto qn(i->second);
    t.comment("ODB " + qn);

    /*
     * We need to compute relative paths, from the project directory
     * into the headers project directory.
     */
    const auto& l(locator_);
    const auto id(l.make_full_path_to_include_directory());
    const auto src_dir(l.make_full_path_to_implementation_directory());
    const auto rp(id.lexically_relative(src_dir));
    t.output_directory(rp.generic_string());

    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    t.pragmas_file(l.make_inclusion_path_for_cpp_header(n, odb_arch)
        .generic_string());

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto tp(l.make_full_path_for_cpp_header(n, types_arch));
    t.types_file(tp.lexically_relative(src_dir).generic_string());

    const auto odb_fctn(formatters::odb::traits::facet());
    const auto odb_rp(locator_.make_relative_include_path_for_facet(odb_fctn,
            true/*for_include_statement*/));

    // --include-regex '%(.*).hpp%<#= o.types_include_directory_path() #>/$1.hpp%'
    std::ostringstream os;
    os << "%(^[a-zA-Z0-9_]+)-odb(.*)%" << odb_rp.generic_string() << "$1-odb$2";
    t.include_regexes().push_back(os.str());

    os.str("");

    const auto types_fctn(formatters::types::traits::facet());
    const auto types_rp(locator_.make_relative_include_path_for_facet(
            types_fctn, true/*for_include_statement*/));

    os << "%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.generic_string() << "/$1-odb$2%";
    t.include_regexes().push_back(os.str());

    t.header_guard_prefix(header_guard_factory::make(types_rp.parent_path()));

    // FIXME: compute move targets

    result_.targets().push_back(t);
}

const fabric::odb_targets& odb_targets_factory::result() const {
    return result_;
}

class cmakelists_updater : public fabric::element_visitor {
public:
    cmakelists_updater(const locator& l, const fabric::odb_targets& targets);

public:
    using fabric::element_visitor::visit;
    void visit(fabric::cmakelists& c);

private:
    const locator& locator_;
    const fabric::odb_targets& targets_;
};

cmakelists_updater::cmakelists_updater(const locator& l,
    const fabric::odb_targets& targets) : locator_(l), targets_(targets) {}

void cmakelists_updater::visit(fabric::cmakelists& c) {
    c.odb_targets(targets_);
    c.include_directory_path(locator_.include_directory_name());
    c.source_directory_name(locator_.source_directory_name());
    c.header_file_extension(locator_.header_file_extension());
    c.implementation_file_extension(locator_.implementation_file_extension());
}

void cmakelists_expander::expand(const locator& l, model& fm) const {
    odb_targets_factory f(l, fm.name());
    for (auto& pair : fm.formattables()) {
        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the extensions
         * can be ignored.
         */
        auto& segment(formattable.master_segment());
        if (segment->origin_type() != yarn::origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        const auto& e(*segment);
        e.accept(f);
    }

    cmakelists_updater cu(l, f.result());
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& segment(formattable.master_segment());
        if (segment->origin_type() != yarn::origin_types::target) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        auto& e(*segment);
        e.accept(cu);
    }
}

} } } }
