// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using log4net;
using NUnit.Framework;

namespace Dogen.TestModels.CSharpModel.Tests
{
    [TestFixture]
    // Analysis disable once InconsistentNaming
    class equality_tests
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof(equality_tests));
        private static readonly string FixtureName = typeof(equality_tests).Name;

        [Test]
        // Analysis disable once InconsistentNaming
        public void identical_objects_are_equal()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var a = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var b = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("a: {0}", ComplexBuiltinsDumper.Dump(a));
                Log.DebugFormat("b: {0}", ComplexBuiltinsDumper.Dump(b));

                Assert.That(object.ReferenceEquals(a, b), Is.False);
                Assert.That(a.Equals(b), Is.True);
                Assert.That(a == b, Is.True);
                Assert.That(a != b, Is.False);

                var c = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                var d = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("c: {0}", PrimitiveBuiltinsDumper.Dump(c));
                Log.DebugFormat("d: {0}", PrimitiveBuiltinsDumper.Dump(d));

                Assert.That(object.ReferenceEquals(c, d), Is.False);
                Assert.That(c.Equals(d), Is.True);
                Assert.That(c == d, Is.True);
                Assert.That(c != d, Is.False);

                var e = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                var f = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("e: {0}", NoPropertiesDumper.Dump(e));
                Log.DebugFormat("f: {0}", NoPropertiesDumper.Dump(f));

                Assert.That(object.ReferenceEquals(e, f), Is.False);
                Assert.That(e.Equals(f), Is.True);
                Assert.That(e == f, Is.True);
                Assert.That(e != f, Is.False);

                var g = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                var h = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("g: {0}", OnePropertyDumper.Dump(g));
                Log.DebugFormat("h: {0}", OnePropertyDumper.Dump(h));

                Assert.That(object.ReferenceEquals(g, h), Is.False);
                Assert.That(g.Equals(h), Is.True);
                Assert.That(g == h, Is.True);
                Assert.That(g != h, Is.False);
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void an_object_is_equal_to_itself()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                #pragma warning disable 1718
                // warning CS1718: A comparison made to same variable. Did you mean to compare
                // warning CS1718: something else?
                var a = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("a: {0}", ComplexBuiltinsDumper.Dump(a));
                // Analysis disable once EqualExpressionComparison
                Assert.That(a.Equals(a), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(a == a, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(a != a, Is.False);

                var b = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("b: {0}", PrimitiveBuiltinsDumper.Dump(b));
                // Analysis disable once EqualExpressionComparison
                Assert.That(b.Equals(b), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(b == b, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(b != b, Is.False);

                var c = NoPropertiesSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("c: {0}", NoPropertiesDumper.Dump(c));
                // Analysis disable once EqualExpressionComparison
                Assert.That(c.Equals(c), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(c == c, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(c != c, Is.False);

                var d = OnePropertySequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("d: {0}", OnePropertyDumper.Dump(d));
                // Analysis disable once EqualExpressionComparison
                Assert.That(d.Equals(d), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(d == d, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(d != d, Is.False);
                #pragma warning restore 1718
            }
        }

        [Test]
        // Analysis disable once InconsistentNaming
        public void distinct_objects_are_unequal()
        {
            using (var lc = new LogConfigurator(FixtureName))
            {
                var en1 = ComplexBuiltinsSequenceGenerator.Sequence().GetEnumerator();
                var a = en1.Current;
                en1.MoveNext();
                var b = en1.Current;
                Log.DebugFormat("a: {0}", ComplexBuiltinsDumper.Dump(a));
                Log.DebugFormat("b: {0}", ComplexBuiltinsDumper.Dump(b));

                Assert.That(object.ReferenceEquals(a, b), Is.False);
                Assert.That(a.Equals(b), Is.False);
                Assert.That(a == b, Is.False);
                Assert.That(a != b, Is.True);

                var en2 = PrimitiveBuiltinsSequenceGenerator.Sequence().GetEnumerator();
                var c = en2.Current;
                en2.MoveNext();
                var d = en2.Current;
                Log.DebugFormat("c: {0}", PrimitiveBuiltinsDumper.Dump(c));
                Log.DebugFormat("d: {0}", PrimitiveBuiltinsDumper.Dump(d));

                Assert.That(object.ReferenceEquals(c, d), Is.False);
                Assert.That(c.Equals(d), Is.False);
                Assert.That(c == d, Is.False);
                Assert.That(c != d, Is.True);

                // Objects without properties are always equal so we ignore
                // NoProperties for this test.

                var en4 = OnePropertySequenceGenerator.Sequence().GetEnumerator();
                var g = en4.Current;
                en4.MoveNext();
                var h = en4.Current;
                Log.DebugFormat("g: {0}", OnePropertyDumper.Dump(g));
                Log.DebugFormat("h: {0}", OnePropertyDumper.Dump(h));

                Assert.That(object.ReferenceEquals(g, h), Is.False);
                Assert.That(g.Equals(h), Is.False);
                Assert.That(g == h, Is.False);
                Assert.That(g != h, Is.True);
            }
        }
    }
}
