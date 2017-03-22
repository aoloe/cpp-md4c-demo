#include <string>
#include "../md4c/md4c.h"

class Markdown
{
    public:
        Markdown(std::string content): content{content} {}
        static int enter_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata);
        static int leave_block_callback(MD_BLOCKTYPE type, void* detail, void* userdata);
        static int enter_span_callback(MD_SPANTYPE type, void* detail, void* userdata);
        static int leave_span_callback(MD_SPANTYPE type, void* detail, void* userdata);
        static int text_callback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata);
        static void debug_log_callback(const char* msg, void* userdata);

        void parse();

    private:
        int enter_block(MD_BLOCKTYPE type, void* detail);
        int leave_block(MD_BLOCKTYPE type, void* detail);
        int enter_span(MD_SPANTYPE type, void* detail);
        int leave_span(MD_SPANTYPE type, void* detail);
        int text(MD_TEXTTYPE type, const std::string text);
        void debug_log(const char* /*msg*/);

        std::string content;
};

