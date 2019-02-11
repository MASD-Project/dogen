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
#include "masd.dogen.annotations/io/type_io.hpp"
#include "masd.dogen.annotations/types/entry_selector.hpp"
#include "masd.dogen.annotations/types/type_repository_selector.hpp"
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
#include "masd.dogen.coding/io/meta_model/orm_model_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/orm_object_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/orm_primitive_properties_io.hpp"
#include "masd.dogen.coding/io/meta_model/endomodel_io.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/orm_transform.hpp"

namespace {

const std::string transform_id("yarn.transforms.orm_transform");

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string mysql("mysql");
const std::string postgresql("postgresql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");

const std::string upper_case("upper_case");
const std::string lower_case("lower_case");

const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");
const std::string invalid_letter_case(
    "Letter case is invalid or unsupported: ");
const std::string invalid_type_override("Invalid type override expression: ");
const std::string duplicate_database_system(
    "Found more than one type override for database system: ");

}

namespace masd::dogen::coding::transforms {

meta_model::orm_database_systems orm_transform::
to_orm_database_system(const std::string& s) {
    using meta_model::orm_database_systems;
    const auto ls(boost::to_lower_copy(s));
    if (ls == mysql) {
        return orm_database_systems::mysql;
    } else if (ls == postgresql) {
        return orm_database_systems::postgresql;
    } else if (ls == oracle) {
        return orm_database_systems::oracle;
    } else if (ls == sql_server) {
        return orm_database_systems::sql_server;
    } else if (ls == sqlite) {
        return orm_database_systems::sqlite;
    }

    BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_daatabase_system + s));
}

std::vector<meta_model::orm_database_systems> orm_transform::
to_orm_database_system(const std::list<std::string>& vs) {
    std::vector<meta_model::orm_database_systems> r;
    r.reserve(vs.size());
    for (const auto& s : vs) {
        r.push_back(to_orm_database_system(s));
    }
    return r;
}

meta_model::letter_cases
orm_transform::to_letter_case(const std::string& s) {
    using meta_model::letter_cases;
    const auto ls(boost::to_lower_copy(s));
    if (ls == upper_case) {
        return letter_cases::upper_case;
    } else if (ls == lower_case) {
        return letter_cases::lower_case;
    }

    BOOST_LOG_SEV(lg, error) << invalid_letter_case << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_letter_case + s));
}

