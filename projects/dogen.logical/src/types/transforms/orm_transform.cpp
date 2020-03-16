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
#include <boost/lexical_cast/bad_lexical_cast.hpp>
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/pair_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/meta_model/orm/letter_case.hpp"
#include "dogen.logical/types/features/orm.hpp"
#include "dogen.logical/lexical_cast/meta_model/orm/letter_case_lc.hpp"
#include "dogen.logical/lexical_cast/meta_model/orm/database_system_lc.hpp"
#include "dogen.logical/types/meta_model/structural/module.hpp"
#include "dogen.logical/types/meta_model/structural/object.hpp"
#include "dogen.logical/types/meta_model/structural/builtin.hpp"
#include "dogen.logical/types/meta_model/element.hpp"
#include "dogen.logical/types/meta_model/structural/visitor.hpp"
#include "dogen.logical/types/meta_model/structural/exception.hpp"
#include "dogen.logical/types/meta_model/structural/primitive.hpp"
#include "dogen.logical/types/meta_model/structural/enumeration.hpp"
#include "dogen.logical/types/meta_model/structural/object_template.hpp"
#include "dogen.logical/io/meta_model/orm/database_system_io.hpp"
#include "dogen.logical/io/meta_model/orm/model_properties_io.hpp"
#include "dogen.logical/io/meta_model/orm/object_properties_io.hpp"
#include "dogen.logical/io/meta_model/orm/primitive_properties_io.hpp"
#include "dogen.logical/io/meta_model/orm/type_mapping_io.hpp"
#include "dogen.logical/io/meta_model/model_io.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/orm_transform.hpp"

namespace {

const std::string transform_id("assets.transforms.orm_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string odb_pragma_prefix("#pragma db ");
const std::string odb_value_type("value");
const std::string odb_object_type("object");
const std::string odb_member_type("member");
const std::string odb_empty_column_attribute("column(\"\")");
const std::string odb_id("id");
const std::string odb_no_id("no_id");
const std::string odb_null("null");
const std::string odb_not_null("not_null");

const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqlite("sqlite");

const std::string invalid_case("Letter case is invalid or unsupported: ");
const std::string invalid_type_override("Invalid type override expression: ");
const std::string duplicate_database_system(
    "Found more than one type override for database system: ");
const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");

}

namespace dogen::logical::transforms {

std::string orm_transform::
to_odb_database(const logical::meta_model::orm::database_system ds) {
    using logical::meta_model::orm::database_system;

    switch (ds) {
    case database_system::mysql: return mysql;
    case database_system::postgresql: return postgresql;
    case database_system::oracle: return oracle;
    case database_system::sql_server: return sql_server;
    case database_system::sqlite: return sqlite;
    default: {
        const auto s(boost::lexical_cast<std::string>(ds));
        BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
        BOOST_THROW_EXCEPTION(
            transformation_error(invalid_daatabase_system + s));
    } }
}

std::string
orm_transform::capitalise_schema_name(const std::string& schema_name,
    const boost::optional<meta_model::orm::letter_case>& lc) {
    /*
     * If we do not have a schema name, there is nothing to be
     * done. Similarly, If the user did not supply a letter case
     * configuration, we take the current schema name as is.
     */
    if (schema_name.empty() || !lc)
        return schema_name;

    /*
     * Populate the capitalised schema name according to the
     * configuration requested by the user.
     */
    using meta_model::orm::letter_case;
    if (*lc == letter_case::upper_case)
        return boost::to_upper_copy(schema_name);
    else if (*lc == letter_case::lower_case)
        return boost::to_lower_copy(schema_name);

    const auto s(boost::lexical_cast<std::string>(*lc));
    BOOST_LOG_SEV(lg, error) << invalid_case << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_case + s));
}

std::vector<meta_model::orm::database_system>
orm_transform::to_orm_database_system(const std::list<std::string>& vs) {
    using meta_model::orm::database_system;
    std::vector<database_system> r;
    r.reserve(vs.size());

    for (const auto& s : vs)
        r.push_back(boost::lexical_cast<database_system>(s));

    return r;
}

std::unordered_map<meta_model::orm::database_system, std::string>
orm_transform::make_type_overrides(const std::list<std::string> ls) {
    BOOST_LOG_SEV(lg, debug) << "Reading type overrides.";
    std::unordered_map<meta_model::orm::database_system, std::string> r;
    if (ls.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No type overrides found.";
        return r;
    }

    using utility::string::splitter;
    for (const auto& s : ls) {
        const auto tokens(splitter::split_csv(s));
        if (tokens.size() != 2) {
            BOOST_LOG_SEV(lg, error) << invalid_type_override << s;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_type_override + s));
        }

        const auto ds(tokens.front());
        using meta_model::orm::database_system;
        const auto first(boost::lexical_cast<database_system>(ds));
        const auto second(tokens.back());
        const auto pair(std::make_pair(first, second));
        const auto inserted(r.insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_database_system << ds;
            BOOST_THROW_EXCEPTION(
                transformation_error(duplicate_database_system + ds));
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished reading type overrides. Read: " << r;
    return r;
}

