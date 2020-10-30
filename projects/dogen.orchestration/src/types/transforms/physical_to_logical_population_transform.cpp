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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/pair_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/io/entities/orm/database_system_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/orm/odb_target.hpp"
#include "dogen.logical/types/entities/orm/odb_targets.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/physical_to_logical_population_transform.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.physical_to_logical_population_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string separator("_");
const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");

const std::string missing_odb_options("Could not find the ODB Options element");
const std::string missing_qualified_name(
    "Qualified name not found for object: ");
const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");
const std::string missing_archetype("Achetype is missing: ");

}

namespace dogen::orchestration::transforms {

using identification::entities::logical_name;
using identification::entities::physical_meta_id;
using logical::entities::element_visitor;
using physical::entities::project_path_properties;

bool odb_target_comparer(const logical::entities::orm::odb_target& lhs,
    const logical::entities::orm::odb_target& rhs) {
    return lhs.name() < rhs.name();
}

class odb_targets_factory : public element_visitor {
private:
    struct archetype_ids {
        std::string types;
        std::string odb;
        std::string odb_option;
    };

public:
    odb_targets_factory(const std::string& target_name,
        const std::list<std::string>& databases,
        const physical::entities::region& region,
        const project_path_properties ppp,
        logical::entities::orm::odb_targets& ots);

private:
    boost::filesystem::path get_path_for_artefact(const std::string& archetype);

