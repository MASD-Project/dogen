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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/io/meta_model/orm/model_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/orm/object_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/orm/primitive_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/orm_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.orm_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string mysql("mysql");
const std::string postgresql("postgresql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");

const std::string upper_case("upper_case");
const std::string lower_case("lower_case");

const std::string invalid_database_system(
    "Database system is invalid or unsupported: ");
const std::string invalid_letter_case(
    "Letter case is invalid or unsupported: ");
const std::string invalid_type_override("Invalid type override expression: ");
const std::string duplicate_database_system(
    "Found more than one type override for database system: ");

}

namespace masd::dogen::coding::transforms {

meta_model::orm::database_system orm_transform::
to_orm_database_system(const std::string& s) {
    using meta_model::orm::database_system;
    const auto ls(boost::to_lower_copy(s));
    if (ls == mysql) {
        return database_system::mysql;
    } else if (ls == postgresql) {
        return database_system::postgresql;
    } else if (ls == oracle) {
        return database_system::oracle;
    } else if (ls == sql_server) {
        return database_system::sql_server;
    } else if (ls == sqlite) {
        return database_system::sqlite;
    }

    BOOST_LOG_SEV(lg, error) << invalid_database_system << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_database_system + s));
}

std::vector<meta_model::orm::database_system> orm_transform::
to_orm_database_system(const std::list<std::string>& vs) {
    std::vector<meta_model::orm::database_system> r;
    r.reserve(vs.size());
    for (const auto& s : vs) {
        r.push_back(to_orm_database_system(s));
    }
    return r;
}

meta_model::orm::letter_case
orm_transform::to_letter_case(const std::string& s) {
    using meta_model::orm::letter_case;
    const auto ls(boost::to_lower_copy(s));
    if (ls == upper_case) {
        return letter_case::upper_case;
    } else if (ls == lower_case) {
        return letter_case::lower_case;
    }

    BOOST_LOG_SEV(lg, error) << invalid_letter_case << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_letter_case + s));
}

std::unordered_map<meta_model::orm::database_system, std::string>
orm_transform::
make_type_overrides(const std::list<std::string> ls) {
    std::unordered_map<meta_model::orm::database_system, std::string> r;

    using utility::string::splitter;
    for (const auto& s : ls) {
        const auto tokens(splitter::split_csv(s));
        if (tokens.size() != 2) {
            BOOST_LOG_SEV(lg, error) << invalid_type_override << s;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_type_override + s));
        }

        const auto ds(tokens.front());
        const auto first(to_orm_database_system(ds));
        const auto second(tokens.back());
        const auto pair(std::make_pair(first, second));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_database_system << ds;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_database_system + ds));
        }
    }

    return r;
}

orm_transform::feature_group orm_transform::
make_feature_group(const variability::meta_model::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto& ds(traits::orm::database_system());
    r.database_system = s.get_by_name(ds);

    const auto& tn(traits::orm::table_name());
    r.table_name = s.get_by_name(tn);

    const auto& sn(traits::orm::schema_name());
    r.schema_name = s.get_by_name(sn);

    const auto& ipk(traits::orm::is_primary_key());
    r.is_primary_key = s.get_by_name(ipk);

    const auto& cn(traits::orm::column_name());
    r.column_name = s.get_by_name(cn);

    const auto& in(traits::orm::is_nullable());
    r.is_nullable = s.get_by_name(in);

    const auto& lc(traits::orm::letter_case());
    r.letter_case = s.get_by_name(lc);

    const auto& to(traits::orm::type_override());
    r.type_override = s.get_by_name(to);

    const auto& ic(traits::orm::is_composite());
    r.is_composite = s.get_by_name(ic);

    return r;
}

boost::optional<meta_model::orm::model_properties>
orm_transform::make_model_properties(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Started creating model configuration.";
    const variability::helpers::configuration_selector s(cfg);
    bool found_any(false);

    meta_model::orm::model_properties r;
    if (s.has_configuration_point(fg.database_system)) {
        found_any = true;
        const auto ds(s.get_text_collection_content(fg.database_system));
        r.database_systems(to_orm_database_system(ds));
    }

    if (s.has_configuration_point(fg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(fg.schema_name));
    }

    if (s.has_configuration_point(fg.letter_case)) {
        found_any = true;
        const auto lc(s.get_text_content(fg.letter_case));
        r.letter_case(to_letter_case(lc));
    }

    if (found_any) {
        BOOST_LOG_SEV(lg, debug) << "Created model configuration: " << r;
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Model configuration is empty.";
    return boost::optional<meta_model::orm::model_properties>();
}

void orm_transform::update_object_properties(
    const feature_group& fg,
    const variability::meta_model::configuration& cfg,
    meta_model::orm::object_properties& oop) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.schema_name))
        oop.schema_name(s.get_text_content(fg.schema_name));

    if (s.has_configuration_point(fg.table_name))
        oop.table_name(s.get_text_content(fg.table_name));
}

boost::optional<meta_model::orm::attribute_properties>
orm_transform::make_attribute_properties(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    bool found_any(false);

    meta_model::orm::attribute_properties r;
    if (s.has_configuration_point(fg.column_name)) {
        found_any = true;
        r.column_name(s.get_text_content(fg.column_name));
    }

    if (s.has_configuration_point(fg.is_primary_key)) {
        found_any = true;
        r.is_primary_key(s.get_boolean_content(fg.is_primary_key));
    }

    if (s.has_configuration_point(fg.is_nullable)) {
        found_any = true;
        r.is_nullable(s.get_boolean_content(fg.is_nullable));
    }

    if (s.has_configuration_point(fg.type_override)) {
        found_any = true;
        const auto to(s.get_text_collection_content(fg.type_override));
        r.type_overrides(make_type_overrides(to));
    }

    if (s.has_configuration_point(fg.is_composite)) {
        found_any = true;
        r.is_composite(s.get_boolean_content(fg.is_composite));
    }

    if (found_any)
        return r;

    return boost::optional<meta_model::orm::attribute_properties>();
}

