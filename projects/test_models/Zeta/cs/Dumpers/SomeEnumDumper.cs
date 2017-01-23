namespace Phi
{
    /// <summary>
    /// Generates sequences of SomeEnum.
    /// </summary>
    public static class SomeEnumDumper
    {
        static internal void Dump(AssistantDumper assistant, SomeEnum value, bool withSeparator = false)
        {
            assistant.IncrementDepth();
            if (assistant.MaximumDepthExceeded())
                return;

            assistant.AddStartObject();
            assistant.AddType("Phi.SomeEnum", true/*withSeparator*/);
            string valueAsString = "Unsupported Value";
            switch (value)
            {
                case SomeEnum.Invalid:
                    valueAsString = "Invalid";
                    break;
            }

            assistant.Add("value", valueAsString);
            assistant.AddEndObject();

            assistant.DecrementDepth();
        }

        public static string Dump(SomeEnum value)
        {
            var assistant = new AssistantDumper();
            Dump(assistant, value);
            return assistant.ToString();
        }
    }
}
