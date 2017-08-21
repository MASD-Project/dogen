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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/yarn/types/traits.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/io/meta_model/languages_io.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/transformation_error.hpp"
#include "dogen/yarn/types/transforms/language_transform.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.transforms.language_transform"));


const std::string cpp_language("cpp");
const std::string csharp_language("csharp");
const std::string la_language("language_agnostic");
const std::string upsilon_language("upsilon");

const std::string unsupported_lanugage("Language is not supported: ");

}

namespace dogen {
namespace yarn {
namespace transforms {

meta_model::languages language_transform::to_language(const std::string& s) {
    using meta_model::languages;
    if (s == cpp_language)
        return languages::cpp;
    else if (s == csharp_language)
        return languages::csharp;
    else if (s == la_language)
        return languages::language_agnostic;
    else if (s == upsilon_language)
        return languages::upsilon;

    BOOST_LOG_SEV(lg, error) << unsupported_lanugage << s;
    BOOST_THROW_EXCEPTION(transformation_error(unsupported_lanugage + s));
}

language_transform::type_group language_transform::
make_type_group(const annotations::type_repository& atrp) {
    type_group r;
    const annotations::type_repository_selector s(atrp);
    r.input_language = s.select_type_by_name(traits::input_language());
    r.output_language = s.select_type_by_name(traits::output_language());
    return r;
}

meta_model::languages
language_transform::make_input_language(const type_group& tg,
    const annotations::annotation& a) {
    const annotations::entry_selector s(a);
    const auto lang_str(s.get_text_content_or_default(tg.input_language));
    return to_language(lang_str);
}

std::list<meta_model::languages>
language_transform::make_output_languages(const type_group& tg,
    const annotations::annotation& a) {
    const annotations::entry_selector s(a);

    std::list<meta_model::languages> r;
    if (!s.has_entry(tg.output_language))
        return r;

    const auto lang_str(s.get_text_collection_content(tg.output_language));
    for (const auto s : lang_str)
        r.push_back(to_language(s));

    return r;
}

void language_transform::
transform(const context& ctx, meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Expanding language. Model: " << im.name().id();

    const auto tg(make_type_group(ctx.type_repository()));
    const auto ra(im.root_module()->annotation());
    using meta_model::languages;
    const bool has_input_language(im.input_language() != languages::invalid);
    if (!has_input_language) {
        const auto il(make_input_language(tg, ra));
        im.input_language(il);
        BOOST_LOG_SEV(lg, debug) << "Expanded input language to: " << il;
    } else {
        BOOST_LOG_SEV(lg, debug) << "Model already has an input language: "
                                 << im.input_language();
    }

    if (im.output_languages().empty()) {
        const auto ol(make_output_languages(tg, ra));

        /*
         * If we did not set an output language, assume the input as
         * output. Validator will ensure this language is actually
         * outputtable.
         */
        if (ol.empty()) {
            im.output_languages().push_back(im.input_language());

            BOOST_LOG_SEV(lg, debug) << "No output language overrides found. "
                                     << "Defaulting to input languae: "
                                     << im.output_languages();
        } else {
            im.output_languages(ol);

            BOOST_LOG_SEV(lg, debug) << "Expanded output languages to: "
                                     << im.output_languages();
        }
    } else {
        BOOST_LOG_SEV(lg, debug) << "Model already has output languages: "
                                 << im.output_languages();
    }

    BOOST_LOG_SEV(lg, debug) << "Expanded language.";
}

} } }