std::unordered_map<meta_model::orm_database_systems, std::string>
orm_transform::
make_type_overrides(const std::list<std::string> ls) {
    std::unordered_map<meta_model::orm_database_systems, std::string> r;

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

std::ostream&
operator<<(std::ostream& s, const orm_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"coding::orm_transform::"
      << "type_group\"" << ", "
      << "\"database_system\": " << v.database_system << ", "
      << "\"table_name\": " << v.table_name << ", "
      << "\"column_name\": " << v.column_name << ", "
      << "\"schema_name\": " << v.schema_name << ", "
      << "\"is_primary_key\": " << v.is_primary_key << ", "
      << "\"letter_case\": " << v.letter_case << ", "
      << "\"type_override\": " << v.type_override
      << "\"is_composite\": " << v.is_composite
      << " }";

    return s;
}

orm_transform::type_group orm_transform::
make_type_group(const annotations::type_repository& atrp) {
    type_group r;

    const annotations::type_repository_selector rs(atrp);

    const auto& ds(traits::orm::database_system());
    r.database_system = rs.select_type_by_name(ds);

    const auto& tn(traits::orm::table_name());
    r.table_name = rs.select_type_by_name(tn);

    const auto& sn(traits::orm::schema_name());
    r.schema_name = rs.select_type_by_name(sn);

    const auto& ipk(traits::orm::is_primary_key());
    r.is_primary_key = rs.select_type_by_name(ipk);

    const auto& cn(traits::orm::column_name());
    r.column_name = rs.select_type_by_name(cn);

    const auto& in(traits::orm::is_nullable());
    r.is_nullable = rs.select_type_by_name(in);

    const auto& lc(traits::orm::letter_case());
    r.letter_case = rs.select_type_by_name(lc);

    const auto& to(traits::orm::type_override());
    r.type_override = rs.select_type_by_name(to);

    const auto& ic(traits::orm::is_composite());
    r.is_composite = rs.select_type_by_name(ic);

    return r;
}

boost::optional<meta_model::orm_model_properties>
orm_transform::make_model_properties(const type_group& tg,
    const annotations::annotation& a) {

    BOOST_LOG_SEV(lg, debug) << "Started creating model configuration.";
    const annotations::entry_selector s(a);
    bool found_any(false);

    meta_model::orm_model_properties r;
    if (s.has_entry(tg.database_system)) {
        found_any = true;
        const auto ds(s.get_text_collection_content(tg.database_system));
        r.database_systems(to_orm_database_system(ds));
    }

    if (s.has_entry(tg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(tg.schema_name));
    }

    if (s.has_entry(tg.letter_case)) {
        found_any = true;
        const auto lc(s.get_text_content(tg.letter_case));
        r.letter_case(to_letter_case(lc));
    }

    if (found_any) {
        BOOST_LOG_SEV(lg, debug) << "Created model configuration: " << r;
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Model configuration is empty.";
    return boost::optional<meta_model::orm_model_properties>();
}

void orm_transform::update_object_properties(
    const type_group& tg, const annotations::annotation& a,
    meta_model::orm_object_properties& cfg) {

    const annotations::entry_selector s(a);
    if (s.has_entry(tg.schema_name))
        cfg.schema_name(s.get_text_content(tg.schema_name));

    if (s.has_entry(tg.table_name))
        cfg.table_name(s.get_text_content(tg.table_name));
}

boost::optional<meta_model::orm_attribute_properties>
orm_transform::make_attribute_properties(const type_group& tg,
    const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    bool found_any(false);

    meta_model::orm_attribute_properties r;
    if (s.has_entry(tg.column_name)) {
        found_any = true;
        r.column_name(s.get_text_content(tg.column_name));
    }

    if (s.has_entry(tg.is_primary_key)) {
        found_any = true;
        r.is_primary_key(s.get_boolean_content(tg.is_primary_key));
    }

    if (s.has_entry(tg.is_nullable)) {
        found_any = true;
        r.is_nullable(s.get_boolean_content(tg.is_nullable));
    }

    if (s.has_entry(tg.type_override)) {
        found_any = true;
        const auto to(s.get_text_collection_content(tg.type_override));
        r.type_overrides(make_type_overrides(to));
    }

    if (s.has_entry(tg.is_composite)) {
        found_any = true;
        r.is_composite(s.get_boolean_content(tg.is_composite));
    }

    if (found_any)
        return r;

    return boost::optional<meta_model::orm_attribute_properties>();
}

void orm_transform::update_primitive_properties(
    const type_group& tg, const annotations::annotation& a,
    meta_model::orm_primitive_properties& cfg) {

    const annotations::entry_selector s(a);
    if (s.has_entry(tg.schema_name))
        cfg.schema_name(s.get_text_content(tg.schema_name));
}

boost::optional<meta_model::orm_module_properties>
orm_transform::make_module_properties(const type_group& tg,
    const annotations::annotation& a) {

    const annotations::entry_selector s(a);
    bool found_any(false);

    meta_model::orm_module_properties r;
    if (s.has_entry(tg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(tg.schema_name));
    }

    if (found_any)
        return r;

    return boost::optional<meta_model::orm_module_properties>();
}

void orm_transform::
transform_objects(const type_group& tg, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming objects.";

    boost::optional<meta_model::letter_cases> lc;
    if (em.orm_properties())
        lc = em.orm_properties()->letter_case();

    for (auto& pair : em.objects()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this object. Configurations are setup during
         * stereotypes transform, if the ORM stereotypes were present.
         */
        auto& o(*pair.second);
        if (!o.orm_properties())
            continue;

        auto& ocfg(*o.orm_properties());

        /*
         * Letter case is always setup to match the model
         * configuration.
         */
        ocfg.letter_case(lc);

        /*
         * Now read all of the configuration for each attribute and
         * detect the presence of primary keys.
         */
        bool has_primary_key(false);
        const auto id(pair.first);
        for (auto& attr : o.local_attributes()) {
            const auto& a(attr.annotation());
            const auto attr_cfg(make_attribute_properties(tg, a));
            has_primary_key |= (attr_cfg && attr_cfg->is_primary_key());
            attr.orm_properties(attr_cfg);
        }

        /*
         * Update the object's configuration with any additional
         * meta-data the user may have supplied.
         */
        const auto& a(o.annotation());
        update_object_properties(tg, a, ocfg);
        ocfg.has_primary_key(has_primary_key);

        BOOST_LOG_SEV(lg, debug) << "ORM configuration for object: "
                                 << pair.first << ": " << ocfg;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming objects.";
}

void orm_transform::
transform_object_templates(const type_group& tg, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming object templates.";

    for (auto& pair : em.object_templates()) {
        auto& c(*pair.second);
        for (auto& attr : c.local_attributes()) {
            const auto& a(attr.annotation());
            attr.orm_properties(make_attribute_properties(tg, a));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming object templates.";
}

void orm_transform::transform_primitives(
    const type_group& tg, meta_model::endomodel& em) {

    BOOST_LOG_SEV(lg, debug) << "Started transforming primitives.";

    boost::optional<meta_model::letter_cases> lc;
    if (em.orm_properties())
        lc = em.orm_properties()->letter_case();

    for (auto& pair : em.primitives()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this primitive. Configurations are setup during
         * stereotypes transform, if the ORM stereotypes were present.
         */
        auto& p(*pair.second);
        if (!p.orm_properties())
            continue;

        auto& cfg(*p.orm_properties());

        /*
         * Letter case is always setup to match the model
         * configuration.
         */
        cfg.letter_case(lc);

        /*
         * Read any additional meta-data the user may have supplied
         * for the configuration.
         */
        const auto& a(p.annotation());
        update_primitive_properties(tg, a, cfg);
        BOOST_LOG_SEV(lg, debug) << "ORM configuration for primitive: "
                                 << pair.first << ": " << cfg;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming primitives.";
}

void orm_transform::
transform_modules(const type_group& tg, meta_model::endomodel& em) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming modules.";

    for (auto& pair : em.modules()) {
        auto& m(*pair.second);
        const auto& a(m.annotation());
        auto cfg(make_module_properties(tg, a));
        if (!cfg)
            continue;

        m.orm_properties(cfg);

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
        for (const auto& id : m.members()) {
            BOOST_LOG_SEV(lg, debug) << "Processing member: " << id;

            const auto i(em.objects().find(id));
            if (i != em.objects().end()) {
                auto& o(*i->second);
                auto& cfg(o.orm_properties());
                const bool update_schema_name(cfg && cfg->schema_name().empty()
                    && (cfg->generate_mapping() || cfg->is_value()));

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                cfg->schema_name(sn);
            } else {
                const auto j(em.primitives().find(id));
                if (j == em.primitives().end())
                    continue;

                auto& p(*j->second);
                auto& cfg(p.orm_properties());
                const bool update_schema_name(cfg &&
                    cfg->schema_name().empty() && cfg->generate_mapping());

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                cfg->schema_name(sn);
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming modules.";
}

void orm_transform::
transform(const context& ctx, meta_model::endomodel& em) {
    tracing::scoped_transform_tracer stp(lg, "orm transform",
        transform_id, em.name().id(), ctx.tracer(), em);

    const auto tg(make_type_group(ctx.type_repository()));
    const auto& rm(*em.root_module());
    em.orm_properties(make_model_properties(tg, rm.annotation()));

    transform_objects(tg, em);
    transform_object_templates(tg, em);
    transform_primitives(tg, em);
    transform_modules(tg, em);

    stp.end_transform(em);
}

}