void orm_transform::update_primitive_properties(const feature_group& fg,
    const variability::meta_model::configuration& cfg,
    meta_model::orm::primitive_properties& opp) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.schema_name))
        opp.schema_name(s.get_text_content(fg.schema_name));
}

boost::optional<meta_model::orm::module_properties>
orm_transform::make_module_properties(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    meta_model::orm::module_properties r;
    const variability::helpers::configuration_selector s(cfg);

    if (s.has_configuration_point(fg.schema_name)) {
        r.schema_name(s.get_text_content(fg.schema_name));
        return r;
    }

    return boost::optional<meta_model::orm::module_properties>();
}

void orm_transform::
transform_objects(const feature_group& fg, meta_model::model& em) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming objects.";

    boost::optional<meta_model::orm::letter_case> lc;
    if (em.orm_properties())
        lc = em.orm_properties()->letter_case();

    for (auto& pair : em.objects()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this object. Configurations are setup during
         * stereofeatures transform, if the ORM stereofeatures were present.
         */
        auto& o(*pair.second);
        if (!o.orm_properties())
            continue;

        auto& op(*o.orm_properties());

        /*
         * Letter case is always setup to match the model
         * configuration.
         */
        op.letter_case(lc);

        /*
         * Now read all of the configuration for each attribute and
         * detect the presence of primary keys.
         */
        bool has_primary_key(false);
        const auto id(pair.first);
        for (auto& attr : o.local_attributes()) {
            const auto& cfg(*attr.configuration());
            const auto attr_op(make_attribute_properties(fg, cfg));
            has_primary_key |= (attr_op && attr_op->is_primary_key());
            attr.orm_properties(attr_op);
        }

        /*
         * Update the object's configuration with any additional
         * meta-data the user may have supplied.
         */
        const auto& cfg(*o.configuration());
        update_object_properties(fg, cfg, op);
        op.has_primary_key(has_primary_key);

        BOOST_LOG_SEV(lg, debug) << "ORM configuration for object: "
                                 << pair.first << ": " << op;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming objects.";
}

void orm_transform::
transform_object_templates(const feature_group& fg, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming object templates.";

    for (auto& pair : m.object_templates()) {
        auto& c(*pair.second);
        for (auto& attr : c.local_attributes()) {
            const auto& cfg(*attr.configuration());
            attr.orm_properties(make_attribute_properties(fg, cfg));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming object templates.";
}

void orm_transform::
transform_primitives(const feature_group& fg, meta_model::model& m) {

    BOOST_LOG_SEV(lg, debug) << "Started transforming primitives.";

    boost::optional<meta_model::orm::letter_case> lc;
    if (m.orm_properties())
        lc = m.orm_properties()->letter_case();

    for (auto& pair : m.primitives()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this primitive. Configurations are setup during
         * stereofeatures transform, if the ORM stereofeatures were present.
         */
        auto& p(*pair.second);
        if (!p.orm_properties())
            continue;

        auto& op(*p.orm_properties());

        /*
         * Letter case is always setup to match the model
         * configuration.
         */
        op.letter_case(lc);

        /*
         * Read any additional meta-data the user may have supplied
         * for the configuration.
         */
        const auto& cfg(*p.configuration());
        update_primitive_properties(fg, cfg, op);
        BOOST_LOG_SEV(lg, debug) << "ORM configuration for primitive: "
                                 << pair.first << ": " << op;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming primitives.";
}

void orm_transform::
transform_modules(const feature_group& fg, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming modules.";

    for (auto& pair : m.modules()) {
        auto& mod(*pair.second);
        BOOST_LOG_SEV(lg, trace) << "Processing: "
                                 << mod.name().qualified().dot();

        const auto& cfg(*mod.configuration());
        BOOST_LOG_SEV(lg, debug) <<"here 1 " << mod.configuration();
        auto omp(make_module_properties(fg, cfg));
        if (!omp)
            continue;

        mod.orm_properties(omp);

        /*
         * If we do not have a schema name at the module level we have
         * nothing to worry about; either the object has no schema
         * name either, or it has been overridden - but either way,
         * its not our problem.
         */
        const auto& sn(m.orm_properties()->schema_name());
        if (sn.empty())
            continue;

        /*
         * If we do have a schema name at the module level, we need to
         * update all objects that do not have a schema name to use
         * it's containing module's schema name.
         */
        for (const auto& id : mod.contains()) {
            BOOST_LOG_SEV(lg, debug) << "Processing contained element: " << id;

            const auto i(m.objects().find(id));
            if (i != m.objects().end()) {
                auto& o(*i->second);
                auto& op(o.orm_properties());
                const bool update_schema_name(op && op->schema_name().empty()
                    && (op->generate_mapping() || op->is_value()));

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                op->schema_name(sn);
            } else {
                const auto j(m.primitives().find(id));
                if (j == m.primitives().end())
                    continue;

                auto& p(*j->second);
                auto& op(p.orm_properties());
                const bool update_schema_name(op &&
                    op->schema_name().empty() && op->generate_mapping());

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                op->schema_name(sn);
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming modules.";
}

void orm_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "orm transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto fg(make_feature_group(*ctx.feature_model()));
    const auto& rm(*m.root_module());
    m.orm_properties(make_model_properties(fg, *rm.configuration()));

    transform_objects(fg, m);
    transform_object_templates(fg, m);
    transform_primitives(fg, m);
    transform_modules(fg, m);

    stp.end_transform(m);
}

}
