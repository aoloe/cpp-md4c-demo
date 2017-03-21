#include <string>
#include <iostream>
#include "md4c/md4c.h"

int enter_block_callback(MD_BLOCKTYPE type, void* /*detail*/, void* /*userdata*/)
{
    switch(type) {
        case MD_BLOCK_DOC:      /* noop */ break;
        case MD_BLOCK_QUOTE:    std::cout << "<..." << std::endl; break;
        case MD_BLOCK_UL:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_OL:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_LI:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_HR:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_H:        std::cout << "<title" << std::endl;  break;
        case MD_BLOCK_CODE:     std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_HTML:     std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_P:        std::cout << "<p" << std::endl;  break;
        case MD_BLOCK_TABLE:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_THEAD:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TBODY:    std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TR:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TH:       std::cout << "<..." << std::endl;  break;
        case MD_BLOCK_TD:       std::cout << "<..." << std::endl;  break;
    }
    return 0;
}

int leave_block_callback(MD_BLOCKTYPE /*type*/, void* /*detail*/, void* /*userdata*/)
{
    return 0;
}

int enter_span_callback(MD_SPANTYPE type, void* /*detail*/, void* /*userdata*/)
{
    switch(type) {
        case MD_SPAN_EM:        std::cout << "<em..." << std::endl; break;
        case MD_SPAN_STRONG:    std::cout << "<strong..." << std::endl; break;
        case MD_SPAN_A:         std::cout << "<..." << std::endl; break;
        case MD_SPAN_IMG:       std::cout << "<..." << std::endl; break;
        case MD_SPAN_CODE:      std::cout << "<..." << std::endl; break;
    }

    return 0;
}

int leave_span_callback(MD_SPANTYPE /*type*/, void* /*detail*/, void* /*userdata*/)
{
    return 0;
}

int text_callback(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE /*size*/, void* /*userdata*/)
{
    switch(type) {
        case MD_TEXT_NULLCHAR:  std::cout << "..." << std::endl; break; 
        case MD_TEXT_BR:        std::cout << "..." << std::endl; break; 
        case MD_TEXT_SOFTBR:    std::cout << "..." << std::endl; break; 
        case MD_TEXT_HTML:      std::cout << "html " << text << std::endl; break; 
        case MD_TEXT_ENTITY:    std::cout << "..." << std::endl; break; 
        default:                std::cout << text << std::endl; break;    
    }
    return 0;
}

void debug_log_callback(const char* /*msg*/, void* /* userdata */)
{
}

/**
 * TODO: we will have to rename this struct...
 */
struct MD_RENDER_HTML {
    void (*process_output)(const MD_CHAR*, MD_SIZE, void*);
    void* userdata;
    unsigned flags;
};

void process_output(const MD_CHAR* text, MD_SIZE size, void* userdata)
{
    // see md2html.c (probably, the c++ version will be very different)
    // membuf_append((struct membuffer*) userdata, text, size);
}

struct UserdataPayload
{
    std::string content;
};

int main()
{
    std::string content = "# This is _markdown_\n\nA markdown file.";

    unsigned parser_flags = 0; // see md2html.c (options handling)
    unsigned renderer_flags = 0; // in the html example: debug(output to stderr) | verbatim_entities

    MD_RENDERER renderer = {
        enter_block_callback,
        leave_block_callback,
        enter_span_callback,
        leave_span_callback,
        text_callback,
        debug_log_callback,
        parser_flags
    };

    UserdataPayload userdata{"userdata payload"};

    MD_RENDER_HTML render = {
        process_output,
        (void*) &userdata,
        renderer_flags
    };

    int status = md_parse(content.c_str(), content.size(), &renderer, (void*) &render);
}
