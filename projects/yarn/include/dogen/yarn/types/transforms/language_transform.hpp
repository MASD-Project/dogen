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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_LANGUAGE_TRANSFORM_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_LANGUAGE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/meta_model/languages.hpp"
#include "dogen/yarn/types/meta_model/endomodel.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class language_transform final {
private:
    static meta_model::languages to_language(const std::string& s);

private:
    struct type_group {
        annotations::type input_language;
        annotations::type output_language;
    };

    static type_group make_type_group(const annotations::type_repository& atrp);

    static meta_model::languages make_input_language(const type_group& tg,
        const annotations::annotation& a);

    static std::list<meta_model::languages>
    make_output_languages(const type_group& tg,
        const annotations::annotation& a);

public:
    static void transform(const context& ctx, meta_model::endomodel& m);
};

} } }

#endif
