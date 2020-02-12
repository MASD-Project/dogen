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
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/pair_io.hpp"
#include "dogen.assets/types/meta_model/orm/common_odb_options.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.generation.cpp/types/fabric/odb_target.hpp"
#include "dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "dogen.generation.cpp/types/fabric/msbuild_targets.hpp"
#include "dogen.generation.cpp/types/fabric/odb_targets.hpp"
#include "dogen.generation.cpp/types/element_visitor.hpp"
#include "dogen.generation.cpp/types/formatters/odb/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formattables/expansion_error.hpp"
#include "dogen.generation.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen.generation.cpp/types/formattables/build_files_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("generation.cpp.formattables.build_files_expander"));

const std::string separator("_");
const std::string missing_odb_options("Could not find the ODB Options element");
const std::string missing_qualified_name(
    "Qualified name not found for object: ");

}

namespace dogen::generation::cpp::formattables {

bool odb_target_comparer(
    const fabric::odb_target& lhs, const fabric::odb_target& rhs) {
    return lhs.name() < rhs.name();
}

class odb_targets_factory : public element_visitor {
public:
    odb_targets_factory(const model& fm,
        const locator& l, const assets::meta_model::name& model_name);

private:
    void generate_targets(const assets::meta_model::name& n);

public:
    using element_visitor::visit;
    void visit(const assets::meta_model::orm::common_odb_options& coo);
    void visit(const assets::meta_model::structural::object& o);
    void visit(const assets::meta_model::structural::primitive& p);

public:
    const fabric::odb_targets& result() const;

private:
    const model& model_;
    const locator locator_;
    const std::string target_name_;
    fabric::odb_targets result_;
};

odb_targets_factory::odb_targets_factory(const model& fm, const locator& l,
    const assets::meta_model::name& model_name)
    : model_(fm), locator_(l),
      target_name_("odb_" + boost::join(model_name.location().model_modules(),
              separator)) {
    result_.main_target_name(target_name_);
}

void odb_targets_factory::
generate_targets(const assets::meta_model::name& n) {
    fabric::odb_target t;
    t.name(target_name_ + separator + n.simple());
    t.comment("ODB " + n.simple());

    /*
     * We need to compute relative paths, from the project directory
     * into the headers project directory.
     */
    const auto& l(locator_);
    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    const auto odb_fp(l.make_full_path_for_cpp_header(n, odb_arch)
        .parent_path());
    const auto src_dir(l.make_full_path_to_implementation_directory());
    const auto rp(odb_fp.lexically_relative(src_dir));
    t.output_directory(rp.generic_string());

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto tp(l.make_full_path_for_cpp_header(n, types_arch));
    t.types_file(tp.lexically_relative(src_dir).generic_string());

    const auto odb_options_rp(locator_.make_relative_path_for_odb_options(n,
            odb_arch, false/*include_source_directory*/));
    t.object_odb_options(odb_options_rp.generic_string());

    BOOST_LOG_SEV(lg, debug) << "Databases: " << model_.odb_databases();
    const auto odb_rp(odb_options_rp.parent_path().generic_string());
    const auto db_count(model_.odb_databases().size());
    for (const auto& db : model_.odb_databases()) {
        if (db == "common")
            continue;

        std::ostringstream os;
        if (db_count > 1)
            os << n.simple() << "-odb-" << db << ".cxx";
        else
            os << n.simple() << "-odb.cxx";

        const auto file_name(os.str());

        std::pair<std::string, std::string> pair;
        pair.first = t.output_directory() + "/" + file_name;
        pair.second = odb_rp + "/";
        t.move_parameters().push_back(pair);
    }
    result_.targets().push_back(t);
}

void odb_targets_factory::
visit(const assets::meta_model::orm::common_odb_options& coo) {
    const auto arch(formatters::odb::traits::new_common_odb_options_archetype());
    result_.common_odb_options(
        locator_.make_relative_path_for_odb_options(coo.name(), arch,
            false/*include_source_directory*/).generic_string()
        );
}

void odb_targets_factory::
visit(const assets::meta_model::structural::object& o) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!o.orm_properties())
        return;

    const auto& n(o.name());
    generate_targets(n);
}

void odb_targets_factory::
visit(const assets::meta_model::structural::primitive& p) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!p.orm_properties())
        return;

    const auto& n(p.name());
    generate_targets(n);
}

const fabric::odb_targets& odb_targets_factory::result() const {
    return result_;
}

class build_files_updater : public element_visitor {
public:
    build_files_updater(const locator& l, const fabric::odb_targets& targets);

public:
    using element_visitor::visit;
    void visit(fabric::cmakelists& c);
    void visit(fabric::msbuild_targets& mt);

private:
    const locator& locator_;
    const fabric::odb_targets& targets_;
};

build_files_updater::build_files_updater(const locator& l,
    const fabric::odb_targets& targets) : locator_(l), targets_(targets) {}

void build_files_updater::visit(fabric::cmakelists& c) {
    c.odb_targets(targets_);
    c.include_directory_path(locator_.include_directory_name());
    c.source_directory_name(locator_.source_directory_name());
    c.tests_directory_name(locator_.tests_directory_name());
    c.header_file_extension(locator_.header_file_extension());
    c.implementation_file_extension(locator_.implementation_file_extension());
}

void build_files_updater::visit(fabric::msbuild_targets& mt) {
    mt.odb_targets(targets_);
}

void build_files_expander::expand(const locator& l, model& fm) const {
    odb_targets_factory f(fm, l, fm.name());
    const auto ott(assets::meta_model::origin_types::target);
    for (auto& pair : fm.formattables()) {
        /*
         * We only want to process target elements; references can be
         * ignored.
         */
        auto& formattable(pair.second);
        auto& segment(formattable.element());
        if (segment->origin_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        const auto& e(*segment);
        e.accept(f);
    }

    /*
     * Obtain the targets and sort them to ensure the container is
     * stable. We obtained the formattables from an unordered map so
     * they could have come in in any order.
     */
    auto odb_targets(f.result());
    odb_targets.targets().sort(odb_target_comparer);

    build_files_updater cu(l, odb_targets);
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& segment(formattable.element());
        if (segment->origin_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        auto& e(*segment);
        e.accept(cu);
    }
}

}
