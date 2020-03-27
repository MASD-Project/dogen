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
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/orm/odb_target.hpp"
#include "dogen.logical/types/entities/orm/odb_targets.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.m2t.cpp/types/transforms/odb/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/expansion_error.hpp"
#include "dogen.m2t.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen.m2t.cpp/types/formattables/build_files_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("m2t.cpp.formattables.build_files_expander"));

const std::string separator("_");
const std::string missing_odb_options("Could not find the ODB Options element");
const std::string missing_qualified_name(
    "Qualified name not found for object: ");

}

namespace dogen::m2t::cpp::formattables {

bool odb_target_comparer(const logical::entities::orm::odb_target& lhs,
    const logical::entities::orm::odb_target& rhs) {
    return lhs.name() < rhs.name();
}

using dogen::logical::entities::element_visitor;

class odb_targets_factory : public element_visitor {
public:
    odb_targets_factory(const model& fm, const locator& l,
        const logical::entities::name& model_name);

private:
    template<typename OdbTargets>
    OdbTargets generate_targets(const logical::entities::name& n);

public:
    using element_visitor::visit;
    void visit(const logical::entities::orm::common_odb_options& coo);
    void visit(const logical::entities::structural::object& o);
    void visit(const logical::entities::structural::primitive& p);

public:
    const logical::entities::orm::odb_targets& result() const;

private:
    const model& model_;
    const locator locator_;
    const std::string target_name_;
    logical::entities::orm::odb_targets result_;
};

odb_targets_factory::odb_targets_factory(const model& fm, const locator& l,
    const logical::entities::name& model_name)
    : model_(fm), locator_(l),
      target_name_("odb_" + boost::join(model_name.location().model_modules(),
              separator)) {
    result_.main_target_name(target_name_);
}

template<typename OdbTarget>
OdbTarget odb_targets_factory::
generate_targets(const logical::entities::name& n) {
    OdbTarget r;
    r.name(target_name_ + separator + n.simple());
    r.comment("ODB " + n.simple());

    /*
     * We need to compute relative paths, from the project directory
     * into the headers project directory.
     */
    const auto& l(locator_);
    const auto odb_arch(transforms::odb::traits::class_header_archetype_qn());
    const auto odb_fp(l.make_full_path_for_cpp_header(n, odb_arch)
        .parent_path());
    const auto src_dir(l.make_full_path_to_implementation_directory());
    const auto rp(odb_fp.lexically_relative(src_dir));
    r.output_directory(rp.generic_string());

    const auto types_arch(transforms::types::traits::class_header_archetype_qn());
    const auto tp(l.make_full_path_for_cpp_header(n, types_arch));
    r.types_file(tp.lexically_relative(src_dir).generic_string());

    const auto odb_options_rp(locator_.make_relative_path_for_odb_options(n,
            odb_arch, false/*include_source_directory*/));
    r.object_odb_options(odb_options_rp.generic_string());

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
        pair.first = r.output_directory() + "/" + file_name;
        pair.second = odb_rp + "/";
        r.move_parameters().push_back(pair);
    }
    return r;
}

void odb_targets_factory::
visit(const logical::entities::orm::common_odb_options& coo) {
    const auto arch(transforms::odb::traits::common_odb_options_archetype_qn());
    result_.common_odb_options(
        locator_.make_relative_path_for_odb_options(coo.name(), arch,
            false/*include_source_directory*/).generic_string()
        );
}

void odb_targets_factory::
visit(const logical::entities::structural::object& o) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!o.orm_properties())
        return;

    const auto& n(o.name());
    result_.targets().push_back(
        generate_targets<logical::entities::orm::odb_target>(n));
}

void odb_targets_factory::
visit(const logical::entities::structural::primitive& p) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!p.orm_properties())
        return;

    const auto& n(p.name());
    result_.targets().push_back(
        generate_targets<logical::entities::orm::odb_target>(n));
}

const logical::entities::orm::odb_targets&
odb_targets_factory::result() const {
    return result_;
}

class build_files_updater : public element_visitor {
public:
    build_files_updater(const locator& l,
        const logical::entities::orm::odb_targets& targets);

public:
    using element_visitor::visit;
    void visit(logical::entities::build::cmakelists& v);
    void visit(logical::entities::visual_studio::msbuild_targets& v);

private:
    const locator& locator_;
    const logical::entities::orm::odb_targets& targets_;
};

build_files_updater::build_files_updater(const locator& l,
    const logical::entities::orm::odb_targets& targets)
    : locator_(l), targets_(targets) {}

void build_files_updater::visit(logical::entities::build::cmakelists& c) {
    c.odb_targets(targets_);
    c.include_directory_path(locator_.include_directory_name());
    c.source_directory_name(locator_.source_directory_name());
    c.tests_directory_name(locator_.tests_directory_name());
    c.header_file_extension(locator_.header_file_extension());
    c.implementation_file_extension(locator_.implementation_file_extension());
}

void build_files_updater::
visit(logical::entities::visual_studio::msbuild_targets& v) {
    v.odb_targets(targets_);
}

void build_files_expander::expand(const locator& l, model& fm) const {
    odb_targets_factory f(fm, l, fm.name());
    const auto ott(logical::entities::origin_types::target);
    for (auto& pair : fm.formattables()) {
        /*
         * We only want to process target elements; references can be
         * ignored.
         */
        auto& formattable(pair.second);
        const auto& e(*formattable.element());
        if (e.origin_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        e.accept(f);
    }

    /*
     * Obtain the targets and sort them to ensure the container is
     * stable. We obtained the formattables from an unordered map so
     * they could have come in in any order.
     */
    const auto odb_targets(
        [&]() {
            auto r(f.result());
            r.targets().sort(odb_target_comparer);
            return r;
        }());

    build_files_updater u(l, odb_targets);
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& e(*formattable.element());
        if (e.origin_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        e.accept(u);
    }
}

}
