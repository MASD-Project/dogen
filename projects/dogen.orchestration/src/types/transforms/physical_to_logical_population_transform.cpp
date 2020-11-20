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
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.physical/types/entities/relation_status.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/pair_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/lexical_cast/entities/relation_status_lc.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/helpers/header_guard_factory.hpp"
#include "dogen.physical/io/entities/project_path_properties_io.hpp"
#include "dogen.logical/io/entities/orm/database_system_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/orm/odb_target.hpp"
#include "dogen.logical/types/entities/orm/odb_targets.hpp"
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/entities/visual_studio/item.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.logical/types/entities/visual_studio/item_group.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.text/io/entities/model_io.hpp"
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.orchestration/types/transforms/transform_exception.hpp"
#include "dogen.orchestration/types/transforms/physical_to_logical_population_transform.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.physical_to_logical_population_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string separator("_");
const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");
const std::string csharp_target("Compile");
const std::string cpp_header_target("ClInclude");
const std::string cpp_impl_target("ClCompile");

const std::string missing_odb_options("Could not find the ODB Options element");
const std::string missing_qualified_name(
    "Qualified name not found for object: ");
const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");
const std::string missing_archetype("Achetype is missing: ");
const std::string invalid_ots("Invalid number of output technical spaces.");
const std::string invalid_relation_status(
    "Relation status is invalid or unsupported: ");

}

namespace dogen::orchestration::transforms {

using identification::entities::logical_meta_id;
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
    logical::entities::orm::odb_options
    make_options(const archetype_ids& ids);

    boost::filesystem::path get_path_for_artefact(const std::string& archetype);

    logical::entities::orm::odb_target
    generate_targets(const logical_name& n, const archetype_ids& ids);

public:
    using element_visitor::visit;
    void visit(logical::entities::orm::common_odb_options& coo);
    void visit(logical::entities::structural::object& o);
    void visit(logical::entities::structural::primitive& p);

private:
    const std::string target_name_;
    const std::list<std::string> databases_;
    const physical::entities::region& region_;
    const project_path_properties project_path_properties_;
    logical::entities::orm::odb_targets& result_;
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
    return a.path_properties().file_path();
}

