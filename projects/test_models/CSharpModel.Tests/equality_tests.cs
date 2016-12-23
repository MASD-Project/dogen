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
		#region Properties
        private static readonly ILog Log = LogManager.GetLogger(typeof(equality_tests));
        private static readonly string FixtureName = typeof(equality_tests).Name;
		#endregion

		#region Tests
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

                var i = AssociationSequenceGenerator.Sequence().GetEnumerator().Current;
                var j = AssociationSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("g: {0}", AssociationDumper.Dump(i));
                Log.DebugFormat("h: {0}", AssociationDumper.Dump(j));

                Assert.That(object.ReferenceEquals(i, j), Is.False);
                Assert.That(i.Equals(j), Is.True);
                Assert.That(i == j, Is.True);
                Assert.That(i != j, Is.False);

                var k = Package1.AssociationInPackageSequenceGenerator.Sequence().GetEnumerator().Current;
                var m = Package1.AssociationInPackageSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("k: {0}", Package1.AssociationInPackageDumper.Dump(k));
                Log.DebugFormat("m: {0}", Package1.AssociationInPackageDumper.Dump(m));

                Assert.That(object.ReferenceEquals(k, m), Is.False);
                Assert.That(k.Equals(m), Is.True);
                Assert.That(k == m, Is.True);
                Assert.That(k != m, Is.False);
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

                var e = AssociationSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("e: {0}", AssociationDumper.Dump(e));
                // Analysis disable once EqualExpressionComparison
                Assert.That(e.Equals(e), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(e == e, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(e != e, Is.False);

                var f = Package1.AssociationInPackageSequenceGenerator.Sequence().GetEnumerator().Current;
                Log.DebugFormat("f: {0}", Package1.AssociationInPackageDumper.Dump(f));
                // Analysis disable once EqualExpressionComparison
                Assert.That(f.Equals(f), Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(f == f, Is.True);
                // Analysis disable once EqualExpressionComparison
                Assert.That(f != f, Is.False);
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

                var en5 = AssociationSequenceGenerator.Sequence().GetEnumerator();
                var i = en5.Current;
                en5.MoveNext();
                var j = en5.Current;
                Log.DebugFormat("g: {0}", AssociationDumper.Dump(i));
                Log.DebugFormat("h: {0}", AssociationDumper.Dump(j));

                Assert.That(object.ReferenceEquals(i, j), Is.False);
                Assert.That(i.Equals(j), Is.False);
                Assert.That(i == j, Is.False);
                Assert.That(i != j, Is.True);

                var en6 = Package1.AssociationInPackageSequenceGenerator.Sequence().GetEnumerator();
                var k = en6.Current;
                en6.MoveNext();
                var m = en6.Current;
                Log.DebugFormat("k: {0}", Package1.AssociationInPackageDumper.Dump(k));
                Log.DebugFormat("m: {0}", Package1.AssociationInPackageDumper.Dump(m));

                Assert.That(object.ReferenceEquals(k, m), Is.False);
                Assert.That(k.Equals(m), Is.False);
                Assert.That(k == m, Is.False);
                Assert.That(k != m, Is.True);
            }
		}

		[Test]
		// Analysis disable once InconsistentNaming
		public void equality_in_inheritance_works_correctly()
		{
			using (var lc = new LogConfigurator(FixtureName))
			{
				/*
				 * Two instances of the same descendant with the same values are equal.  
				 */
				var en = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator();
				var a = en.Current;
				var b = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator().Current;
				Log.DebugFormat("a: {0}", ChildOfAChild1Dumper.Dump(a));
				Log.DebugFormat("b: {0}", ChildOfAChild1Dumper.Dump(b));

				Assert.That(object.ReferenceEquals(a, b), Is.False);
				Assert.That(a.Equals(b), Is.True);
				Assert.That(a == b, Is.True);
				Assert.That(a != b, Is.False);

				/*
				 * Two instances of the same descendant with different values are equal.  
				 */
				en.MoveNext();
				var c = en.Current;
				en.MoveNext();
				var d = en.Current;
				Log.DebugFormat("c: {0}", ChildOfAChild1Dumper.Dump(c));
				Log.DebugFormat("d: {0}", ChildOfAChild1Dumper.Dump(d));

				Assert.That(object.ReferenceEquals(c, d), Is.False);
				Assert.That(c.Equals(d), Is.False);
				Assert.That(c == d, Is.False);
				Assert.That(c != d, Is.True);

				/*
				 * Two instances of the same type with only one different property, inherited
				 * from the base class, are not equal. 
				*/
				var e = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator().Current;
				var f = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator().Current;
				e.Prop0 = 10;
				f.Prop0 = 20;
				Log.DebugFormat("e: {0}", ChildOfAChild1Dumper.Dump(e));
				Log.DebugFormat("f: {0}", ChildOfAChild1Dumper.Dump(f));

				Assert.That(object.ReferenceEquals(e, f), Is.False);
				Assert.That(e.Equals(f), Is.False);
				Assert.That(e == f, Is.False);
				Assert.That(e != f, Is.True);

				/*
				 * Two instances of the same type with only one different property, inherited
				 * from the direct parent, are not equal. 
				*/
				var g = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator().Current;
				var h = ChildOfAChild1SequenceGenerator.Sequence().GetEnumerator().Current;
				g.Prop1 = 30;
				h.Prop1 = 40;
				Log.DebugFormat("g: {0}", ChildOfAChild1Dumper.Dump(g));
				Log.DebugFormat("h: {0}", ChildOfAChild1Dumper.Dump(h));

				Assert.That(object.ReferenceEquals(g, h), Is.False);
				Assert.That(g.Equals(h), Is.False);
				Assert.That(g == h, Is.False);
				Assert.That(g != h, Is.True);
			}
		}
		#endregion
    }
}