    logical::entities::orm::odb_target
    generate_targets(const logical_name& n, const archetype_ids& ids);

public:
    using element_visitor::visit;
    void visit(const logical::entities::orm::common_odb_options& coo);
    void visit(const logical::entities::structural::object& o);
    void visit(const logical::entities::structural::primitive& p);

private:
    const std::string target_name_;
    const std::list<std::string> databases_;
    const physical::entities::region& region_;
    const project_path_properties project_path_properties_;
    logical::entities::orm::odb_targets result_;
};

odb_targets_factory::odb_targets_factory(const std::string& target_name,
    const std::list<std::string>& databases,
    const physical::entities::region& region, const project_path_properties ppp,
    logical::entities::orm::odb_targets& ots)
    : target_name_(target_name), databases_(databases),
      region_(region), project_path_properties_(ppp), result_(ots) {}

boost::filesystem::path
odb_targets_factory::get_path_for_artefact(const std::string& archetype) {
    const physical_meta_id pmid(archetype);
    const auto& aba(region_.artefacts_by_archetype());
    const auto i(aba.find(pmid));
    if (i == aba.end()) {
        BOOST_LOG_SEV(lg, error) << missing_archetype << pmid.value();
        BOOST_THROW_EXCEPTION(
            transform_exception(missing_archetype + pmid.value()));
    }

    const auto& a(*i->second);
    return a.path_properties().file_path().parent_path();
}

logical::entities::orm::odb_target odb_targets_factory::
generate_targets(const logical_name& n, const archetype_ids& ids) {
    logical::entities::orm::odb_target r;
    r.name(target_name_ + separator + n.simple());
    r.comment("ODB " + n.simple());

    /*
     * We need to compute relative paths, from the project directory
     * into the headers project directory.
     */
    const auto src_dir(
        project_path_properties_.implementation_directory_full_path());
    const auto odb_fp(get_path_for_artefact(ids.odb)
        .parent_path());
    const auto rp(odb_fp.lexically_relative(src_dir));
    r.output_directory(rp.generic_string());

    const auto tp(get_path_for_artefact(ids.types));
    r.types_file(tp.lexically_relative(src_dir).generic_string());

    const auto odb_options_rp(get_path_for_artefact(ids.odb_option));
    r.object_odb_options(odb_options_rp.generic_string());

    BOOST_LOG_SEV(lg, debug) << "Databases: " << databases_;
    const auto odb_rp(odb_options_rp.parent_path().generic_string());
    const auto db_count(databases_.size());
    for (const auto& db : databases_) {
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
visit(const logical::entities::orm::common_odb_options& /*coo*/) {
    const auto p(get_path_for_artefact("masd.cpp.odb.common_odb_options"));
    result_.common_odb_options(p.generic_string());
}

void odb_targets_factory::
visit(const logical::entities::structural::object& o) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!o.orm_properties())
        return;

    const auto& n(o.name());
    archetype_ids ids;
    ids.types = "masd.cpp.types.class_header";
    ids.odb = "masd.cpp.odb.class_header";
    ids.odb_option = "masd.cpp.odb.object_odb_options";
    result_.targets().push_back(generate_targets(n, ids));
}

void odb_targets_factory::
visit(const logical::entities::structural::primitive& p) {
    /*
     * We only care about objects which have ORM enabled.
     */
    if (!p.orm_properties())
        return;

    const auto& n(p.name());
    archetype_ids ids;
    ids.types = "masd.cpp.types.primitive_header";
    ids.odb = "masd.cpp.odb.primitive_header";
    ids.odb_option = "masd.cpp.odb.primitive_odb_options";
    result_.targets().push_back(generate_targets(n, ids));
}

class build_files_updater : public element_visitor {
public:
    build_files_updater(const project_path_properties& ppp,
        const logical::entities::orm::odb_targets& targets);

public:
    using element_visitor::visit;
    void visit(logical::entities::build::cmakelists& v);
    void visit(logical::entities::visual_studio::msbuild_targets& v);

private:
    const project_path_properties project_path_properties_;
    const logical::entities::orm::odb_targets& targets_;
};

build_files_updater::build_files_updater(const project_path_properties& ppp,
    const logical::entities::orm::odb_targets& targets)
    : project_path_properties_(ppp), targets_(targets) {}

void build_files_updater::visit(logical::entities::build::cmakelists& c) {
    c.odb_targets(targets_);
    c.include_directory_path(project_path_properties_.include_directory_name());
    c.source_directory_name(project_path_properties_.source_directory_name());
    c.tests_directory_name(project_path_properties_.tests_directory_name());
    c.header_file_extension(project_path_properties_.header_file_extension());
    c.implementation_file_extension(
        project_path_properties_.implementation_file_extension());
}

void build_files_updater::
visit(logical::entities::visual_studio::msbuild_targets& v) {
    v.odb_targets(targets_);
}

std::list<std::string> physical_to_logical_population_transform::
make_odb_databases(const text::entities::model& m) {
    std::list<std::string> r;

    if (!m.logical().orm_properties())
        return r;

    const auto op(*m.logical().orm_properties());
    if (op.database_systems().size() > 1)
        r.push_back("common");

    using logical::entities::orm::database_system;
    for (const auto ds : op.database_systems()) {
        switch (ds) {
        case database_system::mysql:
            r.push_back(mysql);
            break;
        case database_system::postgresql:
            r.push_back(postgresql);
            break;
        case database_system::oracle:
            r.push_back(oracle);
            break;
        case database_system::sql_server:
            r.push_back(sql_server);
            break;
        case database_system::sqlite:
            r.push_back(sqlite);
            break;
        default: {
            const auto s(boost::lexical_cast<std::string>(ds));
            BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
            BOOST_THROW_EXCEPTION(
                transform_exception(invalid_daatabase_system + s));
        } }
    }
    return r;
}

void physical_to_logical_population_transform::
apply(const text::transforms::context& ctx,
    text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "physical to logical population",
        transform_id, m.logical().name().id().value(), *ctx.tracer(), m);

    const auto dbs(make_odb_databases(m));
    const auto& mm(m.logical().name().location().model_modules());
    const auto& mmp(m.physical().meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto target_name("odb_" + boost::join(mm, separator));
    logical::entities::orm::odb_targets ots;
    ots.main_target_name(target_name);

    const auto ott(identification::entities::model_type::target);
    for (auto& region : m.logical_physical_regions()) {
        const auto& e(*region.logical_element());
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id.value();

        /*
         * We only want to process target elements; references can be
         * ignored.
         */
        if (e.provenance().model_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        const auto& pr(region.physical_region());
        odb_targets_factory f(target_name, dbs, pr, ppp, ots);
        e.accept(f);
    }

    /*
     * Obtain the targets and sort them to ensure the container is
     * stable. We obtained the formattables from an unordered map so
     * they could have come in in any order.
     */
    ots.targets().sort(odb_target_comparer);
    build_files_updater u(ppp, ots);

    for (auto& region : m.logical_physical_regions()) {
        const auto& e(*region.logical_element());
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id.value();

        /*
         * We only want to process target elements; references can be
         * ignored.
         */
        if (e.provenance().model_type() != ott) {
            BOOST_LOG_SEV(lg, debug) << "Skipping non-target element.";
            continue;
        }

        e.accept(u);
    }

    stp.end_transform(m);
}

}
