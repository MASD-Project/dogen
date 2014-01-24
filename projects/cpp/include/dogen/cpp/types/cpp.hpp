/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_TYPES_CPP_HPP
#define DOGEN_CPP_TYPES_CPP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace dogen {

/**
 * @brief CPP is the C++ model.
 *
 * @section cpp_0 Objective
 *
 * CPP aims to model the types required by the formatters to generate C++ code.
 * Note that it is @e not a model of the C++ language as a compiler etc would
 * see it; it at a much higher level than an AST. In fact, one can think of CPP
 * as an SML augmented with C++-specific information. Some of that information
 * comes from bringing SML meta-data into the type system; the remaining is
 * directly derived by the information available in SML.
 *
 * @section cpp_1 Info postfix
 *
 * The types in the CPP model should not have any prefixes or post-fixes since
 * they naturally belong to the model; e.g. @e cpp::class tells us everything we
 * need to know. However, names like @e class and @e namespace clash with
 * keywords,  so this is not a workable approach. Models such as ECore have
 * dealt with this problem by choosing a random prefix (e.g. @e EClass, etc).
 * We decided, somewhat arbitrarily, to use the postfix @e _info. It is used by
 * @e type_info, representing meta-data in C++, so at least that's one excuse.
 *
 * @section cpp_2 Other approaches
 *
 * We have tried to make C++ a model of the C++ language at the AST level and
 * the formatters nothing but a trivial dumper of the AST into file; in this
 * world we'd be consuming Clang libraries and using their infrastructure.
 * Whilst this approach was seductive in theorethical terms, it provided to be
 * to cumbersome to work in practice. This is because the AST is so low-level
 * that to describe a simple thing like a class would require large amounts
 * of infrastructure (think of it like talking about cars at the atomic level).
 *
 * We also tried to use SML directly to format C++ code, augmented with
 * high-level meta-data. Since the C++ model shares so many commonalities with
 * SML it only seeemed logical to remove it from the picture altogether and
 * add whatever was missing directly to SML. To avoid making SML language
 * specific, we added the meta-data as a non-typed container. Whilst workable,
 * this approach resulted in a lot of boilerplate code and little type safety.
 *
 * The final aproach considered was to make CPP types inherit from SML. This
 * was also problematic: we do not support cross-model inheritance at present;
 * but much more worryingly, the model would become a complex inheritance
 * graph, with lots of double-dispatching, casting, abstract factories,
 * decorator patterns and all of the complexity that inevitable comes with
 * the heavy use of inheritance.
 *
 * This is why we settled on something which duplicates quite a bit of SML; it
 * seems like the least bad approach.
 *
 */
namespace cpp {
} }

#endif