logical::entities::orm::odb_options odb_targets_factory::
make_options(const archetype_ids& ids) {
    logical::entities::orm::odb_options r;

    const auto inc_dir(
        project_path_properties_.include_directory_full_path());
    BOOST_LOG_SEV(lg, debug) << "Include directory full path: "
                             << inc_dir.generic_string();

    const auto odb_fp(get_path_for_artefact(ids.odb));
    BOOST_LOG_SEV(lg, debug) << "ODB full path: "
                             << odb_fp.generic_string();
    const auto odb_rp(odb_fp.lexically_relative(inc_dir));
    BOOST_LOG_SEV(lg, debug) << "Output directory: " << odb_rp.generic_string();

    std::ostringstream os;
    os << "'#include \"" << odb_rp.generic_string() << "\"'";
    r.epilogue(os.str());
    os.str("");

    const auto tp(get_path_for_artefact(ids.types));
    BOOST_LOG_SEV(lg, debug) << "Types directory: " << tp.generic_string();

    const auto ip(tp.lexically_relative(inc_dir));
    BOOST_LOG_SEV(lg, debug) << "Types file: " << ip.generic_string();
    // const auto ip(locator_.make_inclusion_path_for_cpp_header(n, types_arch));
    const auto types_rp(ip.parent_path());

    os << "'%(.*).hpp%" << types_rp.generic_string() << "/$1.hpp%'";
    r.include_regexes().push_back(os.str());

    os.str("");
    os << "'%(^[a-zA-Z0-9_]+)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    r.include_regexes().push_back(os.str());

    os.str("");
    os << "'%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    r.include_regexes().push_back(os.str());

    using physical::helpers::header_guard_factory;
    r.header_guard_prefix(header_guard_factory::make(odb_rp.parent_path()));
    return r;
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
    BOOST_LOG_SEV(lg, debug) << "Implementation directory full path: "
                             << src_dir.generic_string();

    const auto odb_fp(get_path_for_artefact(ids.odb).parent_path());
    BOOST_LOG_SEV(lg, debug) << "ODB full path: "
                             << odb_fp.generic_string();
    const auto rp(odb_fp.lexically_relative(src_dir));
    BOOST_LOG_SEV(lg, debug) << "Output directory: " << rp.generic_string();

    r.output_directory(rp.generic_string());

    const auto tp(get_path_for_artefact(ids.types));
    BOOST_LOG_SEV(lg, debug) << "Types directory: " << tp.generic_string();

    r.types_file(tp.lexically_relative(src_dir).generic_string());
    BOOST_LOG_SEV(lg, debug) << "Types file: " << r.types_file();

    const auto odb_options(get_path_for_artefact(ids.odb_option));
    BOOST_LOG_SEV(lg, debug) << "ODB options: "
                             << odb_options.generic_string();
    const auto odb_options_rp(odb_options.lexically_relative(src_dir));
    r.object_odb_options(odb_options_rp.generic_string());
    BOOST_LOG_SEV(lg, debug) << "Types file: " << r.object_odb_options();

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
visit(logical::entities::orm::common_odb_options& /*coo*/) {
    BOOST_LOG_SEV(lg, debug) << "Element is common odb options.";
    const auto src_dir(
        project_path_properties_.implementation_directory_full_path());
    const auto fp(get_path_for_artefact("masd.cpp.odb.common_odb_options"));
    const auto rp(fp.lexically_relative(src_dir));
    result_.common_odb_options(rp.generic_string());
}

void odb_targets_factory::
visit(logical::entities::structural::object& o) {
    BOOST_LOG_SEV(lg, debug) << "Element is object.";

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
    o.orm_properties()->odb_options(make_options(ids));

}

void odb_targets_factory::
visit(logical::entities::structural::primitive& p) {
    BOOST_LOG_SEV(lg, debug) << "Element is primitive.";

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
    p.orm_properties()->odb_options(make_options(ids));
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
    BOOST_LOG_SEV(lg, debug) << "Element is cmakelists.";
    c.odb_targets(targets_);

    BOOST_LOG_SEV(lg, debug) << "Path properties: " << project_path_properties_;
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

identification::entities::technical_space
physical_to_logical_population_transform::
get_technical_space(const logical::entities::model& m) {
    const auto& ots(m.output_technical_spaces());
    if (ots.size() != 1) {
        BOOST_LOG_SEV(lg, error) << invalid_ots << " Found: " << ots.size();
        BOOST_THROW_EXCEPTION(transform_exception(invalid_ots));
    }
    return ots.front();
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

std::unordered_set<logical_meta_id>
physical_to_logical_population_transform::
meta_names_for_project_items() {
    std::unordered_set<logical_meta_id> r;

    using f = identification::helpers::logical_meta_name_factory;
    r.insert(f::make_enumeration_name().id());
    r.insert(f::make_primitive_name().id());
    r.insert(f::make_exception_name().id());
    r.insert(f::make_object_name().id());
    r.insert(f::make_builtin_name().id());
    r.insert(f::make_visitor_name().id());
    r.insert(f::make_assistant_name().id());

    return r;
}

bool physical_to_logical_population_transform::
is_project_item(const logical_meta_id& mn)  {
    static const auto mnfpi(meta_names_for_project_items());
    const auto i(mnfpi.find(mn));
    return i != mnfpi.end();
}

void physical_to_logical_population_transform::
apply(const text::transforms::context& ctx, text::entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "physical to logical population",
        transform_id, m.logical().name().id().value(), *ctx.tracer(), m);

    const auto dbs(make_odb_databases(m));
    const auto& mm(m.logical().name().location().model_modules());
    const auto& mmp(m.physical().meta_model_properties());
    const auto& ppp(mmp.project_path_properties());
    const auto target_name("odb_" + boost::join(mm, separator));
    logical::entities::orm::odb_targets odbt;
    odbt.main_target_name(target_name);

    const auto ott(identification::entities::model_type::target);
    for (auto& region : m.logical_physical_regions()) {
        auto& e(*region.logical_element());
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
        odb_targets_factory f(target_name, dbs, pr, ppp, odbt);
        e.accept(f);
    }

    /*
     * Obtain the targets and sort them to ensure the container is
     * stable. We obtained the formattables from an unordered map so
     * they could have come in in any order.
     */
    odbt.targets().sort(odb_target_comparer);
    build_files_updater u(ppp, odbt);

    std::list<std::pair<std::string, std::string>> project_items;
    const auto ots(get_technical_space(m.logical()));
    for (auto& region : m.logical_physical_regions()) {
        auto& e(*region.logical_element());
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

        /*
         * Gather project items.
         */
        const auto& aba(region.physical_region().artefacts_by_archetype());
        for (const auto& pair : aba) {
            const auto& a(*pair.second);

            const auto be(a.meta_name().location().backend());
            using identification::entities::technical_space;
            if ((ots == technical_space::csharp && be != "csharp") ||
                (ots == technical_space::cpp && be != "cpp"))
                continue;

            const auto mt(e.meta_name().id());
            if (!is_project_item(mt))
                continue;

            /*
             * Ensure the item path uses backslashes for compatibility
             * with Visual Studio and MonoDevelop.
             */
            auto rp(a.path_properties().relative_path().generic_string());
            std::replace(rp.begin(), rp.end(), '/', '\\');

            const auto target([&]() {
                if (be == "csharp")
                    return csharp_target;

                const auto rs(a.relations().status());
                using physical::entities::relation_status;
                if (rs == relation_status::not_relatable)
                    return cpp_impl_target;
                else if (rs == relation_status::relatable ||
                    rs == relation_status::facet_default)
                    return cpp_header_target;

                const auto s(boost::lexical_cast<std::string>(rs));
                BOOST_LOG_SEV(lg, error) << invalid_relation_status << s;
                BOOST_THROW_EXCEPTION(
                    transform_exception(invalid_relation_status + s));
            }());
            project_items.push_back(std::make_pair(target, rp));
        }
    }

    /*
     * Now update project items.
     */
    project_items.sort([](const std::pair<std::string, std::string>& lhs,
            const std::pair<std::string, std::string>& rhs){
        return lhs.second < rhs.second;
    });
    auto projects(m.logical().visual_studio_elements().projects());
    for (auto& pair : projects) {
        auto& proj(*pair.second);

        using namespace logical::entities::visual_studio;
        item_group ig;
        for (const auto& pair : project_items) {
            item item;
            item.name(pair.first);
            item.include(pair.second);
            ig.items().push_back(item);
        }
        proj.item_groups().push_back(ig);
    }

    for (const auto& pair : project_items)
        m.logical().project_items().push_back(pair.second);

    stp.end_transform(m);
}

}
