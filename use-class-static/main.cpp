#include <string>
#include "markdown.h"

int main()
{
    std::string content = "# This is _markdown_\n\nA markdown file.";

    Markdown m(content);
    m.parse();
}
