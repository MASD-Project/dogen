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
#include <list>
#include <vector>
#include <algorithm>
#include <boost/make_shared.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/xml/text_reader.hpp"
#include "dogen/upsilon/io/model_io.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/collection.hpp"
#include "dogen/upsilon/types/enumeration.hpp"
#include "dogen/upsilon/types/id_generator.hpp"
#include "dogen/upsilon/types/hydration_error.hpp"
#include "dogen/upsilon/types/hydrator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(dogen::utility::log::logger_factory("upsilon.hydrator"));

const std::string config_name("Config");
const std::string directory_name("Directory");
const std::string public_name("Public");
const std::string private_name("Private");
const std::string value_name("Value");
const std::string name_name("Name");
const std::string name_lower_case_name("name");
const std::string file_name("File");
const std::string target_name("Target");
const std::string pof_name("Pof");
const std::string pof_id_name("pofId");
const std::string schema_name("Schema");
const std::string schema_name_name("SchemaName");
const std::string schema_refs_name("SchemaRefs");
const std::string schema_ref_name("SchemaRef");
const std::string outputs_name("Outputs");
const std::string output_name("Output");
const std::string representations_name("Representations");
const std::string representation_name("Representation");
const std::string type_info_name("TypeInfo");
const std::string types_name("Types");
const std::string id_min_name("IdMin");
const std::string id_max_name("IdMax");
const std::string base_guid_name("BaseGuid");
const std::string dependencies_name("Dependencies");
const std::string tags_name("Tags");
const std::string comment_name("Comment");
const std::string text_name("Text");
const std::string id_name("Id");
const std::string tag_refs_name("TagRefs");
const std::string extends_name("Extends");
const std::string intrinsic_name("Intrinsic");
const std::string default_name("Default");
const std::string xsi_type_name("xsi:type");
const std::string fields_name("Fields");
const std::string type_name_name("TypeName");
const std::string values_name("Values");
const std::string exclusions_name("Exclusions");
const std::string exclusion_name("Exclusion");

const std::string target_java("java");
const std::string target_cpp("cpp");
const std::string target_cs("cs");

const std::string intrinsic_types_integer("integer");
const std::string intrinsic_types_binary("binary");
const std::string intrinsic_types_boolean("boolean");
const std::string intrinsic_types_date("date");
const std::string intrinsic_types_decimal("decimal");
const std::string intrinsic_types_double("double");
const std::string intrinsic_types_guid("guid");
const std::string intrinsic_types_integer64("integer64");
const std::string intrinsic_types_string("string");
const std::string intrinsic_types_utc_time("utctime");
const std::string intrinsic_types_utc_date_time("utcdatetime");

const std::string type_infos_extension(".typeinfos");

const std::string unsupported_value("Unsupported attribute value: ");
const std::string duplicate_schema("Schema name already exists: ");
const std::string schema_not_found("Could not locate schema: ");
const std::string type_infos_not_found("Could not locate type infos: ");

}

namespace dogen {
namespace upsilon {

class config_hydrator {
public:
    config_hydrator(boost::filesystem::path file_name);

private:
    void log_unsupported_element();

private:
    target_types to_target(std::string s) const;

private:
    directory read_directory();
    std::vector<schema_ref> read_schema_refs();

    representation read_representation();
    std::vector<representation> read_representations();
    output read_output();
    std::vector<output> read_outputs();

public:
    config hydrate();

private:
    boost::filesystem::path file_name_;
    utility::xml::text_reader reader_;
};

config_hydrator::config_hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, true/*skip_whitespace*/) { }

void config_hydrator::log_unsupported_element() {
    BOOST_LOG_SEV(lg, warn) << "Unsupported element: "
                            << reader_.name();
}

target_types config_hydrator::to_target(std::string s) const {
    boost::algorithm::to_lower(s);
    if (s == target_java)
        return target_types::java;
    else if (s == target_cpp)
        return target_types::cpp;
    else if (s == target_cs)
        return target_types::cs;
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_value << s;
        BOOST_THROW_EXCEPTION(hydration_error(unsupported_value + s));
    }
}

