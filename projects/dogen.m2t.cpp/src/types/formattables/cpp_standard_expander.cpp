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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/formattables/expansion_error.hpp"
#include "dogen.m2t.cpp/types/formattables/cpp_standard_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("generation.cpp.formattables.cpp_standard_expander"));

const std::string cpp_98("c++-98");
const std::string cpp_11("c++-11");
const std::string cpp_14("c++-14");
const std::string cpp_17("c++-17");

const std::string invalid_standard("Standard is invalid or unsupported: ");

}

namespace dogen::m2t::cpp::formattables {

cpp_standards
cpp_standard_expander::to_cpp_standard(const std::string& s) const {
    if (s == cpp_98)
        return cpp_standards::cpp_98;
    else if (s == cpp_11)
        return cpp_standards::cpp_11;
    else if (s == cpp_14)
        return cpp_standards::cpp_14;
    else if (s == cpp_17)
        return cpp_standards::cpp_17;

    BOOST_LOG_SEV(lg, error) << invalid_standard << s;
    BOOST_THROW_EXCEPTION(expansion_error(invalid_standard + s));
}

cpp_standard_expander::feature_group cpp_standard_expander::
make_feature_group(const variability::entities::feature_model& fm) const {
    const variability::helpers::feature_selector s(fm);
    feature_group r;
    const auto cs(traits::cpp::standard());
    r.cpp_standard = s.get_by_name(cs);
    return r;
}

cpp_standards cpp_standard_expander::make_standard(const feature_group& fg,
    const variability::entities::configuration& cfg) const {
    const variability::helpers::configuration_selector s(cfg);
    const auto cs(s.get_text_content_or_default(fg.cpp_standard));
    return to_cpp_standard(cs);
}

void cpp_standard_expander::
expand(const variability::entities::feature_model& feature_model,
    const variability::entities::configuration& rcfg, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding C++ standard.";

    const auto fg(make_feature_group(feature_model));
    const auto cpp_std(make_standard(fg, rcfg));
    fm.cpp_standard(cpp_std);
    BOOST_LOG_SEV(lg, debug) << "Finished expanding C++ standard.";
}

}
