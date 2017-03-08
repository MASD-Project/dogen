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
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/expansion_error.hpp"
#include "dogen/quilt.cpp/types/formattables/cpp_standard_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.cpp_standard_expander"));

const std::string cpp_98("c++-98");
const std::string cpp_11("c++-11");
const std::string cpp_14("c++-14");

const std::string invalid_standard("Standard is invalid or unsupported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

cpp_standards
cpp_standard_expander::to_cpp_standard(const std::string& s) const {
    if (s == cpp_98)
        return cpp_standards::cpp_98;
    else if (s == cpp_11)
        return cpp_standards::cpp_11;
    if (s == cpp_14)
        return cpp_standards::cpp_14;

    BOOST_LOG_SEV(lg, error) << invalid_standard << s;
    BOOST_THROW_EXCEPTION(expansion_error(invalid_standard + s));
}

cpp_standard_expander::type_group cpp_standard_expander::
make_type_group(const annotations::type_repository& atrp) const {
    const annotations::type_repository_selector s(atrp);
    type_group r;
    const auto cs(traits::cpp::standard());
    r.cpp_standard = s.select_type_by_name(cs);
    return r;
}

cpp_standards cpp_standard_expander::
make_standard(const type_group& tg, const annotations::annotation& ra) const {
    const annotations::entry_selector s(ra);
    const auto cs(s.get_text_content_or_default(tg.cpp_standard));
    return to_cpp_standard(cs);
}

void cpp_standard_expander::
expand(const annotations::type_repository& atrp,
    const annotations::annotation& ra, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding C++ standard.";
    const auto tg(make_type_group(atrp));
    fm.cpp_standard(make_standard(tg, ra));
    BOOST_LOG_SEV(lg, debug) << "Finished expanding C++ standard.";
}

} } } }