directory config_hydrator::read_directory() {
    BOOST_LOG_SEV(lg, debug) << "Reading Directory.";
    reader_.validate_current_element(directory_name);

    directory r;
    reader_.move_next();

    do {
        if (reader_.is_start_element(public_name)) {
            reader_.validate_self_closing();
            r.public_location(reader_.get_attribute<std::string>(value_name));
        } else if (reader_.is_start_element(private_name)) {
            reader_.validate_self_closing();
            r.private_location(reader_.get_attribute<std::string>(value_name));
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(directory_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Directory.";

    return r;
}

std::vector<schema_ref> config_hydrator::read_schema_refs() {
    BOOST_LOG_SEV(lg, debug) << "Reading Schema Refs.";
    reader_.validate_current_element(schema_refs_name);

    std::list<schema_ref> l;
    reader_.move_next();

    do {
        if (reader_.is_start_element(schema_ref_name)) {
            reader_.validate_self_closing();

            schema_ref sr;
            sr.name(reader_.get_attribute<std::string>(name_name));
            sr.file(reader_.get_attribute<std::string>(file_name));
            l.push_back(sr);
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(schema_refs_name));
    reader_.move_next();

    std::vector<schema_ref> r;
    r.reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r));

    BOOST_LOG_SEV(lg, debug) << "Read Schema Refs.";
    return r;
}

representation config_hydrator::read_representation() {
    BOOST_LOG_SEV(lg, debug) << "Reading Representation.";
    reader_.validate_current_element(representation_name);

    representation r;
    const auto s(reader_.get_attribute<std::string>(target_name));
    r.target(to_target(s));
    if (reader_.has_attribute(pof_name))
        r.pof(reader_.get_attribute_as_boolean(pof_name));

    if (reader_.is_empty()) {
        BOOST_LOG_SEV(lg, debug) << "Read Representation.";
        return r;
    }

    reader_.move_next();
    std::list<exclusion> l;
    const auto& tnn(type_name_name);
    do {
        if (reader_.is_start_element(exclusions_name)) {
            reader_.move_next();
            do {
                if (reader_.is_start_element(exclusion_name)) {
                    reader_.validate_self_closing();

                    exclusion exc;
                    exc.type_name(reader_.get_attribute<std::string>(tnn));
                    l.push_back(exc);
                    reader_.move_next();
                }
            } while (!reader_.is_end_element(exclusions_name));
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(representation_name));

    r.exclusions().reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r.exclusions()));

    BOOST_LOG_SEV(lg, debug) << "Read Representation.";

    return r;
}

std::vector<representation> config_hydrator::read_representations() {
    BOOST_LOG_SEV(lg, debug) << "Reading Representations.";
    reader_.validate_current_element(representations_name);

    std::list<representation> l;
    reader_.move_next();

    do {
        if (reader_.is_start_element(representation_name))
            l.push_back(read_representation());
        else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(representations_name));
    reader_.move_next();

    std::vector<representation> r;
    r.reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r));

    BOOST_LOG_SEV(lg, debug) << "Read Representations.";

    return r;
}

output config_hydrator::read_output() {
    BOOST_LOG_SEV(lg, debug) << "Reading Output.";
    reader_.validate_current_element(output_name);

    output r;
    r.schema_name(reader_.get_attribute<std::string>(schema_name_name));
    reader_.move_next();

    do {
        if (reader_.is_start_element(representations_name))
            r.representations(read_representations());
        else {
            log_unsupported_element();
            reader_.move_next();
        }
    } while (!reader_.is_end_element(output_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Output.";
    return r;
}

std::vector<output> config_hydrator::read_outputs() {
    BOOST_LOG_SEV(lg, debug) << "Reading Outputs.";
    reader_.validate_current_element(outputs_name);

    std::list<output> l;
    reader_.move_next();

    do {
        if (reader_.is_start_element(output_name))
            l.push_back(read_output());
        else {
            log_unsupported_element();
            reader_.move_next();
        }
    } while (!reader_.is_end_element(outputs_name));
    reader_.move_next();

    std::vector<output> r;
    r.reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r));

    BOOST_LOG_SEV(lg, debug) << "Read Outputs.";
    return r;
}

