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

}

namespace dogen {
namespace upsilon {

class config_hydrator {
public:
    config_hydrator(boost::filesystem::path file_name);

private:
    directory read_directory();

public:
    config hydrate();

private:
    boost::filesystem::path file_name_;
    utility::xml::text_reader reader_;
};

config_hydrator::config_hydrator(boost::filesystem::path file_name)
    : file_name_(file_name),
      reader_(file_name, true/*skip_whitespace*/) { }


directory config_hydrator::read_directory() {
    reader_.validate_current_element(directory_name);
    BOOST_LOG_SEV(lg, debug) << "Reading Directory.";

    directory r;
    reader_.move_next();

    do {
        if (reader_.is_start_element(public_name))
            r.public_location(reader_.get_attribute<std::string>(value_name));
        else if (reader_.is_start_element(private_name))
            r.private_location(reader_.get_attribute<std::string>(value_name));
        else {
            BOOST_LOG_SEV(lg, warn) << "Unsupported element: "
                                    << reader_.name();
        }

        reader_.move_next();
    } while (!reader_.is_end_element(directory_name));

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
        else {
            BOOST_LOG_SEV(lg, warn) << "Unsupported element: "
                                    << reader_.name();
        }

        reader_.move_next();
    } while (!reader_.is_end_element(config_name));

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
