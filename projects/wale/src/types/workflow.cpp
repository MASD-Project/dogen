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
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/annotations/io/annotation_io.hpp"
#include "dogen/wale/types/key_extractor.hpp"
#include "dogen/wale/types/properties_factory.hpp"
#include "dogen/wale/types/formatter.hpp"
#include "dogen/wale/types/validator.hpp"
#include "dogen/wale/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("wale.workflow"));

const std::string wale_dir("wale");

}

namespace dogen {
namespace wale {

properties workflow::make_properties(const annotations::type_repository& atrp,
    const annotations::annotation& a) const {
    properties_factory f;
    return f.make(atrp, a);
}

properties workflow::make_properties(
    const boost::filesystem::path& template_path,
    const std::unordered_map<std::string, std::string>& kvps) const {
    properties r;
    r.template_path(template_path);
    r.supplied_kvps(kvps);
    return r;
}

boost::filesystem::path
workflow::resolve_path(const boost::filesystem::path& p) const {
    BOOST_LOG_SEV(lg, debug) << "Resolving path: " << p;

    using namespace dogen::utility::filesystem;
    const auto data_dir(dogen::utility::filesystem::data_files_directory());
    const auto dir(data_dir / wale_dir);
    const auto r(dir / p);

    BOOST_LOG_SEV(lg, debug) << "Resolved path: " << r;
    return r;
}

std::string workflow::
read_content(const boost::filesystem::path& template_path) const {
    BOOST_LOG_SEV(lg, debug) << "Reading content. Path: " << template_path;
    using utility::filesystem::read_file_content;
    return read_file_content(template_path);
}

void workflow::update_actual_kvps(text_template& tt) const {
    key_extractor ke;
    const auto keys(ke.extract(tt.content()));
    tt.properties().expected_keys(keys);
}

std::string workflow::format(const text_template& tt) const {
    formatter fmt;
    return fmt.format(tt);
}

void workflow::validate(const text_template& tt) const {
    validator v;
    v.validate(tt);
}

std::string workflow::execute(const properties& props) const {
    text_template tt;
    tt.properties(props);
    tt.properties().template_path(resolve_path(props.template_path()));
    tt.content(read_content(tt.properties().template_path()));
    update_actual_kvps(tt);
    validate(tt);
    return format(tt);
}

std::string workflow::execute(const annotations::type_repository& atrp,
    const annotations::annotation& a) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow. Annotation: " << a;

    const auto props(make_properties(atrp, a));
    const auto r(execute(props));

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow. Result: " << r;
    return r;
}

std::string workflow::execute(const boost::filesystem::path& template_path,
    const std::unordered_map<std::string, std::string>& kvps) const {
    BOOST_LOG_SEV(lg, debug) << "Executing workflow. Template path: "
                             << template_path << " supplied kvps: " << kvps;

    properties props;
    props.template_path(template_path);
    props.supplied_kvps(kvps);
    const auto r(execute(props));

    BOOST_LOG_SEV(lg, debug) << "Finished executing workflow. Result: " << r;
    return r;
}

} }