config config_hydrator::hydrate() {
    BOOST_LOG_SEV(lg, debug) << "Reading Config.";
    reader_.next_element(config_name);
    reader_.move_next();

    config r;
    r.file_name(file_name_.filename());
    do {
        if (reader_.is_start_element(directory_name))
            r.directory(read_directory());
        else if (reader_.is_start_element(schema_refs_name))
            r.schema_refs(read_schema_refs());
        else if (reader_.is_start_element(outputs_name))
            r.outputs(read_outputs());
        else {
            log_unsupported_element();
            reader_.move_next();
        }
    } while (!reader_.is_end_element(config_name));

    BOOST_LOG_SEV(lg, debug) << "Read Config.";
    return r;
}

class type_information_hydrator {
public:
    type_information_hydrator(boost::filesystem::path file_name);

private:
    void log_unsupported_element();

public:
    type_information hydrate();

private:
    boost::filesystem::path file_name_;
    utility::xml::text_reader reader_;
};

type_information_hydrator::
type_information_hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, true/*skip_whitespace*/) { }

void type_information_hydrator::log_unsupported_element() {
    BOOST_LOG_SEV(lg, warn) << "Unsupported element: "
                            << reader_.name();
}

type_information type_information_hydrator::hydrate() {
    BOOST_LOG_SEV(lg, debug) << "Reading Type Infos.";
    reader_.next_element(types_name);

    type_information r;
    r.file_name(file_name_.filename());

    std::list<type_information_entry> l;
    reader_.move_next();
    do {
        reader_.validate_current_element(type_info_name);
        reader_.validate_self_closing();

        type_information_entry tie;
        tie.name(reader_.get_attribute<std::string>(name_lower_case_name));
        tie.pof_id(reader_.get_attribute<std::string>(pof_id_name));
        l.push_back(tie);

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));

    r.entries().reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r.entries()));

    BOOST_LOG_SEV(lg, debug) << "Read Type Infos.";
    return r;
}

class schema_hydrator {
public:
    schema_hydrator(boost::filesystem::path file_name);

private:
    void log_unsupported_element();

private:
    intrinsic_types to_intrinsic_types(std::string s) const;

private:
    std::vector<dependency> read_dependencies();
    tag read_tag();

    bool read_type_base_fields(const std::string& schema_name, type& t);
    boost::shared_ptr<type> read_primitive(const std::string& schema_name);

    field read_field();
    name read_name();
    name read_name(const std::string& schema_name);
    boost::shared_ptr<type> read_compound(const std::string& schema_name);
    boost::shared_ptr<type> read_enumeration(const std::string& schema_name);
    boost::shared_ptr<type> read_collection(const std::string& schema_name);
    boost::shared_ptr<type> read_type(const std::string& schema_name);

public:
    schema hydrate();

private:
    boost::filesystem::path file_name_;
    utility::xml::text_reader reader_;
};

schema_hydrator::schema_hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, true/*skip_whitespace*/) { }

void schema_hydrator::log_unsupported_element() {
    BOOST_LOG_SEV(lg, warn) << "Unsupported element: "
                            << reader_.name();
}

