using System.Text;

namespace Dogen.TestModels.CSharpModel
{
    class Dumper
    {
		#region Properties
        private readonly StringBuilder _stringBuilder;
		// private readonly int _depth;
		private readonly string _type = "__type__";
		#endregion

        public Dumper ()
        {
			_stringBuilder = new StringBuilder();
			// _depth = 100;
        }

		public void AddStartObject()
		{
			_stringBuilder.Append("{ ");
		}

		public void AddEndObject()
		{
			_stringBuilder.Append(" }");
		}

		public void AddPairSeparator()
		{
			_stringBuilder.Append(" : ");
		}

		public void AddMemberSeparator()
		{
			_stringBuilder.Append(", ");
		}

		public void AddQuoted(string s)
        {
			_stringBuilder.Append("\"" + s + "\"");
        }

		public void AddObjectType(string objectName)
		{
			AddQuoted(_type);
			AddPairSeparator();
			AddQuoted(objectName);
		}

        public void WriteValueType(string key)
        {
        }

		public string Dump()
		{
			return _stringBuilder.ToString();
		}
    }
}
