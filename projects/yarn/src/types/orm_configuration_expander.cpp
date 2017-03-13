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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/io/orm_model_configuration_io.hpp"
#include "dogen/yarn/io/orm_object_configuration_io.hpp"
#include "dogen/yarn/io/orm_primitive_configuration_io.hpp"
#include "dogen/yarn/types/orm_configuration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.orm_configuration_expander"));

const std::string mysql("mysql");
const std::string postgresql("postgresql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqllite("sqllite");

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

namespace dogen {
namespace yarn {

orm_database_systems orm_configuration_expander::
to_orm_database_system(const std::string& s) const {

    const auto ls(boost::to_lower_copy(s));
    if (ls == mysql) {
        return orm_database_systems::mysql;
    } else if (ls == postgresql) {
        return orm_database_systems::postgresql;
    } else if (ls == oracle) {
        return orm_database_systems::oracle;
    } else if (ls == sql_server) {
        return orm_database_systems::sql_server;
    } else if (ls == sqllite) {
        return orm_database_systems::sqllite;
    }

    BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
    BOOST_THROW_EXCEPTION(expansion_error(invalid_daatabase_system + s));
}

std::vector<orm_database_systems> orm_configuration_expander::
to_orm_database_system(const std::list<std::string>& vs) const {
    std::vector<orm_database_systems> r;
    r.reserve(vs.size());
    for (const auto& s : vs) {
        r.push_back(to_orm_database_system(s));
    }
    return r;
}

letter_cases
orm_configuration_expander::to_letter_case(const std::string& s) const {
    const auto ls(boost::to_lower_copy(s));
    if (ls == upper_case) {
        return letter_cases::upper_case;
    } else if (ls == lower_case) {
        return letter_cases::lower_case;
    }

    BOOST_LOG_SEV(lg, error) << invalid_letter_case << s;
    BOOST_THROW_EXCEPTION(expansion_error(invalid_letter_case + s));
}

std::unordered_map<orm_database_systems, std::string>
orm_configuration_expander::
make_type_overrides(const std::list<std::string> ls) const {
    std::unordered_map<orm_database_systems, std::string> r;

    using utility::string::splitter;
    for (const auto& s : ls) {
        const auto tokens(splitter::split_csv(s));
        if (tokens.size() != 2) {
            BOOST_LOG_SEV(lg, error) << invalid_type_override << s;
            BOOST_THROW_EXCEPTION(expansion_error(invalid_type_override + s));
        }

        const auto ds(tokens.front());
        const auto first(to_orm_database_system(ds));
        const auto second(tokens.back());
        const auto pair(std::make_pair(first, second));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_database_system << ds;
            BOOST_THROW_EXCEPTION(
                expansion_error(duplicate_database_system + ds));
        }
    }

    return r;
}

std::ostream&
operator<<(std::ostream& s, const orm_configuration_expander::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"yarn::orm_configuration_expander::"
      << "type_group\"" << ", "
      << "\"generate_mapping\": " << v.generate_mapping << ", "
      << "\"database_system\": " << v.database_system << ", "
      << "\"table_name\": " << v.table_name << ", "
      << "\"column_name\": " << v.column_name << ", "
      << "\"schema_name\": " << v.schema_name << ", "
      << "\"is_primary_key\": " << v.is_primary_key << ", "
      << "\"letter_case\": " << v.letter_case << ", "
      << "\"is_value\": " << v.is_value << ", "
      << "\"type_override\": " << v.type_override
      << " }";

    return s;
}

orm_configuration_expander::type_group orm_configuration_expander::
make_type_group(const annotations::type_repository& atrp) const {
    type_group r;

    const annotations::type_repository_selector rs(atrp);

    const auto& gm(traits::orm::generate_mapping());
    r.generate_mapping = rs.select_type_by_name(gm);

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

    const auto& iv(traits::orm::is_value());
    r.is_value = rs.select_type_by_name(iv);

    const auto& to(traits::orm::type_override());
    r.type_override = rs.select_type_by_name(to);

    return r;
}

boost::optional<orm_model_configuration>
orm_configuration_expander::make_model_configuration(const type_group& tg,
    const annotations::annotation& a) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating model configuration.";
    const annotations::entry_selector s(a);
    bool found_any(false);

    orm_model_configuration r;
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
    return boost::optional<orm_model_configuration>();
}

boost::optional<orm_object_configuration>
orm_configuration_expander::make_object_configuration(const type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    bool found_any(false);

    orm_object_configuration r;
    if (s.has_entry(tg.generate_mapping)) {
        found_any = true;
        r.generate_mapping(s.get_boolean_content(tg.generate_mapping));
    }

    if (s.has_entry(tg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(tg.schema_name));
    }

    if (s.has_entry(tg.table_name)) {
        found_any = true;
        r.table_name(s.get_text_content(tg.table_name));
    }

    if (s.has_entry(tg.is_value)) {
        found_any = true;
        r.is_value(s.get_boolean_content(tg.is_value));
    }

    if (found_any)
        return r;

    return boost::optional<orm_object_configuration>();
}

boost::optional<orm_attribute_configuration>
orm_configuration_expander::make_attribute_configuration(const type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    bool found_any(false);

    orm_attribute_configuration r;
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

    if (found_any)
        return r;

    return boost::optional<orm_attribute_configuration>();
}

boost::optional<orm_primitive_configuration>
orm_configuration_expander::make_primitive_configuration(const type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    bool found_any(false);

    orm_primitive_configuration r;
    if (s.has_entry(tg.generate_mapping)) {
        found_any = true;
        r.generate_mapping(s.get_boolean_content(tg.generate_mapping));
    }

    if (s.has_entry(tg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(tg.schema_name));
    }

    if (found_any)
        return r;

    return boost::optional<orm_primitive_configuration>();
}

boost::optional<orm_module_configuration>
orm_configuration_expander::make_module_configuration(const type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    bool found_any(false);

    orm_module_configuration r;
    if (s.has_entry(tg.schema_name)) {
        found_any = true;
        r.schema_name(s.get_text_content(tg.schema_name));
    }

    if (found_any)
        return r;

    return boost::optional<orm_module_configuration>();
}

void orm_configuration_expander::
expand_objects(const type_group& tg, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started object expansion.";

    boost::optional<letter_cases> lc;
    if (im.orm_configuration())
        lc = im.orm_configuration()->letter_case();

    for (auto& pair : im.objects()) {
        bool has_primary_key(false);
        auto& o(pair.second);
        for (auto& attr : o.local_attributes()) {
            const auto& a(attr.annotation());
            const auto cfg(make_attribute_configuration(tg, a));
            has_primary_key |= (cfg && cfg->is_primary_key());
            attr.orm_configuration(cfg);
        }

        const auto& a(o.annotation());
        auto cfg(make_object_configuration(tg, a));
        if (cfg && (cfg->generate_mapping() || cfg->is_value())) {
            cfg->has_primary_key(has_primary_key);
            cfg->letter_case(lc);
            BOOST_LOG_SEV(lg, debug) << "ORM configuration for object: "
                                     << pair.first << ": " << *cfg;
        }

        o.orm_configuration(cfg);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished object expansion.";
}

void orm_configuration_expander::
expand_concepts(const type_group& tg, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started concept expansion.";

    for (auto& pair : im.concepts()) {
        auto& c(pair.second);
        for (auto& attr : c.local_attributes()) {
            const auto& a(attr.annotation());
            attr.orm_configuration(make_attribute_configuration(tg, a));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished module expansion.";
}

void orm_configuration_expander::expand_primitives(
    const type_group& tg, intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Started primitive expansion.";

    boost::optional<letter_cases> lc;
    if (im.orm_configuration())
        lc = im.orm_configuration()->letter_case();

    for (auto& pair : im.primitives()) {
        auto& p(pair.second);
        const auto& a(p.annotation());
        auto cfg(make_primitive_configuration(tg, a));
        if (cfg && cfg->generate_mapping()) {
            cfg->letter_case(lc);
            BOOST_LOG_SEV(lg, debug) << "ORM configuration for primitive: "
                                     << pair.first << ": " << *cfg;
        }

        p.orm_configuration(cfg);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished primitive expansion.";
}

void orm_configuration_expander::
expand_modules(const type_group& tg, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started module expansion.";

    for (auto& pair : im.modules()) {
        auto& m(pair.second);
        const auto& a(m.annotation());
        auto cfg(make_module_configuration(tg, a));
        if (!cfg)
            continue;

        m.orm_configuration(cfg);

        /*
         * If we do not have a schema name at the module level we have
         * nothing to worry about; either the object has no schema
         * name either, or it has been overridden - but either way,
         * its not our problem.
         */
        const auto& sn(m.orm_configuration()->schema_name());
        if (sn.empty())
            continue;

        /*
         * If we do have a schema name at the module level, we need to
         * update all objects that do not have a schema name to use
         * it's containing module's schema name.
         */
        for (const auto& id : m.members()) {
            BOOST_LOG_SEV(lg, debug) << "Processing member: " << id;

            const auto i(im.objects().find(id));
            if (i != im.objects().end()) {
                auto& o(i->second);
                auto& cfg(o.orm_configuration());
                const bool update_schema_name(cfg && cfg->schema_name().empty()
                    && (cfg->generate_mapping() || cfg->is_value()));

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                cfg->schema_name(sn);
            } else {
                const auto j(im.primitives().find(id));
                if (j == im.primitives().end())
                    continue;

                auto& p(j->second);
                auto& cfg(p.orm_configuration());
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

    BOOST_LOG_SEV(lg, debug) << "Finished module expansion.";
}

void orm_configuration_expander::
expand(const annotations::type_repository& atrp, intermediate_model& im) const {
    BOOST_LOG_SEV(lg, debug) << "Started expansion.";

    const auto tg(make_type_group(atrp));
    const auto& rm(im.root_module());
    im.orm_configuration(make_model_configuration(tg, rm.annotation()));

    expand_objects(tg, im);
    expand_concepts(tg, im);
    expand_primitives(tg, im);
    expand_modules(tg, im);

    BOOST_LOG_SEV(lg, debug) << "Finished expansion.";
}

} }
