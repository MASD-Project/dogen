// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_SQLITE_HXX
#define DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_SQLITE_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2046500 // 2.5.0-b.15
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/sqlite/gregorian-traits.hxx>
#include <odb/boost/date-time/sqlite/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/sqlite/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20465UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen.relational/types/tracing/transform.hpp"

#include "dogen.relational/odb/tracing/run_id-odb-sqlite.hxx"
#include "dogen.relational/odb/tracing/transform_id-odb-sqlite.hxx"

#include "dogen.relational/odb/tracing/transform-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/sqlite/version.hxx>
#include <odb/sqlite/forward.hxx>
#include <odb/sqlite/binding.hxx>
#include <odb/sqlite/sqlite-types.hxx>
#include <odb/sqlite/query.hxx>

namespace odb
{
  // transform
  //
  template <typename A>
  struct query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >
  {
    // start
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::boost::posix_time::ptime,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    start_type_;

    static const start_type_ start;

    // end
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::boost::posix_time::ptime,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    end_type_;

    static const end_type_ end;

    // id
    //
    struct id_class_
    {
      id_class_ ()
      {
      }

      // value
      //
      typedef
      sqlite::query_column<
        sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::query_type,
        sqlite::id_text >
      value_type_;

      static const value_type_ value;
    };

    static const id_class_ id;

    // name
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    name_type_;

    static const name_type_ name;

    // description
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::std::string,
        sqlite::id_text >::query_type,
      sqlite::id_text >
    description_type_;

    static const description_type_ description;

    // run_id
    //
    struct run_id_class_
    {
      run_id_class_ ()
      {
      }

      // value
      //
      typedef
      sqlite::query_column<
        sqlite::value_traits<
          ::std::string,
          sqlite::id_text >::query_type,
        sqlite::id_text >
      value_type_;

      static const value_type_ value;
    };

    static const run_id_class_ run_id;

    // type
    //
    typedef
    sqlite::query_column<
      sqlite::value_traits<
        ::dogen::relational::tracing::transform_type,
        sqlite::id_integer >::query_type,
      sqlite::id_integer >
    type_type_;

    static const type_type_ type;
  };

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::start_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::
  start (A::table_name, "\"START\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::end_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::
  end (A::table_name, "\"END\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::id_class_::
  value (A::table_name, "\"ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::id_class_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::name_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::
  name (A::table_name, "\"NAME\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::description_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::
  description (A::table_name, "\"DESCRIPTION\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::run_id_class_::value_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::run_id_class_::
  value (A::table_name, "\"RUN_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::run_id_class_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::run_id;

  template <typename A>
  const typename query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::type_type_
  query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >::
  type (A::table_name, "\"TYPE\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >:
    query_columns< ::dogen::relational::tracing::transform, id_sqlite, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::relational::tracing::transform, id_sqlite >:
    public access::object_traits< ::dogen::relational::tracing::transform >
  {
    public:
    struct image_type
    {
      // start_
      //
      details::buffer start_value;
      std::size_t start_size;
      bool start_null;

      // end_
      //
      details::buffer end_value;
      std::size_t end_size;
      bool end_null;

      // id_
      //
      composite_value_traits< ::dogen::relational::tracing::transform_id, id_sqlite >::image_type id_value;

      // name_
      //
      details::buffer name_value;
      std::size_t name_size;
      bool name_null;

      // description_
      //
      details::buffer description_value;
      std::size_t description_size;
      bool description_null;

      // run_id_
      //
      composite_value_traits< ::dogen::relational::tracing::run_id, id_sqlite >::image_type run_id_value;

      // type_
      //
      long long type_value;
      bool type_null;

      std::size_t version;
    };

    using object_traits<object_type>::id;

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (sqlite::bind*,
          image_type&,
          sqlite::statement_kind);

    static bool
    init (image_type&,
          const object_type&,
          sqlite::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    typedef sqlite::no_id_object_statements<object_type> statements_type;

    typedef sqlite::query_base query_base_type;

    static const std::size_t column_count = 7UL;
    static const std::size_t id_column_count = 0UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
  };

  // transform
  //
}

#include "dogen.relational/odb/tracing/transform-odb-sqlite.ixx"

#include <odb/post.hxx>

#endif // DOGEN_RELATIONAL_ODB_TRACING_TRANSFORM_ODB_SQLITE_HXX
