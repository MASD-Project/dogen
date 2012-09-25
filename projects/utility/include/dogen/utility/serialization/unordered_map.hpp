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

#ifndef __SSRC_WSPR_UTILITY_UNORDERED_MAP_H
#define __SSRC_WSPR_UTILITY_UNORDERED_MAP_H

// This is a horrible kluge to work around boost serialization not
// supporting <unordered_map>.  As soon as boost serialization supports
// unordered_map, get rid of all of the hacks.

#include <unordered_map>
#include <boost/serialization/serialization.hpp>

#define hash_map unordered_map
#define hash_multimap unordered_multimap

#ifdef BOOST_HASH_MAP_HEADER
#undef BOOST_HASH_MAP_HEADER
#endif
#ifdef BOOST_STD_EXTENSION_NAMESPACE
#undef BOOST_STD_EXTENSION_NAMESPACE
#endif
#ifdef BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#undef BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#endif

#define BOOST_HASH_MAP_HEADER <unordered_map>
#define BOOST_STD_EXTENSION_NAMESPACE std
#define BOOST_SERIALIZATION_HASH_COLLECTIONS_LOAD_IMP_HPP
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/collections_load_imp.hpp>

namespace boost{
  namespace serialization {
    namespace stl {
      template<class Archive, class Container, class InputFunction>
      inline void load_hash_collection(Archive & ar, Container &s)
      {
        s.clear();
        // retrieve number of elements
        collection_size_type count;
        collection_size_type bucket_count;
        boost::serialization::item_version_type item_version(0);
        ar >> BOOST_SERIALIZATION_NVP(count);
        if(3 < ar.get_library_version()){
          ar >> BOOST_SERIALIZATION_NVP(bucket_count)
             >> BOOST_SERIALIZATION_NVP(item_version);
        }

        s.rehash(bucket_count);

        InputFunction ifunc;
        while(count-- > 0){
          ifunc(ar, s, item_version);
        }
      }
    }
  }
}

#include <boost/serialization/hash_map.hpp>
#undef hash_map
#undef hash_multimap

#endif
