/*
 * Copyright 2006-2009 Savarese Software Research Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.savarese.com/software/ApacheLicense-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SSRC_WSPR_UTILITY_UNORDERED_SET_H
#define __SSRC_WSPR_UTILITY_UNORDERED_SET_H

// This is a horrible kluge to work around boost serialization not
// supporting <unordered_set>.  As soon as boost serialization supports
// unordered_set, get rid of all of the hacks.

#include <unordered_set>
#include <boost/serialization/serialization.hpp>
#include "dogen/utility/serialization/unordered_map.hpp" // load_hash_collection

#define hash_set unordered_set
#define hash_multiset unordered_multiset

#ifdef BOOST_HASH_SET_HEADER
#undef BOOST_HASH_SET_HEADER
#endif
#ifdef BOOST_STD_EXTENSION_NAMESPACE
#undef BOOST_STD_EXTENSION_NAMESPACE
#endif
#ifdef BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#undef BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#endif

#define BOOST_HASH_SET_HEADER <unordered_set>
#define BOOST_STD_EXTENSION_NAMESPACE std
#define BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collections_load_imp.hpp>

#include <boost/serialization/hash_set.hpp>
#undef hash_set
#undef hash_multiset

#endif