std::string orm_transform::
make_odb_pragmas_for_type_overrides(const std::unordered_map<
    logical::meta_model::orm::database_system, std::string>& type_overrides) {
    if (type_overrides.empty())
        return std::string();

    std::ostringstream s;
    bool is_first(true);
    for (const auto pair : type_overrides) {
        if (!is_first)
            s << " ";

        const auto ds(pair.first);
        const auto type(pair.second);
        s << to_odb_database(ds) << ":type(\"" << type << "\")";
        is_first = false;
    }

    return s.str();
}

std::list<meta_model::orm::type_mapping>
orm_transform::make_type_mappings(const std::list<std::string> ls) {
    BOOST_LOG_SEV(lg, debug) << "Reading type mappings.";
    using meta_model::orm::type_mapping;
    std::list<type_mapping> r;

    if (ls.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No type mappings found.";
        return r;
    }

    using utility::string::splitter;
    for (const auto& s : ls) {
        const auto tokens(splitter::split_csv(s));
        const auto sz(tokens.size());
        if (sz < 2 || sz > 5) {
            BOOST_LOG_SEV(lg, error) << invalid_type_override << s;
            BOOST_THROW_EXCEPTION(
                transformation_error(invalid_type_override + s));
        }

        /*
         * If there are only two tokens, then we know who they are:
         * source and destination.
         */
        type_mapping tm;
        if (sz == 2) {
            tm.source_type(ls.front());
            tm.destination_type(ls.back());
            r.push_back(tm);
            continue;
        }

        /*
         * For all other cases - i.e. 3 to 5 fields - we need to
         * determine what was supplied. We do this by detecting the
         * presence of the database system. Note that we've got this
         * dodgy throwing logic because we do not yet have proper
         * support for non-throwing lexical casts.
         */
        auto i(tokens.begin());
        using meta_model::orm::database_system;
        try {
            /*
             * If the first field is a valid database system, then the
             * next field must be the source type.
             */
            tm.database(boost::lexical_cast<database_system>(*i));
            tm.source_type(*(++i));
        } catch (const boost::bad_lexical_cast& /*e*/) {
            /*
             * If we have 5 fields then the first field must be a
             * valid database system.
             */
            if (sz == 5)
                throw;

            /*
             * Otherwise, the field must be a source type.
             */
            BOOST_LOG_SEV(lg, debug) << "Processing first field as source: "
                                     << *i;
            tm.source_type(*i);
        }

        /*
         * We must have a destination type.
         */
        ++i;
        tm.destination_type(*i);

        /*
         * We may or may not have a "to source type" function.
         */
        ++i;
        if (i != tokens.end())
            tm.to_source_type(*i);

        /*
         * We may or may not have a "from source type" function.
         */
        ++i;
        if (i != tokens.end())
            tm.to_destination_type(*i);

        r.push_back(tm);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished reading type mappings. Read: " << r;
    return r;
}

std::list<std::string>
orm_transform::make_odb_pragmas_for_type_mappings(const
    std::list<meta_model::orm::type_mapping>& tms) {

    std::list<std::string> r;
    for (const auto& tm: tms) {
        std::ostringstream s;
        s << "map ";
        if (tm.database())
            s << to_odb_database(*tm.database()) << ":";

        s << "type(\"" << tm.source_type() << "\") as(\""
          << tm.destination_type() << "\")";

        if (!tm.to_source_type().empty())
            s << " to(\"" << tm.to_source_type() << "\")";

        if (!tm.to_destination_type().empty())
            s << " from(\"" << tm.to_destination_type() << "\")";

        r.push_back(s.str());
    }
    return r;
}

boost::optional<meta_model::orm::model_properties>
orm_transform::make_model_properties(const features::orm::feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Started creating model configuration.";
    const auto scfg(features::orm::make_static_configuration(fg, cfg));
    bool found(false);

    meta_model::orm::model_properties r;
    if (!scfg.database_system.empty()) {
        found = true;
        r.database_systems(to_orm_database_system(scfg.database_system));
    }

    if (!scfg.letter_case.empty()) {
        found = true;
        using logical::meta_model::orm::letter_case;
        const auto lc(boost::lexical_cast<letter_case>(scfg.letter_case));
        r.letter_case(lc);
    }

    if (!scfg.schema_name.empty()) {
        found = true;
        r.schema_name(scfg.schema_name);
        r.capitalised_schema_name(
            capitalise_schema_name(r.schema_name(), r.letter_case()));
    }

    if (found) {
        BOOST_LOG_SEV(lg, debug) << "Created model configuration: " << r;
        return r;
    }

    BOOST_LOG_SEV(lg, debug) << "Model configuration is empty.";
    return boost::optional<meta_model::orm::model_properties>();
}

void orm_transform::update_object_properties(
    const features::orm::feature_group& fg,
    const variability::meta_model::configuration& cfg,
    const boost::optional<meta_model::orm::letter_case>& lc,
    const std::string& simple_name,
    meta_model::orm::object_properties& oop) {

    const auto pragma_prefix(
        [&]() {
            std::ostringstream s;
            s << odb_pragma_prefix
              << (oop.is_value() ? odb_value_type : odb_object_type)
              << "(" << simple_name << ") ";
            return s.str();
        }());

    const auto scfg(features::orm::make_static_configuration(fg, cfg));
    oop.table_name(scfg.table_name);
    for (const auto& pg : scfg.odb_pragma)
        oop.odb_pragmas().push_back(pragma_prefix + pg);

    /*
     * If we have overridden the schema name in the configuration,
     * then that takes precedence.
     */
    if (!scfg.schema_name.empty()) {
        oop.schema_name(scfg.schema_name);
        const auto csn(capitalise_schema_name(oop.schema_name(), lc));
        oop.capitalised_schema_name(csn);
    }

    /*
     * If we have a schema name - either because it was defaulted from
     * a module, or because it was supplied in the configuration, and
     * we're "active", generate the appropriate ODB pragma.
     */
    const bool is_active((oop.is_value() || oop.generate_mapping()));
    if (!oop.schema_name().empty() && is_active) {
        std::ostringstream s;
        s << pragma_prefix << "schema(\""
          << oop.capitalised_schema_name() << "\")";
        oop.odb_pragmas().push_back(s.str());
    }

    /*
     * If the user has requested ORM support and this object does not
     * have a primary key, then we need to inject ODB's pragma for "no
     * primary key".
     */
    if (oop.generate_mapping() && !oop.is_value() && !oop.has_primary_key())
        oop.odb_pragmas().push_back(pragma_prefix + odb_no_id);
}

boost::optional<meta_model::orm::attribute_properties>
orm_transform::make_attribute_properties(const features::orm::feature_group& fg,
    const variability::meta_model::configuration& cfg,
    const std::string& simple_name, const meta_model::attribute& attr) {

    const auto pragma_prefix(
        [&]() {
            std::ostringstream s;
            s << odb_pragma_prefix << odb_member_type
              << "(" << simple_name << "::" << attr.member_variable_name()
              << ") ";
            return s.str();
        }());

    bool found(false);
    const auto scfg(features::orm::make_static_configuration(fg, cfg));
    using meta_model::orm::attribute_properties;
    attribute_properties r;
    for (const auto& pg : scfg.odb_pragma)
        r.odb_pragmas().push_back(pragma_prefix + pg);

    if (!scfg.column_name.empty()) {
        found = true;
        r.column_name(scfg.column_name);
    }

    if (scfg.is_primary_key) {
        found = true;
        r.is_primary_key(*scfg.is_primary_key);
        r.odb_pragmas().push_back(pragma_prefix + odb_id);
    }

    if (scfg.is_nullable) {
        found = true;
        r.is_nullable(*scfg.is_nullable);

        if (*r.is_nullable())
            r.odb_pragmas().push_back(pragma_prefix + odb_null);
        else
            r.odb_pragmas().push_back(pragma_prefix + odb_not_null);
    }

    if (!scfg.type_override.empty()) {
        found = true;
        r.type_overrides(make_type_overrides(scfg.type_override));
        const auto tos(make_odb_pragmas_for_type_overrides(r.type_overrides()));
        r.odb_pragmas().push_back(pragma_prefix + tos);
    }

    if (scfg.is_composite) {
        found = true;
        r.is_composite(*scfg.is_composite);

        /*
         * For composite keys, we do not want to use the column name as a
         * prefix.
         */
        r.odb_pragmas().push_back(pragma_prefix + odb_empty_column_attribute);
    }

    if (found)
        return r;

    return boost::optional<attribute_properties>();
}

void orm_transform::update_primitive_properties(
    const features::orm::feature_group& fg,
    const variability::meta_model::configuration& cfg,
    const boost::optional<meta_model::orm::letter_case>& lc,
    const std::string& simple_name,
    meta_model::orm::primitive_properties& opp) {
    const auto scfg(features::orm::make_static_configuration(fg, cfg));

    /*
     * Compute the ODB pragma prefix for this primitive.
     */
    const auto pragma_prefix(
        [&]() {
            std::ostringstream s;
            s << odb_pragma_prefix << odb_value_type
              << "(" << simple_name << ") ";
            return s.str();
        }());

    /*
     * If we have overridden the schema name in the configuration,
     * then that takes precedence.
     */
    if (!scfg.schema_name.empty()) {
        opp.schema_name(scfg.schema_name);
        const auto csn(capitalise_schema_name(opp.schema_name(), lc));
        opp.capitalised_schema_name(csn);
    }

    /*
     * If we have a schema name - either because it was defaulted from
     * a module, or because it was supplied in the configuration, and
     * we're "active", generate the appropriate ODB pragma.
     */
    if (!opp.schema_name().empty() && opp.generate_mapping()) {
        std::ostringstream s;
        s << pragma_prefix << "schema(\""
          << opp.capitalised_schema_name() << "\")";
        opp.odb_pragmas().push_back(s.str());
    }

    /*
     * Note that we handle the processing of type overrides here, but
     * these are expressed into ODB pragmas at the (anonymous)
     * attribute level.
     */
    if (!scfg.type_override.empty())
        opp.type_overrides(make_type_overrides(scfg.type_override));
    else
        BOOST_LOG_SEV(lg, debug) << "Primitive has no type overrides.";

    /*
     * Handle type mappings for this primitive.
     */
    if (!scfg.type_mapping.empty()) {
        opp.type_mappings(make_type_mappings(scfg.type_mapping));
        auto tms(make_odb_pragmas_for_type_mappings(opp.type_mappings()));
        for (const auto& tm : tms)
            opp.odb_pragmas().push_back(odb_pragma_prefix + tm);
    } else
        BOOST_LOG_SEV(lg, debug) << "Primitive has no type mappings.";
}

boost::optional<meta_model::orm::module_properties>
orm_transform::make_module_properties(const features::orm::feature_group& fg,
    const variability::meta_model::configuration& cfg,
    const boost::optional<meta_model::orm::letter_case>& lc) {

    using meta_model::orm::module_properties;

    const auto scfg(features::orm::make_static_configuration(fg, cfg));
    if (scfg.schema_name.empty())
        return boost::optional<module_properties>();

    module_properties r;
    r.schema_name(scfg.schema_name);
    r.capitalised_schema_name(capitalise_schema_name(r.schema_name(), lc));
    return r;
}

void orm_transform::transform_objects(
    const features::orm::feature_group& fg, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming objects.";

    boost::optional<meta_model::orm::letter_case> lc;
    if (m.orm_properties())
        lc = m.orm_properties()->letter_case();

    for (auto& pair : m.structural_elements().objects()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this object. Configurations are setup during
         * stereotypes transform, if the ORM stereotypes were present.
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
        const auto& sn(o.name().simple());
        const auto id(pair.first);
        for (auto& attr : o.local_attributes()) {
            const auto& cfg(*attr.configuration());
            const auto attr_op(make_attribute_properties(fg, cfg, sn, attr));
            has_primary_key |= (attr_op && attr_op->is_primary_key());
            attr.orm_properties(attr_op);
        }
        op.has_primary_key(has_primary_key);

        /*
         * Update the object's configuration with any additional
         * meta-data the user may have supplied.
         */
        const auto& cfg(*o.configuration());
        update_object_properties(fg, cfg, lc, sn, op);

        BOOST_LOG_SEV(lg, debug) << "ORM configuration for object: "
                                 << pair.first << ": " << op;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming objects.";
}

void orm_transform::transform_primitives(
    const features::orm::feature_group& fg, meta_model::model& m) {

    BOOST_LOG_SEV(lg, debug) << "Started transforming primitives.";

    boost::optional<meta_model::orm::letter_case> lc;
    if (m.orm_properties())
        lc = m.orm_properties()->letter_case();

    for (auto& pair : m.structural_elements().primitives()) {
        /*
         * If we do not have a configuration, there is nothing to be
         * done for this primitive. Configurations are setup during
         * stereotypes transform, if the ORM stereotypes were present.
         */
        auto& p(*pair.second);
        BOOST_LOG_SEV(lg, trace) << "Processing: "
                                 << p.name().qualified().dot();

        if (!p.orm_properties()) {
            BOOST_LOG_SEV(lg, trace) << "No ORM properties found.";
            continue;
        }

        /*
         * Letter case is always setup to match the model
         * configuration.
         */
        auto& op(*p.orm_properties());
        op.letter_case(lc);

        /*
         * Compute the ODB pragma prefix for this primitive.
         */
        const auto sn(p.name().simple());
        const auto& cfg(*p.configuration());
        update_primitive_properties(fg, cfg, lc, sn, op);
        BOOST_LOG_SEV(lg, debug) << "ORM configuration for primitive: "
                                 << pair.first << ": " << op;

        /*
         * For primitives, we need to inject manually the attribute
         * level pragmas, if there was a top-level pragma. This is
         * because users cannot see the internal attribute.
         *
         * We add this pragma so as to name the primitive's internal
         * value attribute correctly. Primitives do not have column
         * names; they are set by the type that owns them. This avoids
         * names such as "primitive_id_primitive_id", which become
         * "primitive_id" instead.
         *
         * In addition, we also need to obtain all of the type
         * overrides.
         */
        auto& attr(p.value_attribute());
        const auto pragma_prefix(
            [&]() {
                std::ostringstream s;
                s << odb_pragma_prefix << odb_member_type << "(" << sn
                  << "::" << attr.member_variable_name() << ") ";
                return s.str();
            }());
        std::ostringstream s;
        s << pragma_prefix << odb_empty_column_attribute;

        meta_model::orm::attribute_properties ap;
        const auto& to(op.type_overrides());
        if (!to.empty())
            s << " " << make_odb_pragmas_for_type_overrides(to);
        ap.odb_pragmas().push_back(s.str());

        attr.orm_properties(ap);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming primitives.";
}

void orm_transform::transform_modules(
    const features::orm::feature_group& fg, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Started transforming modules.";

    boost::optional<meta_model::orm::letter_case> lc;
    if (m.orm_properties())
        lc = m.orm_properties()->letter_case();

    for (auto& pair : m.structural_elements().modules()) {
        auto& mod(*pair.second);
        BOOST_LOG_SEV(lg, trace) << "Processing: "
                                 << mod.name().qualified().dot();

        const auto& cfg(*mod.configuration());
        const auto omp(make_module_properties(fg, cfg, lc));
        if (!omp)
            continue;

        mod.orm_properties(omp);

        /*
         * If we do not have a schema name at the module level we have
         * nothing to worry about; either the object has no schema
         * name either, or it has been overridden - but either way,
         * its not our problem.
         */
        const auto sn(m.orm_properties()->schema_name());
        const auto csn(m.orm_properties()->capitalised_schema_name());
        if (sn.empty())
            continue;

        /*
         * If we do have a schema name at the module level, we need to
         * update all objects that do not have a schema name to use
         * it's containing module's schema name. Note that this is not
         * done correctly at present, as we do not take into account
         * modules that contain modules.
         */
        for (const auto& id : mod.contains()) {
            BOOST_LOG_SEV(lg, debug) << "Processing contained element: " << id;

            const auto i(m.structural_elements().objects().find(id));
            if (i != m.structural_elements().objects().end()) {
                auto& o(*i->second);
                auto& op(o.orm_properties());
                const bool update_schema_name(op && op->schema_name().empty()
                    && (op->generate_mapping() || op->is_value()));

                if (!update_schema_name)
                    continue;

                BOOST_LOG_SEV(lg, debug) << "Updating schema name for: " << id
                                         << " to: " << sn;
                op->schema_name(sn);
                op->capitalised_schema_name(csn);
            } else {
                const auto j(m.structural_elements().primitives().find(id));
                if (j == m.structural_elements().primitives().end())
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
                op->capitalised_schema_name(csn);
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming modules.";
}

void orm_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "orm transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * First we must transform the model. If the model has no ORM
     * configuration, there is no need to continue.
     */
    const auto& fm(*ctx.feature_model());
    const auto fg(features::orm::make_feature_group(fm));
    const auto& rm(*m.root_module());
    m.orm_properties(make_model_properties(fg, *rm.configuration()));
    if (!m.orm_properties()) {
        BOOST_LOG_SEV(lg, debug) << "Model does not have an ORM configuration.";
        return;
    }

    /*
     * Then we must transform modules next, in order to ensure the
     * schema name is populated accordingly.
     */
    transform_modules(fg, m);

    /*
     * Finally we can transform objects and primitives, in no
     * particular order.
     */
    transform_objects(fg, m);
    transform_primitives(fg, m);

    stp.end_transform(m);
}

}
