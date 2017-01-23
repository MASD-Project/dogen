using System;

namespace Phi
{
    /// <summary>
    /// Generates sequences of TestType.
    /// </summary>
    public static class TestTypeDumper
    {
        static internal void Dump(AssistantDumper assistant, TestType value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Phi.TestType", true/*withSeparator*/);
            if (value == null)
            {
                assistant.Add("data", "<null>");
                assistant.AddEndObject();
                return;
            }

            assistant.AddKey("data");
            assistant.AddPairSeparator();
            assistant.AddStartObject();
            assistant.AddKey("Version");
            assistant.AddPairSeparator();
            Zeta.StringDumper.Dump(assistant, value.Version, true/*withSeparator*/);
            assistant.AddKey("AField");
            assistant.AddPairSeparator();
            Zeta.StringDumper.Dump(assistant, value.AField);
            assistant.AddEndObject(); // data
            assistant.AddEndObject(); // main object
            assistant.HandleMemberSeparator(withSeparator);

            assistant.DecrementDepth();
        }

        public static string Dump(TestType value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