intrinsic_types
schema_hydrator::to_intrinsic_types(std::string s) const {
    boost::algorithm::to_lower(s);
    if (s == intrinsic_types_integer)
        return intrinsic_types::integer;
    else if (s == intrinsic_types_binary)
        return intrinsic_types::binary;
    else if (s == intrinsic_types_boolean)
        return intrinsic_types::boolean;
    else if (s == intrinsic_types_date)
        return intrinsic_types::date;
    else if (s == intrinsic_types_decimal)
        return intrinsic_types::decimal;
    else if (s == intrinsic_types_double)
        return intrinsic_types::double_x;
    else if (s == intrinsic_types_guid)
        return intrinsic_types::guid;
    else if (s == intrinsic_types_integer64)
        return intrinsic_types::integer64;
    else if (s == intrinsic_types_string)
        return intrinsic_types::string;
    else if (s == intrinsic_types_utc_time)
        return intrinsic_types::utc_time;
    else if (s == intrinsic_types_utc_date_time)
        return intrinsic_types::utc_date_time;
    else {
        BOOST_LOG_SEV(lg, error) << unsupported_value << s;
        BOOST_THROW_EXCEPTION(hydration_error(unsupported_value + s));
    }
}

std::vector<dependency> schema_hydrator::read_dependencies() {
    BOOST_LOG_SEV(lg, debug) << "Reading Dependencies.";
    reader_.validate_current_element(dependencies_name);

    std::list<dependency> l;
    reader_.move_next();

    do {
        if (reader_.is_start_element(name_name)) {
            reader_.validate_self_closing();

            dependency d;
            d.name(reader_.get_attribute<std::string>(value_name));
            l.push_back(d);
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(dependencies_name));
    reader_.move_next();

    std::vector<dependency> r;
    r.reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r));

    BOOST_LOG_SEV(lg, debug) << "Read Dependencies.";
    return r;
}

