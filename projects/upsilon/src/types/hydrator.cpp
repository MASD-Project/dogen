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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/xml/text_reader.hpp"
#include "dogen/upsilon/types/hydration_error.hpp"
#include "dogen/upsilon/types/primitive.hpp"
#include "dogen/upsilon/types/compound.hpp"
#include "dogen/upsilon/types/enumeration.hpp"
#include "dogen/upsilon/types/collection.hpp"
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
const std::string field_type_name("TypeName");

const std::string target_java("JAVA");
const std::string target_cpp("CPP");
const std::string target_cs("CS");

const std::string intrinsic_types_integer("Integer");
const std::string intrinsic_types_binary("Binary");
const std::string intrinsic_types_boolean("Boolean");
const std::string intrinsic_types_date("Date");
const std::string intrinsic_types_decimal("Decimal");
const std::string intrinsic_types_double("Double");
const std::string intrinsic_types_guid("Guid");
const std::string intrinsic_types_integer64("Integer64");
const std::string intrinsic_types_string("String");
const std::string intrinsic_types_utc_time("UtcTime");
const std::string intrinsic_types_utc_date_time("UtcDateTime");

const std::string unsupported_value("Unsupported attribute value: ");

}

namespace dogen {
namespace upsilon {

class config_hydrator {
public:
    config_hydrator(boost::filesystem::path file_name);

private:
    void log_unsupported_element();

private:
    target_types to_target(const std::string& s) const;

private:
    directory read_directory();
    std::vector<schema_ref> read_schema_refs();

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

target_types config_hydrator::to_target(const std::string& s) const {
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
    reader_.validate_current_element(directory_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Directory.";

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
    reader_.validate_current_element(schema_refs_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Schema Refs.";

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

std::vector<representation> config_hydrator::read_representations() {
    reader_.validate_current_element(representations_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Representations.";

    std::list<representation> l;
    reader_.move_next();

    do {
        if (reader_.is_start_element(representation_name)) {
            reader_.validate_self_closing();

            representation rep;
            const auto s(reader_.get_attribute<std::string>(target_name));
            rep.target(to_target(s));
            if (reader_.has_attribute(pof_name))
                rep.pof(reader_.get_attribute_as_boolean(pof_name));

            l.push_back(rep);
        } else
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
    reader_.validate_current_element(output_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Output.";

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
    reader_.validate_current_element(outputs_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Outputs.";

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
    reader_.next_element(config_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Config.";

    reader_.move_next();

    config r;
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
    std::vector<type_information> hydrate();

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

std::vector<type_information> type_information_hydrator::hydrate() {
    reader_.next_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Type Infos.";

    std::list<type_information> l;
    reader_.move_next();
    do {
        reader_.validate_current_element(type_info_name);
        reader_.validate_self_closing();

        type_information ti;
        ti.name(reader_.get_attribute<std::string>(name_lower_case_name));
        ti.pof_id(reader_.get_attribute<std::string>(pof_id_name));
        l.push_back(ti);

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));

    std::vector<type_information> r;
    r.reserve(l.size());
    std::copy(l.begin(), l.end(), std::back_inserter(r));

    BOOST_LOG_SEV(lg, debug) << "Read Type Infos.";
    return r;
}

class schema_hydrator {
public:
    schema_hydrator(boost::filesystem::path file_name);

private:
    void log_unsupported_element();

private:
    intrinsic_types to_intrinsic_types(const std::string& s) const;

private:
    std::vector<dependency> read_dependencies();
    tag read_tag();

    bool read_type_base_fields(type& t);
    boost::shared_ptr<type> read_primitive();

    field read_field();
    boost::shared_ptr<type> read_compound();
    boost::shared_ptr<type> read_enumeration();
    boost::shared_ptr<type> read_collection();
    boost::shared_ptr<type> read_type();

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
schema_hydrator::to_intrinsic_types(const std::string& s) const {
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
    reader_.validate_current_element(dependencies_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Dependencies.";

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

bool schema_hydrator::read_type_base_fields(type& t) {
    if (reader_.is_start_element(name_name)) {
        reader_.validate_self_closing();
        t.name(reader_.get_attribute<std::string>(value_name));
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
        t.extends(reader_.get_attribute<std::string>(value_name));
        return true;
    } else if (reader_.is_start_element(tag_refs_name)) {
        reader_.validate_self_closing();
        t.tag_refs().push_back(
            reader_.get_attribute<std::string>(value_name));
        return true;
    }
    return false;
}

boost::shared_ptr<type> schema_hydrator::read_primitive() {
    reader_.validate_current_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Primitive.";

    auto r(boost::make_shared<primitive>());
    reader_.move_next();

    do {
        if (read_type_base_fields(*r)) {
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

    BOOST_LOG_SEV(lg, debug) << "Read Primitive.";
    return r;
}

field schema_hydrator::read_field() {
    reader_.validate_current_element(fields_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Field.";

    field r;
    reader_.move_next();

    do {
        if (reader_.is_start_element(name_name)) {
            reader_.validate_self_closing();
            r.name(reader_.get_attribute<std::string>(value_name));
        } else if (reader_.is_start_element(comment_name)) {
            reader_.validate_self_closing();
            r.comment(reader_.get_attribute<std::string>(text_name));
        } else if (reader_.is_start_element(field_type_name)) {
            reader_.validate_self_closing();
            type_name tn;
            tn.name(reader_.get_attribute<std::string>(value_name));
            tn.schema_name(
                reader_.get_attribute<std::string>(schema_name_name));
            r.type_name(tn);
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(fields_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Field.";
    return r;
}

boost::shared_ptr<type> schema_hydrator::read_compound() {
    reader_.validate_current_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Compound.";

    auto r(boost::make_shared<compound>());
    reader_.move_next();

    std::list<field> fields;
    do {
        if (read_type_base_fields(*r)) {
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

    BOOST_LOG_SEV(lg, debug) << "Read Compound.";
    return r;
}

boost::shared_ptr<type> schema_hydrator::read_enumeration() {
    reader_.validate_current_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Enumeration.";

    auto r(boost::make_shared<enumeration>());
    reader_.move_next();

    do {
        if (read_type_base_fields(*r)) {
            // do nothing
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Enumeration.";
    return r;
}

boost::shared_ptr<type> schema_hydrator::read_collection() {
    reader_.validate_current_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Collection.";

    auto r(boost::make_shared<collection>());
    reader_.move_next();

    do {
        if (read_type_base_fields(*r)) {
            // do nothing
        } else
            log_unsupported_element();

        reader_.move_next();
    } while (!reader_.is_end_element(types_name));
    reader_.move_next();

    BOOST_LOG_SEV(lg, debug) << "Read Collection.";
    return r;
}

boost::shared_ptr<type> schema_hydrator::read_type() {
    reader_.validate_current_element(types_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Type.";

    const auto s(reader_.get_attribute<std::string>(xsi_type_name));
    if (s == "Primitive")
        return read_primitive();
    else if (s == "Compound")
        return read_compound();
    else if (s == "Enumeration")
        return read_enumeration();
    else if (s == "Collection")
        return read_collection();
    else {
        BOOST_LOG_SEV(lg, warn) << "Unsupported type: " << s;
        reader_.move_next();
        return boost::shared_ptr<type>();
    }

    BOOST_LOG_SEV(lg, debug) << "Read Tag.";
}

schema schema_hydrator::hydrate() {
    reader_.next_element(schema_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Schema.";

    schema r;
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
            const auto t(read_type());
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

std::vector<type_information> hydrator::
hydrate_type_information(boost::filesystem::path f) {
    type_information_hydrator h(f);
    return h.hydrate();
}

model hydrator::hydrate(boost::filesystem::path /*config_file*/) {
    model r;
    return r;
}

} }
