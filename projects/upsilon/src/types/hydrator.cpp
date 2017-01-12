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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/xml/text_reader.hpp"
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
const std::string file_name("File");
const std::string target_name("Target");
const std::string pof_name("Pof");
const std::string schema_name("SchemaName");
const std::string schema_refs_name("SchemaRefs");
const std::string schema_ref_name("SchemaRef");
const std::string outputs_name("Outputs");
const std::string output_name("Output");
const std::string representations_name("Representations");
const std::string representation_name("Representation");

const std::string target_java("JAVA");
const std::string target_cpp("CPP");
const std::string target_cs("CS");

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
    r.schema_name(reader_.get_attribute<std::string>(schema_name));
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

config hydrator::hydrate_config(boost::filesystem::path f) {
    BOOST_LOG_SEV(lg, debug) << "Hydrating config file: " << f;
    config_hydrator h(f);
    return h.hydrate();
}

schema hydrator::hydrate_schema(boost::filesystem::path /*f*/) {
    schema r;
    return r;
}

type_information hydrator::
hydrate_type_information(boost::filesystem::path /*f*/) {
    type_information r;
    return r;
}

model hydrator::hydrate(boost::filesystem::path /*config_file*/) {
    model r;
    return r;
}

} }
