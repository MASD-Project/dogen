#ifndef DOGEN_DOGEN_HPP
#define DOGEN_DOGEN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @mainpage About
 *
 * @b Dogen is the Domain Generator. Generator is the code generator
 * that creates object models for domain driven programming.
 *
 * The key concept in Dogen is that of a @e domain @e type. Its
 * basically a POD in C++ terminology or a POJO in java terms: a data
 * object without any complex behaviour. The objective of Dogen is to
 * generate representations of the different @e facets of the domain
 * type according to the rules of some @e grammar, where:
 *
 * @li @e Facet: different "aspects" of the domain type we're
 * interested in. For example, hashing, serialisation, etc. These are
 * in effect the trivial behaviours that can be associated with a
 * domain type. @see facet_types.
 *
 * @li @e Grammar: The code generation must be expressed using some @e
 * grammar; that is, it must obey to a set of rules defined
 * somewhere. Typical grammars are programming languages such as C++
 * or SQL, but they can also be more esoteric such as a Dia diagram;
 * it uses the Dia XML grammar.
 *
 * @li @e Representation: A physical expression of a domain
 * type, made by intersecting a facet and a grammar.
 *
 */
namespace dogen { }

#endif