tag schema_hydrator::read_tag() {
    reader_.validate_current_element(tags_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Tag.";

    tag r;
    reader_.move_next();

    do {
        if (reader_.is_start_element(name_name)) {
            reader_.validate_self_closing();
            r.name(reader_.get_attribute<std::string>(value_name));
        } else if (reader_.is_start_element(comment_name)) {
            reader_.validate_self_closing();
            r.comment(reader_.get_attribute<std::string>(text_name));
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(tags_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Tag.";
    return r;
}

bool schema_hydrator::
read_type_base_fields(const std::string& schema_name, type& t) {
    if (reader_.is_start_element(name_name)) {
        reader_.validate_self_closing();
        t.name(read_name(schema_name));
        return true;
    } else if (reader_.is_start_element(id_name)) {
        reader_.validate_self_closing();
        t.pof_id(reader_.get_attribute<std::string>(value_name));
        return true;
    } else if (reader_.is_start_element(comment_name)) {
        reader_.validate_self_closing();
        t.comment(reader_.get_attribute<std::string>(text_name));
        return true;
    } else if (reader_.is_start_element(extends_name)) {
        reader_.validate_self_closing();
        t.extends(read_name());
        return true;
    } else if (reader_.is_start_element(tag_refs_name)) {
        reader_.validate_self_closing();
        t.tag_refs().push_back(reader_.get_attribute<std::string>(value_name));
        return true;
    }
    return false;
}

boost::shared_ptr<type>
schema_hydrator::read_primitive(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, trace) << "Reading Primitive.";
    reader_.validate_current_element(types_name);

    auto r(boost::make_shared<primitive>());
    reader_.move_next();

    do {
        if (read_type_base_fields(schema_name, *r)) {
            // do nothing
        } else if (reader_.is_start_element(intrinsic_name)) {
            reader_.validate_self_closing();
            const auto s(reader_.get_attribute<std::string>(value_name));
            r->intrinsic(to_intrinsic_types(s));
        } else if (reader_.is_start_element(default_name)) {
            reader_.validate_self_closing();
            r->default_value(reader_.get_attribute<std::string>(value_name));
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, trace) << "Read Primitive.";
    return r;
}

field schema_hydrator::read_field() {
    BOOST_LOG_SEV(lg, trace) << "Reading Field.";
    reader_.validate_current_element(fields_name);

    field r;
    reader_.move_next();

    do {
        if (reader_.is_start_element(name_name)) {
            reader_.validate_self_closing();
            r.name(reader_.get_attribute<std::string>(value_name));
        } else if (reader_.is_start_element(comment_name)) {
            reader_.validate_self_closing();
            r.comment(reader_.get_attribute<std::string>(text_name));
        } else if (reader_.is_start_element(type_name_name))
            r.type_name(read_name());
        else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(fields_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, trace) << "Read Field.";
    return r;
}

name schema_hydrator::read_name(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, trace) << "Reading Name.";

    name r;
    reader_.validate_self_closing();

    r.value(reader_.get_attribute<std::string>(value_name));
    r.schema_name(schema_name);

    id_generator g;
    r.id(g.generate(r));

    return r;
}

name schema_hydrator::read_name() {
    BOOST_LOG_SEV(lg, trace) << "Reading Name.";

    name r;
    reader_.validate_self_closing();

    r.value(reader_.get_attribute<std::string>(value_name));
    if (reader_.has_attribute(schema_name_name))
        r.schema_name(reader_.get_attribute<std::string>(schema_name_name));

    id_generator g;
    r.id(g.generate(r));

    BOOST_LOG_SEV(lg, trace) << "Read Name.";
    return r;
}

boost::shared_ptr<type>
schema_hydrator::read_compound(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, trace) << "Reading Compound.";
    reader_.validate_current_element(types_name);

    auto r(boost::make_shared<compound>());
    reader_.move_next();

    std::list<field> fields;
    do {
        if (read_type_base_fields(schema_name, *r)) {
            reader_.move_next();
        } else if (reader_.is_start_element(fields_name)) {
            fields.push_back(read_field());
        } else {
            log_unsupported_element();
            reader_.move_next();
        }
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    r->fields().reserve(fields.size());
    std::copy(fields.begin(), fields.end(), std::back_inserter(r->fields()));

    BOOST_LOG_SEV(lg, trace) << "Read Compound.";
    return r;
}

boost::shared_ptr<type>
schema_hydrator::read_enumeration(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, trace) << "Reading Enumeration.";
    reader_.validate_current_element(types_name);

    auto r(boost::make_shared<enumeration>());
    reader_.move_next();

    std::list<std::string> values;
    do {
        if (read_type_base_fields(schema_name, *r)) {
            // do nothing
        } else if (reader_.is_start_element(values_name)) {
            reader_.move_next();
            values.push_back(reader_.value_as_string());
            reader_.move_next();
        } else if (reader_.is_start_element(default_name))
            r->default_value(reader_.get_attribute<std::string>(value_name));
        else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    r->values().reserve(values.size());
    std::copy(values.begin(), values.end(), std::back_inserter(r->values()));

    BOOST_LOG_SEV(lg, trace) << "Read Enumeration.";
    return r;
}

boost::shared_ptr<type>
schema_hydrator::read_collection(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, trace) << "Reading Collection.";
    reader_.validate_current_element(types_name);

    auto r(boost::make_shared<collection>());
    reader_.move_next();

    do {
        if (read_type_base_fields(schema_name, *r)) {
            // do nothing
        } else if (reader_.is_start_element(type_name_name))
            r->type_name(read_name());
        else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, trace) << "Read Collection.";
    return r;
}

boost::shared_ptr<type>
schema_hydrator::read_type(const std::string& schema_name) {
    BOOST_LOG_SEV(lg, debug) << "Reading Type.";
    reader_.validate_current_element(types_name);

    const auto s(reader_.get_attribute<std::string>(xsi_type_name));
    if (s == "Primitive")
        return read_primitive(schema_name);
    else if (s == "Compound")
        return read_compound(schema_name);
    else if (s == "Enumeration")
        return read_enumeration(schema_name);
    else if (s == "Collection")
        return read_collection(schema_name);

    BOOST_LOG_SEV(lg, warn) << "Unsupported type: " << s;
    reader_.move_next();
    return boost::shared_ptr<type>();
}

schema schema_hydrator::hydrate() {
    BOOST_LOG_SEV(lg, debug) << "Reading Schema.";
    do {
        reader_.read();
        if (reader_.is_comment())
            BOOST_LOG_SEV(lg, trace) << "Skipping comment.";
    } while (reader_.is_comment());

    reader_.validate_current_element(schema_name);

    schema r;
    r.file_name(file_name_.filename());
    r.name(reader_.get_attribute<std::string>(name_name));
    r.id_min(reader_.get_attribute<std::string>(id_min_name));
    r.id_max(reader_.get_attribute<std::string>(id_max_name));
    r.base_guid(reader_.get_attribute<std::string>(base_guid_name));

    std::list<tag> tags;
    std::list<boost::shared_ptr<type>> types;

    reader_.move_next();
    do {
        if (reader_.is_start_element(dependencies_name))
            r.dependencies(read_dependencies());
        else if (reader_.is_start_element(tags_name))
            tags.push_back(read_tag());
        else if (reader_.is_start_element(types_name)) {
            const auto t(read_type(r.name()));
            if (t)
                types.push_back(t);
        } else {
            log_unsupported_element();
            reader_.move_next();
        }
    } while (!reader_.is_end_element(schema_name));

    r.tags().reserve(tags.size());
    std::copy(tags.begin(), tags.end(), std::back_inserter(r.tags()));

    r.types().reserve(types.size());
    std::copy(types.begin(), types.end(), std::back_inserter(r.types()));

    BOOST_LOG_SEV(lg, debug) << "Read Schema.";
    return r;
}

config hydrator::hydrate_config(boost::filesystem::path f) {
    BOOST_LOG_SEV(lg, debug) << "Hydrating config file: " << f;
    config_hydrator h(f);
    return h.hydrate();
}

schema hydrator::hydrate_schema(boost::filesystem::path f) {
    BOOST_LOG_SEV(lg, debug) << "Hydrating schema file: " << f;
    schema_hydrator h(f);
    return h.hydrate();
}

type_information hydrator::hydrate_type_information(boost::filesystem::path f) {
    BOOST_LOG_SEV(lg, debug) << "Hydrating type infos file: " << f;
    type_information_hydrator h(f);
    return h.hydrate();
}

model hydrator::hydrate(boost::filesystem::path config_file) {
    BOOST_LOG_SEV(lg, debug) << "Started hydrating upsilon model";

    model r;
    r.config(hydrate_config(config_file));

    using namespace boost::filesystem;
    using utility::filesystem::find_file_recursively_upwards;

    auto directory_path(config_file.parent_path());
    for (const auto& schema_ref : r.config().schema_refs()) {
        const path sp(schema_ref.file());
        const auto abs_sp(find_file_recursively_upwards(directory_path, sp));

        if (abs_sp.empty()) {
            const auto gs(sp.generic_string());
            BOOST_LOG_SEV(lg, error) << schema_not_found << gs;
            BOOST_THROW_EXCEPTION(hydration_error(schema_not_found + gs));
        }

        const auto s(hydrate_schema(abs_sp));
        {
            const auto pair(std::make_pair(schema_ref.name(), s));
            const auto inserted(r.schemas().insert(pair).second);
            if (!inserted) {
                const auto sn(schema_ref.name());
                BOOST_LOG_SEV(lg, error) << duplicate_schema << sn;
                BOOST_THROW_EXCEPTION(hydration_error(duplicate_schema + sn));
            }
        }

        path tip(schema_ref.file() + type_infos_extension);
        const auto abs_tip(find_file_recursively_upwards(directory_path, tip));

        if (abs_tip.empty()) {
            const auto gs(tip.generic_string());
            BOOST_LOG_SEV(lg, warn) << type_infos_not_found << gs;
            continue;
        }

        const auto ti(hydrate_type_information(abs_tip));
        {
            const auto pair(std::make_pair(schema_ref.name(), ti));
            const auto inserted(r.type_information().insert(pair).second);
            if (!inserted) {
                const auto sn(schema_ref.name());
                BOOST_LOG_SEV(lg, error) << duplicate_schema << sn;
                BOOST_THROW_EXCEPTION(hydration_error(duplicate_schema + sn));
            }
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished hydrating upsilon model. Result: "
                             << r;
    return r;
}

} }
