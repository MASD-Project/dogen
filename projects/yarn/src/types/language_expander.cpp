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
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/io/languages_io.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/language_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.language_expander"));


const std::string cpp_language("cpp");
const std::string csharp_language("csharp");
const std::string la_language("language_agnostic");
const std::string upsilon_language("upsilon");

const std::string unsupported_lanugage("Language is not supported: ");

}

namespace dogen {
namespace yarn {

languages language_expander::to_language(const std::string& s) const {
    if (s == cpp_language)
        return languages::cpp;
    else if (s == csharp_language)
        return languages::csharp;
    else if (s == la_language)
        return languages::language_agnostic;
    else if (s == upsilon_language)
        return languages::upsilon;

    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(expansion_error(unsupported_lanugage + s));
}

language_expander::type_group language_expander::
make_type_group(const annotations::type_repository& atrp) const {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.language = s.select_type_by_name(traits::language());
    return r;
}

languages language_expander::make_language(const type_group& tg,
    const annotations::annotation& a) const {
    const annotations::entry_selector s(a);
    const auto lang_str(s.get_text_content_or_default(tg.language));
    return to_language(lang_str);
}

void language_expander::
expand(const annotations::type_repository& atrp, intermediate_model& im) const {
    const auto tg(make_type_group(atrp));
    const auto ra(im.root_module().annotation());
    const auto l(make_language(tg, ra));
    im.language(l);
}

} }
